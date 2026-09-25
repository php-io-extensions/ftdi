# Traps

* [Windows excluded](windows-excluded.md) - PIE `os-families-exclude: windows`
* [Do not rebuild ext/ in place](do-not-rebuild-in-place.md) - Copy → build → sync → delete copy
* [No sudo pie from checkout](no-sudo-pie-from-checkout.md) - Root-owned files under `ext/`
* [IDE stub path lag](ide-stub-path-lag.md) - Stubs at `ide/0.9.0`; regenerate only with a version bump
* [libftdi1 required](libftdi1-required.md) - Compile + runtime dependency
* [Context free ownership](context-free-ownership.md) - PHP GC does not `ftdi_free`
* [Zephir and raw-C vars](zephir-narrows-raw-c-vars.md) - A var raw C writes must be Zephir-owned and start as a string, or it narrows or leaks
