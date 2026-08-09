---
type: Trap
title: Context free ownership
description: PHP GC does not call ftdi_free — callers must free FTDIContext
resource: /ftdi/ftdi.zep
tags: [ftdi, trap, ownership, handles]
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

# Trap

`FTDIContext` is a PHP object wrapping an opaque native pointer. Dropping the object without `FTDI::ftdiFree()` does **not** release libftdi1 resources.[^ftdi-zep][^ctx-zep]

Same class of bug as forgetting `System::close` on a posi FD — different free API.

# Correct teardown (README pattern)

```php
FTDI::ftdiUSBClose($ftdi);
FTDI::ftdiDeinit($ftdi);
FTDI::ftdiFree($ftdi);
```

Prefer `try` / `finally` so free runs on error paths.[^readme]

Also free device-list handles from `ftdiUSBFindAll` via `ftdiListFree` / `ftdiListFree2`.

See [Handle ownership](/conventions/handle-ownership.md).

[^ftdi-zep]: ftdi.zep
[^ctx-zep]: ftdicontext.zep
[^readme]: README.md
