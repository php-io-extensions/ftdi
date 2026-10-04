# ext-ftdi

[![Latest Version on Packagist](https://img.shields.io/packagist/v/php-io-extensions/ftdi.svg)](https://packagist.org/packages/php-io-extensions/ftdi)
[![License](https://img.shields.io/packagist/l/php-io-extensions/ftdi.svg)](LICENSE)

[libftdi1](https://www.intra2net.com/en/developer/libftdi/) for PHP, written in C against the Zend API: FTDI USB chips such as the FT232H, FT2232H and FT232R, their MPSSE engine for I2C, SPI and GPIO, asynchronous transfers driven by libusb's event pump, and EEPROM access.

An FTDI board turns any laptop into a hardware bench: one USB cable gives you a UART, or an MPSSE engine that clocks I2C and SPI and drives GPIO pins. ext-ftdi binds libftdi one to one under libftdi's own function names, so the C examples and documentation apply unchanged, and adds PHP objects that own the C pointers, so a PHP program cannot free a context twice or touch memory libusb has already released.

```
ext-ftdi                        libftdi1 calls, 1:1                    ← this package
  → microscrap/mpsse            MPSSE I2C, SPI and GPIO in PHP
    → microscrap/scrapyard-usb  the `usb` driver
      → scrapyard-io/framework  protocol managers, transports, circuits
```

## Requirements

- PHP 8.4 or newer, NTS or ZTS
- Linux or macOS
- libftdi1 1.5 or newer and libusb-1.0 1.0.16 or newer, with their headers, found through `pkg-config`:
  - macOS: `brew install libftdi pkg-config`
  - Debian, Raspberry Pi OS, Ubuntu: `sudo apt install libftdi1-dev pkg-config`
- Read-write access to the USB device. On Linux, run as root or add a udev rule such as `SUBSYSTEM=="usb", ATTR{idVendor}=="0403", MODE="0660", GROUP="plugdev"` and join that group. libftdi detaches the kernel's `ftdi_sio` serial driver from the interface it opens.

## Installation

With [PIE](https://github.com/php/pie):

```bash
pie install php-io-extensions/ftdi
```

From a checkout, with the bundled installers. Each one checks for libftdi1 and libusb, builds in a disposable copy, installs `ftdi.so` into the PHP's `extension_dir`, writes `30-ftdi.ini` into its conf.d directory, and checks that the extension loads:

```bash
./install-macos.sh                     # Homebrew php@8.4 and php@8.4-zts
./install-debian-trixie.sh             # the php on PATH: Debian trixie, Raspberry Pi OS, Ubuntu 24.04+
./install-macos.sh /path/to/bin/php    # either script takes specific PHP binaries
```

By hand:

```bash
phpize && ./configure --enable-ftdi && make && make install
echo 'extension=ftdi' > "$(php -r 'echo PHP_CONFIG_FILE_SCAN_DIR;')/30-ftdi.ini"
```

## Usage

### List attached devices

```php
use Ftdi\FtdiProductId;
use Ftdi\FtdiVendorId;

$ftdi = ftdi_new() ?? throw new RuntimeException('ftdi_new() failed');

$found = ftdi_usb_find_all($ftdi, FtdiVendorId::FTDI->value, FtdiProductId::FT232H->value);

foreach ($found['devices'] as $device) {
    $strings = ftdi_usb_get_strings($ftdi, $device);
    printf("%s, serial %s\n", $strings['description'], $strings['serial']);
}
```

### Talk to the MPSSE engine

Open an FT232H, switch it to MPSSE, and read the eight ADBUS pins with the `GET_BITS_LOW` opcode:

```php
$ftdi = ftdi_new() ?? throw new RuntimeException('ftdi_new() failed');

if (ftdi_usb_open($ftdi, FtdiVendorId::FTDI->value, FtdiProductId::FT232H->value) < 0) {
    throw new RuntimeException(ftdi_get_error_string($ftdi));
}

ftdi_usb_reset($ftdi);
ftdi_set_bitmode($ftdi, 0x00, BITMODE_RESET);
ftdi_set_bitmode($ftdi, 0x00, BITMODE_MPSSE);
ftdi_tcio_flush($ftdi);

// SEND_IMMEDIATE makes the chip answer now instead of when its buffer fills.
ftdi_write_data($ftdi, chr(GET_BITS_LOW) . chr(SEND_IMMEDIATE), 2);

$reply = '';
while (strlen($reply) < 1) {
    $chunk = ftdi_read_data($ftdi, 1);      // "" until the answer arrives
    if ($chunk === false) {
        throw new RuntimeException(ftdi_get_error_string($ftdi));
    }
    $reply .= $chunk;
}
printf("ADBUS 0b%08b\n", ord($reply));
```

### Submit transfers and pump libusb

The submit functions return at once with an `FTDITransferControl`. libusb completes the transfer while its events are handled, either by calling `ftdi_handle_events_timeout()` or by adding the descriptors from `ftdi_get_pollfds()` to your own event loop:

```php
$tx = ftdi_write_data_submit($ftdi, chr(GET_BITS_LOW) . chr(SEND_IMMEDIATE), 2)
    ?? throw new RuntimeException(ftdi_get_error_string($ftdi));
$rx = ftdi_read_data_submit($ftdi, 1)
    ?? throw new RuntimeException(ftdi_get_error_string($ftdi));

while (! ftdi_transfer_completed($rx)) {
    ftdi_handle_events_timeout($ftdi, 10_000);      // microseconds
}

$written = ftdi_transfer_data_done($tx);            // 2
$pins = ftdi_transfer_read_done($rx);               // the byte read

ftdi_usb_close($ftdi);
ftdi_free($ftdi);
```

## Objects

| Class | Wraps | Lifetime |
|---|---|---|
| `Ftdi\FTDIContext` | `struct ftdi_context *` | Created by `ftdi_new()`; released by `ftdi_free()` or garbage collection. Its read-only properties read the struct live: `chipType`, `usbReadTimeout`, `usbWriteTimeout`, `interfaceIndex`, `baudrate`, `bitbangEnabled`, `bitbangMode`, `channel`, `inEndpoint`, `outEndpoint`, `readBufferChunkSize`, `writeBufferChunkSize`, `maxPacketSize`, `moduleDetachMode`, `errorStr`. `toArray()` returns them all. |
| `Ftdi\FTDIDevice` | `struct libusb_device *`, referenced | Listed by `ftdi_usb_find_all()`; usable with the context that found it until that context is deinitialised. |
| `Ftdi\FTDITransferControl` | `struct ftdi_transfer_control *` and its buffer | Returned by `ftdi_write_data_submit()` and `ftdi_read_data_submit()`; owns the buffer until the transfer is collected or cancelled. Live read-only `completed`, `size`, `offset`, and `toArray()`. |
| `Ftdi\FTDIVersionInfo` | `struct ftdi_version_info` | Readonly snapshot: `major`, `minor`, `micro`, `versionStr`, `snapshotStr`. |
| `Ftdi\FTDIEeprom` | the context's EEPROM image | Readonly snapshot from `ftdi_get_eeprom()`: every `enum ftdi_eeprom_value` as a camelCase int, `vendorId` through `userDataAddr`, 0 where the chip has no such value, plus `manufacturer`, `product` and `serial`. Meaningful after `ftdi_read_eeprom()` and `ftdi_eeprom_decode()`. |

None of them can be created with `new`, cloned or serialised.

A context keeps track of the transfers and devices made from it, so nothing ever reaches freed libusb memory:

- `ftdi_usb_close()`, `ftdi_deinit()`, `ftdi_free()`, `ftdi_init()` over an initialised context, and the context's release all cancel its pending transfers first.
- `ftdi_deinit()`, `ftdi_free()` and the context's release also drop its device references before libusb shuts down.
- A transfer object released while its transfer is pending cancels the transfer.

## Functions

The names are libftdi's. Four are spelt as `microscrap/ftdi` exported them: `ftdi_tci_flush`, `ftdi_tco_flush`, `ftdi_tcio_flush` and `ftdi_read_chip_id`.

| Group | Functions |
|---|---|
| Context | `ftdi_new(): ?FTDIContext`, `ftdi_init`, `ftdi_deinit`, `ftdi_free`, `ftdi_set_interface`, `ftdi_get_library_version(): FTDIVersionInfo`, `ftdi_get_error_string` |
| Devices | `ftdi_usb_find_all(ctx, vendor, product): array{count, devices: list<FTDIDevice>}`, `ftdi_usb_get_strings` / `ftdi_usb_get_strings2(ctx, device): array{result, manufacturer, description, serial}`, `ftdi_usb_open_dev`, `ftdi_usb_open`, `ftdi_usb_open_desc`, `ftdi_usb_open_desc_index`, `ftdi_usb_open_bus_addr`, `ftdi_usb_open_string`, `ftdi_usb_close`, `ftdi_usb_reset` |
| Flushes | `ftdi_tci_flush`, `ftdi_tco_flush`, `ftdi_tcio_flush`, and the `ftdi_usb_purge_*` calls that ftdi.h deprecates |
| Line | `ftdi_convert_baudrate_ut_export(baud, ctx): array{result, value, index}`, `ftdi_set_baudrate`, `ftdi_set_line_property`, `ftdi_set_line_property2`, `ftdi_set_bitmode`, `ftdi_disable_bitbang`, `ftdi_read_pins`, `ftdi_set_latency_timer`, `ftdi_get_latency_timer`, `ftdi_set_timeouts`, `ftdi_poll_modem_status`, `ftdi_setflowctrl`, `ftdi_setflowctrl_xonxoff`, `ftdi_setdtr`, `ftdi_setrts`, `ftdi_setdtr_rts`, `ftdi_set_event_char`, `ftdi_set_error_char` |
| Synchronous data | `ftdi_write_data(ctx, data, size): int`, `ftdi_read_data(ctx, size): string\|false`, `ftdi_write_data_set_chunksize`, `ftdi_write_data_get_chunksize`, `ftdi_read_data_set_chunksize`, `ftdi_read_data_get_chunksize` |
| Asynchronous data | `ftdi_write_data_submit(ctx, data, size)` and `ftdi_read_data_submit(ctx, size): ?FTDITransferControl`, `ftdi_transfer_data_done(tc): int`, `ftdi_transfer_read_done(tc): string\|false`, `ftdi_transfer_data_cancel`, `ftdi_transfer_completed` |
| libusb event pump | `ftdi_get_pollfds(ctx): list<array{fd, events}>`, `ftdi_pollfds_handle_timeouts`, `ftdi_get_next_timeout(ctx): array{result, usec}`, `ftdi_handle_events_timeout(ctx, timeout_us)` |
| EEPROM | `ftdi_get_eeprom(ctx): FTDIEeprom`, `ftdi_eeprom_initdefaults`, `ftdi_eeprom_set_strings`, `ftdi_eeprom_get_strings`, `ftdi_eeprom_build`, `ftdi_eeprom_decode`, `ftdi_get_eeprom_value`, `ftdi_set_eeprom_value`, `ftdi_get_eeprom_buf(ctx, size): string\|false`, `ftdi_set_eeprom_buf`, `ftdi_set_eeprom_user_data`, `ftdi_set_ft232h_cbus(ctx): string`, `ftdi_read_eeprom_location`, `ftdi_read_eeprom`, `ftdi_read_chip_id(ctx, &chip_id)`, `ftdi_write_eeprom_location`, `ftdi_write_eeprom`, `ftdi_erase_eeprom` |

## Behaviour

- **Return codes** are libftdi's. `ftdi_get_error_string()` explains a negative one.
- **Out parameters**: a call that reads one value through a C out parameter returns that value, or the negative code on failure. These are `ftdi_read_pins`, `ftdi_get_latency_timer`, `ftdi_poll_modem_status`, the chunk size getters, `ftdi_get_eeprom_value` and `ftdi_read_eeprom_location`.
- **Arguments** are checked against the C type: bytes 0–255, vendor and product IDs 0–0xFFFF, sizes within the data given, enum arguments within the enum. Anything outside throws `ValueError` instead of being truncated.
- **Failure without a value** is null where an object is returned (`ftdi_new()` and the two submit functions) and false where bytes are returned (`ftdi_read_data`, `ftdi_transfer_read_done`, `ftdi_get_eeprom_buf`).
- **Misuse** throws `Error`: calling into a context that `ftdi_free()` released (a second `ftdi_free()` does nothing), calling into a deinitialised context before `ftdi_init()`, or passing a device from another context or from before a deinit.
- **Transfers**:
  - With no device open, the submit functions return null and set the error string to "USB device unavailable", as libftdi's synchronous calls do. libftdi 1.5's submit functions return NULL there without setting any error string.
  - `ftdi_transfer_data_done()` and `ftdi_transfer_read_done()` wait for the transfer, free it, and return the bytes moved. Called again on a transfer that was already collected or cancelled, they return -1 and false.
  - Cancelling a transfer that was already collected or cancelled does nothing.
- **Re-initialising**: `ftdi_init()` over an initialised context deinitialises it first. Plain libftdi would leak the old libusb context.
- **EEPROM strings**: libftdi 1.5's `ftdi_eeprom_get_strings()` copies each string without a NULL check, and a fresh context, `ftdi_eeprom_initdefaults()` or `ftdi_eeprom_decode()` can leave any of the three NULL. The context records which strings libftdi holds and asks only for those; the others come back as "".
- **Not bound**: `ftdi_list_free` and `ftdi_list_free2`, because `ftdi_usb_find_all()` frees the list itself and each `FTDIDevice` holds its own libusb reference; and `ftdi_set_usbdev`, because PHP has no way to obtain a libusb device handle.

## Constants

Every member of every enum in `ftdi.h`, under libftdi's own unprefixed names:

| Enum | Constants |
|---|---|
| chip and line | `TYPE_*`, `NONE`, `ODD`, `EVEN`, `MARK`, `SPACE`, `STOP_BIT_*`, `BITS_*`, `BREAK_*` |
| modes | `BITMODE_*`, `INTERFACE_*`, `AUTO_DETACH_SIO_MODULE`, `DONT_DETACH_SIO_MODULE`, `AUTO_DETACH_REATACH_SIO_MODULE` |
| EEPROM | the `enum ftdi_eeprom_value` names (`VENDOR_ID` … `USER_DATA_ADDR`), `CBUS_*`, `CBUSH_*`, `CBUSX_*` |

And every numeric `#define` in `ftdi.h`:

| Group | Constants |
|---|---|
| MPSSE opcodes and flags | `MPSSE_*`, `SET_BITS_LOW`, `SET_BITS_HIGH`, `GET_BITS_LOW`, `GET_BITS_HIGH`, `TCK_DIVISOR`, `SEND_IMMEDIATE`, `WAIT_ON_HIGH`, `WAIT_ON_LOW`, … |
| control requests and flags | `SIO_*`, `FTDI_DEVICE_OUT_REQTYPE`, `FTDI_DEVICE_IN_REQTYPE` |
| EEPROM bits | `INVERT_*`, `CHANNEL_IS_*`, `DRIVE_*`, … |

`SIO_RESET_PURGE_RX` and `SIO_RESET_PURGE_TX` are left out: ftdi.h deprecates them with a compile warning in favour of `SIO_TCIFLUSH` and `SIO_TCOFLUSH`.

Enums: `Ftdi\FtdiVendorId::FTDI` (0x0403) and `Ftdi\FtdiProductId::{FT232R, FT2232H, FT4232H, FT232H, FT230X, FT4232HP, FT4232HA}`.

## Upgrading from 0.9

0.10 is a rewrite in C that replaces the Zephir ext-ftdi 0.9 and absorbs `microscrap/ftdi`. Remove `microscrap/ftdi` from your `composer.json`: its functions and enums now come from the extension.

| 0.9 | 0.10 |
|---|---|
| `Ftdi\FTDI::ftdiNew()`, `FTDI::ftdiUSBOpen(...)` and the other statics | `ftdi_new()`, `ftdi_usb_open(...)` and the other libftdi names |
| `$context->handle <= 0` after `ftdiNew()` | `ftdi_new() === null` |
| `$tc->handle === 0` after a submit | the submit returned null |
| `ftdi_read_data()` and `ftdi_get_eeprom_buf()` returned `""` on error | they return false |
| `ftdi_usb_find_all()` returned `['count', 'listHandle']` and devices as ints | `['count', 'devices' => list<FTDIDevice>]` |
| `FTDI::setFT232HCbus(FTDIEeprom)` | `ftdi_set_ft232h_cbus(FTDIContext)` |
| `Microscrap\Bindings\FTDI\Enums\FtdiVendorId`, `FtdiProductId` | `Ftdi\FtdiVendorId`, `Ftdi\FtdiProductId` |
| `handle`, `contextHandle`, `bufHandle`, `eepromHandle` properties | gone: the objects own their pointers |
| out-of-range sizes clamped | `ValueError` |

## Testing

```bash
composer install
php -d extension=/path/to/modules/ftdi.so vendor/bin/pest
```

The suite needs no FTDI device attached.

## Security

ext-ftdi gives PHP code raw access to USB devices it can open, including writing their EEPROM. See [SECURITY.md](SECURITY.md) for what that means and how to report a vulnerability.

## License

MIT. See [LICENSE](LICENSE).
