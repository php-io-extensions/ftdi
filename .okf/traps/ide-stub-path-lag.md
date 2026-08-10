---
type: Trap
title: IDE stub path lag
description: ide/0.2.0 lags behind package 0.7.0 — do not regenerate casually
resource: /ide
tags: [ftdi, trap, ide, stubs]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: ide-020
    resource: /ide/0.2.0
    title: ide/0.2.0 stubs
  - id: config
    resource: /config.json
    title: config.json
  - id: composer
    resource: /composer.json
    title: composer.json
---

# Trap

Package version is **0.7.0**, but committed IDE stubs still live under `ide/0.2.0/`.[^ide-020][^composer]

Treat that tree as a **lagging autocomplete aid**, not as the source of truth for the public API. Source of truth is `ftdi/*.zep` + `src/ftdi-eeprom.h` + ScrapyardIO ecosystem **0.7.x** docs (package README only links there).

The stub tree also includes `ide/0.2.0/Ftdi/I2C.php`, which is **not** a Zephir class in the current package — another reason not to trust stubs as API inventory.

# Agent rule

- Do **not** regenerate or invent `ide/0.7.0/` stubs as part of routine OKF/docs work unless Angel explicitly asks.
- Do not edit stale stub trees as if they were implementation.

When stubs are eventually refreshed, they should match `config.json` version and the implemented methods only.

[^ide-020]: ide/0.2.0 stubs
[^config]: config.json
[^composer]: composer.json
