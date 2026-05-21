#!/bin/bash

# Installer for the ftdi (libftdi1) extension on Debian Trixie
# and compatible systems: Ubuntu 24.04+, Raspberry Pi OS Bookworm/Trixie.
#
# - Resolves PHP binary and extension dir automatically
# - Runs zephir fullclean / generate / stubs, then compiles with phpize
# - Installs ftdi.so and enables it for CLI, FPM, and Apache SAPIs

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXTENSION_NAME="ftdi"
BUILD_SO="${SCRIPT_DIR}/ext/modules/${EXTENSION_NAME}.so"
LOG_FILE="${SCRIPT_DIR}/build.log"

if [ "${EUID:-$(id -u)}" -ne 0 ]; then
    SUDO="sudo"
else
    SUDO=""
fi

die()  { echo ""; echo "❌ $*"; exit 1; }
step() { echo "$*"; }
ok()   { echo "   ✓ $*"; }
APT_UPDATED=0

is_pkg_installed() {
    local pkg="$1"
    dpkg-query -W -f='${Status}' "$pkg" 2>/dev/null | grep -q "install ok installed"
}

ensure_apt_pkg() {
    local pkg="$1"
    local hint="$2"

    if is_pkg_installed "$pkg"; then
        ok "${pkg} present"
        return 0
    fi

    step "   Installing ${pkg} (${hint})..."
    if [ "$APT_UPDATED" -eq 0 ]; then
        $SUDO apt-get update -y >/dev/null
        APT_UPDATED=1
    fi
    $SUDO apt-get install -y --no-install-recommends "$pkg" >/dev/null
    ok "${pkg} installed"
}

show_failure_logs() {
    if [ -f "$LOG_FILE" ]; then
        echo ""
        echo "---- Last 80 lines of ${LOG_FILE} ----"
        tail -80 "$LOG_FILE" || true
    fi
}

# sudo pie install (or any root build in ext/) leaves root-owned artifacts that
# break subsequent user builds. Scrub them before zephir/phpize touch ext/.
reset_ext_build_tree() {
    local ext_dir="${SCRIPT_DIR}/ext"
    local item used_sudo=0

    [ -d "$ext_dir" ] || return 0

    for item in \
        "$ext_dir/build" \
        "$ext_dir/autom4te.cache" \
        "$ext_dir/modules" \
        "$ext_dir/.libs" \
        "$ext_dir/kernel/.libs" \
        "$ext_dir/ftdi/.libs" \
        "$ext_dir/src/.libs" \
        "$ext_dir/Makefile" \
        "$ext_dir/config.status" \
        "$ext_dir/config.h" \
        "$ext_dir/configure" \
        "$ext_dir/libtool" \
        "$ext_dir/config.cache" \
        "$ext_dir/run-tests.php"
    do
        [ -e "$item" ] || continue
        if rm -rf "$item" 2>/dev/null; then
            continue
        fi
        [ -n "$SUDO" ] || return 1
        $SUDO rm -rf "$item" || return 1
        used_sudo=1
    done

    if ! find "$ext_dir" \( -name '*.dep' -o -name '*.lo' -o -name '*.la' \) -delete 2>/dev/null; then
        [ -n "$SUDO" ] || return 1
        $SUDO find "$ext_dir" \( -name '*.dep' -o -name '*.lo' -o -name '*.la' \) -delete 2>/dev/null || return 1
        used_sudo=1
    fi

    if [ "$used_sudo" -eq 1 ] && [ -n "$SUDO" ]; then
        $SUDO chown -R "$(id -u)":"$(id -g)" "$ext_dir" 2>/dev/null || true
    fi
}

echo "=========================================="
echo " ftdi Extension Installer (Debian Trixie / Raspberry Pi OS)"
echo "=========================================="
echo ""

# ── Preflight ────────────────────────────────────────────────────────────────
step "🔎 Preflight checks..."
command -v php >/dev/null 2>&1 || die "php not found in PATH"

PHP_VER_MM="$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"

if ! command -v php-config >/dev/null 2>&1; then
    ensure_apt_pkg "php${PHP_VER_MM}-dev" "php-config and headers"
fi
if ! command -v cc >/dev/null 2>&1; then
    ensure_apt_pkg "build-essential" "compiler toolchain"
fi
if ! command -v pkg-config >/dev/null 2>&1; then
    ensure_apt_pkg "pkg-config" "dependency discovery"
fi
if ! is_pkg_installed "libftdi1-dev"; then
    ensure_apt_pkg "libftdi1-dev" "FTDI headers and library"
fi
if ! is_pkg_installed "libusb-1.0-0-dev"; then
    ensure_apt_pkg "libusb-1.0-0-dev" "USB transport headers and library"
fi

if [ -n "${ZEPHIR_BIN:-}" ]; then
    ZEPHIR="$ZEPHIR_BIN"
