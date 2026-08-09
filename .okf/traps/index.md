# Traps

* [Windows excluded](windows-excluded.md) - PIE `os-families-exclude: windows`
* [Do not rebuild ext/ in place](do-not-rebuild-in-place.md) - Copy → build → sync → delete copy
* [No sudo pie from checkout](no-sudo-pie-from-checkout.md) - Root-owned files under `ext/`
* [IDE stub path lag](ide-stub-path-lag.md) - `ide/0.2.0` lags behind 0.7.0
* [libftdi1 required](libftdi1-required.md) - Compile + runtime dependency
* [Context free ownership](context-free-ownership.md) - PHP GC does not `ftdi_free`
