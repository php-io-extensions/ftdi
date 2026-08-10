---
okf_version: "0.2"
---

# php-io-extensions/ftdi

Cross-platform (Linux + macOS) PHP extension: Zephir static class `Ftdi\FTDI` plus opaque companion DTOs (`FTDIContext`, `FTDIEeprom`, `FTDITransferControl`, `FTDIVersionInfo`) that call **libftdi1** (with a thin EEPROM/chip-id helper in `src/ftdi-eeprom.{c,h}`). Contexts carry opaque `handle` integers — not flat POSIX FDs like posi. Windows is excluded. No FFI. Version **0.7.0** (0.7.x reconstitution / version-alignment pass; prior line was 0.5.0).

**Prefer** concepts with `status: stable` when present; content is currently `draft` pending Angel’s human verification of the OKF docs (implementation facts are grounded in shipped Zephir/`src/`/`ext/` plus ScrapyardIO ecosystem **0.7.x** pages — package README is a docs pointer only).

# Orientation

* [Package overview](orientation/overview.md) - What ftdi is, version targets, and what it deliberately is not
* [Stack segmentation](orientation/stack-segmentation.md) - Boundaries vs microscrap/ftdi, USB drivers, and MPSSE

# Architecture

* [Layered stack](architecture/stack.md) - Zephir → libftdi1 (+ thin EEPROM helpers)
* [libftdi1 binding](architecture/libftdi-binding.md) - Opaque context handles and static call shape
* [EEPROM C helpers](architecture/eeprom-c-helpers.md) - `src/ftdi-eeprom.{c,h}` + optimizer

# Public PHP API

* [Ftdi\\FTDI](api/ftdi.md) - Static libftdi1 bindings (lifecycle, USB, baud, I/O, bitmode, async, EEPROM, errors)
* [Ftdi\\FTDIContext](api/ftdi-context.md) - Opaque context DTO + `toArray()`
* [Ftdi\\FTDIEeprom](api/ftdi-eeprom.md) - EEPROM image DTO + `toArray()`
* [Ftdi\\FTDITransferControl](api/ftdi-transfer-control.md) - Async transfer DTO + `toArray()`
* [Ftdi\\FTDIVersionInfo](api/ftdi-version-info.md) - Library version DTO + `toArray()`

# Build & packaging

* [Zephir + PIE install](build/zephir-and-pie.md) - installers, PIE, phpize from `ext/`; **libftdi1** required
* [Committed ext/ notes](build/packaging-ext.md) - Ship-ready tree, version headers, stubs lag

# Conventions

* [Sibling patterns](conventions/sibling-patterns.md) - Shared php-io-extensions packaging style
* [Handle ownership](conventions/handle-ownership.md) - FTDIContext free + list/transfer handles
* [No FFI](conventions/no-ffi.md) - Extension-only binding
* [Constants outside the extension](conventions/constants-outside-ext.md) - No PHP class constants; app/microscrap enums

# Traps

* [Windows excluded](traps/windows-excluded.md) - PIE `os-families-exclude: windows`
* [Do not rebuild ext/ in place](traps/do-not-rebuild-in-place.md) - Copy → build → sync → delete copy
* [No sudo pie from checkout](traps/no-sudo-pie-from-checkout.md) - Root-owned files under `ext/`
* [IDE stub path lag](traps/ide-stub-path-lag.md) - `ide/0.2.0` lags behind 0.7.0
* [libftdi1 required](traps/libftdi1-required.md) - Compile + runtime dependency
* [Context free ownership](traps/context-free-ownership.md) - PHP GC does not `ftdi_free`

# Playbooks

* [Minimal open / baud demo](playbooks/demo-open-baud.md) - README-style open, baud, line, I/O, free
* [Regenerate committed ext/](playbooks/regenerate-ext.md) - Maintainer steps on a **copy** of the tree

# Indexes

* [Orientation](orientation/) — start here
* [Architecture](architecture/)
* [API](api/)
* [Build](build/)
* [Conventions](conventions/)
* [Traps](traps/)
* [Playbooks](playbooks/)
