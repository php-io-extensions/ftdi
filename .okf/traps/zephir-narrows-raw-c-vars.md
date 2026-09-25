---
type: Trap
title: Zephir and vars that raw C writes
description: A var raw C writes must be Zephir-owned and start as a string; otherwise it narrows to a native type or leaks on return
resource: /ftdi/ftdi.zep
tags: [ftdi, trap, zephir, memory]
status: draft
generated: { by: claude-code/claude-opus-5.5, at: "2026-09-24T22:30:00Z" }
sources:
  - id: zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep (ftdiReadData, ftdiTransferReadDone and eight more)
  - id: main-h
    resource: /ext/kernel/main.h
    title: RETURN_CCTOR / RETURN_CCTORW
---

# Trap

Two ways a `var` that a `%{ }%` block writes goes wrong.[^zep]

- **Narrowing.** `let out = false;` makes Zephir declare `zend_bool out`. `ZVAL_STRINGL(&out, …)` then writes a zval into one byte of stack, and the method returns a bool. 0.9.0's `ftdiTransferReadDone` always returned `false` this way.
- **Leak.** A var Zephir never assigns is not tracked by its memory manager. The return macros copy it (`RETURN_CCTOR` / `RETURN_CCTORW` → `ZVAL_DUP`, which adds a reference),[^main-h] and nothing drops the local's reference. Every string C put there leaks: 32 bytes per 2-byte `ftdiReadData` reply, measured on the FT232H. The same held for anything C wrote into a var that then went into an array or a property.

# Do

In Zephir, give every such var a string before the block. That tracks it and keeps it a zval. At the top of the block, swap Zephir's allocated `""` for the interned one, then write freely:

```zephir
let out = "";

%{
    zval_ptr_dtor(&out);
    ZVAL_EMPTY_STRING(&out);      // or ZVAL_FALSE(&out) for a string|bool result
    …
    ZVAL_STRINGL(&out, buf, n);
}%

return out;
```

After a regenerate, check each such method in `ext/ftdi/ftdi.zep.c`. The var is in the `zval` list, `ZEPHIR_INIT_VAR(&var)` appears, and the method ends in `RETURN_CCTOR` or `RETURN_MM`, never `RETURN_CCTORW`.

[^zep]: ftdi.zep (ftdiReadData, ftdiTransferReadDone and eight more)
[^main-h]: RETURN_CCTOR / RETURN_CCTORW
