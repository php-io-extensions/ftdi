---
type: Architecture
title: libftdi1 binding
description: Opaque context handles and static call shape for libftdi1
resource: /ftdi/ftdi.zep
tags: [ftdi, architecture, libftdi1, handles]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
  - id: ctx-zep
    resource: /ftdi/ftdicontext.zep
    title: ftdicontext.zep
  - id: readme
    resource: /README.md
    title: README.md
---

# Call shape

Almost every libftdi1 operation is a **static** method on `Ftdi\FTDI` that takes an `FTDIContext` (or a related DTO) and marshals `handle` into C as `(struct ftdi_context *)(uintptr_t)handle`.[^ftdi-zep][^ctx-zep]

| Concern | Mechanism |
|---------|-----------|
| Context allocation | `FTDI::ftdiNew()` → `FTDIContext` with `handle` (`-1` on failure)[^readme] |
| Session teardown | `ftdiUSBClose` → `ftdiDeinit` → `ftdiFree` |
| Device lists | `ftdiUSBFindAll` returns `count` + `listHandle`; free with `ftdiListFree` / `ftdiListFree2` |
| Async I/O | `ftdiWriteDataSubmit` / `ftdiReadDataSubmit` → `FTDITransferControl`; complete with `ftdiTransferDataDone` |
| Errors | Return codes from libftdi1; string via `ftdiGetErrorString` / `FTDIContext::$errorStr` |

# Contrast with posi

| | **ftdi** | **posi** |
|--|----------|----------|
| Primary handle | Opaque `FTDIContext::$handle` (pointer as int) | Flat FD `int` |
| Free / close | `ftdiFree` / `ftdiUSBClose` | `System::close` |
| Native library | libftdi1 (+ libusb) | libc POSIX |
| Companion objects | Context / EEPROM / transfer / version DTOs | Memory buffers for ioctl structs |

# Agent rule

Do not document invented wrappers, FFI shims, or “FD-style” APIs. Ground method lists in `ftdi/ftdi.zep` only — see [Ftdi\\FTDI](/api/ftdi.md).

[^ftdi-zep]: ftdi.zep
[^ctx-zep]: ftdicontext.zep
[^readme]: README.md
