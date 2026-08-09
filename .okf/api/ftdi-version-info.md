---
type: API
title: Ftdi\\FTDIVersionInfo
description: Library version DTO from ftdiGetLibraryVersion + toArray()
resource: /ftdi/ftdiversioninfo.zep
tags: [ftdi, api, FTDIVersionInfo]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: ver-zep
    resource: /ftdi/ftdiversioninfo.zep
    title: ftdiversioninfo.zep
  - id: ftdi-zep
    resource: /ftdi/ftdi.zep
    title: ftdi.zep
---

# Class

`Ftdi\FTDIVersionInfo` — DTO for libftdi1 library version. Populated by `FTDI::ftdiGetLibraryVersion()` (no device open required).[^ver-zep][^ftdi-zep]

# Fields

| Property | Role |
|----------|------|
| `major` / `minor` / `micro` | Version numbers |
| `versionStr` | Human-readable string (e.g. `"1.5"`) |
| `snapshotStr` | Snapshot/build id (empty for releases) |

# Methods

| Method | Notes |
|--------|-------|
| `toArray()` | Associative array of the fields above |

No other methods on this class.

[^ver-zep]: ftdiversioninfo.zep
[^ftdi-zep]: ftdi.zep
