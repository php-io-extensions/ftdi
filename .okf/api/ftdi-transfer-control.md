---
type: API
title: Ftdi\\FTDITransferControl
description: Async transfer control DTO with opaque handles and toArray()
resource: /ftdi/ftditransfercontrol.zep
tags: [ftdi, api, FTDITransferControl]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: tc-zep
    resource: /ftdi/ftditransfercontrol.zep
    title: ftditransfercontrol.zep
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Class

`Ftdi\FTDITransferControl` — DTO for libftdi1 asynchronous transfer control. Populated by `FTDI::ftdiWriteDataSubmit()` and `FTDI::ftdiReadDataSubmit()`. Complete or cancel via `ftdiTransferDataDone` / `ftdiTransferDataCancel`.[^tc-zep][^ftdi-zep]

# Fields

| Property | Role |
|----------|------|
| `handle` | Opaque `struct ftdi_transfer_control *` as int |
| `completed` | Completion flag from the C struct |
| `size` | Requested transfer size |
| `offset` | Current offset |
| `contextHandle` | Parent context pointer as int |
| `bufHandle` | Transfer buffer pointer as int |

# Methods

| Method | Notes |
|--------|-------|
| `toArray()` | Associative array of the fields above |

No other methods on this class.

[^tc-zep]: ftditransfercontrol.zep
[^ftdi-zep]: ftdi.zep
