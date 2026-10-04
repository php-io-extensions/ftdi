# Agent guidance — php-io-extensions/ftdi

1. **Read [`.okf/index.md`](.okf/index.md) first** before changing the API, the C, or packaging. Open only the concepts the change touches.
2. **libftdi1, 1:1.** One PHP function = one libftdi call under libftdi's name (four keep `microscrap/ftdi`'s spelling: `ftdi_tci_flush`, `ftdi_tco_flush`, `ftdi_tcio_flush`, `ftdi_read_chip_id`). No MPSSE helpers, no event loop, no throwing on negative libftdi codes. Composites belong in `microscrap/mpsse`. Never invent a function libftdi does not export.
3. **Plain C on the Zend API.** No Zephir, no FFI. Source: `ftdi.c`. Links libftdi1 ≥ 1.5 and libusb-1.0 ≥ 1.0.16 through pkg-config. See [`.okf/architecture/module.md`](.okf/architecture/module.md).
4. **Objects own the C pointers.** `FTDIContext`, `FTDIDevice`, `FTDITransferControl` are created only by functions, never cloned or serialised. A context cancels its pending transfers and unrefs its devices before any libusb teardown. Keep that order in every new function that closes, deinitialises or frees. See [`.okf/api/objects.md`](.okf/api/objects.md).
5. **No PHP call may crash, leak or report a stale error**, even where libftdi 1.5 would. Each guard is recorded in [`.okf/architecture/libftdi-1-5-guards.md`](.okf/architecture/libftdi-1-5-guards.md); a new one gets a row there, read from libftdi's source.
6. **The stub is the declaration.** Edit `ftdi.stub.php` (no `use` statements; fully qualify `\Ftdi\…`), regenerate `ftdi_arginfo.h` with gen_stub, commit both. Never hand-edit arginfo. See [`.okf/runbooks/build.md`](.okf/runbooks/build.md).
7. **Constants mirror `ftdi.h`.** Every enum member and numeric `#define`, as `@cvalue`, unprefixed. A name new in a later libftdi raises the `config.m4` floor and the installers' check together. See [`.okf/api/constants.md`](.okf/api/constants.md).
8. **Arguments are checked, never truncated.** Ranges from the C type or enum; sizes against the data; out of range → `ValueError` naming the argument. Failure without a value: null for objects, false for bytes.
9. **NTS and ZTS.** No module globals; `ZEND_TSRMLS_CACHE_UPDATE()` in MINIT and RINIT. Every change builds and passes Pest under Homebrew `php@8.4` and `php@8.4-zts` (`php84`, `zhp`) and on Linux (the Pi via `fnk`).
10. **Tests are Pest v4 and need no device.** FT232H checks are scratch scripts run by hand, never committed, never in `tests/`. Tests never write EEPROM.
11. **Durable facts go in `.okf`.** Update the matching concept, bump its `generated.at`, append `.okf/log.md`. The bundle documents the package, never a session, and lives at the repo root only.
12. **Versions**: `composer.json` `version` and `PHP_FTDI_VERSION` move together, and only past a published tag.
