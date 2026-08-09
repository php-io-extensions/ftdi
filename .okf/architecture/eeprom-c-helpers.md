---
type: Architecture
title: EEPROM C helpers
description: Thin src/ftdi-eeprom helpers and FtdiReadChipIdOptimizer
resource: /src/ftdi-eeprom.h
tags: [ftdi, architecture, eeprom, c-abi]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: eeprom-h
    resource: /src/ftdi-eeprom.h
    title: ftdi-eeprom.h
  - id: eeprom-c
    resource: /src/ftdi-eeprom.c
    title: ftdi-eeprom.c
  - id: config
    resource: /config.json
    title: config.json
  - id: chip-opt
    resource: /optimizers/FtdiReadChipIdOptimizer.php
    title: FtdiReadChipIdOptimizer.php
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Role

`config.json` lists `src/ftdi-eeprom.c` under `extra-sources` and `optimizers` under `optimizer-dirs`.[^config] The C header exposes a single helper:[^eeprom-h]

```c
void ftdi_read_chip_id(zval *return_value, zval *ctx_handle);
```

Implementation calls `ftdi_read_chipid` and builds an associative array with keys `status` and (on success) `chipId`.[^eeprom-c]

`FtdiReadChipIdOptimizer` rewrites a Zephir call to `ftdi_read_chip_id` into that C helper.[^chip-opt]

# Public PHP surface

The **public** method `FTDI::ftdiReadChipId(FTDIContext $ftdi): array` is implemented in `ftdi.zep` with inline C and returns:[^ftdi-zep]

| Key | Meaning |
|-----|---------|
| `result` | libftdi1 return code |
| `chipid` | unsigned chip id as int |

Do **not** document the C helper’s `status` / `chipId` keys as the PHP API — those are the ABI helper’s shape. Agents and docs must cite the Zephir return keys (`result` / `chipid`) for public usage (also what README shows).

# Other EEPROM work

EEPROM init/build/decode/read/write/erase and `setFT232HCbus` live as Zephir methods on `FTDI` (mostly inline C against libftdi1), not as additional entries in `src/ftdi-eeprom.h`. Do not invent extra C ABI symbols beyond what is on disk.

[^eeprom-h]: ftdi-eeprom.h
[^eeprom-c]: ftdi-eeprom.c
[^config]: config.json
[^chip-opt]: FtdiReadChipIdOptimizer.php
[^ftdi-zep]: ftdi.zep
