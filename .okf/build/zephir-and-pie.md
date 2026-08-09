---
type: Playbook
title: Zephir + PIE install
description: Platform installers, PIE, and phpize builds — libftdi1 required
resource: /composer.json
tags: [ftdi, build, pie, zephir, libftdi1]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
  - id: debian
    resource: /install-debian-trixie.sh
    title: install-debian-trixie.sh
  - id: pre
    resource: /pre-install.sh
    title: pre-install.sh
  - id: readme
    resource: /README.md
    title: Package README
---

# Requirements

| Component | Notes |
|-----------|--------|
| OS | Linux or macOS (Windows excluded) |
| PHP | `>= 8.3` |
| **libftdi1** | Required at **compile and runtime** — Debian `libftdi1-dev` / runtime `libftdi1-2`; macOS `brew install libftdi`; pkg-config name `libftdi1`[^readme] |
| mpsse (optional) | Separate host install when MPSSE workflows are intended — not a PHP Composer dep of this extension[^readme] |
| Zephir | Required by platform installers when regenerating C; **not** required for PIE/`phpize` from committed `ext/` |
| Compiler | C toolchain (`clang` / `gcc`) |

# PIE (consumers)

```bash
pie install php-io-extensions/ftdi
```

Uses `type: php-ext`, `extension-name: ftdi`, `build-path: "ext"`, `--enable-ftdi`.[^composer]

Enable if needed:

```ini
extension=ftdi
```

Confirm: `php -m | grep ftdi`.

**Do not** `sudo pie install` from a development checkout — see [No sudo pie from checkout](/traps/no-sudo-pie-from-checkout.md).[^readme]

# Platform installers (on disk)

```bash
bash install-macos.sh            # macOS (+ Herd-aware PHP resolution)
bash install-debian-trixie.sh    # Debian Trixie / Raspberry Pi OS
```

`pre-install.sh` supports installer plumbing.[^pre][^install][^debian]

# Manual build from committed `ext/`

Consumers and CI may `phpize` / `configure` / `make` **from the ship-ready `ext/`** without Zephir. That compiles the committed C; it does **not** regenerate Zephir output. **libftdi1** headers + pkg-config must be present.

```bash
cd ext
phpize
./configure --enable-ftdi
make
sudo make install
```

# Critical agent rule

Do **not** run Zephir / full installers inside the primary checkout when the goal is to refresh generated C. Work on a **copy** — see [Do not rebuild in place](/traps/do-not-rebuild-in-place.md) and [Regenerate ext](/playbooks/regenerate-ext.md).

[^composer]: PIE package manifest
[^install]: install-macos.sh
[^debian]: install-debian-trixie.sh
[^pre]: pre-install.sh
[^readme]: Package README
