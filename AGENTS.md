# Agent guidance — php-io-extensions/ftdi

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing architecture, API, or packaging.
2. Open only the concept files you need; prefer `status: stable` when present (most are currently `draft`).
3. This package is **Linux + macOS** libftdi1 bindings — Windows excluded. No FFI. Requires **libftdi1** at compile and runtime (`pkg-config libftdi1`; brew `libftdi`; debian `libftdi1-dev`).
4. Public PHP API: namespace `Ftdi\` — static `FTDI` plus companion DTOs `FTDIContext`, `FTDIEeprom`, `FTDITransferControl`, `FTDIVersionInfo`. Zephir sources: `ftdi/{ftdi,ftdicontext,ftdieeprom,ftditransfercontrol,ftdiversioninfo}.zep`. Thin C helper: `src/ftdi-eeprom.{c,h}`.
5. **Do not invent APIs** not present as implemented methods in `.zep` / `src/ftdi-eeprom.h` / README. Opaque context objects use `handle` ints — not flat POSIX FDs like posi.
6. **Constants** (`INTERFACE_*`, `BITMODE_*`, `FLOW_*`, vendor/product IDs, …) live **outside** the extension (app locals or microscrap enums) — same convention as posi/sdl3.
7. **Never rebuild ship-ready `ext/` in place.** The committed `ext/` is PIE/consumer build input. To regenerate after Zephir changes: copy the tree → run the installer / Zephir build in the **copy** → sync only intentional artifacts back → delete the copy. See [`.okf/playbooks/regenerate-ext.md`](.okf/playbooks/regenerate-ext.md) and [`.okf/traps/do-not-rebuild-in-place.md`](.okf/traps/do-not-rebuild-in-place.md). Do **not** run zephir/phpize/make/`pie install` in the primary checkout just to “refresh” `ext/`.
8. **Do not `sudo pie install` from a development checkout** — root-owned files under `ext/` break later builds. Use `pie install` (prompts for the final install step) or the platform install scripts.
9. Build/install for local use: `install-macos.sh`, `install-debian-trixie.sh`, or `pie install php-io-extensions/ftdi` (consumers). Prefer working on a disposable copy when the install path regenerates C. PIE/`phpize` from committed `ext/` must work without Zephir.
10. Downstream: `microscrap/ftdi` (global helpers) and `microscrap/mpsse` are **peers** — document composition only; not dependencies of this extension. Optional MPSSE workflows need a separate **mpsse** install.
11. When you learn a durable package fact, **update the matching `.okf` concept**, bump `generated.at`, and append `.okf/log.md`.
12. Keep the OKF bundle at package root only — never nest `.okf` under `ftdi/` or `src/`.
