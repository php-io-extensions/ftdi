---
type: API
title: Ftdi\\FTDI
description: Static libftdi1 bindings — lifecycle, USB, baud, I/O, bitmode, async, EEPROM, errors
resource: /ftdi/ftdi.zep
tags: [ftdi, api, FTDI, libftdi1]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
  - id: readme
    resource: /README.md
    title: README.md
---

# Class

`Ftdi\FTDI` — all methods **static**. Implemented surface grounded in `ftdi/ftdi.zep` (also documented in README).[^ftdi-zep][^readme]

Constants (`INTERFACE_*`, `BITMODE_*`, `FLOW_*`, …) are **not** defined by the extension — see [Constants outside](/conventions/constants-outside-ext.md).

# Method groups

## Lifecycle / context

| Method | Notes |
|--------|-------|
| `ftdiNew` | `(): FTDIContext` — allocate; check `handle >= 0` |
| `ftdiInit` | `(FTDIContext $ftdi): int` |
| `ftdiSetInterface` | `(FTDIContext $ftdi, int $iface): int` |
| `ftdiDeinit` | `(FTDIContext $ftdi): void` |
| `ftdiFree` | `(FTDIContext $ftdi): void` — do not use context after |
| `ftdiSetUSBDev` | `(FTDIContext $ftdi, int $usbDevHandle): void` |
| `ftdiGetLibraryVersion` | `(): FTDIVersionInfo` |

## USB open / close / enumerate

| Method | Notes |
|--------|-------|
| `ftdiUSBFindAll` | `(FTDIContext $ftdi, int $vendor, int $product): array` → `count`, `listHandle` |
| `ftdiListFree` | `(int $listHandle): void` |
| `ftdiListFree2` | `(int $listHandle): void` |
| `ftdiUSBGetStrings` | `(FTDIContext $ftdi, int $devHandle): array` → manufacturer / description / serial |
| `ftdiUSBGetStrings2` | `(FTDIContext $ftdi, int $devHandle): array` |
| `ftdiUSBOpenDev` | `(FTDIContext $ftdi, int $devHandle): int` |
| `ftdiUSBOpen` | `(FTDIContext $ftdi, int $vendor, int $product): int` |
| `ftdiUSBOpenDesc` | `(FTDIContext $ftdi, int $vendor, int $product, mixed $description, mixed $serial): int` |
| `ftdiUSBOpenDescIndex` | `(…, int $index): int` |
| `ftdiUSBOpenBusAddr` | `(FTDIContext $ftdi, int $bus, int $addr): int` |
| `ftdiUSBOpenString` | `(FTDIContext $ftdi, mixed $description): int` |
| `ftdiUSBClose` | `(FTDIContext $ftdi): int` |
| `ftdiUSBReset` | `(FTDIContext $ftdi): int` |

## Flush / purge

| Method |
|--------|
| `ftdiTCIFlush` |
| `ftdiTCOFlush` |
| `ftdiTCIOFlush` |
| `ftdiUSBPurgeRXBuffer` |
| `ftdiUSBPurgeTXBuffer` |
| `ftdiUSBPurgeBuffers` |

Each takes `(FTDIContext $ftdi): int`.

## Baud / line

| Method | Notes |
|--------|-------|
| `ftdiConvertBaudrateUTExport` | `(int $baudrate, FTDIContext $ftdi): array` → `value`, `index` |
| `ftdiSetBaudrate` | `(FTDIContext $ftdi, int $baudrate): int` |
| `ftdiSetLineProperty` | `(FTDIContext $ftdi, int $bits, int $sbit, int $parity): int` |
| `ftdiSetLineProperty2` | `(…, int $breakType): int` |

## Read / write

| Method | Notes |
|--------|-------|
| `ftdiWriteData` | `(FTDIContext $ftdi, mixed $data, int $size): int` |
| `ftdiWriteDataSetChunksize` | `(FTDIContext $ftdi, int $chunksize): int` |
| `ftdiWriteDataGetChunksize` | `(FTDIContext $ftdi): int` |
| `ftdiReadData` | `(FTDIContext $ftdi, int $size): string` |
| `ftdiReadDataSetChunksize` | `(FTDIContext $ftdi, int $chunksize): int` |
| `ftdiReadDataGetChunksize` | `(FTDIContext $ftdi): int` |

