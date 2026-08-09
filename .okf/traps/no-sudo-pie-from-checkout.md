---
type: Trap
title: No sudo pie from checkout
description: sudo pie install from a development checkout can leave root-owned files under ext/
resource: /README.md
tags: [ftdi, trap, pie, permissions]
status: draft
generated: { by: okf-documentation-generator/cursor-grok-4.5, at: "2026-08-09T18:02:00Z" }
sources:
  - id: readme
    resource: /README.md
    title: README.md
---

# Trap

README warns: do **not** run `sudo pie install` from a development checkout — that can leave **root-owned files under `ext/`** and break later builds.[^readme]

# Do

- Run `pie install` as your user (it prompts only for the final privileged install step), or
- Use `install-macos.sh` / `install-debian-trixie.sh`, or
- Work on a disposable **copy** when regenerating C (see [Regenerate ext](/playbooks/regenerate-ext.md)).

# Do not

- `sudo pie install` inside the primary package checkout.
- Chown-fix root-owned `ext/` as a substitute for the correct install path.

[^readme]: README.md
