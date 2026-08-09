---
type: Playbook
title: Regenerate committed ext/
description: Maintainer Zephir rebuild on a disposable copy — never in-place on ship-ready ext/
resource: /install-macos.sh
tags: [ftdi, playbook, packaging, zephir]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: debian
    resource: /install-debian-trixie.sh
    title: install-debian-trixie.sh
  - id: config
    resource: /config.json
    title: config.json
  - id: php-h
    resource: /ext/php_ftdi.h
    title: php_ftdi.h
  - id: composer
    resource: /composer.json
    title: composer.json
  - id: readme
    resource: /README.md
    title: README.md
---

# When

Before tagging a Packagist/PIE release, or after changing `.zep` / `src/ftdi-eeprom.{c,h}` / `optimizers/` / `config.json`.

# Critical rule

**Never regenerate ship-ready `ext/` in the primary checkout.** Always work on a **copy** of the tree, install/build there, then sync intentional outputs back and delete the copy.[^install]

Ensure **libftdi1** is installed on the build host first.[^readme]

# Steps

1. Confirm version targets are **0.7.0** (or the release you intend) in `composer.json`, `config.json`, and plan the matching `PHP_FTDI_VERSION` string.[^composer][^config][^php-h]

2. Copy the package:

```bash
SRC=/path/to/php-io-extensions/ftdi
COPY=/tmp/ftdi-rebuild-$(date +%Y%m%d)
cp -R "$SRC" "$COPY"
cd "$COPY"
```

3. On Linux or macOS with Zephir + matching PHP + libftdi1, run the platform installer **in the copy** (or equivalent Zephir generate + build):

```bash
bash install-macos.sh
# or
bash install-debian-trixie.sh
```

4. Smoke in the copy:

```bash
php -n -d extension=./ext/modules/ftdi.so --ri ftdi
php -r 'use Ftdi\FTDI; $v = FTDI::ftdiGetLibraryVersion(); echo $v->versionStr, "\n";'
```

5. Sync **only** intentional artifacts back into the primary checkout (generated `ext/` sources you mean to ship, ABI mirrors under `ext/src/`, version header). Do **not** sync phpize junk (`Makefile`, `modules/*.so`, `autom4te.cache`, …).

6. Delete the copy:

```bash
rm -rf "$COPY"
```

7. Update `.okf` + `log.md` if the public surface or packaging changed.

# Explicit non-goals for agents

- Do not run zephir / phpize / make / `pie install` in the primary folder to “refresh” C.
- Do not `sudo pie install` from the checkout (root-owned `ext/` risk).
- Do not regenerate IDE stubs unless Angel asks (current stubs lag at `ide/0.2.0`).

See [Do not rebuild in place](/traps/do-not-rebuild-in-place.md).

[^install]: install-macos.sh
[^debian]: install-debian-trixie.sh
[^config]: config.json
[^php-h]: php_ftdi.h
[^composer]: composer.json
[^readme]: README.md
