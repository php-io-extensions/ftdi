# Log

## 2026-10-12

* **Version**: 0.10.5 in `composer.json` and `PHP_FTDI_VERSION`. No API change. Steps past 0.10.1 through 0.10.4 to line up with the sibling extensions.
* **README**: rewritten on the php-io-extensions template (header badges, two-part basic usage, requirements table, PIE / install script / phpize install paths, API, OKF section, suite run). Suite count (12 passed, 85 assertions) run against a scratch build on Homebrew PHP 8.4 NTS, libftdi1 1.5.

## 2026-10-09

* `extra.venusian.system` in composer.json: the apt packages `venusian build` installs to compile the extension, the run-time packages a `.deb` carrying it depends on or recommends beyond what `dpkg-shlibdeps` sees, and the Homebrew packages for a dev install.

## 2026-10-04

* **Creation**: Bundle created for ext-ftdi 0.10.0, the plain-C rewrite: [module](/architecture/module.md), [libftdi 1.5 guards](/architecture/libftdi-1-5-guards.md), [objects](/api/objects.md), [functions](/api/functions.md), [async](/api/async.md), [EEPROM](/api/eeprom.md), [constants](/api/constants.md), [build](/runbooks/build.md), [upgrade from 0.9](/reference/upgrade-from-0-9.md).
* **Update**: libftdi1 floor raised to 1.5 in `config.m4` and both installers; 1.4 lacks bound functions and constants. [module](/architecture/module.md)
