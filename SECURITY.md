# Security Policy

## Supported versions

ext-ftdi is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in the
next release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/ftdi](https://github.com/php-io-extensions/ftdi) repository's **Security** tab.
If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform, PHP build (NTS or ZTS) and libftdi1
version (`php --ri ftdi` shows it), and steps to reproduce. Reports are read and weighed for the
release line in development; before 1.0 there is no response-time commitment.

A defect in libftdi1 or libusb itself belongs with those projects. Report it here as well when
ext-ftdi should guard against it, as it already does for libftdi 1.5's copy from a NULL string in
`ftdi_eeprom_get_strings()` and its leak of the old libusb context when `ftdi_init()` runs over an
initialised context.

## Security model

ext-ftdi binds libftdi1 one to one. Each function performs the libftdi call with the privileges
of the PHP process, the same as C code linked into that process. Load it only where every PHP
script the process runs is trusted, such as a CLI program driving hardware. Do not load it into a
shared web host.

- **Device access.** Any FTDI device the process may open can be opened, reconfigured, reset, and
  driven through its pins. On Linux, opening a device detaches the kernel's `ftdi_sio` driver from
  that interface. Grant USB access through a udev rule scoped to the devices and group that need
  it, not by running PHP as root.
- **EEPROM.** `ftdi_write_eeprom()`, `ftdi_write_eeprom_location()`, `ftdi_erase_eeprom()` and
  `ftdi_set_eeprom_buf()` followed by a write change the chip's stored configuration, including
  its USB IDs. A wrong image can leave a device that no longer enumerates as an FTDI part until it
  is reprogrammed. Restrict them with `disable_functions` where a program has no need to write
  EEPROM.
- **Memory ownership.** Contexts, devices and transfers are PHP objects that own their C pointers.
  They cannot be created with `new`, cloned or serialised. A context cancels its pending transfers
  and drops its device references before libusb state goes away, and calls on a released or
  deinitialised context throw `Error`, so no PHP call reaches freed libusb memory.
- **Arguments.** Every argument is checked against its C type: bytes, USB IDs, sizes against the
  data given, enum values against the enum. Out-of-range values throw `ValueError`; nothing is
  truncated into a different value.

A report is in scope when ext-ftdi itself reads or writes memory it should not: a size check that
can be bypassed, a transfer or device outliving the libusb state it points at, a crash reachable
from well-formed PHP arguments. Effects of a valid libftdi call the script asked for, such as
reprogramming an EEPROM, are the documented behaviour.
