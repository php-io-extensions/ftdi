---
type: API
title: Ftdi\\FTDITransferControl
description: Async transfer control DTO with opaque handles and toArray()
resource: /ftdi/ftditransfercontrol.zep
tags: [ftdi, api, FTDITransferControl]
status: draft
generated: { by: cursor-agent/claude-opus-5.5, at: "2026-09-23T23:20:00Z" }
sources:
  - id: tc-zep
    resource: /ftdi/ftditransfercontrol.zep
    title: ftditransfercontrol.zep
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Class

`Ftdi\FTDITransferControl` — DTO for libftdi1 asynchronous transfer control. Populated by `FTDI::ftdiWriteDataSubmit()` and `FTDI::ftdiReadDataSubmit()`. Poll with `ftdiTransferCompleted`; finish with exactly one terminal call: `ftdiTransferDataDone`, `ftdiTransferReadDone` (reads, returns the bytes) or `ftdiTransferDataCancel`.[^tc-zep][^ftdi-zep]

# Fields

| Property | Role |
|----------|------|
| `handle` | Opaque `struct ftdi_transfer_control *` as int |
| `completed` | Completion flag from the C struct; refreshed by `ftdiTransferCompleted`, set to `1` by any terminal call |
| `size` | Requested transfer size |
| `offset` | Current offset; after done / read-done, the byte count returned |
| `contextHandle` | Parent context pointer as int |
| `bufHandle` | Extension-owned transfer buffer (`emalloc`) as int, for writes and reads alike |

After any terminal call, `handle` and `bufHandle` are `0`. The extension has already freed the buffer; the caller never frees it.

# Methods

| Method | Notes |
|--------|-------|
| `toArray()` | Associative array of the fields above |

No other methods on this class.

[^tc-zep]: ftditransfercontrol.zep
[^ftdi-zep]: ftdi.zep
