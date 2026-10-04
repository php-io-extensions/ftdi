---
okf_version: "0.2"
---

# ext-ftdi

* [Module](architecture/module.md) - Scope, file layout, libftdi1/libusb linkage, undeclared libftdi exports, ZTS cache, class registration.
* [libftdi 1.5 guards](architecture/libftdi-1-5-guards.md) - Where libftdi 1.5 behaviour would crash, leak or mislead from PHP, and the binding code that prevents each case.

# API

* [Objects](api/objects.md) - FTDIContext, FTDIDevice, FTDITransferControl, FTDIVersionInfo, FTDIEeprom; ownership, the dependents registry, teardown order, live properties.
* [Functions](api/functions.md) - Every bound libftdi call by group, return conventions, out parameters, argument ranges, empty-string-as-NULL, what is not bound.
* [Async transfers and the libusb pump](api/async.md) - Submit, collect, cancel, completion; pumping libusb by timeout or by joining its poll descriptors to an event loop.
* [EEPROM](api/eeprom.md) - Reading, decoding, editing and writing the EEPROM image; the FTDIEeprom snapshot; string presence tracking; FT232H CBUS bytes.
* [Constants](api/constants.md) - Every ftdi.h enum member and numeric define as a header-valued constant, the two skipped, and keeping the list in step with libftdi.

# Runbooks

* [Build, install, test](runbooks/build.md) - libftdi1/libusb prerequisites, gen_stub after a stub edit, scratch builds, the two installers, Pest, FT232H smoke, PIE.

# Reference

* [Upgrade from 0.9](reference/upgrade-from-0-9.md) - Zephir ext-ftdi 0.9 plus microscrap/ftdi to C ext-ftdi 0.10, call by call.