## Bitmode / pins / modem / flow

| Method | Notes |
|--------|-------|
| `ftdiSetBitmode` | `(FTDIContext $ftdi, int $bitmask, int $mode): int` |
| `ftdiDisableBitbang` | `(FTDIContext $ftdi): int` |
| `ftdiReadPins` | `(FTDIContext $ftdi): int` |
| `ftdiSetLatencyTimer` | `(FTDIContext $ftdi, int $latency): int` |
| `ftdiGetLatencyTimer` | `(FTDIContext $ftdi): int` |
| `ftdiSetTimeouts` | `(FTDIContext $ftdi, int $readTimeout, int $writeTimeout): void` |
| `ftdiPollModemStatus` | `(FTDIContext $ftdi): int` |
| `ftdiSetFlowCtrl` | `(FTDIContext $ftdi, int $flowctrl): int` |
| `ftdiSetFlowCtrlXonXoff` | `(FTDIContext $ftdi, int $xon, int $xoff): int` |
| `ftdiSetDtr` | `(FTDIContext $ftdi, int $state): int` |
| `ftdiSetRts` | `(FTDIContext $ftdi, int $state): int` |
| `ftdiSetDtrRts` | `(FTDIContext $ftdi, int $dtr, int $rts): int` |
| `ftdiSetEventChar` | `(FTDIContext $ftdi, int $eventch, int $enable): int` |
| `ftdiSetErrorChar` | `(FTDIContext $ftdi, int $errorch, int $enable): int` |

## Async transfer

| Method | Notes |
|--------|-------|
| `ftdiWriteDataSubmit` | `(FTDIContext $ftdi, mixed $data, int $size): FTDITransferControl` |
| `ftdiReadDataSubmit` | `(FTDIContext $ftdi, int $size): FTDITransferControl` |
| `ftdiTransferDataDone` | `(FTDITransferControl $tc): int` |
| `ftdiTransferDataCancel` | `(FTDITransferControl $tc): void` |

## EEPROM / chip id

| Method | Notes |
|--------|-------|
| `ftdiGetEeprom` | `(FTDIContext $ftdi): FTDIEeprom` |
| `ftdiEepromInitDefaults` | `(FTDIContext $ftdi, mixed $manufacturer, mixed $product, mixed $serial): int` |
| `ftdiEepromSetStrings` | `(FTDIContext $ftdi, mixed $manufacturer, mixed $product, mixed $serial): int` |
| `ftdiEepromGetStrings` | `(FTDIContext $ftdi): array` → manufacturer / product / serial |
| `ftdiEepromBuild` | `(FTDIContext $ftdi): int` |
| `ftdiEepromDecode` | `(FTDIContext $ftdi, int $verbose): int` |
| `ftdiGetEepromValue` | `(FTDIContext $ftdi, int $valueName): int` |
| `ftdiSetEepromValue` | `(FTDIContext $ftdi, int $valueName, int $value): int` |
| `ftdiGetEepromBuf` | `(FTDIContext $ftdi, int $size): string` |
| `ftdiSetEepromBuf` | `(FTDIContext $ftdi, mixed $buf): int` |
| `ftdiSetEepromUserData` | `(FTDIContext $ftdi, mixed $buf): int` |
| `setFT232HCbus` | `(FTDIEeprom $eeprom): string` |
| `ftdiReadEepromLocation` | `(FTDIContext $ftdi, int $eepromAddr): int` |
| `ftdiReadEeprom` | `(FTDIContext $ftdi): int` |
| `ftdiReadChipId` | `(FTDIContext $ftdi): array` → `result`, `chipid` |
| `ftdiWriteEepromLocation` | `(FTDIContext $ftdi, int $eepromAddr, int $eepromVal): int` |
| `ftdiWriteEeprom` | `(FTDIContext $ftdi): int` — **destructive** |
| `ftdiEraseEeprom` | `(FTDIContext $ftdi): int` — **destructive** |

## Errors

| Method | Notes |
|--------|-------|
| `ftdiGetErrorString` | `(FTDIContext $ftdi): string` |

# Ownership

Pair successful open/new with close/deinit/free — see [Handle ownership](/conventions/handle-ownership.md) and [Context free ownership](/traps/context-free-ownership.md).

[^ftdi-zep]: ftdi.zep
[^readme]: README.md
