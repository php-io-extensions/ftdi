---
type: API
title: Ftdi\\FTDI
description: Static libftdi1 bindings — lifecycle, USB, baud, I/O, bitmode, async, event pump, EEPROM, errors
resource: /ftdi/ftdi.zep
tags: [ftdi, api, FTDI, libftdi1, libusb]
status: draft
generated: { by: cursor-agent/claude-opus-5.5, at: "2026-09-23T23:20:00Z" }
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
| `ftdiWriteDataSubmit` | `(FTDIContext $ftdi, mixed $data, int $size): FTDITransferControl` — copies `data` into an extension-owned buffer; `size` clamped to `strlen($data)` |
| `ftdiReadDataSubmit` | `(FTDIContext $ftdi, int $size): FTDITransferControl` |
| `ftdiTransferCompleted` | `(FTDITransferControl $tc): int` — refreshes `completed` / `offset` from the struct; `0` when `handle === 0` |
| `ftdiTransferDataDone` | `(FTDITransferControl $tc): int` — `-1` when `handle === 0` |
| `ftdiTransferReadDone` | `(FTDITransferControl $tc): string\|false` — first `ret` bytes of the read buffer; `false` when `ret < 0` or `handle === 0` |
| `ftdiTransferDataCancel` | `(FTDITransferControl $tc): void` — no-op when `handle === 0` |

Since 0.9.0 the PHP string passed to `ftdiWriteDataSubmit` may be freed while the transfer is in flight. Done, read-done and cancel are terminal: each frees the extension-owned buffer and sets `handle` and `bufHandle` to `0`, so a second terminal call returns `-1` / `false` / nothing and never double-frees.[^ftdi-zep]

## Event pump

1:1 libusb bindings over `ftdi_context->usb_ctx`. They let a caller drive async transfers from its own loop instead of blocking in `ftdiTransferDataDone`. Every method returns `-1` (or `[]`) on a dead context.

| Method | Notes |
|--------|-------|
| `ftdiGetPollfds` | `(FTDIContext $ftdi): array` — list of `['fd' => int, 'events' => int]`; `[]` when libusb returns `NULL`. libusb 1.0.29 on macOS returns one fd, so don't treat `[]` as the Darwin value |
| `ftdiPollfdsHandleTimeouts` | `(FTDIContext $ftdi): int` — `libusb_pollfds_handle_timeouts` |
| `ftdiGetNextTimeout` | `(FTDIContext $ftdi): array` — `['result' => int, 'usec' => int]`; `usec` is set only when `result === 1` |
| `ftdiHandleEventsTimeout` | `(FTDIContext $ftdi, int $timeoutUs): int` — `libusb_handle_events_timeout_completed(usb_ctx, &tv, NULL)`; negative timeouts clamp to `0` |

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
