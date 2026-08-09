---
type: Convention
title: Sibling patterns
description: Shared php-io-extensions packaging style (ftdi among peers)
tags: [ftdi, convention, packaging]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: composer
    resource: /composer.json
    title: ftdi composer.json
  - id: config
    resource: /config.json
    title: ftdi config.json
---

# Patterns this package owns / shares

| Pattern | How ftdi uses it | Shared with |
|---------|------------------|-------------|
| Thin Zephir + native library | `ftdi/*.zep` → libftdi1 (+ `src/ftdi-eeprom`) | posi (libc ABI), sdl3 (SDL3) |
| PIE `type: php-ext`, `build-path: ext` | Same layout | posi / sdl3 / metal |
| Static namespaced API | Flat `Ftdi\FTDI` + companion DTOs | Flat `Posi\…`; nested `Sdl3\…` |
| Opaque `int` handles | Context / list / transfer pointers | SDL / Metal opaque objects; posi FDs |
| Constants outside extension | App / microscrap enums | posi / sdl3 |
| Windows excluded | `os-families-exclude: ["windows"]` | posi / sdl3 |
| Zephir `optimizer-dirs` | `optimizers/` | posi |
| Version line **0.7.0** | Alignment pass from 0.5.0 | ecosystem 0.7.x |

# Distinctives

- **Requires pkg-config library libftdi1** at compile + runtime (unlike posi’s libc-only path).
- Handle model is **opaque context objects**, not flat FDs.
- Optional MPSSE workflow depends on a separate **mpsse** install — composition only.

Keep peer packages as composition boundaries only — no Composer `require` on microscrap/posi/sdl3 from this extension.

[^composer]: ftdi composer.json
[^config]: ftdi config.json
