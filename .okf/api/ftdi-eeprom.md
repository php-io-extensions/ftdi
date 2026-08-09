---
type: API
title: Ftdi\\FTDIEeprom
description: EEPROM image DTO with field bag and toArray()
resource: /ftdi/ftdieeprom.zep
tags: [ftdi, api, FTDIEeprom]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: eeprom-zep
    resource: /ftdi/ftdieeprom.zep
    title: ftdieeprom.zep
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Class

`Ftdi\FTDIEeprom` — DTO for EEPROM image / descriptor fields. Obtained via `FTDI::ftdiGetEeprom()`; also accepted by `FTDI::setFT232HCbus()`.[^eeprom-zep][^ftdi-zep]

# Notable fields

| Property | Role |
|----------|------|
| `eepromHandle` | Opaque EEPROM pointer as int |
| `vendorId` / `productId` | USB IDs |
| `manufacturer` / `product` / `serial` | String descriptors |
| `cbusFunction0`…`cbusFunction9` | CBUS pin functions |
| Channel / driver / RS485 / drive / slew / power fields | Chip-specific EEPROM knobs (see Zephir for full list) |

# Methods

| Method | Notes |
|--------|-------|
| `toArray()` | Associative array of EEPROM fields (does **not** include `eepromHandle` in the returned map) |

No other methods on this class — EEPROM operations go through `Ftdi\FTDI` statics (`ftdiEepromBuild`, `ftdiReadEeprom`, …).

[^eeprom-zep]: ftdieeprom.zep
[^ftdi-zep]: ftdi.zep
