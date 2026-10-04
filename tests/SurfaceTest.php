<?php

declare(strict_types=1);

use Ftdi\FTDIContext;
use Ftdi\FTDIDevice;
use Ftdi\FTDIEeprom;
use Ftdi\FTDITransferControl;
use Ftdi\FTDIVersionInfo;
use Ftdi\FtdiProductId;
use Ftdi\FtdiVendorId;

it('registers the ftdi.h enum members and defines', function () {
    expect(TYPE_232H)->toBe(6)
        ->and(BITMODE_MPSSE)->toBe(0x02)
        ->and(INTERFACE_A)->toBe(1)
        ->and(BITS_8)->toBe(8)
        ->and(STOP_BIT_1)->toBe(0)
        ->and(NONE)->toBe(0)
        ->and(SPACE)->toBe(4)
        ->and(VENDOR_ID)->toBe(0)
        ->and(USER_DATA_ADDR)->toBe(57)
        ->and(CBUSH_CLK7_5)->toBe(12)
        ->and(MPSSE_DO_WRITE)->toBe(0x10)
        ->and(SEND_IMMEDIATE)->toBe(0x87)
        ->and(TCK_DIVISOR)->toBe(0x86)
        ->and(SIO_RTS_CTS_HS)->toBe(0x100)
        ->and(SIO_SET_DTR_HIGH)->toBe(0x101)
        ->and(FTDI_DEVICE_OUT_REQTYPE)->toBe(0x40)
        ->and(defined('SIO_RESET_PURGE_RX'))->toBeFalse();
});

it('carries the FTDI USB IDs as enums', function () {
    expect(FtdiVendorId::FTDI->value)->toBe(0x0403)
        ->and(FtdiProductId::FT232H->value)->toBe(0x6014)
        ->and(FtdiProductId::from(0x6010))->toBe(FtdiProductId::FT2232H)
        ->and(FtdiProductId::cases())->toHaveCount(7);
});

it('reports the library version as a read-only snapshot', function () {
    $version = ftdi_get_library_version();

    expect($version)->toBeInstanceOf(FTDIVersionInfo::class)
        ->and($version->major)->toBe(1)
        ->and($version->versionStr)->not->toBeEmpty()
        ->and($version->toArray())->toHaveKeys(['major', 'minor', 'micro', 'versionStr', 'snapshotStr'])
        ->and(fn () => $version->major = 2)->toThrow(Error::class);
});

it('creates contexts only through ftdi_new()', function () {
    expect(fn () => new FTDIContext())->toThrow(Error::class)
        ->and(fn () => new FTDIDevice())->toThrow(Error::class)
        ->and(fn () => new FTDITransferControl())->toThrow(Error::class)
        ->and(fn () => clone ftdi_new())->toThrow(Error::class);
});

it('reads the context struct live through read-only properties', function () {
    $ftdi = ftdi_new();

    expect($ftdi)->toBeInstanceOf(FTDIContext::class)
        ->and($ftdi->usbReadTimeout)->toBe(5000)
        ->and($ftdi->readBufferChunkSize)->toBeGreaterThan(0)
        ->and($ftdi->errorStr)->toBe('')
        ->and(isset($ftdi->baudrate))->toBeTrue()
        ->and($ftdi->toArray())->toHaveCount(15)
        ->and((array) $ftdi)->toHaveKey('chipType')
        ->and(fn () => $ftdi->baudrate = 9600)->toThrow(Error::class);

    ftdi_set_timeouts($ftdi, 250, 500);

    expect($ftdi->usbReadTimeout)->toBe(250)
        ->and($ftdi->usbWriteTimeout)->toBe(500);

    ftdi_read_data_set_chunksize($ftdi, 1024);

    expect($ftdi->readBufferChunkSize)->toBe(1024)
        ->and(ftdi_read_data_get_chunksize($ftdi))->toBe(1024);
});

it('reports a device that is not there with libftdi codes and its error string', function () {
    $ftdi = ftdi_new();

    expect(ftdi_usb_open($ftdi, FtdiVendorId::FTDI->value, NO_SUCH_PRODUCT))->toBe(-3)
        ->and(ftdi_get_error_string($ftdi))->toBe('device not found')
        ->and(ftdi_usb_find_all($ftdi, FtdiVendorId::FTDI->value, NO_SUCH_PRODUCT))->toBe(['count' => 0, 'devices' => []]);
});

