---
type: Trap
title: Windows excluded
description: PIE os-families-exclude windows — Unix only
resource: /composer.json
tags: [ftdi, trap, windows, pie]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: composer
    resource: /composer.json
    title: composer.json
  - id: readme
    resource: /README.md
    title: README.md
---

# Trap

`composer.json` sets `php-ext.os-families-exclude: ["windows"]`.[^composer] This extension targets **Linux and macOS**. Do not add Windows build matrices, Win32 polyfills, or FFI fallbacks “for completeness.”

Consumers on Windows should not expect `pie install php-io-extensions/ftdi` to succeed.

[^composer]: composer.json
[^readme]: README.md