elif command -v zephir >/dev/null 2>&1; then
    ZEPHIR="$(command -v zephir)"
elif [ -x "$HOME/.config/composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.config/composer/vendor/bin/zephir"
elif [ -x "$HOME/.composer/vendor/bin/zephir" ]; then
    ZEPHIR="$HOME/.composer/vendor/bin/zephir"
else
    die "Zephir not found. Install via: composer global require phalcon/zephir  (or set ZEPHIR_BIN)"
fi
ok "Found zephir: $ZEPHIR"

PHP_VER_NN="$(php -r 'echo PHP_MAJOR_VERSION.PHP_MINOR_VERSION;')"
PHP_BIN_REAL="$(php -r 'echo PHP_BINARY;' 2>/dev/null)"
PHP_BIN_DIR="$(dirname "$PHP_BIN_REAL")"

_PHP_VER_NODOT="${PHP_VER_MM//./}"
RESOLVED_PHP_CONFIG=""
for _candidate in \
    "${PHP_BIN_DIR}/php-config${_PHP_VER_NODOT}" \
    "${PHP_BIN_DIR}/php-config" \
    "$(command -v "php-config${_PHP_VER_NODOT}" 2>/dev/null || true)" \
    "$(command -v php-config 2>/dev/null || true)"
do
    if [ -x "$_candidate" ]; then
        RESOLVED_PHP_CONFIG="$_candidate"
        break
    fi
done
[ -n "$RESOLVED_PHP_CONFIG" ] || die "Could not locate php-config. Install php-dev (apt install php${PHP_VER_MM}-dev)."

PHP_EXT_DIR="$("$RESOLVED_PHP_CONFIG" --extension-dir 2>/dev/null)" \
    || die "Could not determine PHP extension dir from php-config."
[ -n "$PHP_EXT_DIR" ] || die "Could not determine PHP extension dir."

CLI_SCAN_DIR="$(php --ini 2>/dev/null | awk -F': ' '/Scan for additional \.ini files in:/{print $2}' || true)"

ok "PHP version:   ${PHP_VER_MM}"
ok "PHP binary:    ${PHP_BIN_REAL}"
ok "Extension dir: ${PHP_EXT_DIR}"

if pkg-config --exists libftdi1; then
    ok "Found libftdi1: $(pkg-config libftdi1 --modversion)"
else
    ensure_apt_pkg "libftdi1-dev" "FTDI pkg-config metadata"
    if pkg-config --exists libftdi1; then
        ok "Found libftdi1: $(pkg-config libftdi1 --modversion)"
    else
        die "libftdi1 still not found after installing dependencies."
    fi
fi

# GCC 14 on Trixie promotes some Zephir kernel warnings to errors.
export CFLAGS="${CFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types -Wno-error=int-conversion -Wno-pointer-compare"
export CPPFLAGS="${CPPFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types"
echo ""

# ── Zephir ───────────────────────────────────────────────────────────────────
cd "${SCRIPT_DIR}"

step "🧹 reset ext/ build tree..."
if ! reset_ext_build_tree; then
    die "Could not reset ${SCRIPT_DIR}/ext build artifacts (likely root-owned from sudo pie install). Run: sudo rm -rf ext/build ext/autom4te.cache ext/modules ext/.libs && sudo chown -R \$(id -un):\$(id -gn) ext/"
fi
ok "ext/ build tree reset"
echo ""

step "🧹 zephir fullclean..."
if ! "$ZEPHIR" fullclean >"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "zephir fullclean failed. See ${LOG_FILE}."
fi
ok "zephir fullclean complete"
echo ""

step "📦 pre-install (generate, src/, clang/)..."
if ! bash "${SCRIPT_DIR}/pre-install.sh" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "pre-install.sh failed. See ${LOG_FILE}."
fi
ok "pre-install complete"

for required_file in \
    "${SCRIPT_DIR}/ext/kernel/file.c" \
    "${SCRIPT_DIR}/ext/kernel/require.c" \
    "${SCRIPT_DIR}/ext/kernel/main.c"
do
    [ -f "$required_file" ] || die "Missing required kernel overlay file: ${required_file}"
done
ok "clang kernel overlays are present in ext/kernel/"
echo ""

step "📄 zephir stubs..."
if ! "$ZEPHIR" stubs >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "zephir stubs failed. See ${LOG_FILE}."
fi
ok "zephir stubs complete"
echo ""

step "📄 apply clang/config.m4 (after stubs)..."
cp "${SCRIPT_DIR}/clang/config.m4" "${SCRIPT_DIR}/ext/config.m4"
ok "clang/config.m4 applied"
echo ""

# ── Compile ───────────────────────────────────────────────────────────────────
step "   Compiling..."
cd "${SCRIPT_DIR}/ext"
find . -name "*.dep" -delete 2>/dev/null || true
if ! phpize >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "phpize failed. See ${LOG_FILE}."
fi
if ! ./configure "--with-php-config=${RESOLVED_PHP_CONFIG}" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "configure failed. See ${LOG_FILE}."
fi
if ! make -j"$(nproc 2>/dev/null || echo 4)" >>"$LOG_FILE" 2>&1; then
    show_failure_logs
    die "make failed. See ${LOG_FILE}."
fi
cd "${SCRIPT_DIR}"

if [ ! -f "$BUILD_SO" ]; then
    show_failure_logs
    die "Build output not found at ${BUILD_SO}."
fi
ok "Build complete"
echo ""

# ── Install .so ───────────────────────────────────────────────────────────────
step "📦 Installing binary..."
$SUDO mkdir -p "$PHP_EXT_DIR"
$SUDO cp -f "$BUILD_SO" "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
$SUDO chmod 755 "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
ok "Copied to: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

# ── Enable across SAPIs ───────────────────────────────────────────────────────
step "⚙️  Enabling extension..."
declare -a CONF_DIR_CANDIDATES=()

if [ -n "${CLI_SCAN_DIR:-}" ] && [ "$CLI_SCAN_DIR" != "(none)" ] && [ -d "$CLI_SCAN_DIR" ]; then
    CONF_DIR_CANDIDATES+=("$CLI_SCAN_DIR")
fi
for d in \
    "/etc/php/${PHP_VER_MM}/cli/conf.d" \
    "/etc/php/${PHP_VER_MM}/fpm/conf.d" \
    "/etc/php/${PHP_VER_MM}/apache2/conf.d"; do
    [ -d "$d" ] && CONF_DIR_CANDIDATES+=("$d")
done
ALPINE_CONF="/etc/php${PHP_VER_NN}/conf.d"
[ -d "$ALPINE_CONF" ] && CONF_DIR_CANDIDATES+=("$ALPINE_CONF")

CONF_DIRS=()
while IFS= read -r _line; do
    CONF_DIRS+=("$_line")
done < <(printf "%s\n" "${CONF_DIR_CANDIDATES[@]:-}" | awk '!seen[$0]++')

[ "${#CONF_DIRS[@]}" -eq 0 ] && echo "   ⚠️  No conf.d directories found."

INI_NAME="30-${EXTENSION_NAME}.ini"
INI_CONTENT="extension=${EXTENSION_NAME}.so"
for confd in "${CONF_DIRS[@]:-}"; do
    INI_PATH="${confd}/${INI_NAME}"
    echo "$INI_CONTENT" | $SUDO tee "$INI_PATH" >/dev/null
    ok "Written: $INI_PATH"
done
echo ""

# ── Verify ────────────────────────────────────────────────────────────────────
step "🔍 Verifying installation (CLI)..."
VERIFIED=0
for attempt in 1 2 3 4 5; do
    if "$PHP_BIN_REAL" -r 'exit(class_exists("Ftdi\\FTDI", false) ? 0 : 1);' 2>/dev/null; then
        ok "Ftdi\\FTDI is available in CLI"
        VERIFIED=1
        break
    fi
    sleep 1
done
if [ "$VERIFIED" -eq 0 ]; then
    VERIFY_ERRORS="$("$PHP_BIN_REAL" -m 2>&1 || true)"
    printf "%s\n" "$VERIFY_ERRORS" | grep -i "${EXTENSION_NAME}\|error\|warn" || true
    "$PHP_BIN_REAL" --ini 2>/dev/null | grep -E "Scan for additional|Additional \.ini" || true
    die "Ftdi\\\\FTDI not available after install. Check ${INI_NAME} and build.log."
fi

if ! "$PHP_BIN_REAL" -m 2>/dev/null | grep -qx "${EXTENSION_NAME}"; then
    echo "   ⚠️  ${EXTENSION_NAME} not listed in php -m (Ftdi\\\\FTDI is loaded — may be OK)"
else
    ok "Module ${EXTENSION_NAME} listed in php -m"
fi
echo ""

# ── FPM reload ───────────────────────────────────────────────────────────────
if command -v systemctl >/dev/null 2>&1; then
    for svc in "php${PHP_VER_MM}-fpm" "php-fpm"; do
        if systemctl is-active --quiet "${svc}.service" 2>/dev/null; then
            step "🔁 Reloading ${svc}..."
            $SUDO systemctl reload "${svc}" || true
            ok "${svc} reloaded"
            break
        fi
    done
fi

step "=========================================="
step " Extension Information (CLI)"
step "=========================================="
"$PHP_BIN_REAL" --ri "${EXTENSION_NAME}" || true
echo ""

echo "✅  Installation complete!"
echo ""
echo "File locations:"
echo "  • Binary: ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
for d in "${CONF_DIRS[@]:-}"; do
    echo "  • Config: ${d}/${INI_NAME}"
done
echo ""
