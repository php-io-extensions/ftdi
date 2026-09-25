---
type: Orientation
title: Package overview
description: What ftdi is, version targets, and what it deliberately is not
resource: /composer.json
tags: [ftdi, orientation, php-ext, libftdi1]
status: draft
generated: { by: cursor-agent/claude-opus-5.5, at: "2026-09-23T23:20:00Z" }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: config
    resource: /config.json
    title: Zephir config
  - id: readme
    resource: /README.md
    title: README
  - id: php-h
    resource: /ext/php_ftdi.h
    title: php_ftdi.h
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Summary

`php-io-extensions/ftdi` is a **Linux + macOS** PHP extension (`type: php-ext`) that exposes **libftdi1** to PHP through static methods on `Ftdi\FTDI` and opaque companion DTOs. Zephir methods call libftdi1 C APIs (with a thin helper in `src/ftdi-eeprom.{c,h}`). Device sessions are `FTDIContext` objects whose `handle` is an opaque integer pointer — **not** flat POSIX FDs like posi. There is **no FFI**.[^composer][^readme][^ftdi-zep]

| Fact | Value |
|------|--------|
| Package | `php-io-extensions/ftdi` |
| Extension name | `ftdi` |
| Version | `0.9.0` |
| Prior release lines | `0.8.0`, `0.7.0`, `0.5.0` |
| PHP | `>= 8.3` (composer + README agree) |
| Native library | **libftdi1** + **libusb-1.0** (compile + runtime; pkg-config `libftdi1`, `libusb-1.0`) |
| OS | **Unix** — Linux + macOS; Windows excluded (`os-families-exclude`) |
| Namespace | `Ftdi\` — `FTDI`, `FTDIContext`, `FTDIEeprom`, `FTDITransferControl`, `FTDIVersionInfo` |
| Author | Project Saturn Studios, LLC |
| License | MIT |

Version strings are aligned at **0.9.0** in `composer.json`, `config.json`, and `PHP_FTDI_VERSION` in `ext/php_ftdi.h`.[^composer][^config][^php-h]

# End capability

1. Allocate / init / free libftdi1 contexts (`ftdiNew` / `ftdiInit` / `ftdiDeinit` / `ftdiFree`).
2. USB open/close/reset, string descriptors, device enumeration lists.
3. UART baud / line property, read/write, flush/purge, flow control, modem lines.
4. Bitbang / MPSSE bitmode, pin read, latency / timeouts.
5. Asynchronous transfer submit / completed / done / read-done / cancel, plus the libusb event pump (pollfds, next timeout, handle events).
6. EEPROM read/write/build/decode and chip ID.
7. Report library version and last error string.

# What it is not

- Not a Windows extension.
- Not an FFI or pure-PHP polyfill.
- Not a full MPSSE protocol stack — MPSSE mode can be entered via `ftdiSetBitmode`; higher-level MPSSE workflows use a separate **mpsse** install / `microscrap/mpsse`.
- Not the ergonomic helper layer — that is optional downstream `microscrap/ftdi`.

# Public namespace

| Class | Zephir | Role |
|-------|--------|------|
| `Ftdi\FTDI` | `ftdi/ftdi.zep` | Static libftdi1 bindings |
| `Ftdi\FTDIContext` | `ftdi/ftdicontext.zep` | Opaque context DTO |
| `Ftdi\FTDIEeprom` | `ftdi/ftdieeprom.zep` | EEPROM image DTO |
| `Ftdi\FTDITransferControl` | `ftdi/ftditransfercontrol.zep` | Async transfer DTO |
| `Ftdi\FTDIVersionInfo` | `ftdi/ftdiversioninfo.zep` | Library version DTO |

IDE stubs live under `ide/0.9.0/`, regenerated with the version bump (see [IDE stub path lag](/traps/ide-stub-path-lag.md)).

See [Stack segmentation](/orientation/stack-segmentation.md) and [Layered stack](/architecture/stack.md).

[^composer]: PIE package manifest
[^config]: Zephir config
[^readme]: README
[^php-h]: php_ftdi.h
[^ftdi-zep]: ftdi.zep
