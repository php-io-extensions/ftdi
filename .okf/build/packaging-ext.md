---
type: Convention
title: Committed ext/ notes
description: Ship-ready ext/ tree, version header, and stub lag
resource: /ext/php_ftdi.h
tags: [ftdi, build, packaging]
status: draft
generated: { by: cursor-agent/claude-opus-5.5, at: "2026-09-23T23:20:00Z" }
sources:
  - id: php-h
    resource: /ext/php_ftdi.h
    title: php_ftdi.h
  - id: config
    resource: /config.json
    title: Zephir config
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: eeprom-ext
    resource: /ext/src/ftdi-eeprom.c
    title: ext/src ftdi-eeprom mirror
---

# What ships in `ext/`

PIE/`phpize` builds from the pre-generated C tree under `ext/` (`build-path: ext`).[^composer] That tree is **ship-ready** — treat it as release artifact input, not a scratch build folder.

| Artifact | Role |
|----------|------|
| `ext/php_ftdi.h` | `PHP_FTDI_VERSION` (`0.9.0`)[^php-h] |
| `ext/ftdi/*.zep.c` / `.zep.h` | Generated Zephir C |
| `ext/src/ftdi-eeprom.{c,h}` | Mirror of package `src/` helpers[^eeprom-ext] |
| `ext/kernel/{file,main,require}.c` | Must equal the `clang/kernel/` overlays, not stock Zephir |
| `ext/config.m4` | Copy of `clang/config.m4`: `--enable-ftdi` + libftdi1 + libusb-1.0 (the event-pump bindings include `<libusb.h>`; libftdi 1.5's `ftdi.h` does not pull it in) |

Integrity rule: **phpize / configure / make from `ext/` must work without Zephir.** Agents must not leave the committed tree dependent on a local Zephir generate step.

# Version alignment

Package version **0.9.0** is recorded in:

- `composer.json` → `"version": "0.9.0"`
- `config.json` → `"version": "0.9.0"`
- `ext/php_ftdi.h` → `PHP_FTDI_VERSION "0.9.0"`

Prior release lines: 0.8.0, 0.7.0, 0.5.0.

# Stubs

IDE stubs live under `ide/0.9.0/` — see [IDE stub path lag](/traps/ide-stub-path-lag.md).

# Regenerating

Only on a disposable **copy** of the tree — see [Regenerate committed ext/](/playbooks/regenerate-ext.md).

[^php-h]: php_ftdi.h
[^config]: Zephir config
[^composer]: PIE package manifest
[^eeprom-ext]: ext/src ftdi-eeprom mirror
