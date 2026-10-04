#!/bin/bash

# Builds ext-ftdi in a disposable copy and installs it into each PHP given, on
# Debian Trixie and systems built from it (Raspberry Pi OS, Ubuntu 24.04+).
#
#   ./install-debian-trixie.sh                      # the php on PATH
#   ./install-debian-trixie.sh /path/to/bin/php ... # specific PHP binaries
#
# For each PHP: phpize/configure/make against that PHP's php-config, copy the
# .so into its extension_dir, and enable it with 30-ftdi.ini in its conf.d scan
# dir. When 30-ftdi.ini is already a symlink into Debian's mods-available, the
# file is written through it, so every SAPI linking it stays enabled.
# Needs build-essential, pkg-config, libftdi1-dev, and the PHP headers (php8.4-dev, or a source build's).

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOURCES=(config.m4 ftdi.c php_ftdi.h ftdi_arginfo.h)
INI_NAME="30-ftdi.ini"

die() { printf '✖ %s\n' "$*" >&2; exit 1; }
step() { printf '▶ %s\n' "$*"; }

[[ "$(uname -s)" == "Linux" ]] || die "This installer is for Linux; on macOS run install-macos.sh."

SUDO=""
if [[ "${EUID:-$(id -u)}" -ne 0 ]]; then
    SUDO="sudo"
fi

if [[ $# -gt 0 ]]; then
    PHP_BINS=("$@")
else
    PHP_BINS=("$(command -v php || die "php not found on PATH")")
fi

# A tool next to the PHP binary, then its Debian-versioned name (phpize8.4), then PATH.
find_tool() {
    local bin_dir="$1" name="$2" version="$3" candidate
    for candidate in "${bin_dir}/${name}" "${bin_dir}/${name}${version}" \
        "$(command -v "${name}${version}" || true)" "$(command -v "${name}" || true)"; do
        if [[ -n "$candidate" && -x "$candidate" ]]; then
            printf '%s' "$candidate"
            return 0
        fi
    done
    return 1
}

BUILD_DIR=""
cleanup() { if [[ -n "$BUILD_DIR" ]]; then rm -rf "$BUILD_DIR"; fi; }
trap cleanup EXIT

for PHP_BIN in "${PHP_BINS[@]}"; do
    [[ -x "$PHP_BIN" ]] || die "$PHP_BIN not found or not executable"
    BIN_DIR="$(dirname "$(readlink -f "$PHP_BIN")")"
    VERSION="$("$PHP_BIN" -r 'echo PHP_MAJOR_VERSION, ".", PHP_MINOR_VERSION;')"
    PHPIZE="$(find_tool "$BIN_DIR" phpize "$VERSION")" || die "phpize for PHP ${VERSION} not found; install php${VERSION}-dev"
    PHP_CONFIG="$(find_tool "$BIN_DIR" php-config "$VERSION")" || die "php-config for PHP ${VERSION} not found; install php${VERSION}-dev"
    command -v cc >/dev/null 2>&1 || die "cc not found; install build-essential"
    pkg-config --exists 'libftdi1 >= 1.5' 'libusb-1.0 >= 1.0.16' 2>/dev/null || die "libftdi1 1.5+ and libusb-1.0 1.0.16+ not found; install pkg-config libftdi1-dev"

    step "Building for $("$PHP_BIN" -r 'echo PHP_VERSION, PHP_ZTS ? " ZTS" : " NTS";') (${PHP_BIN})"
    BUILD_DIR="$(mktemp -d "${TMPDIR:-/tmp}/ftdi-build.XXXXXX")"
    for f in "${SOURCES[@]}"; do
        cp "${SCRIPT_DIR}/${f}" "${BUILD_DIR}/"
    done
    if ! (cd "$BUILD_DIR" \
        && "$PHPIZE" \
        && ./configure --enable-ftdi --with-php-config="$PHP_CONFIG" \
        && make -j"$(nproc)") >"${BUILD_DIR}/build.log" 2>&1; then
        tail -40 "${BUILD_DIR}/build.log" >&2
        die "Build failed for ${PHP_BIN}"
    fi

    EXT_DIR="$("$PHP_BIN" -r 'echo ini_get("extension_dir");')"
    SCAN_DIR="$("$PHP_BIN" -r 'echo PHP_CONFIG_FILE_SCAN_DIR;')"
    [[ -d "$EXT_DIR" ]] || die "extension_dir ${EXT_DIR} does not exist"
    [[ -n "$SCAN_DIR" && -d "$SCAN_DIR" ]] || die "conf.d scan dir '${SCAN_DIR}' does not exist"

    $SUDO install -m 0644 "${BUILD_DIR}/modules/ftdi.so" "${EXT_DIR}/ftdi.so"
    printf 'extension=ftdi\n' | $SUDO tee "${SCAN_DIR}/${INI_NAME}" >/dev/null

    "$PHP_BIN" -r 'exit(extension_loaded("ftdi") ? 0 : 1);' || die "ftdi did not load in ${PHP_BIN}"
    step "Installed ${EXT_DIR}/ftdi.so, enabled by ${SCAN_DIR}/${INI_NAME}"

    rm -rf "$BUILD_DIR"
    BUILD_DIR=""
done
