---
type: Convention
title: Handle ownership
description: Caller owns FTDIContext, device lists, and transfer controls; PHP GC does not free them
tags: [ftdi, convention, memory, handles]
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

# Rules

| Resource | Create | Release |
|----------|--------|---------|
| Context | `FTDI::ftdiNew` (+ `ftdiInit` as needed) | `ftdiUSBClose` (if open) → `ftdiDeinit` → `ftdiFree` |
| Device list | `ftdiUSBFindAll` → `listHandle` | `ftdiListFree` or `ftdiListFree2` |
| Async transfer | `ftdiWriteDataSubmit` / `ftdiReadDataSubmit` | `ftdiTransferDataDone` or `ftdiTransferDataCancel` |

# Semantics

- `ftdiNew` failure: `handle < 0` (often `-1`) — do not free a failed allocation path beyond what README/API imply; check before use.[^readme][^ctx-zep]
- Dropping an `FTDIContext` without `ftdiFree` **leaks** native libftdi1 state.[^ftdi-zep]
- After `ftdiFree`, do not reuse the context object.
- List handles from `ftdiUSBFindAll` must be freed explicitly.

# Checklist

1. Pair every successful `ftdiNew` with `ftdiFree` (preferably in `finally`).
2. Close USB before deinit/free when a device was opened.
3. Free every non-zero `listHandle`.
4. Complete or cancel every submitted async transfer.

See also [Context free ownership trap](/traps/context-free-ownership.md).

[^ftdi-zep]: ftdi.zep
[^ctx-zep]: ftdicontext.zep
[^readme]: README.md
