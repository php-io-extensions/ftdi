---
type: Convention
title: No FFI
description: Bindings ship as a compiled PHP extension — not FFI or pure-PHP polyfills
tags: [ftdi, convention, ffi]
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

# Rule

`php-io-extensions/ftdi` is a **compiled Zephir/C extension** (`type: php-ext`).[^composer] Do not add FFI wrappers, `dl()` hacks, or pure-PHP libftdi1 polyfills inside this package.

Consumers who want ergonomic helpers use optional downstream `microscrap/ftdi` — still extension-backed, not FFI.[^readme]

[^composer]: composer.json
[^readme]: README.md
