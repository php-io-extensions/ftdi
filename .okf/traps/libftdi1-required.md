---
type: Trap
title: libftdi1 required
description: libftdi1 is required at compile and runtime — missing pkg-config breaks builds
resource: /README.md
tags: [ftdi, trap, libftdi1, dependencies]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: readme
    resource: /README.md
    title: README.md
  - id: config-m4
    resource: /ext/config.m4
    title: ext/config.m4
---

# Trap

Unlike posi (libc only), this extension **requires libftdi1** at both compile time and runtime.[^readme]

| Platform | Typical packages |
|----------|------------------|
| Debian / Ubuntu / Raspberry Pi OS | `libftdi1-dev` (build), `libftdi1-2` (runtime) |
| macOS | `brew install libftdi` |
| pkg-config name | `libftdi1` |

Optional MPSSE workflows need a separate **mpsse** install — that is **not** a substitute for libftdi1, and it is not a PHP Composer dependency of this extension.

# Symptoms

- `configure` / PIE fails looking for libftdi1 headers or `.pc` metadata.
- Extension loads but USB calls fail because the shared library is missing at runtime.

Install libftdi1 **before** `pie install` or platform installers.

[^readme]: README.md
[^config-m4]: ext/config.m4
