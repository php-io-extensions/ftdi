---
type: API
title: Async transfers and the libusb pump
description: Submit, collect, cancel, completion; pumping libusb by timeout or by joining its poll descriptors to an event loop.
resource: ftdi.c
tags: [ftdi, async, libusb, event-loop]
status: draft
generated: { by: claude-opus/5.5, at: 2026-10-04T14:15:50Z }
sources:
  - id: ftdi-c
    resource: ftdi.c
    title: ftdi.c
---

# Transfers

| Function | Does |
|---|---|
| `ftdi_write_data_submit(ctx, $data, $size): ?FTDITransferControl` | copies `$size` bytes into an owned buffer, `ftdi_write_data_submit()` |
| `ftdi_read_data_submit(ctx, $size): ?FTDITransferControl` | owned `$size`-byte buffer, `ftdi_read_data_submit()` |
| `ftdi_transfer_completed($tc): int` | `tc->completed`; 1 once collected/cancelled |
| `ftdi_transfer_data_done($tc): int` | waits, frees `tc`, returns bytes moved or libftdi code; -1 if already collected/cancelled |
| `ftdi_transfer_read_done($tc): string\|false` | same, returns the bytes read; false on failure or already collected |
| `ftdi_transfer_data_cancel($tc): void` | cancel with zero timeout, frees `tc` and buffer; repeat = no-op |

Null from a submit: no device open (error string "USB device unavailable", see [libftdi guards](/architecture/libftdi-1-5-guards.md)) or libftdi's own submit failure. Buffer lives in the object until collected, cancelled, or object/context teardown cancels it. See [objects](/api/objects.md).[^ftdi-c]

Read semantics are libftdi's: a read submit first serves bytes already in libftdi's read buffer, so it can be complete on return.

# Pumping libusb

Transfers progress only while libusb handles events on `ctx->usb_ctx`.

- Blocking: `ftdi_handle_events_timeout(ctx, $us)` → `libusb_handle_events_timeout_completed`, returns libusb code. Loop until `ftdi_transfer_completed()`.
- Event loop: `ftdi_get_pollfds(ctx)` → `list<['fd', 'events']>` (libusb `POLLIN`/`POLLOUT` bits). Watch those fds; when any fires, `ftdi_handle_events_timeout(ctx, 0)`. Bound the wait by `ftdi_get_next_timeout(ctx)` → `['result', 'usec']` (`result` 1 = deadline in `usec`, 0 = none). `ftdi_pollfds_handle_timeouts(ctx)` = `libusb_pollfds_handle_timeouts()`: nonzero when libusb's own descriptors cover its timeouts, 0 when the caller must also honour `ftdi_get_next_timeout()`.

All pump functions need an initialised context (`Error` otherwise).[^ftdi-c]

[^ftdi-c]: ftdi.c
