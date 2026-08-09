---
type: Architecture
title: Layered stack
description: Zephir → libftdi1 (+ thin EEPROM helpers)
resource: /config.json
tags: [ftdi, architecture, zephir, libftdi1]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: config
    resource: /config.json
    title: Zephir config
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
  - id: eeprom-h
    resource: /src/ftdi-eeprom.h
    title: ftdi-eeprom.h
  - id: chip-opt
    resource: /optimizers/FtdiReadChipIdOptimizer.php
    title: FtdiReadChipIdOptimizer.php
---

# Layers

```text
PHP (Ftdi\{FTDI, FTDIContext, FTDIEeprom, FTDITransferControl, FTDIVersionInfo})
        │  Zephir static methods / DTO fields
        │  (inline C blocks + optional optimizers)
        ▼
Thin C helpers (src/ftdi-eeprom.{c,h})   optional ABI helpers (chip id)
        │
        ▼
libftdi1                                 ftdi_new, ftdi_usb_open, …
        │
        ▼
libusb / host USB stack
```

Unlike posi (Zephir → C ABI → libc FDs), the dominant path here is **Zephir inline C → libftdi1**, with opaque `struct ftdi_context *` values stored as PHP `int` on `FTDIContext::$handle`.[^ftdi-zep]

# Source map

| Layer | Path | Role |
|-------|------|------|
| Zephir | `ftdi/{ftdi,ftdicontext,ftdieeprom,ftditransfercontrol,ftdiversioninfo}.zep` | Public PHP API |
| Headers / C | `src/ftdi-eeprom.{c,h}` | Extra sources for chip-id helper (`extra-sources`)[^config][^eeprom-h] |
| Optimizers | `optimizers/FtdiReadChipIdOptimizer.php` | Compile-time rewrite for `ftdi_read_chip_id`[^chip-opt] |
| Packaging | `composer.json` | `build-path: ext`, Windows excluded |
| Ship-ready C | `ext/` | Pre-generated tree for PIE/`phpize` |

# Design intent

- Keep public surface as static `FTDI::*` methods mirroring libftdi1 names.
- Carry device state in `FTDIContext` (and related DTOs), not bare FDs.
- Ship committed `ext/` so consumers build without Zephir.

See [libftdi1 binding](/architecture/libftdi-binding.md) and [EEPROM C helpers](/architecture/eeprom-c-helpers.md).

[^config]: Zephir config
[^ftdi-zep]: ftdi.zep
[^eeprom-h]: ftdi-eeprom.h
[^chip-opt]: FtdiReadChipIdOptimizer.php
