---
type: Trap
title: IDE stub path lag
description: Stubs live at ide/0.9.0 — regenerate only alongside a version bump
resource: /ide
tags: [ftdi, trap, ide, stubs]
status: draft
generated: { by: cursor-agent/claude-opus-5.5, at: "2026-09-23T23:20:00Z" }
sources:
  - id: ide-090
    resource: /ide/0.9.0
    title: ide/0.9.0 stubs
  - id: config
    resource: /config.json
    title: config.json
  - id: install
    resource: /install-macos.sh
    title: install-macos.sh
---

# Trap

IDE stubs live at `ide/0.9.0/Ftdi/` (`FTDI`, `FTDIContext`, `FTDIEeprom`, `FTDITransferControl`, `FTDIVersionInfo`). The installer regenerates them with `zephir stubs`, into a directory named after `config.json`'s `version`.[^ide-090][^config][^install]

The stale `ide/0.2.0/` tree, including a phantom `I2C.php` stub with no Zephir class behind it, was removed on 2026-09-23.

# Agent rule

- Regenerate stubs only alongside a version bump, on the disposable copy used to regenerate `ext/`. Then sync `ide/<version>/` back and delete the previous tree.
- The source of truth for the API is `ftdi/*.zep`, not the stubs.

[^ide-090]: ide/0.9.0 stubs
[^config]: config.json
[^install]: install-macos.sh