it('fails I/O on a context with no device open', function () {
    $ftdi = ftdi_new();

    expect(ftdi_write_data($ftdi, 'abc', 3))->toBe(-666)
        ->and(ftdi_read_data($ftdi, 4))->toBeFalse()
        ->and(ftdi_read_pins($ftdi))->toBe(-2)
        ->and(ftdi_write_data_submit($ftdi, 'abc', 3))->toBeNull()
        ->and(ftdi_read_data_submit($ftdi, 3))->toBeNull()
        ->and(ftdi_get_error_string($ftdi))->toBe('USB device unavailable');

    $chipId = 'untouched';

    expect(ftdi_read_chip_id($ftdi, $chipId))->not->toBe(0)
        ->and($chipId)->toBe('untouched');
});

it('refuses arguments outside what the C call takes', function () {
    $ftdi = ftdi_new();

    expect(fn () => ftdi_write_data($ftdi, 'abc', 4))->toThrow(ValueError::class)
        ->and(fn () => ftdi_write_data_submit($ftdi, 'abc', -1))->toThrow(ValueError::class)
        ->and(fn () => ftdi_read_data_submit($ftdi, 0))->toThrow(ValueError::class)
        ->and(fn () => ftdi_set_bitmode($ftdi, 0x100, BITMODE_MPSSE))->toThrow(ValueError::class)
        ->and(fn () => ftdi_set_line_property($ftdi, 9, STOP_BIT_1, NONE))->toThrow(ValueError::class)
        ->and(fn () => ftdi_set_interface($ftdi, 7))->toThrow(ValueError::class)
        ->and(fn () => ftdi_usb_open($ftdi, 0x10000, 1))->toThrow(ValueError::class)
        ->and(fn () => ftdi_get_eeprom_value($ftdi, 58))->toThrow(ValueError::class)
        ->and(fn () => ftdi_handle_events_timeout($ftdi, -1))->toThrow(ValueError::class);
});

it('snapshots the EEPROM image with every value and string', function () {
    $eeprom = ftdi_get_eeprom(ftdi_new());

    expect($eeprom)->toBeInstanceOf(FTDIEeprom::class)
        ->and($eeprom->vendorId)->toBeInt()
        ->and($eeprom->channelARs485)->toBeInt()
        ->and($eeprom->manufacturer)->toBeString()
        ->and($eeprom->toArray())->toHaveCount(61)
        ->and(fn () => $eeprom->vendorId = 1)->toThrow(Error::class);
});

it('refuses every call on a context ftdi_free() released, and frees once', function () {
    $ftdi = ftdi_new();
    ftdi_free($ftdi);
    ftdi_free($ftdi);

    expect(fn () => ftdi_usb_open($ftdi, 0x0403, 0x6014))->toThrow(Error::class, 'released by ftdi_free()')
        ->and(fn () => $ftdi->baudrate)->toThrow(Error::class)
        ->and(fn () => $ftdi->toArray())->toThrow(Error::class)
        ->and(fn () => ftdi_get_error_string($ftdi))->toThrow(Error::class);
});

it('refuses calls on a deinitialised context until ftdi_init()', function () {
    $ftdi = ftdi_new();
    ftdi_deinit($ftdi);

    expect(fn () => ftdi_get_pollfds($ftdi))->toThrow(Error::class, 'call ftdi_init() first')
        ->and(fn () => ftdi_get_eeprom($ftdi))->toThrow(Error::class)
        ->and(ftdi_init($ftdi))->toBe(0)
        ->and(ftdi_get_pollfds($ftdi))->toBeArray()
        ->and(ftdi_init($ftdi))->toBe(0);
});

it('reports libusb pump state for an idle context', function () {
    $ftdi = ftdi_new();

    expect(ftdi_get_next_timeout($ftdi))->toBe(['result' => 0, 'usec' => 0])
        ->and(ftdi_handle_events_timeout($ftdi, 0))->toBe(0);
});
