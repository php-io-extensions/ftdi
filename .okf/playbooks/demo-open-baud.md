---
type: Playbook
title: Minimal open / baud demo
description: README-style context new, USB open, baud, line, write/read, free
resource: /README.md
tags: [ftdi, playbook, demo]
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

# Prerequisites

- Extension loaded: `extension=ftdi`
- **libftdi1** installed and loadable
- Unix host (Linux or macOS)
- An FTDI device attached (example IDs: FT232RL `0x0403`/`0x6001`)

# Demo

```php
<?php

use Ftdi\FTDI;

$ftdi = FTDI::ftdiNew();
if ($ftdi->handle < 0) {
    throw new RuntimeException('ftdi_new failed');
}

FTDI::ftdiInit($ftdi);

// FT232RL default IDs: vendor 0x0403, product 0x6001
if (FTDI::ftdiUSBOpen($ftdi, 0x0403, 0x6001) !== 0) {
    throw new RuntimeException(FTDI::ftdiGetErrorString($ftdi));
}

FTDI::ftdiSetBaudrate($ftdi, 115200);
FTDI::ftdiSetLineProperty($ftdi, 8, 1, 0); // 8N1

FTDI::ftdiWriteData($ftdi, "hello\n", 6);
$response = FTDI::ftdiReadData($ftdi, 256);

FTDI::ftdiUSBClose($ftdi);
FTDI::ftdiDeinit($ftdi);
FTDI::ftdiFree($ftdi);
```

Grounded in README usage examples.[^readme][^ftdi-zep]

# Notes

- Replace line-property integers with platform-correct libftdi1 constants / enums — see [Constants outside](/conventions/constants-outside-ext.md).
- Optional ergonomics: `composer require microscrap/ftdi` for C-ish helpers (downstream only).
- For MPSSE-capable chips, see README bitmode examples and optional `microscrap/mpsse` — composition only.

[^readme]: README.md
[^ftdi-zep]: ftdi.zep
