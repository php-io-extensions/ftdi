---
type: Orientation
title: Stack segmentation
description: Boundaries vs microscrap/ftdi, USB drivers, and MPSSE
tags: [ftdi, orientation, boundaries]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: composer
    resource: /composer.json
    title: PIE package manifest
  - id: readme
    resource: /README.md
    title: Package README
---

# Who owns what

| Concern | Package | Notes |
|---------|---------|--------|
| Native libftdi1 C API in PHP | **`php-io-extensions/ftdi`** | This package — Zephir extension |
| Global / C-ish helpers wrapping `Ftdi\FTDI` | `microscrap/ftdi` | Downstream; not a dependency of this extension[^readme] |
| Higher-level MPSSE helpers | `microscrap/mpsse` (pulls `microscrap/ftdi`) | Downstream; optional MPSSE **library** install is also separate[^readme] |
| USB / FTDI chip drivers at OS level | host kernel / udev / vendor drivers | Outside this package |
| `INTERFACE_*` / `BITMODE_*` / baud constants | app locals or microscrap enums | Not compiled into this extension |
| POSIX FDs / termios | `php-io-extensions/posi` | Peer — different handle model |
| Display / window / Metal / SDL | `php-io-extensions/{metal,sdl3,…}` | Peers — not deps of ftdi |

# Composition sketch

```text
PHP app / tubes / USB workflows
  ├─ microscrap/mpsse          → optional MPSSE helpers (requires mpsse + this ext)
  ├─ microscrap/ftdi           → optional global helpers wrapping Ftdi\FTDI
  └─ php-io-extensions/ftdi    → Ftdi\{FTDI, FTDIContext, …}
         └─ libftdi1 (+ libusb)
```

# Hard rules

1. Do **not** document `microscrap/ftdi` or `microscrap/mpsse` APIs inside this OKF — only the composition boundary.
2. Do **not** add microscrap or display extensions as runtime Composer deps of this package.
3. Do **not** nest a second `.okf` under `ftdi/` or `src/`.
4. Keep Windows out of PIE (`os-families-exclude: ["windows"]`).[^composer]
5. Treat MPSSE as an **optional host workflow** — README requires a separate **mpsse** install when that path is intended; it is not a PHP `require` of this extension.

[^composer]: PIE package manifest
[^readme]: Package README
