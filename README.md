# Ftdi - The FTDI extension for direct libftdi1 bindings.

This project provides direct bindings to [libftdi1](https://www.intra2net.com/en/developer/libftdi/).

Extension repository: [https://github.com/php-io-extensions/ftdi](https://github.com/php-io-extensions/ftdi)

## Highlights

* Direct access to libftdi1 functions from PHP
* Support for serial-only devices (such as FT232RL) and MPSSE-capable devices (such as FT232H)
* USB open/read/write/flush/reset operations
* EEPROM read/write/decode/build operations
* Asynchronous transfer submission and completion

## Requirements

* PHP 8.3+
* **libftdi1** — required at compile and runtime
  * Debian/Ubuntu/Raspberry Pi OS: `libftdi1-dev` (runtime: `libftdi1-2`)
  * macOS: `brew install libftdi`
* If your intended workflow includes MPSSE device usage, install **mpsse** as well

## Compilation Requirements

* A C language toolchain
* **libftdi1** development headers and pkg-config metadata (see Requirements)

* Manual installation
  * Zephir PHP
  * ext-zephir_parser

* Automated installation
  * PIE

## Manual compilation instructions

### Zephir

* Clone this repository and checkout the release to use (or master for the latest updates)
* `cd ftdi`
* Install **libftdi1** if it is not already present (see Requirements)
* This extension is intended to be used with MPSSE-capable devices (for example FT232H) and serial-only devices (for example FT232RL)
* If MPSSE is intended, install **mpsse** as well
* The installers include procedures to do this for you. However, if they are already installed, using PIE is easiest.
* Run the installer for your platform
  * Raspberry Pi / Debian Trixie: `bash install-debian-trixie.sh`
  * macOS: `bash install-macos.sh`

### PIE

If dependencies are already installed, using PIE is the easiest path:

* Clone this repository and checkout the release to use (or master for the latest updates)
* `cd ftdi`
* `pie install`

Do **not** run `sudo pie install` from a development checkout — that can leave root-owned files under `ext/` and break later builds. Use `pie install` (it prompts only for the final install step) or the platform install scripts above.

## Automated compilation instructions

* Ensure **libftdi1** is installed first
* If MPSSE usage is intended, ensure **mpsse** is installed as well
* `pie install php-io-extensions/ftdi`
* PIE should compile the extension and place it where your default PHP binary expects extensions
* If PIE does not automatically enable the extension, add it to your `php.ini`:

  ```ini
  extension=ftdi
  ```

Confirm the module is loaded:

```bash
php -m | grep ftdi
```

## Usage

FTDI bindings are invoked through the `Ftdi\FTDI` class. All methods are static.

```php
<?php

use Ftdi\FTDI;

$ftdi = FTDI::ftdiNew();
if ($ftdi->handle < 0) {
    throw new RuntimeException('ftdi_new failed');
}

FTDI::ftdiInit($ftdi);

// FT232RL default IDs: vendor 0x0403, product 0x6001
if (FTDI::ftdiUSBOpen($ftdi, 0x0403, 0x6001) !== 0) {
    throw new RuntimeException(FTDI::ftdiGetErrorString($ftdi));
}

FTDI::ftdiSetBaudrate($ftdi, 115200);
FTDI::ftdiSetLineProperty($ftdi, 8, 1, 0); // 8N1

FTDI::ftdiWriteData($ftdi, "hello\n", 6);
$response = FTDI::ftdiReadData($ftdi, 256);

FTDI::ftdiUSBClose($ftdi);
FTDI::ftdiDeinit($ftdi);
FTDI::ftdiFree($ftdi);
```

Constants and enum values follow libftdi1 conventions. Define them in PHP or load them from your platform headers.

### C-ish global helper style

This extension can also be used in a C-ish style through global helper methods by installing [`microscrap/ftdi`](https://github.com/microscrap/ftdi).

```bash
composer require microscrap/ftdi
```

If you want to utilize MPSSE, install [`microscrap/mpsse`](https://github.com/microscrap/mpsse) instead:

```bash
composer require microscrap/mpsse
```

`microscrap/mpsse` also installs `microscrap/ftdi`.

You can also roll your own helper layer, or use this extension directly without helper packages.

---

## Static Methods API

### `FTDI::ftdiNew(): FTDIContext`

Allocates a new libftdi1 context via `ftdi_new()` and returns a hydrated `FTDIContext`. Check `handle >= 0` before use; `-1` means allocation failed.

**Example**

```php
<?php

use Ftdi\FTDI;

$ftdi = FTDI::ftdiNew();

if ($ftdi->handle < 0) {
    throw new RuntimeException($ftdi->errorStr);
}
```

---

### `FTDI::ftdiInit(FTDIContext $ftdi): int`

Initialises an allocated context (`ftdi_init`). Returns `0` on success, non-zero on failure (libftdi1 error code).

**Example**

```php
<?php

use Ftdi\FTDI;

$ftdi = FTDI::ftdiNew();
if (FTDI::ftdiInit($ftdi) !== 0) {
    throw new RuntimeException(FTDI::ftdiGetErrorString($ftdi));
}
```

---

### `FTDI::ftdiSetInterface(FTDIContext $ftdi, int $iface): int`

Selects the interface channel on multi-port chips (`ftdi_set_interface`). Use libftdi1 `INTERFACE_*` constants (`INTERFACE_ANY`, `INTERFACE_A`, `INTERFACE_B`, …). Returns `0` on success.

---

### `FTDI::ftdiDeinit(FTDIContext $ftdi): void`

Deinitialises a context (`ftdi_deinit`) without freeing it. Call before `ftdiFree()` when you are done with a device session.

---

### `FTDI::ftdiFree(FTDIContext $ftdi): void`

Frees the libftdi1 context (`ftdi_free`). Do not use the `FTDIContext` after this call.

**Example**

```php
<?php

use Ftdi\FTDI;

FTDI::ftdiUSBClose($ftdi);
FTDI::ftdiDeinit($ftdi);
FTDI::ftdiFree($ftdi);
```

---

### `FTDI::ftdiSetUSBDev(FTDIContext $ftdi, int $usbDevHandle): void`

Attaches an existing libusb device handle (opaque integer) to the context (`ftdi_set_usbdev`).

---

### `FTDI::ftdiGetLibraryVersion(): FTDIVersionInfo`

Returns libftdi1 version information without opening a device (`ftdi_get_library_version`).

**Example**

```php
<?php

use Ftdi\FTDI;

$vi = FTDI::ftdiGetLibraryVersion();
echo $vi->versionStr; // e.g. "1.5"
```

---

### `FTDI::ftdiUSBFindAll(FTDIContext $ftdi, int $vendor, int $product): array`

Enumerates matching USB devices (`ftdi_usb_find_all`). Returns:

* `count` — number of devices found (or negative error code)
* `listHandle` — opaque pointer to the device list; pass to `ftdiListFree()` or `ftdiListFree2()`

**Example**

```php
<?php

use Ftdi\FTDI;

$found = FTDI::ftdiUSBFindAll($ftdi, 0x0403, 0x6014);
if ($found['count'] > 0 && $found['listHandle'] !== 0) {
    FTDI::ftdiListFree($found['listHandle']);
}
```

---

### `FTDI::ftdiListFree(int $listHandle): void`

Frees a device list allocated by `ftdi_usb_find_all` (`ftdi_list_free`).

---

### `FTDI::ftdiListFree2(int $listHandle): void`

Alternative list free (`ftdi_list_free2`).

---

### `FTDI::ftdiUSBGetStrings(FTDIContext $ftdi, int $devHandle): array`

Reads USB string descriptors for a device (`ftdi_usb_get_strings`). Returns `manufacturer`, `description`, and `serial` strings. `$devHandle` is an opaque `libusb_device` pointer.

---

### `FTDI::ftdiUSBGetStrings2(FTDIContext $ftdi, int $devHandle): array`

Same as `ftdiUSBGetStrings`, using `ftdi_usb_get_strings2`.

---

### `FTDI::ftdiUSBOpenDev(FTDIContext $ftdi, int $devHandle): int`

Opens a specific USB device by opaque handle (`ftdi_usb_open_dev`). Returns `0` on success.

---

### `FTDI::ftdiUSBOpen(FTDIContext $ftdi, int $vendor, int $product): int`

Opens the first device matching vendor and product IDs (`ftdi_usb_open`). Returns `0` on success.

**Example — FT232H**

```php
<?php

use Ftdi\FTDI;

if (FTDI::ftdiUSBOpen($ftdi, 0x0403, 0x6014) !== 0) {
    throw new RuntimeException(FTDI::ftdiGetErrorString($ftdi));
}
```

---

### `FTDI::ftdiUSBOpenDesc(FTDIContext $ftdi, int $vendor, int $product, mixed $description, mixed $serial): int`

Opens a device matching vendor/product and optional description/serial strings (`ftdi_usb_open_desc`). Pass empty strings to skip a filter.

---

### `FTDI::ftdiUSBOpenDescIndex(FTDIContext $ftdi, int $vendor, int $product, mixed $description, mixed $serial, int $index): int`

Like `ftdiUSBOpenDesc`, but selects the Nth matching device (`ftdi_usb_open_desc_index`).

---

### `FTDI::ftdiUSBOpenBusAddr(FTDIContext $ftdi, int $bus, int $addr): int`

Opens a device by USB bus and address (`ftdi_usb_open_bus_addr`).

---

### `FTDI::ftdiUSBOpenString(FTDIContext $ftdi, mixed $description): int`

Opens a device by its USB description string (`ftdi_usb_open_string`).

---

### `FTDI::ftdiUSBClose(FTDIContext $ftdi): int`

Closes the USB connection (`ftdi_usb_close`). Returns `0` on success.

---

### `FTDI::ftdiUSBReset(FTDIContext $ftdi): int`

Sends a USB reset to the device (`ftdi_usb_reset`).

---

### `FTDI::ftdiTCIFlush(FTDIContext $ftdi): int`

Flushes the input buffer (`ftdi_tciflush`).

---

### `FTDI::ftdiTCOFlush(FTDIContext $ftdi): int`

Flushes the output buffer (`ftdi_tcoflush`).

---

### `FTDI::ftdiTCIOFlush(FTDIContext $ftdi): int`

Flushes both directions (`ftdi_tcioflush`).

---

### `FTDI::ftdiUSBPurgeRXBuffer(FTDIContext $ftdi): int`

Purges the device RX buffer (`ftdi_usb_purge_rx_buffer`).

---

### `FTDI::ftdiUSBPurgeTXBuffer(FTDIContext $ftdi): int`

Purges the device TX buffer (`ftdi_usb_purge_tx_buffer`).

---

### `FTDI::ftdiUSBPurgeBuffers(FTDIContext $ftdi): int`

Purges both RX and TX buffers (`ftdi_usb_purge_buffers`).

---

### `FTDI::ftdiConvertBaudrateUTExport(int $baudrate, FTDIContext $ftdi): array`

Wraps `convert_baudrate_UT_export` and returns `value` and `index`.

---

### `FTDI::ftdiSetBaudrate(FTDIContext $ftdi, int $baudrate): int`

Sets the UART baud rate (`ftdi_set_baudrate`). Returns `0` on success.

**Example**

```php
<?php

use Ftdi\FTDI;

FTDI::ftdiSetBaudrate($ftdi, 115200);
```

---

### `FTDI::ftdiSetLineProperty(FTDIContext $ftdi, int $bits, int $sbit, int $parity): int`

Sets data bits, stop bits, and parity (`ftdi_set_line_property`). Use libftdi1 `BITS_*`, `STOP_BIT_*`, and `PARITY_*` constants.

**Example — 8 data bits, 1 stop bit, no parity**

```php
<?php

use Ftdi\FTDI;

FTDI::ftdiSetLineProperty($ftdi, 8, 1, 0);
```

---

### `FTDI::ftdiSetLineProperty2(FTDIContext $ftdi, int $bits, int $sbit, int $parity, int $breakType): int`

Like `ftdiSetLineProperty`, with an additional break type argument (`ftdi_set_line_property2`).

---

### `FTDI::ftdiWriteData(FTDIContext $ftdi, mixed $data, int $size): int`

Writes up to `$size` bytes to the device (`ftdi_write_data`). Returns the number of bytes written, or `-1` on failure.

**Example**

```php
<?php

use Ftdi\FTDI;

$payload = "AT\r\n";
$written = FTDI::ftdiWriteData($ftdi, $payload, strlen($payload));
```

---

### `FTDI::ftdiWriteDataSetChunksize(FTDIContext $ftdi, int $chunksize): int`

Sets the write buffer chunk size (`ftdi_write_data_set_chunksize`).

---

### `FTDI::ftdiWriteDataGetChunksize(FTDIContext $ftdi): int`

Returns the current write chunk size (`ftdi_write_data_get_chunksize`).

---

### `FTDI::ftdiReadData(FTDIContext $ftdi, int $size): string`

Reads up to `$size` bytes (`ftdi_read_data`). Returns a binary string (may be shorter than requested). Returns an empty string on failure or when no data is available within the timeout.

**Example**

```php
<?php

use Ftdi\FTDI;

FTDI::ftdiSetTimeouts($ftdi, 1000, 1000);
$chunk = FTDI::ftdiReadData($ftdi, 4096);
```

---

### `FTDI::ftdiReadDataSetChunksize(FTDIContext $ftdi, int $chunksize): int`

Sets the read buffer chunk size (`ftdi_read_data_set_chunksize`).

---

### `FTDI::ftdiReadDataGetChunksize(FTDIContext $ftdi): int`

Returns the current read chunk size (`ftdi_read_data_get_chunksize`).

---

### `FTDI::ftdiSetBitmode(FTDIContext $ftdi, int $bitmask, int $mode): int`

Enables bitbang or MPSSE mode (`ftdi_set_bitmode`). `$mode` uses libftdi1 `BITMODE_*` values (`BITMODE_RESET`, `BITMODE_MPSSE`, `BITMODE_BITBANG`, …). `$bitmask` sets the pin direction/output mask.

**Example — enable MPSSE on FT232H**

```php
<?php

use Ftdi\FTDI;

// Reset then enter MPSSE mode (constants from libftdi1/ftdi.h)
FTDI::ftdiSetBitmode($ftdi, 0x00, 0x00); // BITMODE_RESET
FTDI::ftdiSetBitmode($ftdi, 0xFF, 0x02); // BITMODE_MPSSE with all outputs
```

---

### `FTDI::ftdiWriteDataSubmit(FTDIContext $ftdi, mixed $data, int $size): FTDITransferControl`

Submits an asynchronous write (`ftdi_write_data_submit`). Returns an `FTDITransferControl` DTO; poll with `ftdiTransferDataDone()`.

---

### `FTDI::ftdiReadDataSubmit(FTDIContext $ftdi, int $size): FTDITransferControl`

Submits an asynchronous read (`ftdi_read_data_submit`).

---

### `FTDI::ftdiTransferDataDone(FTDITransferControl $tc): int`

Blocks until an async transfer completes (`ftdi_transfer_data_done`). Returns bytes transferred, or `-1` on error.

**Example**

```php
<?php

use Ftdi\FTDI;

$tc = FTDI::ftdiWriteDataSubmit($ftdi, $payload, strlen($payload));
$done = FTDI::ftdiTransferDataDone($tc);
```

---

### `FTDI::ftdiTransferDataCancel(FTDITransferControl $tc): void`

Cancels a pending async transfer (`ftdi_transfer_data_cancel`).

---

### `FTDI::ftdiDisableBitbang(FTDIContext $ftdi): int`

Disables bitbang/MPSSE and returns to UART mode (`ftdi_disable_bitbang`).

---

### `FTDI::ftdiReadPins(FTDIContext $ftdi): int`

Reads the current pin state in bitbang mode (`ftdi_read_pins`). Returns an 8-bit pin bitmask, or `-1` on error.

---

### `FTDI::ftdiSetLatencyTimer(FTDIContext $ftdi, int $latency): int`

Sets the USB latency timer in milliseconds (`ftdi_set_latency_timer`).

---

### `FTDI::ftdiSetTimeouts(FTDIContext $ftdi, int $readTimeout, int $writeTimeout): void`

Sets `FTDIContext` timeout fields directly (`usb_read_timeout` and `usb_write_timeout`).

---

### `FTDI::ftdiGetLatencyTimer(FTDIContext $ftdi): int`

Returns the current latency timer value (`ftdi_get_latency_timer`).

---

### `FTDI::ftdiPollModemStatus(FTDIContext $ftdi): int`

Polls modem status lines (`ftdi_poll_modem_status`). Returns a status bitmask (CTS, DSR, RI, RLSD, … per libftdi1).

---

### `FTDI::ftdiSetFlowCtrl(FTDIContext $ftdi, int $flowctrl): int`

Sets hardware flow control (`ftdi_setflowctrl`). Use libftdi1 `FLOW_*` constants.

---

### `FTDI::ftdiSetFlowCtrlXonXoff(FTDIContext $ftdi, int $xon, int $xoff): int`

Sets software XON/XOFF flow control characters (`ftdi_setflowctrl_xonxoff`).

---

### `FTDI::ftdiSetDtr(FTDIContext $ftdi, int $state): int`

Sets the DTR line (`ftdi_setdtr`).

---

### `FTDI::ftdiSetRts(FTDIContext $ftdi, int $state): int`

Sets the RTS line (`ftdi_setrts`).

---

### `FTDI::ftdiSetDtrRts(FTDIContext $ftdi, int $dtr, int $rts): int`

Sets DTR and RTS together (`ftdi_setdtr_rts`).

---

### `FTDI::ftdiSetEventChar(FTDIContext $ftdi, int $eventch, int $enable): int`

Configures the event character (`ftdi_set_event_char`).

---

### `FTDI::ftdiSetErrorChar(FTDIContext $ftdi, int $errorch, int $enable): int`

Configures the error character (`ftdi_set_error_char`).

---

### `FTDI::ftdiGetEeprom(FTDIContext $ftdi): FTDIEeprom`

Returns an `FTDIEeprom` object populated from the current context EEPROM values.

---

### `FTDI::ftdiEepromInitDefaults(FTDIContext $ftdi, mixed $manufacturer, mixed $product, mixed $serial): int`

Initialises EEPROM defaults with string descriptors (`ftdi_eeprom_initdefaults`).

---

### `FTDI::ftdiEepromSetStrings(FTDIContext $ftdi, mixed $manufacturer, mixed $product, mixed $serial): int`

Updates manufacturer, product, and serial strings in the EEPROM image (`ftdi_eeprom_set_strings`).

---

### `FTDI::ftdiEepromGetStrings(FTDIContext $ftdi): array`

Reads EEPROM string fields. Returns `manufacturer`, `product`, and `serial`.

---

### `FTDI::ftdiEepromBuild(FTDIContext $ftdi): int`

Builds the EEPROM binary image from the in-memory structure (`ftdi_eeprom_build`).

---

### `FTDI::ftdiEepromDecode(FTDIContext $ftdi, int $verbose): int`

Decodes a raw EEPROM buffer already loaded into the context (`ftdi_eeprom_decode`).

---

### `FTDI::ftdiGetEepromValue(FTDIContext $ftdi, int $valueName): int`

Reads an integer EEPROM field by libftdi1 name constant (`ftdi_get_eeprom_value`).

---

### `FTDI::ftdiSetEepromValue(FTDIContext $ftdi, int $valueName, int $value): int`

Sets an integer EEPROM field (`ftdi_set_eeprom_value`).

---

### `FTDI::ftdiGetEepromBuf(FTDIContext $ftdi, int $size): string`

Returns `$size` bytes from the raw EEPROM image buffer (`ftdi_get_eeprom_buf`).

---

### `FTDI::ftdiSetEepromBuf(FTDIContext $ftdi, mixed $buf): int`

Replaces the raw EEPROM image buffer (`ftdi_set_eeprom_buf`).

---

### `FTDI::ftdiSetEepromUserData(FTDIContext $ftdi, mixed $buf): int`

Sets the EEPROM user-data section (`ftdi_set_eeprom_user_data`).

---

### `FTDI::setFT232HCbus(FTDIEeprom $eeprom): string`

Encodes FT232H CBUS pin functions into the five raw EEPROM bytes at offsets `0x18`–`0x1c` via libftdi's `set_ft232h_cbus`. Returns an empty string if the EEPROM handle is missing.

---

### `FTDI::ftdiReadEepromLocation(FTDIContext $ftdi, int $eepromAddr): int`

Reads one 16-bit word from EEPROM at `$eepromAddr` (`ftdi_read_eeprom_location`).

---

### `FTDI::ftdiReadEeprom(FTDIContext $ftdi): int`

Reads the full EEPROM from the device into the context (`ftdi_read_eeprom`).

---

### `FTDI::ftdiReadChipId(FTDIContext $ftdi): array`

Reads the chip ID (`ftdi_read_chipid`). Returns `result` (libftdi1 return code) and `chipid` (unsigned integer).

**Example**

```php
<?php

use Ftdi\FTDI;

$id = FTDI::ftdiReadChipId($ftdi);
if ($id['result'] === 0) {
    printf("chip id: 0x%X\n", $id['chipid']);
}
```

---

### `FTDI::ftdiWriteEepromLocation(FTDIContext $ftdi, int $eepromAddr, int $eepromVal): int`

Writes one 16-bit word to EEPROM at `$eepromAddr` (`ftdi_write_eeprom_location`).

---

### `FTDI::ftdiWriteEeprom(FTDIContext $ftdi): int`

Programs the EEPROM from the in-memory image (`ftdi_write_eeprom`). **Destructive** — use with care.

---

### `FTDI::ftdiEraseEeprom(FTDIContext $ftdi): int`

Erases the device EEPROM (`ftdi_erase_eeprom`). **Destructive**.

---

### `FTDI::ftdiGetErrorString(FTDIContext $ftdi): string`

Returns the last libftdi1 error string for the context (`ftdi_get_error_string`).

**Example**

```php
<?php

use Ftdi\FTDI;

if (FTDI::ftdiUSBOpen($ftdi, 0x0403, 0x6001) !== 0) {
    fwrite(STDERR, FTDI::ftdiGetErrorString($ftdi) . PHP_EOL);
}
```

---

## Quick reference

| Method | Signature |
|--------|-----------|
| `ftdiNew` | `FTDI::ftdiNew(): FTDIContext` |
| `ftdiInit` | `FTDI::ftdiInit(FTDIContext $ftdi): int` |
| `ftdiSetInterface` | `FTDI::ftdiSetInterface(FTDIContext $ftdi, int $iface): int` |
| `ftdiDeinit` | `FTDI::ftdiDeinit(FTDIContext $ftdi): void` |
| `ftdiFree` | `FTDI::ftdiFree(FTDIContext $ftdi): void` |
| `ftdiSetUSBDev` | `FTDI::ftdiSetUSBDev(FTDIContext $ftdi, int $usbDevHandle): void` |
| `ftdiGetLibraryVersion` | `FTDI::ftdiGetLibraryVersion(): FTDIVersionInfo` |
| `ftdiUSBFindAll` | `FTDI::ftdiUSBFindAll(FTDIContext $ftdi, int $vendor, int $product): array` |
| `ftdiListFree` | `FTDI::ftdiListFree(int $listHandle): void` |
| `ftdiListFree2` | `FTDI::ftdiListFree2(int $listHandle): void` |
| `ftdiUSBGetStrings` | `FTDI::ftdiUSBGetStrings(FTDIContext $ftdi, int $devHandle): array` |
| `ftdiUSBGetStrings2` | `FTDI::ftdiUSBGetStrings2(FTDIContext $ftdi, int $devHandle): array` |
| `ftdiUSBOpenDev` | `FTDI::ftdiUSBOpenDev(FTDIContext $ftdi, int $devHandle): int` |
| `ftdiUSBOpen` | `FTDI::ftdiUSBOpen(FTDIContext $ftdi, int $vendor, int $product): int` |
| `ftdiUSBOpenDesc` | `FTDI::ftdiUSBOpenDesc(FTDIContext $ftdi, int $vendor, int $product, mixed $description, mixed $serial): int` |
| `ftdiUSBOpenDescIndex` | `FTDI::ftdiUSBOpenDescIndex(FTDIContext $ftdi, int $vendor, int $product, mixed $description, mixed $serial, int $index): int` |
| `ftdiUSBOpenBusAddr` | `FTDI::ftdiUSBOpenBusAddr(FTDIContext $ftdi, int $bus, int $addr): int` |
| `ftdiUSBOpenString` | `FTDI::ftdiUSBOpenString(FTDIContext $ftdi, mixed $description): int` |
| `ftdiUSBClose` | `FTDI::ftdiUSBClose(FTDIContext $ftdi): int` |
| `ftdiUSBReset` | `FTDI::ftdiUSBReset(FTDIContext $ftdi): int` |
| `ftdiTCIFlush` | `FTDI::ftdiTCIFlush(FTDIContext $ftdi): int` |
| `ftdiTCOFlush` | `FTDI::ftdiTCOFlush(FTDIContext $ftdi): int` |
| `ftdiTCIOFlush` | `FTDI::ftdiTCIOFlush(FTDIContext $ftdi): int` |
| `ftdiUSBPurgeRXBuffer` | `FTDI::ftdiUSBPurgeRXBuffer(FTDIContext $ftdi): int` |
| `ftdiUSBPurgeTXBuffer` | `FTDI::ftdiUSBPurgeTXBuffer(FTDIContext $ftdi): int` |
| `ftdiUSBPurgeBuffers` | `FTDI::ftdiUSBPurgeBuffers(FTDIContext $ftdi): int` |
| `ftdiConvertBaudrateUTExport` | `FTDI::ftdiConvertBaudrateUTExport(int $baudrate, FTDIContext $ftdi): array` |
| `ftdiSetBaudrate` | `FTDI::ftdiSetBaudrate(FTDIContext $ftdi, int $baudrate): int` |
| `ftdiSetLineProperty` | `FTDI::ftdiSetLineProperty(FTDIContext $ftdi, int $bits, int $sbit, int $parity): int` |
| `ftdiSetLineProperty2` | `FTDI::ftdiSetLineProperty2(FTDIContext $ftdi, int $bits, int $sbit, int $parity, int $breakType): int` |
| `ftdiWriteData` | `FTDI::ftdiWriteData(FTDIContext $ftdi, mixed $data, int $size): int` |
| `ftdiWriteDataSetChunksize` | `FTDI::ftdiWriteDataSetChunksize(FTDIContext $ftdi, int $chunksize): int` |
| `ftdiWriteDataGetChunksize` | `FTDI::ftdiWriteDataGetChunksize(FTDIContext $ftdi): int` |
| `ftdiReadData` | `FTDI::ftdiReadData(FTDIContext $ftdi, int $size): string` |
| `ftdiReadDataSetChunksize` | `FTDI::ftdiReadDataSetChunksize(FTDIContext $ftdi, int $chunksize): int` |
| `ftdiReadDataGetChunksize` | `FTDI::ftdiReadDataGetChunksize(FTDIContext $ftdi): int` |
| `ftdiSetBitmode` | `FTDI::ftdiSetBitmode(FTDIContext $ftdi, int $bitmask, int $mode): int` |
| `ftdiWriteDataSubmit` | `FTDI::ftdiWriteDataSubmit(FTDIContext $ftdi, mixed $data, int $size): FTDITransferControl` |
| `ftdiReadDataSubmit` | `FTDI::ftdiReadDataSubmit(FTDIContext $ftdi, int $size): FTDITransferControl` |
| `ftdiTransferDataDone` | `FTDI::ftdiTransferDataDone(FTDITransferControl $tc): int` |
| `ftdiTransferDataCancel` | `FTDI::ftdiTransferDataCancel(FTDITransferControl $tc): void` |
| `ftdiDisableBitbang` | `FTDI::ftdiDisableBitbang(FTDIContext $ftdi): int` |
| `ftdiReadPins` | `FTDI::ftdiReadPins(FTDIContext $ftdi): int` |
| `ftdiSetLatencyTimer` | `FTDI::ftdiSetLatencyTimer(FTDIContext $ftdi, int $latency): int` |
| `ftdiSetTimeouts` | `FTDI::ftdiSetTimeouts(FTDIContext $ftdi, int $readTimeout, int $writeTimeout): void` |
| `ftdiGetLatencyTimer` | `FTDI::ftdiGetLatencyTimer(FTDIContext $ftdi): int` |
| `ftdiPollModemStatus` | `FTDI::ftdiPollModemStatus(FTDIContext $ftdi): int` |
| `ftdiSetFlowCtrl` | `FTDI::ftdiSetFlowCtrl(FTDIContext $ftdi, int $flowctrl): int` |
| `ftdiSetFlowCtrlXonXoff` | `FTDI::ftdiSetFlowCtrlXonXoff(FTDIContext $ftdi, int $xon, int $xoff): int` |
| `ftdiSetDtr` | `FTDI::ftdiSetDtr(FTDIContext $ftdi, int $state): int` |
| `ftdiSetRts` | `FTDI::ftdiSetRts(FTDIContext $ftdi, int $state): int` |
| `ftdiSetDtrRts` | `FTDI::ftdiSetDtrRts(FTDIContext $ftdi, int $dtr, int $rts): int` |
| `ftdiSetEventChar` | `FTDI::ftdiSetEventChar(FTDIContext $ftdi, int $eventch, int $enable): int` |
| `ftdiSetErrorChar` | `FTDI::ftdiSetErrorChar(FTDIContext $ftdi, int $errorch, int $enable): int` |
| `ftdiGetEeprom` | `FTDI::ftdiGetEeprom(FTDIContext $ftdi): FTDIEeprom` |
| `ftdiEepromInitDefaults` | `FTDI::ftdiEepromInitDefaults(FTDIContext $ftdi, mixed $manufacturer, mixed $product, mixed $serial): int` |
| `ftdiEepromSetStrings` | `FTDI::ftdiEepromSetStrings(FTDIContext $ftdi, mixed $manufacturer, mixed $product, mixed $serial): int` |
| `ftdiEepromGetStrings` | `FTDI::ftdiEepromGetStrings(FTDIContext $ftdi): array` |
| `ftdiEepromBuild` | `FTDI::ftdiEepromBuild(FTDIContext $ftdi): int` |
| `ftdiEepromDecode` | `FTDI::ftdiEepromDecode(FTDIContext $ftdi, int $verbose): int` |
| `ftdiGetEepromValue` | `FTDI::ftdiGetEepromValue(FTDIContext $ftdi, int $valueName): int` |
| `ftdiSetEepromValue` | `FTDI::ftdiSetEepromValue(FTDIContext $ftdi, int $valueName, int $value): int` |
| `ftdiGetEepromBuf` | `FTDI::ftdiGetEepromBuf(FTDIContext $ftdi, int $size): string` |
| `ftdiSetEepromBuf` | `FTDI::ftdiSetEepromBuf(FTDIContext $ftdi, mixed $buf): int` |
| `ftdiSetEepromUserData` | `FTDI::ftdiSetEepromUserData(FTDIContext $ftdi, mixed $buf): int` |
| `setFT232HCbus` | `FTDI::setFT232HCbus(FTDIEeprom $eeprom): string` |
| `ftdiReadEepromLocation` | `FTDI::ftdiReadEepromLocation(FTDIContext $ftdi, int $eepromAddr): int` |
| `ftdiReadEeprom` | `FTDI::ftdiReadEeprom(FTDIContext $ftdi): int` |
| `ftdiReadChipId` | `FTDI::ftdiReadChipId(FTDIContext $ftdi): array` |
| `ftdiWriteEepromLocation` | `FTDI::ftdiWriteEepromLocation(FTDIContext $ftdi, int $eepromAddr, int $eepromVal): int` |
| `ftdiWriteEeprom` | `FTDI::ftdiWriteEeprom(FTDIContext $ftdi): int` |
| `ftdiEraseEeprom` | `FTDI::ftdiEraseEeprom(FTDIContext $ftdi): int` |
| `ftdiGetErrorString` | `FTDI::ftdiGetErrorString(FTDIContext $ftdi): string` |
