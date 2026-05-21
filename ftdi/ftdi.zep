namespace Ftdi;

use Ftdi\FTDIContext;
use Ftdi\FTDIEeprom;
use Ftdi\FTDITransferControl;
use Ftdi\FTDIVersionInfo;

%{
#include <stdint.h>
#include <sys/time.h>
#include <libftdi1/ftdi.h>
/* Not in public ftdi.h; wraps internal ftdi_convert_baudrate for testing. */
extern int convert_baudrate_UT_export(int baudrate, struct ftdi_context *ftdi,
                                      unsigned short *value, unsigned short *index);
/* Exported from libftdi but not declared in ftdi.h (defined in ftdi.c). */
extern void set_ft232h_cbus(struct ftdi_eeprom *eeprom, unsigned char *output);
}%

class FTDI
{
    public static function ftdiInit(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_init(_ctx);
            }
        }%

        return result;
    }

    /**
     * Allocate a new libftdi1 context and return it as a hydrated FTDIContext DTO.
     *
     * Wraps ftdi_new(). On success the returned object's handle carries the
     * ftdi_context pointer as an opaque integer; pass it to subsequent calls.
     * Check handle >= 0 before use -- a value of -1 means ftdi_new() failed.
     *
     * @return <FTDIContext>
     */
    public static function ftdiNew() -> <FTDIContext>
    {
        var context;
        var errorStr;
        int handle;
        int chipType;
        int usbReadTimeout;
        int usbWriteTimeout;
        int ifaceIdx;
        int baudrate;
        int bitbangEnabled;
        int bitbangMode;
        int channel;
        int inEndpoint;
        int outEndpoint;
        int readBufferChunkSize;
        int writeBufferChunkSize;
        int maxPacketSize;
        int moduleDetachMode;

        %{
            struct ftdi_context *_ctx = ftdi_new();
            if (!_ctx) {
                handle             = (zend_long)-1;
                chipType           = (zend_long)0;
                usbReadTimeout     = (zend_long)0;
                usbWriteTimeout    = (zend_long)0;
                ifaceIdx           = (zend_long)0;
                baudrate           = (zend_long)0;
                bitbangEnabled     = (zend_long)0;
                bitbangMode        = (zend_long)0;
                channel            = (zend_long)0;
                inEndpoint         = (zend_long)0;
                outEndpoint        = (zend_long)0;
                readBufferChunkSize  = (zend_long)0;
                writeBufferChunkSize = (zend_long)0;
                maxPacketSize      = (zend_long)0;
                moduleDetachMode   = (zend_long)0;
                ZVAL_STRING(&errorStr, "ftdi_new() returned NULL");
            } else {
                handle             = (zend_long)(uintptr_t)_ctx;
                chipType           = (zend_long)_ctx->type;
                usbReadTimeout     = (zend_long)_ctx->usb_read_timeout;
                usbWriteTimeout    = (zend_long)_ctx->usb_write_timeout;
                ifaceIdx           = (zend_long)_ctx->index;
                baudrate           = (zend_long)_ctx->baudrate;
                bitbangEnabled     = (zend_long)_ctx->bitbang_enabled;
                bitbangMode        = (zend_long)_ctx->bitbang_mode;
                channel            = (zend_long)_ctx->interface;
                inEndpoint         = (zend_long)_ctx->in_ep;
                outEndpoint        = (zend_long)_ctx->out_ep;
                readBufferChunkSize  = (zend_long)_ctx->readbuffer_chunksize;
                writeBufferChunkSize = (zend_long)_ctx->writebuffer_chunksize;
                maxPacketSize      = (zend_long)_ctx->max_packet_size;
                moduleDetachMode   = (zend_long)_ctx->module_detach_mode;
                const char *_err = _ctx->error_str;
                ZVAL_STRING(&errorStr, _err ? _err : "");
            }
        }%

        let context = new FTDIContext();
        let context->handle             = handle;
        let context->chipType           = chipType;
        let context->usbReadTimeout     = usbReadTimeout;
        let context->usbWriteTimeout    = usbWriteTimeout;
        let context->interfaceIndex     = ifaceIdx;
        let context->baudrate           = baudrate;
        let context->bitbangEnabled     = bitbangEnabled;
        let context->bitbangMode        = bitbangMode;
        let context->channel            = channel;
        let context->inEndpoint         = inEndpoint;
        let context->outEndpoint        = outEndpoint;
        let context->readBufferChunkSize  = readBufferChunkSize;
        let context->writeBufferChunkSize = writeBufferChunkSize;
        let context->maxPacketSize      = maxPacketSize;
        let context->moduleDetachMode   = moduleDetachMode;
        let context->errorStr           = errorStr;

        return context;
    }



    public static function ftdiSetInterface(<FTDIContext> ftdi, int iface) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_interface(_ctx, iface);
            }
        }%

        return result;
    }

    public static function ftdiDeinit(<FTDIContext> ftdi) -> void
    {
        int handle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                ftdi_deinit(_ctx);
            }
        }%
    }

    public static function ftdiFree(<FTDIContext> ftdi) -> void
    {
        int handle;
        let handle = ftdi->handle;
        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) { ftdi_free(_ctx); }
        }%
    }

    public static function ftdiSetUSBDev(<FTDIContext> ftdi, int usbDevHandle) -> void
    {
        int handle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct libusb_device_handle *_usb =
                (struct libusb_device_handle *)(uintptr_t)usbDevHandle;
            if (_ctx) {
                ftdi_set_usbdev(_ctx, _usb);
            }
        }%
    }

    /**
     * Return libftdi1 library version information without requiring a device.
     *
     * Wraps ftdi_get_library_version() which returns a struct by value --
     * no ftdi_context is needed.
     *
     * @return <FTDIVersionInfo>
     */
    public static function ftdiGetLibraryVersion() -> <FTDIVersionInfo>
    {
        var versionInfo;
        var versionStr;
        var snapshotStr;
        int major;
        int minor;
        int micro;

        %{
            struct ftdi_version_info _vi = ftdi_get_library_version();
            major = (zend_long)_vi.major;
            minor = (zend_long)_vi.minor;
            micro = (zend_long)_vi.micro;
            ZVAL_STRING(&versionStr,  _vi.version_str  ? _vi.version_str  : "");
            ZVAL_STRING(&snapshotStr, _vi.snapshot_str ? _vi.snapshot_str : "");
        }%

        let versionInfo = new FTDIVersionInfo();
        let versionInfo->major       = major;
        let versionInfo->minor       = minor;
        let versionInfo->micro       = micro;
        let versionInfo->versionStr  = versionStr;
        let versionInfo->snapshotStr = snapshotStr;

        return versionInfo;
    }

    public static function ftdiUSBFindAll(<FTDIContext> ftdi, int vendor, int product) -> array
    {
        int handle;
        int count;
        int listHandle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct ftdi_device_list *_list = NULL;

            count = (zend_long)0;
            listHandle = (zend_long)0;

            if (_ctx) {
                int _c = ftdi_usb_find_all(_ctx, &_list, (int)vendor, (int)product);
                count = (zend_long)_c;
                if (_list) {
                    listHandle = (zend_long)(uintptr_t)_list;
                }
            }
        }%

        return [
            "count":      count,
            "listHandle": listHandle
        ];
    }

    public static function ftdiListFree(int listHandle) -> void
    {
        %{
            struct ftdi_device_list *_list =
                (struct ftdi_device_list *)(uintptr_t)listHandle;
            if (_list) {
                ftdi_list_free(&_list);
            }
        }%
    }

    public static function ftdiListFree2(int listHandle) -> void
    {
        %{
            struct ftdi_device_list *_list =
                (struct ftdi_device_list *)(uintptr_t)listHandle;
            if (_list) {
                ftdi_list_free2(_list);
            }
        }%
    }

    public static function ftdiUSBGetStrings(<FTDIContext> ftdi, int devHandle) -> array
    {
        var manufacturer;
        var description;
        var serial;
        int handle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct libusb_device *_dev = (struct libusb_device *)(uintptr_t)devHandle;
            char _mnf[256]   = {0};
            char _desc[256] = {0};
            char _serial[256] = {0};

            if (_ctx && _dev) {
                (void)ftdi_usb_get_strings(
                    _ctx,
                    _dev,
                    _mnf,
                    (int)sizeof(_mnf),
                    _desc,
                    (int)sizeof(_desc),
                    _serial,
                    (int)sizeof(_serial)
                );
            }

            ZVAL_STRING(&manufacturer, _mnf);
            ZVAL_STRING(&description, _desc);
            ZVAL_STRING(&serial, _serial);
        }%

        return [
            "manufacturer": manufacturer,
            "description": description,
            "serial": serial
        ];
    }

    public static function ftdiUSBGetStrings2(<FTDIContext> ftdi, int devHandle) -> array
    {
        var manufacturer;
        var description;
        var serial;
        int handle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct libusb_device *_dev = (struct libusb_device *)(uintptr_t)devHandle;
            char _mnf[256]     = {0};
            char _desc[256]    = {0};
            char _serial[256] = {0};

            if (_ctx && _dev) {
                (void)ftdi_usb_get_strings2(
                    _ctx,
                    _dev,
                    _mnf,
                    (int)sizeof(_mnf),
                    _desc,
                    (int)sizeof(_desc),
                    _serial,
                    (int)sizeof(_serial)
                );
            }

            ZVAL_STRING(&manufacturer, _mnf);
            ZVAL_STRING(&description, _desc);
            ZVAL_STRING(&serial, _serial);
        }%

        return [
            "manufacturer": manufacturer,
            "description": description,
            "serial": serial
        ];
    }

    public static function ftdiUSBOpenDev(<FTDIContext> ftdi, int devHandle) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct libusb_device *_dev = (struct libusb_device *)(uintptr_t)devHandle;
            result = (zend_long)-1;
            if (_ctx && _dev) {
                result = (zend_long)ftdi_usb_open_dev(_ctx, _dev);
            }
        }%

        return result;
    }

    public static function ftdiUSBOpen(<FTDIContext> ftdi, int vendor, int product) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_open(_ctx, (int)vendor, (int)product);
            }
        }%

        return result;
    }

    public static function ftdiUSBOpenDesc(<FTDIContext> ftdi, int vendor, int product, var description, var serial) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            const char *_desc = NULL;
            const char *_serial = NULL;

            result = (zend_long)-1;
            if (_ctx) {
                if (Z_STRLEN_P(description) > 0) {
                    _desc = Z_STRVAL_P(description);
                }
                if (Z_STRLEN_P(serial) > 0) {
                    _serial = Z_STRVAL_P(serial);
                }
                result = (zend_long)ftdi_usb_open_desc(
                    _ctx,
                    (int)vendor,
                    (int)product,
                    _desc,
                    _serial
                );
            }
        }%

        return result;
    }

    public static function ftdiUSBOpenDescIndex(<FTDIContext> ftdi, int vendor, int product, var description, var serial, int index) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            const char *_desc = NULL;
            const char *_serial = NULL;

            result = (zend_long)-1;
            if (_ctx) {
                if (Z_STRLEN_P(description) > 0) {
                    _desc = Z_STRVAL_P(description);
                }
                if (Z_STRLEN_P(serial) > 0) {
                    _serial = Z_STRVAL_P(serial);
                }
                result = (zend_long)ftdi_usb_open_desc_index(
                    _ctx,
                    (int)vendor,
                    (int)product,
                    _desc,
                    _serial,
                    (unsigned int)index
                );
            }
        }%

        return result;
    }

    public static function ftdiUSBOpenBusAddr(<FTDIContext> ftdi, int bus, int addr) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_open_bus_addr(
                    _ctx,
                    (uint8_t)bus,
                    (uint8_t)addr
                );
            }
        }%

        return result;
    }

    public static function ftdiUSBOpenString(<FTDIContext> ftdi, var description) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_open_string(_ctx, Z_STRVAL_P(description));
            }
        }%

        return result;
    }

    public static function ftdiUSBClose(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_close(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiUSBReset(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_reset(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiTCIFlush(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_tciflush(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiTCOFlush(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_tcoflush(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiTCIOFlush(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_tcioflush(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiUSBPurgeRXBuffer(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_purge_rx_buffer(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiUSBPurgeTXBuffer(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_purge_tx_buffer(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiUSBPurgeBuffers(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_purge_buffers(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiConvertBaudrateUTExport(int baudrate, <FTDIContext> ftdi) -> array
    {
        int handle;
        int value;
        int index;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            unsigned short _value = 0;
            unsigned short _index = 0;

            value = (zend_long)0;
            index = (zend_long)0;

            if (_ctx) {
                (void)convert_baudrate_UT_export((int)baudrate, _ctx, &_value, &_index);
                value = (zend_long)_value;
                index = (zend_long)_index;
            }
        }%

        return [
            "value": value,
            "index": index
        ];
    }

    public static function ftdiSetBaudrate(<FTDIContext> ftdi, int baudrate) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_baudrate(_ctx, (int)baudrate);
            }
        }%

        return result;
    }

    public static function ftdiSetLineProperty(<FTDIContext> ftdi, int bits, int sbit, int parity) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_line_property(
                    _ctx,
                    (enum ftdi_bits_type)bits,
                    (enum ftdi_stopbits_type)sbit,
                    (enum ftdi_parity_type)parity
                );
            }
        }%

        return result;
    }

    public static function ftdiSetLineProperty2(<FTDIContext> ftdi, int bits, int sbit, int parity, int breakType) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_line_property2(
                    _ctx,
                    (enum ftdi_bits_type)bits,
                    (enum ftdi_stopbits_type)sbit,
                    (enum ftdi_parity_type)parity,
                    (enum ftdi_break_type)breakType
                );
            }
        }%

        return result;
    }

    public static function ftdiWriteData(<FTDIContext> ftdi, var data, int size) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            int _slen;
            int _size;

            result = (zend_long)-1;
            if (_ctx) {
                _slen = (int)Z_STRLEN_P(data);
                _size = (int)size;
                if (_size > _slen) {
                    _size = _slen;
                }
                if (_size < 0) {
                    _size = 0;
                }
                result = (zend_long)ftdi_write_data(
                    _ctx,
                    (const unsigned char *)Z_STRVAL_P(data),
                    _size
                );
            }
        }%

        return result;
    }

    public static function ftdiWriteDataSetChunksize(<FTDIContext> ftdi, int chunksize) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_write_data_set_chunksize(
                    _ctx,
                    (unsigned int)chunksize
                );
            }
        }%

        return result;
    }

    public static function ftdiWriteDataGetChunksize(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            unsigned int _chunksize = 0;

            result = (zend_long)-1;
            if (_ctx) {
                int _rc = ftdi_write_data_get_chunksize(_ctx, &_chunksize);
                if (_rc == 0) {
                    result = (zend_long)_chunksize;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiReadData(<FTDIContext> ftdi, int size) -> string
    {
        var out;
        int handle;

        if size <= 0 {
            return "";
        }

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;

            ZVAL_EMPTY_STRING(&out);
            if (_ctx) {
                unsigned char *_buf = (unsigned char *)emalloc((size_t)size);
                if (_buf) {
                    int _n = ftdi_read_data(_ctx, _buf, size);
                    if (_n > 0) {
                        ZVAL_STRINGL(&out, (char *)_buf, (size_t)_n);
                    } else if (_n == 0) {
                        ZVAL_EMPTY_STRING(&out);
                    } else {
                        ZVAL_EMPTY_STRING(&out);
                    }
                    efree(_buf);
                }
            }
        }%

        return out;
    }

    public static function ftdiReadDataSetChunksize(<FTDIContext> ftdi, int chunksize) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_read_data_set_chunksize(
                    _ctx,
                    (unsigned int)chunksize
                );
            }
        }%

        return result;
    }

    public static function ftdiReadDataGetChunksize(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            unsigned int _chunksize = 0;

            result = (zend_long)-1;
            if (_ctx) {
                int _rc = ftdi_read_data_get_chunksize(_ctx, &_chunksize);
                if (_rc == 0) {
                    result = (zend_long)_chunksize;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiSetBitmode(<FTDIContext> ftdi, int bitmask, int mode) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_bitmode(
                    _ctx,
                    (unsigned char)bitmask,
                    (unsigned char)mode
                );
            }
        }%

        return result;
    }

    public static function ftdiWriteDataSubmit(<FTDIContext> ftdi, var data, int size) -> <FTDITransferControl>
    {
        var transferControl;
        int handle;
        int tcHandle;
        int completed;
        int transferSize;
        int offset;
        int contextHandle;
        int bufHandle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct ftdi_transfer_control *_tc = NULL;

            tcHandle      = (zend_long)0;
            completed     = (zend_long)0;
            transferSize  = (zend_long)0;
            offset        = (zend_long)0;
            contextHandle = (zend_long)0;
            bufHandle     = (zend_long)0;

            if (_ctx) {
                _tc = ftdi_write_data_submit(_ctx, (unsigned char *)Z_STRVAL_P(data), size);
                if (_tc) {
                    tcHandle      = (zend_long)(uintptr_t)_tc;
                    completed     = (zend_long)_tc->completed;
                    transferSize  = (zend_long)_tc->size;
                    offset        = (zend_long)_tc->offset;
                    contextHandle = (zend_long)(uintptr_t)_tc->ftdi;
                    bufHandle     = (zend_long)(uintptr_t)_tc->buf;
                }
            }
        }%

        let transferControl = new FTDITransferControl();
        let transferControl->handle = tcHandle;
        let transferControl->completed = completed;
        let transferControl->size = transferSize;
        let transferControl->offset = offset;
        let transferControl->contextHandle = contextHandle;
        let transferControl->bufHandle = bufHandle;

        return transferControl;
    }

    public static function ftdiReadDataSubmit(<FTDIContext> ftdi, int size) -> <FTDITransferControl>
    {
        var transferControl;
        int handle;
        int tcHandle;
        int completed;
        int transferSize;
        int offset;
        int contextHandle;
        int bufHandle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct ftdi_transfer_control *_tc = NULL;
            unsigned char *_buf = NULL;

            tcHandle      = (zend_long)0;
            completed     = (zend_long)0;
            transferSize  = (zend_long)0;
            offset        = (zend_long)0;
            contextHandle = (zend_long)0;
            bufHandle     = (zend_long)0;

            if (_ctx && size > 0) {
                _buf = (unsigned char *)emalloc((size_t)size);
                if (_buf) {
                    _tc = ftdi_read_data_submit(_ctx, _buf, size);
                    if (_tc) {
                        tcHandle      = (zend_long)(uintptr_t)_tc;
                        completed     = (zend_long)_tc->completed;
                        transferSize  = (zend_long)_tc->size;
                        offset        = (zend_long)_tc->offset;
                        contextHandle = (zend_long)(uintptr_t)_tc->ftdi;
                        bufHandle     = (zend_long)(uintptr_t)_buf;
                    } else {
                        efree(_buf);
                    }
                }
            }
        }%

        let transferControl = new FTDITransferControl();
        let transferControl->handle = tcHandle;
        let transferControl->completed = completed;
        let transferControl->size = transferSize;
        let transferControl->offset = offset;
        let transferControl->contextHandle = contextHandle;
        let transferControl->bufHandle = bufHandle;

        return transferControl;
    }

    public static function ftdiTransferDataDone(<FTDITransferControl> tc) -> int
    {
        int handle;
        int result;

        let handle = tc->handle;

        %{
            struct ftdi_transfer_control *_tc = (struct ftdi_transfer_control *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_tc) {
                result = (zend_long)ftdi_transfer_data_done(_tc);
            }
        }%

        return result;
    }

    public static function ftdiTransferDataCancel(<FTDITransferControl> tc) -> void
    {
        int handle;

        let handle = tc->handle;

        %{
            struct ftdi_transfer_control *_tc = (struct ftdi_transfer_control *)(uintptr_t)handle;
            struct timeval _to;
            _to.tv_sec = 0;
            _to.tv_usec = 0;
            if (_tc) {
                (void)ftdi_transfer_data_cancel(_tc, &_to);
            }
        }%
    }

    public static function ftdiDisableBitbang(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_disable_bitbang(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiReadPins(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                unsigned char _pins = 0;
                int _rc = ftdi_read_pins(_ctx, &_pins);
                if (_rc == 0) {
                    result = (zend_long)_pins;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiSetLatencyTimer(<FTDIContext> ftdi, int latency) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_latency_timer(
                    _ctx,
                    (unsigned char)latency
                );
            }
        }%

        return result;
    }

    public static function ftdiSetTimeouts(<FTDIContext> ftdi, int readTimeout, int writeTimeout) -> void
    {
        int handle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                _ctx->usb_read_timeout  = (int)readTimeout;
                _ctx->usb_write_timeout = (int)writeTimeout;
            }
        }%
    }

    public static function ftdiGetLatencyTimer(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                unsigned char _latency = 0;
                int _rc = ftdi_get_latency_timer(_ctx, &_latency);
                if (_rc == 0) {
                    result = (zend_long)_latency;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiPollModemStatus(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                unsigned short _status = 0;
                int _rc = ftdi_poll_modem_status(_ctx, &_status);
                if (_rc == 0) {
                    result = (zend_long)_status;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiSetFlowCtrl(<FTDIContext> ftdi, int flowctrl) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setflowctrl(_ctx, (int)flowctrl);
            }
        }%

        return result;
    }

    public static function ftdiSetFlowCtrlXonXoff(<FTDIContext> ftdi, int xon, int xoff) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setflowctrl_xonxoff(
                    _ctx,
                    (unsigned char)xon,
                    (unsigned char)xoff
                );
            }
        }%

        return result;
    }

    public static function ftdiSetDtr(<FTDIContext> ftdi, int state) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setdtr(_ctx, (int)state);
            }
        }%

        return result;
    }

    public static function ftdiSetRts(<FTDIContext> ftdi, int state) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setrts(_ctx, (int)state);
            }
        }%

        return result;
    }

    public static function ftdiSetDtrRts(<FTDIContext> ftdi, int dtr, int rts) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setdtr_rts(_ctx, (int)dtr, (int)rts);
            }
        }%

        return result;
    }

    public static function ftdiSetEventChar(<FTDIContext> ftdi, int eventch, int enable) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_event_char(
                    _ctx,
                    (unsigned char)eventch,
                    (unsigned char)enable
                );
            }
        }%

        return result;
    }

    public static function ftdiSetErrorChar(<FTDIContext> ftdi, int errorch, int enable) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_error_char(
                    _ctx,
                    (unsigned char)errorch,
                    (unsigned char)enable
                );
            }
        }%

        return result;
    }

    public static function ftdiGetEeprom(<FTDIContext> ftdi) -> <FTDIEeprom>
    {
        int handle;
        int eepromHandle;
        int vendorId;
        int productId;
        int selfPowered;
        int remoteWakeup;
        int isNotPnp;
        int suspendDbus7;
        int inIsIsochronous;
        int outIsIsochronous;
        int suspendPullDowns;
        int useSerial;
        int usbVersion;
        int useUsbVersion;
        int maxPower;
        int channelAType;
        int channelBType;
        int channelADriver;
        int channelBDriver;
        int cbusFunction0;
        int cbusFunction1;
        int cbusFunction2;
        int cbusFunction3;
        int cbusFunction4;
        int cbusFunction5;
        int cbusFunction6;
        int cbusFunction7;
        int cbusFunction8;
        int cbusFunction9;
        int highCurrent;
        int highCurrentA;
        int highCurrentB;
        int invert;
        int group0Drive;
        int group0Schmitt;
        int group0Slew;
        int group1Drive;
        int group1Schmitt;
        int group1Slew;
        int group2Drive;
        int group2Schmitt;
        int group2Slew;
        int group3Drive;
        int group3Schmitt;
        int group3Slew;
        int chipSize;
        int chipType;
        int powerSave;
        int clockPolarity;
        int dataOrder;
        int flowControl;
        int channelCDriver;
        int channelDDriver;
        int channelARs485;
        int channelBRs485;
        int channelCRs485;
        int channelDRs485;
        int releaseNumber;
        int externalOscillator;
        int userDataAddr;
        var manufacturer;
        var product;
        var serial;

        let handle = ftdi->handle;
        let eepromHandle = 0;
        let vendorId = 0, productId = 0, selfPowered = 0, remoteWakeup = 0,
            isNotPnp = 0, suspendDbus7 = 0, inIsIsochronous = 0, outIsIsochronous = 0,
            suspendPullDowns = 0, useSerial = 0, usbVersion = 0, useUsbVersion = 0,
            maxPower = 0, channelAType = 0, channelBType = 0, channelADriver = 0,
            channelBDriver = 0, cbusFunction0 = 0, cbusFunction1 = 0, cbusFunction2 = 0,
            cbusFunction3 = 0, cbusFunction4 = 0, cbusFunction5 = 0, cbusFunction6 = 0,
            cbusFunction7 = 0, cbusFunction8 = 0, cbusFunction9 = 0, highCurrent = 0,
            highCurrentA = 0, highCurrentB = 0, invert = 0, group0Drive = 0,
            group0Schmitt = 0, group0Slew = 0, group1Drive = 0, group1Schmitt = 0,
            group1Slew = 0, group2Drive = 0, group2Schmitt = 0, group2Slew = 0,
            group3Drive = 0, group3Schmitt = 0, group3Slew = 0, chipSize = 0,
            chipType = 0, powerSave = 0, clockPolarity = 0, dataOrder = 0,
            flowControl = 0, channelCDriver = 0, channelDDriver = 0, channelARs485 = 0,
            channelBRs485 = 0, channelCRs485 = 0, channelDRs485 = 0, releaseNumber = 0,
            externalOscillator = 0, userDataAddr = 0;
        let manufacturer = "", product = "", serial = "";

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                eepromHandle = (zend_long)(uintptr_t)_ctx->eeprom;
                int _v = 0;
                ftdi_get_eeprom_value(_ctx, VENDOR_ID,          &_v); vendorId          = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, PRODUCT_ID,         &_v); productId         = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, SELF_POWERED,       &_v); selfPowered       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, REMOTE_WAKEUP,      &_v); remoteWakeup      = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, IS_NOT_PNP,         &_v); isNotPnp          = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, SUSPEND_DBUS7,      &_v); suspendDbus7      = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, IN_IS_ISOCHRONOUS,  &_v); inIsIsochronous   = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, OUT_IS_ISOCHRONOUS, &_v); outIsIsochronous  = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, SUSPEND_PULL_DOWNS, &_v); suspendPullDowns  = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, USE_SERIAL,         &_v); useSerial         = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, USB_VERSION,        &_v); usbVersion        = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, USE_USB_VERSION,    &_v); useUsbVersion     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, MAX_POWER,          &_v); maxPower          = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_A_TYPE,     &_v); channelAType      = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_B_TYPE,     &_v); channelBType      = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_A_DRIVER,   &_v); channelADriver    = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_B_DRIVER,   &_v); channelBDriver    = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_0,    &_v); cbusFunction0     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_1,    &_v); cbusFunction1     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_2,    &_v); cbusFunction2     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_3,    &_v); cbusFunction3     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_4,    &_v); cbusFunction4     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_5,    &_v); cbusFunction5     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_6,    &_v); cbusFunction6     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_7,    &_v); cbusFunction7     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_8,    &_v); cbusFunction8     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CBUS_FUNCTION_9,    &_v); cbusFunction9     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, HIGH_CURRENT,       &_v); highCurrent       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, HIGH_CURRENT_A,     &_v); highCurrentA      = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, HIGH_CURRENT_B,     &_v); highCurrentB      = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, INVERT,             &_v); invert            = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP0_DRIVE,       &_v); group0Drive       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP0_SCHMITT,     &_v); group0Schmitt     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP0_SLEW,        &_v); group0Slew        = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP1_DRIVE,       &_v); group1Drive       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP1_SCHMITT,     &_v); group1Schmitt     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP1_SLEW,        &_v); group1Slew        = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP2_DRIVE,       &_v); group2Drive       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP2_SCHMITT,     &_v); group2Schmitt     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP2_SLEW,        &_v); group2Slew        = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP3_DRIVE,       &_v); group3Drive       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP3_SCHMITT,     &_v); group3Schmitt     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, GROUP3_SLEW,        &_v); group3Slew        = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHIP_SIZE,          &_v); chipSize          = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHIP_TYPE,          &_v); chipType          = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, POWER_SAVE,         &_v); powerSave         = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CLOCK_POLARITY,     &_v); clockPolarity     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, DATA_ORDER,         &_v); dataOrder         = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, FLOW_CONTROL,       &_v); flowControl       = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_C_DRIVER,   &_v); channelCDriver    = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_D_DRIVER,   &_v); channelDDriver    = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_A_RS485,    &_v); channelARs485     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_B_RS485,    &_v); channelBRs485     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_C_RS485,    &_v); channelCRs485     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, CHANNEL_D_RS485,    &_v); channelDRs485     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, RELEASE_NUMBER,     &_v); releaseNumber     = (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, EXTERNAL_OSCILLATOR,&_v); externalOscillator= (zend_long)_v;
                ftdi_get_eeprom_value(_ctx, USER_DATA_ADDR,     &_v); userDataAddr      = (zend_long)_v;

                char _mnf[256] = {0}, _prod[256] = {0}, _ser[256] = {0};
                ftdi_eeprom_get_strings(_ctx,
                    _mnf,  (int)sizeof(_mnf),
                    _prod, (int)sizeof(_prod),
                    _ser,  (int)sizeof(_ser)
                );
                ZVAL_STRING(&manufacturer, _mnf[0] ? _mnf : "");
                ZVAL_STRING(&product,      _prod[0] ? _prod : "");
                ZVAL_STRING(&serial,       _ser[0]  ? _ser  : "");
            }
        }%

        var eeprom;
        let eeprom = new FTDIEeprom();
        let eeprom->eepromHandle       = eepromHandle;
        let eeprom->vendorId           = vendorId;
        let eeprom->productId          = productId;
        let eeprom->selfPowered        = selfPowered;
        let eeprom->remoteWakeup       = remoteWakeup;
        let eeprom->isNotPnp           = isNotPnp;
        let eeprom->suspendDbus7       = suspendDbus7;
        let eeprom->inIsIsochronous    = inIsIsochronous;
        let eeprom->outIsIsochronous   = outIsIsochronous;
        let eeprom->suspendPullDowns   = suspendPullDowns;
        let eeprom->useSerial          = useSerial;
        let eeprom->usbVersion         = usbVersion;
        let eeprom->useUsbVersion      = useUsbVersion;
        let eeprom->maxPower           = maxPower;
        let eeprom->channelAType       = channelAType;
        let eeprom->channelBType       = channelBType;
        let eeprom->channelADriver     = channelADriver;
        let eeprom->channelBDriver     = channelBDriver;
        let eeprom->cbusFunction0      = cbusFunction0;
        let eeprom->cbusFunction1      = cbusFunction1;
        let eeprom->cbusFunction2      = cbusFunction2;
        let eeprom->cbusFunction3      = cbusFunction3;
        let eeprom->cbusFunction4      = cbusFunction4;
        let eeprom->cbusFunction5      = cbusFunction5;
        let eeprom->cbusFunction6      = cbusFunction6;
        let eeprom->cbusFunction7      = cbusFunction7;
        let eeprom->cbusFunction8      = cbusFunction8;
        let eeprom->cbusFunction9      = cbusFunction9;
        let eeprom->highCurrent        = highCurrent;
        let eeprom->highCurrentA       = highCurrentA;
        let eeprom->highCurrentB       = highCurrentB;
        let eeprom->invert             = invert;
        let eeprom->group0Drive        = group0Drive;
        let eeprom->group0Schmitt      = group0Schmitt;
        let eeprom->group0Slew         = group0Slew;
        let eeprom->group1Drive        = group1Drive;
        let eeprom->group1Schmitt      = group1Schmitt;
        let eeprom->group1Slew         = group1Slew;
        let eeprom->group2Drive        = group2Drive;
        let eeprom->group2Schmitt      = group2Schmitt;
        let eeprom->group2Slew         = group2Slew;
        let eeprom->group3Drive        = group3Drive;
        let eeprom->group3Schmitt      = group3Schmitt;
        let eeprom->group3Slew         = group3Slew;
        let eeprom->chipSize           = chipSize;
        let eeprom->chipType           = chipType;
        let eeprom->powerSave          = powerSave;
        let eeprom->clockPolarity      = clockPolarity;
        let eeprom->dataOrder          = dataOrder;
        let eeprom->flowControl        = flowControl;
        let eeprom->channelCDriver     = channelCDriver;
        let eeprom->channelDDriver     = channelDDriver;
        let eeprom->channelARs485      = channelARs485;
        let eeprom->channelBRs485      = channelBRs485;
        let eeprom->channelCRs485      = channelCRs485;
        let eeprom->channelDRs485      = channelDRs485;
        let eeprom->releaseNumber      = releaseNumber;
        let eeprom->externalOscillator = externalOscillator;
        let eeprom->userDataAddr       = userDataAddr;
        let eeprom->manufacturer       = manufacturer;
        let eeprom->product            = product;
        let eeprom->serial             = serial;

        return eeprom;
    }

    public static function ftdiEepromInitDefaults(
        <FTDIContext> ftdi,
        var manufacturer,
        var product,
        var serial
    ) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            char *_m = NULL;
            char *_p = NULL;
            char *_s = NULL;

            result = (zend_long)-1;
            if (_ctx) {
                if (Z_STRLEN_P(manufacturer) > 0) {
                    _m = estrndup(Z_STRVAL_P(manufacturer), Z_STRLEN_P(manufacturer));
                }
                if (Z_STRLEN_P(product) > 0) {
                    _p = estrndup(Z_STRVAL_P(product), Z_STRLEN_P(product));
                }
                if (Z_STRLEN_P(serial) > 0) {
                    _s = estrndup(Z_STRVAL_P(serial), Z_STRLEN_P(serial));
                }
                result = (zend_long)ftdi_eeprom_initdefaults(_ctx, _m, _p, _s);
                if (_m) {
                    efree(_m);
                }
                if (_p) {
                    efree(_p);
                }
                if (_s) {
                    efree(_s);
                }
            }
        }%

        return result;
    }

    public static function ftdiEepromSetStrings(
        <FTDIContext> ftdi,
        var manufacturer,
        var product,
        var serial
    ) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            const char *_m = NULL;
            const char *_p = NULL;
            const char *_s = NULL;

            result = (zend_long)-1;
            if (_ctx) {
                if (Z_STRLEN_P(manufacturer) > 0) {
                    _m = Z_STRVAL_P(manufacturer);
                }
                if (Z_STRLEN_P(product) > 0) {
                    _p = Z_STRVAL_P(product);
                }
                if (Z_STRLEN_P(serial) > 0) {
                    _s = Z_STRVAL_P(serial);
                }
                result = (zend_long)ftdi_eeprom_set_strings(_ctx, _m, _p, _s);
            }
        }%

        return result;
    }

    public static function ftdiEepromGetStrings(<FTDIContext> ftdi) -> array
    {
        var manufacturer;
        var product;
        var serial;
        int handle;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            char _mnf[256]   = {0};
            char _prod[256]  = {0};
            char _serial[256] = {0};

            if (_ctx) {
                (void)ftdi_eeprom_get_strings(
                    _ctx,
                    _mnf,
                    (int)sizeof(_mnf),
                    _prod,
                    (int)sizeof(_prod),
                    _serial,
                    (int)sizeof(_serial)
                );
            }

            ZVAL_STRING(&manufacturer, _mnf);
            ZVAL_STRING(&product, _prod);
            ZVAL_STRING(&serial, _serial);
        }%

        return [
            "manufacturer": manufacturer,
            "product": product,
            "serial": serial
        ];
    }

    public static function ftdiEepromBuild(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_eeprom_build(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiEepromDecode(<FTDIContext> ftdi, int verbose) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_eeprom_decode(_ctx, (int)verbose);
            }
        }%

        return result;
    }

    public static function ftdiGetEepromValue(<FTDIContext> ftdi, int valueName) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            int _value = 0;
            int _rc;

            result = (zend_long)-1;
            if (_ctx) {
                _rc = ftdi_get_eeprom_value(
                    _ctx,
                    (enum ftdi_eeprom_value)valueName,
                    &_value
                );
                if (_rc == 0) {
                    result = (zend_long)_value;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiSetEepromValue(<FTDIContext> ftdi, int valueName, int value) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_eeprom_value(
                    _ctx,
                    (enum ftdi_eeprom_value)valueName,
                    (int)value
                );
            }
        }%

        return result;
    }

    public static function ftdiGetEepromBuf(<FTDIContext> ftdi, int size) -> string
    {
        var out;
        int handle;

        if size <= 0 {
            return "";
        }

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;

            ZVAL_EMPTY_STRING(&out);
            if (_ctx) {
                unsigned char *_buf = (unsigned char *)emalloc((size_t)size);
                if (_buf) {
                    int _rc = ftdi_get_eeprom_buf(_ctx, _buf, size);
                    if (_rc == 0) {
                        ZVAL_STRINGL(&out, (char *)_buf, (size_t)size);
                    } else {
                        ZVAL_EMPTY_STRING(&out);
                    }
                    efree(_buf);
                }
            }
        }%

        return out;
    }

    public static function ftdiSetEepromBuf(<FTDIContext> ftdi, var buf) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_eeprom_buf(
                    _ctx,
                    (const unsigned char *)Z_STRVAL_P(buf),
                    (int)Z_STRLEN_P(buf)
                );
            }
        }%

        return result;
    }

    public static function ftdiSetEepromUserData(<FTDIContext> ftdi, var buf) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_eeprom_user_data(
                    _ctx,
                    Z_STRVAL_P(buf),
                    (int)Z_STRLEN_P(buf)
                );
            }
        }%

        return result;
    }

    /**
     * Encode FT232H CBUS EEPROM bytes via libftdi's set_ft232h_cbus.
     * Requires a decoded EEPROM (ftdi->eeprom); returns the five raw bytes
     * written at offsets 0x18–0x1c of the EEPROM image buffer, or empty string
     * if the context or eeprom pointer is missing.
     */
    public static function setFT232HCbus(<FTDIEeprom> eeprom) -> string
    {
        var out;
        int eepromHandle;

        let eepromHandle = eeprom->eepromHandle;

        %{
            struct ftdi_eeprom *_eep = (struct ftdi_eeprom *)(uintptr_t)eepromHandle;
            unsigned char _buf[64] = {0};

            ZVAL_EMPTY_STRING(&out);
            if (_eep) {
                set_ft232h_cbus(_eep, _buf);
                ZVAL_STRINGL(&out, (char *)(_buf + 0x18), (size_t)5);
            }
        }%

        return out;
    }

    public static function ftdiReadEepromLocation(<FTDIContext> ftdi, int eepromAddr) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            unsigned short _val = 0;
            int _rc;

            result = (zend_long)-1;
            if (_ctx) {
                _rc = ftdi_read_eeprom_location(_ctx, (int)eepromAddr, &_val);
                if (_rc == 0) {
                    result = (zend_long)_val;
                } else {
                    result = (zend_long)_rc;
                }
            }
        }%

        return result;
    }

    public static function ftdiReadEeprom(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_read_eeprom(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiReadChipId(<FTDIContext> ftdi) -> array
    {
        int handle;
        int ret;
        int chipid;

        let handle = ftdi->handle;
        let ret    = -1;
        let chipid = 0;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                unsigned int _chipid_val = 0;
                ret    = (zend_long)ftdi_read_chipid(_ctx, &_chipid_val);
                chipid = (zend_long)_chipid_val;
            }
        }%

        return [
            "result": ret,
            "chipid": chipid
        ];
    }

    public static function ftdiWriteEepromLocation(
        <FTDIContext> ftdi,
        int eepromAddr,
        int eepromVal
    ) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_write_eeprom_location(
                    _ctx,
                    (int)eepromAddr,
                    (unsigned short)eepromVal
                );
            }
        }%

        return result;
    }

    public static function ftdiWriteEeprom(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_write_eeprom(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiEraseEeprom(<FTDIContext> ftdi) -> int
    {
        int handle;
        int result;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_erase_eeprom(_ctx);
            }
        }%

        return result;
    }

    public static function ftdiGetErrorString(<FTDIContext> ftdi) -> string
    {
        int handle;
        var out;

        let handle = ftdi->handle;

        %{
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            const char *_err = NULL;
            if (_ctx) {
                _err = ftdi_get_error_string(_ctx);
            }
            ZVAL_STRING(&out, _err ? _err : "");
        }%

        return out;
    }
}
