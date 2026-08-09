---
type: Convention
title: Constants outside the extension
description: No PHP class constants in the extension — app or microscrap enums own INTERFACE_/BITMODE_/FLOW_ values
tags: [ftdi, convention, constants, enums]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: readme
    resource: /README.md
    title: README.md
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Rule

libftdi1 constant values (`INTERFACE_*`, `BITMODE_*`, `BITS_*`, `STOP_BIT_*`, `PARITY_*`, `FLOW_*`, vendor/product IDs, …) are **not** compiled into this extension as PHP class constants.[^readme]

Define them in:

- Application-local PHP enums / consts, or
- Downstream microscrap packages,

matching host libftdi1 headers. Prefer backed PHP enums (`FULLY UPPERCASE` cases) in application code — do not add class-level constants to the extension classes.

README: “Constants and enum values follow libftdi1 conventions. Define them in PHP or load them from your platform headers.”[^readme]

[^readme]: README.md
[^ftdi-zep]: ftdi.zep
