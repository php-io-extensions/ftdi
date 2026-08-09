---
type: API
title: Ftdi\\FTDIContext
description: Opaque libftdi1 context DTO with handle fields and toArray()
resource: /ftdi/ftdicontext.zep
tags: [ftdi, api, FTDIContext]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: ctx-zep
    resource: /ftdi/ftdicontext.zep
    title: ftdicontext.zep
  - id: readme
    resource: /README.md
    title: README.md
---

# Class

`Ftdi\FTDIContext` — data-transfer object for a libftdi1 `struct ftdi_context`. Populated by `FTDI::ftdiNew()` (and hydrated by subsequent calls). Pass the object into static `FTDI::*` methods; they use `$handle`.[^ctx-zep][^readme]

# Fields

| Property | Role |
|----------|------|
| `handle` | Opaque `struct ftdi_context *` as int; **`-1`** = failed / unusable |
| `chipType` | Chip type enum value |
| `usbReadTimeout` / `usbWriteTimeout` | USB timeouts (ms) |
| `interfaceIndex` | Multi-interface chip index field |
| `baudrate` | Configured baud (0 until set) |
| `bitbangEnabled` | Non-zero when bitbang active |
| `bitbangMode` | Active bitbang/MPSSE mode |
| `channel` | Interface channel (`ftdi_set_interface`); named to avoid reserved word `interface` |
| `inEndpoint` / `outEndpoint` | USB endpoints |
| `readBufferChunkSize` / `writeBufferChunkSize` | Chunk sizes |
| `maxPacketSize` | Max USB packet size |
| `moduleDetachMode` | Kernel module detach mode |
| `errorStr` | Last error string |

# Methods

| Method | Notes |
|--------|-------|
| `toArray()` | Associative array of the fields above |

No other methods are defined on this class in Zephir — do not invent openers/closers on the DTO itself; use `Ftdi\FTDI` statics.

# Ownership

Caller must `ftdiUSBClose` (if opened), then `ftdiDeinit`, then `ftdiFree`. PHP GC does **not** free the native context — see [Context free ownership](/traps/context-free-ownership.md).

[^ctx-zep]: ftdicontext.zep
[^readme]: README.md
