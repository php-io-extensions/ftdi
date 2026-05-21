
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"

#include <stdint.h>
#include <sys/time.h>
#include <libftdi1/ftdi.h>
/* Not in public ftdi.h; wraps internal ftdi_convert_baudrate for testing. */
extern int convert_baudrate_UT_export(int baudrate, struct ftdi_context *ftdi,
                                      unsigned short *value, unsigned short *index);
/* Exported from libftdi but not declared in ftdi.h (defined in ftdi.c). */
extern void set_ft232h_cbus(struct ftdi_eeprom *eeprom, unsigned char *output);



ZEPHIR_INIT_CLASS(Ftdi_FTDI)
{
	ZEPHIR_REGISTER_CLASS(Ftdi, FTDI, ftdi, ftdi, ftdi_ftdi_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Ftdi_FTDI, ftdiInit)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_init(_ctx);
            }
        
	RETURN_LONG(result);
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
PHP_METHOD(Ftdi_FTDI, ftdiNew)
{
	zval context, errorStr, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, handle = 0, chipType = 0, usbReadTimeout = 0, usbWriteTimeout = 0, ifaceIdx = 0, baudrate = 0, bitbangEnabled = 0, bitbangMode = 0, channel = 0, inEndpoint = 0, outEndpoint = 0, readBufferChunkSize = 0, writeBufferChunkSize = 0, maxPacketSize = 0, moduleDetachMode = 0;

	ZVAL_UNDEF(&context);
	ZVAL_UNDEF(&errorStr);
	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
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
        
	ZEPHIR_INIT_VAR(&context);
	object_init_ex(&context, ftdi_ftdicontext_ce);
	if (zephir_has_constructor(&context)) {
		ZEPHIR_CALL_METHOD(NULL, &context, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, handle);
	zephir_update_property_zval(&context, ZEND_STRL("handle"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, chipType);
	zephir_update_property_zval(&context, ZEND_STRL("chipType"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, usbReadTimeout);
	zephir_update_property_zval(&context, ZEND_STRL("usbReadTimeout"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, usbWriteTimeout);
	zephir_update_property_zval(&context, ZEND_STRL("usbWriteTimeout"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, ifaceIdx);
	zephir_update_property_zval(&context, ZEND_STRL("interfaceIndex"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, baudrate);
	zephir_update_property_zval(&context, ZEND_STRL("baudrate"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, bitbangEnabled);
	zephir_update_property_zval(&context, ZEND_STRL("bitbangEnabled"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, bitbangMode);
	zephir_update_property_zval(&context, ZEND_STRL("bitbangMode"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, channel);
	zephir_update_property_zval(&context, ZEND_STRL("channel"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, inEndpoint);
	zephir_update_property_zval(&context, ZEND_STRL("inEndpoint"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, outEndpoint);
	zephir_update_property_zval(&context, ZEND_STRL("outEndpoint"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, readBufferChunkSize);
	zephir_update_property_zval(&context, ZEND_STRL("readBufferChunkSize"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, writeBufferChunkSize);
	zephir_update_property_zval(&context, ZEND_STRL("writeBufferChunkSize"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, maxPacketSize);
	zephir_update_property_zval(&context, ZEND_STRL("maxPacketSize"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, moduleDetachMode);
	zephir_update_property_zval(&context, ZEND_STRL("moduleDetachMode"), &_0);
	zephir_update_property_zval(&context, ZEND_STRL("errorStr"), &errorStr);
	RETURN_CCTOR(&context);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetInterface)
{
	zend_long iface, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *iface_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(iface)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &iface_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_interface(_ctx, iface);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiDeinit)
{
	zend_long handle = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                ftdi_deinit(_ctx);
            }
        
}

PHP_METHOD(Ftdi_FTDI, ftdiFree)
{
	zend_long handle = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) { ftdi_free(_ctx); }
        
}

PHP_METHOD(Ftdi_FTDI, ftdiSetUSBDev)
{
	zend_long usbDevHandle, handle = 0;
	zval *ftdi = NULL, ftdi_sub, *usbDevHandle_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(usbDevHandle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &usbDevHandle_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct libusb_device_handle *_usb =
                (struct libusb_device_handle *)(uintptr_t)usbDevHandle;
            if (_ctx) {
                ftdi_set_usbdev(_ctx, _usb);
            }
        
}

/**
 * Return libftdi1 library version information without requiring a device.
 *
 * Wraps ftdi_get_library_version() which returns a struct by value --
 * no ftdi_context is needed.
 *
 * @return <FTDIVersionInfo>
 */
PHP_METHOD(Ftdi_FTDI, ftdiGetLibraryVersion)
{
	zval versionInfo, versionStr, snapshotStr, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, major = 0, minor = 0, micro = 0;

	ZVAL_UNDEF(&versionInfo);
	ZVAL_UNDEF(&versionStr);
	ZVAL_UNDEF(&snapshotStr);
	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	
            struct ftdi_version_info _vi = ftdi_get_library_version();
            major = (zend_long)_vi.major;
            minor = (zend_long)_vi.minor;
            micro = (zend_long)_vi.micro;
            ZVAL_STRING(&versionStr,  _vi.version_str  ? _vi.version_str  : "");
            ZVAL_STRING(&snapshotStr, _vi.snapshot_str ? _vi.snapshot_str : "");
        
	ZEPHIR_INIT_VAR(&versionInfo);
	object_init_ex(&versionInfo, ftdi_ftdiversioninfo_ce);
	if (zephir_has_constructor(&versionInfo)) {
		ZEPHIR_CALL_METHOD(NULL, &versionInfo, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, major);
	zephir_update_property_zval(&versionInfo, ZEND_STRL("major"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, minor);
	zephir_update_property_zval(&versionInfo, ZEND_STRL("minor"), &_0);
	ZVAL_UNDEF(&_0);
	ZVAL_LONG(&_0, micro);
	zephir_update_property_zval(&versionInfo, ZEND_STRL("micro"), &_0);
	zephir_update_property_zval(&versionInfo, ZEND_STRL("versionStr"), &versionStr);
	zephir_update_property_zval(&versionInfo, ZEND_STRL("snapshotStr"), &snapshotStr);
	RETURN_CCTOR(&versionInfo);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBFindAll)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long vendor, product, handle = 0, count = 0, listHandle = 0;
	zval *ftdi = NULL, ftdi_sub, *vendor_param = NULL, *product_param = NULL, _0, _1;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &ftdi, &vendor_param, &product_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, count);
	zephir_array_update_string(return_value, SL("count"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, listHandle);
	zephir_array_update_string(return_value, SL("listHandle"), &_1, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Ftdi_FTDI, ftdiListFree)
{
	zval *listHandle_param = NULL;
	zend_long listHandle;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(listHandle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &listHandle_param);
	
            struct ftdi_device_list *_list =
                (struct ftdi_device_list *)(uintptr_t)listHandle;
            if (_list) {
                ftdi_list_free(&_list);
            }
        
}

PHP_METHOD(Ftdi_FTDI, ftdiListFree2)
{
	zval *listHandle_param = NULL;
	zend_long listHandle;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(listHandle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &listHandle_param);
	
            struct ftdi_device_list *_list =
                (struct ftdi_device_list *)(uintptr_t)listHandle;
            if (_list) {
                ftdi_list_free2(_list);
            }
        
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBGetStrings)
{
	zend_long devHandle, handle = 0;
	zval *ftdi = NULL, ftdi_sub, *devHandle_param = NULL, manufacturer, description, serial, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&manufacturer);
	ZVAL_UNDEF(&description);
	ZVAL_UNDEF(&serial);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(devHandle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &devHandle_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	zephir_create_array(return_value, 3, 0);
	zephir_array_update_string(return_value, SL("manufacturer"), &manufacturer, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("description"), &description, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("serial"), &serial, PH_COPY | PH_SEPARATE);
	return;
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBGetStrings2)
{
	zend_long devHandle, handle = 0;
	zval *ftdi = NULL, ftdi_sub, *devHandle_param = NULL, manufacturer, description, serial, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&manufacturer);
	ZVAL_UNDEF(&description);
	ZVAL_UNDEF(&serial);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(devHandle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &devHandle_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	zephir_create_array(return_value, 3, 0);
	zephir_array_update_string(return_value, SL("manufacturer"), &manufacturer, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("description"), &description, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("serial"), &serial, PH_COPY | PH_SEPARATE);
	return;
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenDev)
{
	zend_long devHandle, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *devHandle_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(devHandle)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &devHandle_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            struct libusb_device *_dev = (struct libusb_device *)(uintptr_t)devHandle;
            result = (zend_long)-1;
            if (_ctx && _dev) {
                result = (zend_long)ftdi_usb_open_dev(_ctx, _dev);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBOpen)
{
	zend_long vendor, product, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *vendor_param = NULL, *product_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &vendor_param, &product_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_open(_ctx, (int)vendor, (int)product);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenDesc)
{
	zend_long vendor, product, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *vendor_param = NULL, *product_param = NULL, *description, description_sub, *serial, serial_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&description_sub);
	ZVAL_UNDEF(&serial_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
		Z_PARAM_ZVAL(description)
		Z_PARAM_ZVAL(serial)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &ftdi, &vendor_param, &product_param, &description, &serial);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenDescIndex)
{
	zend_long vendor, product, index, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *vendor_param = NULL, *product_param = NULL, *description, description_sub, *serial, serial_sub, *index_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&description_sub);
	ZVAL_UNDEF(&serial_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(6, 6)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
		Z_PARAM_ZVAL(description)
		Z_PARAM_ZVAL(serial)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(6, 0, &ftdi, &vendor_param, &product_param, &description, &serial, &index_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenBusAddr)
{
	zend_long bus, addr, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *bus_param = NULL, *addr_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(bus)
		Z_PARAM_LONG(addr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &bus_param, &addr_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_open_bus_addr(
                    _ctx,
                    (uint8_t)bus,
                    (uint8_t)addr
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBOpenString)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *description, description_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&description_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(description)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &description);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_open_string(_ctx, Z_STRVAL_P(description));
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBClose)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_close(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBReset)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_reset(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiTCIFlush)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_tciflush(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiTCOFlush)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_tcoflush(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiTCIOFlush)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_tcioflush(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBPurgeRXBuffer)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_purge_rx_buffer(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBPurgeTXBuffer)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_purge_tx_buffer(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiUSBPurgeBuffers)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_usb_purge_buffers(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiConvertBaudrateUTExport)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *baudrate_param = NULL, *ftdi = NULL, ftdi_sub, _0, _1;
	zend_long baudrate, handle = 0, value = 0, index = 0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(baudrate)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &baudrate_param, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, value);
	zephir_array_update_string(return_value, SL("value"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, index);
	zephir_array_update_string(return_value, SL("index"), &_1, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Ftdi_FTDI, ftdiSetBaudrate)
{
	zend_long baudrate, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *baudrate_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(baudrate)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &baudrate_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_baudrate(_ctx, (int)baudrate);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetLineProperty)
{
	zend_long bits, sbit, parity, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *bits_param = NULL, *sbit_param = NULL, *parity_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(bits)
		Z_PARAM_LONG(sbit)
		Z_PARAM_LONG(parity)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &ftdi, &bits_param, &sbit_param, &parity_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetLineProperty2)
{
	zend_long bits, sbit, parity, breakType, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *bits_param = NULL, *sbit_param = NULL, *parity_param = NULL, *breakType_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(5, 5)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(bits)
		Z_PARAM_LONG(sbit)
		Z_PARAM_LONG(parity)
		Z_PARAM_LONG(breakType)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(5, 0, &ftdi, &bits_param, &sbit_param, &parity_param, &breakType_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiWriteData)
{
	zend_long size, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *data, data_sub, *size_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(data)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &data, &size_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiWriteDataSetChunksize)
{
	zend_long chunksize, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *chunksize_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(chunksize)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &chunksize_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_write_data_set_chunksize(
                    _ctx,
                    (unsigned int)chunksize
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiWriteDataGetChunksize)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadData)
{
	zend_long size, handle = 0;
	zval *ftdi = NULL, ftdi_sub, *size_param = NULL, out, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&out);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &size_param);
	if (size <= 0) {
		RETURN_STRING("");
	}
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_CCTORW(&out);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadDataSetChunksize)
{
	zend_long chunksize, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *chunksize_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(chunksize)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &chunksize_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_read_data_set_chunksize(
                    _ctx,
                    (unsigned int)chunksize
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadDataGetChunksize)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetBitmode)
{
	zend_long bitmask, mode, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *bitmask_param = NULL, *mode_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(bitmask)
		Z_PARAM_LONG(mode)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &bitmask_param, &mode_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_bitmode(
                    _ctx,
                    (unsigned char)bitmask,
                    (unsigned char)mode
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiWriteDataSubmit)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long size, ZEPHIR_LAST_CALL_STATUS, handle = 0, tcHandle = 0, completed = 0, transferSize = 0, offset = 0, contextHandle = 0, bufHandle = 0;
	zval *ftdi = NULL, ftdi_sub, *data, data_sub, *size_param = NULL, transferControl, _0, _1;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&transferControl);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(data)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &ftdi, &data, &size_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	ZEPHIR_INIT_VAR(&transferControl);
	object_init_ex(&transferControl, ftdi_ftditransfercontrol_ce);
	if (zephir_has_constructor(&transferControl)) {
		ZEPHIR_CALL_METHOD(NULL, &transferControl, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, tcHandle);
	zephir_update_property_zval(&transferControl, ZEND_STRL("handle"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, completed);
	zephir_update_property_zval(&transferControl, ZEND_STRL("completed"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, transferSize);
	zephir_update_property_zval(&transferControl, ZEND_STRL("size"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, offset);
	zephir_update_property_zval(&transferControl, ZEND_STRL("offset"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, contextHandle);
	zephir_update_property_zval(&transferControl, ZEND_STRL("contextHandle"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, bufHandle);
	zephir_update_property_zval(&transferControl, ZEND_STRL("bufHandle"), &_1);
	RETURN_CCTOR(&transferControl);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadDataSubmit)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long size, ZEPHIR_LAST_CALL_STATUS, handle = 0, tcHandle = 0, completed = 0, transferSize = 0, offset = 0, contextHandle = 0, bufHandle = 0;
	zval *ftdi = NULL, ftdi_sub, *size_param = NULL, transferControl, _0, _1;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&transferControl);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &ftdi, &size_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	ZEPHIR_INIT_VAR(&transferControl);
	object_init_ex(&transferControl, ftdi_ftditransfercontrol_ce);
	if (zephir_has_constructor(&transferControl)) {
		ZEPHIR_CALL_METHOD(NULL, &transferControl, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, tcHandle);
	zephir_update_property_zval(&transferControl, ZEND_STRL("handle"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, completed);
	zephir_update_property_zval(&transferControl, ZEND_STRL("completed"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, transferSize);
	zephir_update_property_zval(&transferControl, ZEND_STRL("size"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, offset);
	zephir_update_property_zval(&transferControl, ZEND_STRL("offset"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, contextHandle);
	zephir_update_property_zval(&transferControl, ZEND_STRL("contextHandle"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, bufHandle);
	zephir_update_property_zval(&transferControl, ZEND_STRL("bufHandle"), &_1);
	RETURN_CCTOR(&transferControl);
}

PHP_METHOD(Ftdi_FTDI, ftdiTransferDataDone)
{
	zend_long handle = 0, result = 0;
	zval *tc = NULL, tc_sub, _0;

	ZVAL_UNDEF(&tc_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(tc, zephir_get_internal_ce(SL("ftdi\\ftditransfercontrol")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &tc);
	zephir_read_property(&_0, tc, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_transfer_control *_tc = (struct ftdi_transfer_control *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_tc) {
                result = (zend_long)ftdi_transfer_data_done(_tc);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiTransferDataCancel)
{
	zend_long handle = 0;
	zval *tc = NULL, tc_sub, _0;

	ZVAL_UNDEF(&tc_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(tc, zephir_get_internal_ce(SL("ftdi\\ftditransfercontrol")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &tc);
	zephir_read_property(&_0, tc, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_transfer_control *_tc = (struct ftdi_transfer_control *)(uintptr_t)handle;
            struct timeval _to;
            _to.tv_sec = 0;
            _to.tv_usec = 0;
            if (_tc) {
                (void)ftdi_transfer_data_cancel(_tc, &_to);
            }
        
}

PHP_METHOD(Ftdi_FTDI, ftdiDisableBitbang)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_disable_bitbang(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadPins)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetLatencyTimer)
{
	zend_long latency, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *latency_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(latency)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &latency_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_latency_timer(
                    _ctx,
                    (unsigned char)latency
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetTimeouts)
{
	zend_long readTimeout, writeTimeout, handle = 0;
	zval *ftdi = NULL, ftdi_sub, *readTimeout_param = NULL, *writeTimeout_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(readTimeout)
		Z_PARAM_LONG(writeTimeout)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &readTimeout_param, &writeTimeout_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                _ctx->usb_read_timeout  = (int)readTimeout;
                _ctx->usb_write_timeout = (int)writeTimeout;
            }
        
}

PHP_METHOD(Ftdi_FTDI, ftdiGetLatencyTimer)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiPollModemStatus)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetFlowCtrl)
{
	zend_long flowctrl, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *flowctrl_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(flowctrl)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &flowctrl_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setflowctrl(_ctx, (int)flowctrl);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetFlowCtrlXonXoff)
{
	zend_long xon, xoff, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *xon_param = NULL, *xoff_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(xon)
		Z_PARAM_LONG(xoff)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &xon_param, &xoff_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setflowctrl_xonxoff(
                    _ctx,
                    (unsigned char)xon,
                    (unsigned char)xoff
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetDtr)
{
	zend_long state, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *state_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &state_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setdtr(_ctx, (int)state);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetRts)
{
	zend_long state, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *state_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &state_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setrts(_ctx, (int)state);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetDtrRts)
{
	zend_long dtr, rts, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *dtr_param = NULL, *rts_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(dtr)
		Z_PARAM_LONG(rts)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &dtr_param, &rts_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_setdtr_rts(_ctx, (int)dtr, (int)rts);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetEventChar)
{
	zend_long eventch, enable, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *eventch_param = NULL, *enable_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(eventch)
		Z_PARAM_LONG(enable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &eventch_param, &enable_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_event_char(
                    _ctx,
                    (unsigned char)eventch,
                    (unsigned char)enable
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetErrorChar)
{
	zend_long errorch, enable, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *errorch_param = NULL, *enable_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(errorch)
		Z_PARAM_LONG(enable)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &errorch_param, &enable_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_error_char(
                    _ctx,
                    (unsigned char)errorch,
                    (unsigned char)enable
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiGetEeprom)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, handle = 0, eepromHandle = 0, vendorId = 0, productId = 0, selfPowered = 0, remoteWakeup = 0, isNotPnp = 0, suspendDbus7 = 0, inIsIsochronous = 0, outIsIsochronous = 0, suspendPullDowns = 0, useSerial = 0, usbVersion = 0, useUsbVersion = 0, maxPower = 0, channelAType = 0, channelBType = 0, channelADriver = 0, channelBDriver = 0, cbusFunction0 = 0, cbusFunction1 = 0, cbusFunction2 = 0, cbusFunction3 = 0, cbusFunction4 = 0, cbusFunction5 = 0, cbusFunction6 = 0, cbusFunction7 = 0, cbusFunction8 = 0, cbusFunction9 = 0, highCurrent = 0, highCurrentA = 0, highCurrentB = 0, invert = 0, group0Drive = 0, group0Schmitt = 0, group0Slew = 0, group1Drive = 0, group1Schmitt = 0, group1Slew = 0, group2Drive = 0, group2Schmitt = 0, group2Slew = 0, group3Drive = 0, group3Schmitt = 0, group3Slew = 0, chipSize = 0, chipType = 0, powerSave = 0, clockPolarity = 0, dataOrder = 0, flowControl = 0, channelCDriver = 0, channelDDriver = 0, channelARs485 = 0, channelBRs485 = 0, channelCRs485 = 0, channelDRs485 = 0, releaseNumber = 0, externalOscillator = 0, userDataAddr = 0;
	zval *ftdi = NULL, ftdi_sub, manufacturer, product, serial, _0, eeprom, _1;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&manufacturer);
	ZVAL_UNDEF(&product);
	ZVAL_UNDEF(&serial);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&eeprom);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	eepromHandle = 0;
	vendorId = 0;
	productId = 0;
	selfPowered = 0;
	remoteWakeup = 0;
	isNotPnp = 0;
	suspendDbus7 = 0;
	inIsIsochronous = 0;
	outIsIsochronous = 0;
	suspendPullDowns = 0;
	useSerial = 0;
	usbVersion = 0;
	useUsbVersion = 0;
	maxPower = 0;
	channelAType = 0;
	channelBType = 0;
	channelADriver = 0;
	channelBDriver = 0;
	cbusFunction0 = 0;
	cbusFunction1 = 0;
	cbusFunction2 = 0;
	cbusFunction3 = 0;
	cbusFunction4 = 0;
	cbusFunction5 = 0;
	cbusFunction6 = 0;
	cbusFunction7 = 0;
	cbusFunction8 = 0;
	cbusFunction9 = 0;
	highCurrent = 0;
	highCurrentA = 0;
	highCurrentB = 0;
	invert = 0;
	group0Drive = 0;
	group0Schmitt = 0;
	group0Slew = 0;
	group1Drive = 0;
	group1Schmitt = 0;
	group1Slew = 0;
	group2Drive = 0;
	group2Schmitt = 0;
	group2Slew = 0;
	group3Drive = 0;
	group3Schmitt = 0;
	group3Slew = 0;
	chipSize = 0;
	chipType = 0;
	powerSave = 0;
	clockPolarity = 0;
	dataOrder = 0;
	flowControl = 0;
	channelCDriver = 0;
	channelDDriver = 0;
	channelARs485 = 0;
	channelBRs485 = 0;
	channelCRs485 = 0;
	channelDRs485 = 0;
	releaseNumber = 0;
	externalOscillator = 0;
	userDataAddr = 0;
	ZEPHIR_INIT_VAR(&manufacturer);
	ZVAL_STRING(&manufacturer, "");
	ZEPHIR_INIT_VAR(&product);
	ZVAL_STRING(&product, "");
	ZEPHIR_INIT_VAR(&serial);
	ZVAL_STRING(&serial, "");
	
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
        
	ZEPHIR_INIT_VAR(&eeprom);
	object_init_ex(&eeprom, ftdi_ftdieeprom_ce);
	if (zephir_has_constructor(&eeprom)) {
		ZEPHIR_CALL_METHOD(NULL, &eeprom, "__construct", NULL, 0);
		zephir_check_call_status();
	}

	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, eepromHandle);
	zephir_update_property_zval(&eeprom, ZEND_STRL("eepromHandle"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, vendorId);
	zephir_update_property_zval(&eeprom, ZEND_STRL("vendorId"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, productId);
	zephir_update_property_zval(&eeprom, ZEND_STRL("productId"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, selfPowered);
	zephir_update_property_zval(&eeprom, ZEND_STRL("selfPowered"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, remoteWakeup);
	zephir_update_property_zval(&eeprom, ZEND_STRL("remoteWakeup"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, isNotPnp);
	zephir_update_property_zval(&eeprom, ZEND_STRL("isNotPnp"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, suspendDbus7);
	zephir_update_property_zval(&eeprom, ZEND_STRL("suspendDbus7"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, inIsIsochronous);
	zephir_update_property_zval(&eeprom, ZEND_STRL("inIsIsochronous"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, outIsIsochronous);
	zephir_update_property_zval(&eeprom, ZEND_STRL("outIsIsochronous"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, suspendPullDowns);
	zephir_update_property_zval(&eeprom, ZEND_STRL("suspendPullDowns"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, useSerial);
	zephir_update_property_zval(&eeprom, ZEND_STRL("useSerial"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, usbVersion);
	zephir_update_property_zval(&eeprom, ZEND_STRL("usbVersion"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, useUsbVersion);
	zephir_update_property_zval(&eeprom, ZEND_STRL("useUsbVersion"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, maxPower);
	zephir_update_property_zval(&eeprom, ZEND_STRL("maxPower"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelAType);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelAType"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelBType);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelBType"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelADriver);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelADriver"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelBDriver);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelBDriver"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction0);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction0"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction1);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction1"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction2);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction2"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction3);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction3"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction4);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction4"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction5);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction5"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction6);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction6"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction7);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction7"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction8);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction8"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, cbusFunction9);
	zephir_update_property_zval(&eeprom, ZEND_STRL("cbusFunction9"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, highCurrent);
	zephir_update_property_zval(&eeprom, ZEND_STRL("highCurrent"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, highCurrentA);
	zephir_update_property_zval(&eeprom, ZEND_STRL("highCurrentA"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, highCurrentB);
	zephir_update_property_zval(&eeprom, ZEND_STRL("highCurrentB"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, invert);
	zephir_update_property_zval(&eeprom, ZEND_STRL("invert"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group0Drive);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group0Drive"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group0Schmitt);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group0Schmitt"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group0Slew);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group0Slew"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group1Drive);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group1Drive"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group1Schmitt);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group1Schmitt"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group1Slew);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group1Slew"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group2Drive);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group2Drive"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group2Schmitt);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group2Schmitt"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group2Slew);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group2Slew"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group3Drive);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group3Drive"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group3Schmitt);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group3Schmitt"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, group3Slew);
	zephir_update_property_zval(&eeprom, ZEND_STRL("group3Slew"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, chipSize);
	zephir_update_property_zval(&eeprom, ZEND_STRL("chipSize"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, chipType);
	zephir_update_property_zval(&eeprom, ZEND_STRL("chipType"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, powerSave);
	zephir_update_property_zval(&eeprom, ZEND_STRL("powerSave"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, clockPolarity);
	zephir_update_property_zval(&eeprom, ZEND_STRL("clockPolarity"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, dataOrder);
	zephir_update_property_zval(&eeprom, ZEND_STRL("dataOrder"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, flowControl);
	zephir_update_property_zval(&eeprom, ZEND_STRL("flowControl"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelCDriver);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelCDriver"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelDDriver);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelDDriver"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelARs485);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelARs485"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelBRs485);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelBRs485"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelCRs485);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelCRs485"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, channelDRs485);
	zephir_update_property_zval(&eeprom, ZEND_STRL("channelDRs485"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, releaseNumber);
	zephir_update_property_zval(&eeprom, ZEND_STRL("releaseNumber"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, externalOscillator);
	zephir_update_property_zval(&eeprom, ZEND_STRL("externalOscillator"), &_1);
	ZVAL_UNDEF(&_1);
	ZVAL_LONG(&_1, userDataAddr);
	zephir_update_property_zval(&eeprom, ZEND_STRL("userDataAddr"), &_1);
	zephir_update_property_zval(&eeprom, ZEND_STRL("manufacturer"), &manufacturer);
	zephir_update_property_zval(&eeprom, ZEND_STRL("product"), &product);
	zephir_update_property_zval(&eeprom, ZEND_STRL("serial"), &serial);
	RETURN_CCTOR(&eeprom);
}

PHP_METHOD(Ftdi_FTDI, ftdiEepromInitDefaults)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *manufacturer, manufacturer_sub, *product, product_sub, *serial, serial_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&manufacturer_sub);
	ZVAL_UNDEF(&product_sub);
	ZVAL_UNDEF(&serial_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(manufacturer)
		Z_PARAM_ZVAL(product)
		Z_PARAM_ZVAL(serial)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &ftdi, &manufacturer, &product, &serial);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiEepromSetStrings)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *manufacturer, manufacturer_sub, *product, product_sub, *serial, serial_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&manufacturer_sub);
	ZVAL_UNDEF(&product_sub);
	ZVAL_UNDEF(&serial_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(manufacturer)
		Z_PARAM_ZVAL(product)
		Z_PARAM_ZVAL(serial)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(4, 0, &ftdi, &manufacturer, &product, &serial);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiEepromGetStrings)
{
	zend_long handle = 0;
	zval *ftdi = NULL, ftdi_sub, manufacturer, product, serial, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&manufacturer);
	ZVAL_UNDEF(&product);
	ZVAL_UNDEF(&serial);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	zephir_create_array(return_value, 3, 0);
	zephir_array_update_string(return_value, SL("manufacturer"), &manufacturer, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("product"), &product, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("serial"), &serial, PH_COPY | PH_SEPARATE);
	return;
}

PHP_METHOD(Ftdi_FTDI, ftdiEepromBuild)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_eeprom_build(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiEepromDecode)
{
	zend_long verbose, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *verbose_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(verbose)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &verbose_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_eeprom_decode(_ctx, (int)verbose);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiGetEepromValue)
{
	zend_long valueName, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *valueName_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(valueName)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &valueName_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetEepromValue)
{
	zend_long valueName, value, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *valueName_param = NULL, *value_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(valueName)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &valueName_param, &value_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_eeprom_value(
                    _ctx,
                    (enum ftdi_eeprom_value)valueName,
                    (int)value
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiGetEepromBuf)
{
	zend_long size, handle = 0;
	zval *ftdi = NULL, ftdi_sub, *size_param = NULL, out, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&out);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &size_param);
	if (size <= 0) {
		RETURN_STRING("");
	}
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_CCTORW(&out);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetEepromBuf)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *buf, buf_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&buf_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(buf)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &buf);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_eeprom_buf(
                    _ctx,
                    (const unsigned char *)Z_STRVAL_P(buf),
                    (int)Z_STRLEN_P(buf)
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiSetEepromUserData)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *buf, buf_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&buf_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_ZVAL(buf)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &buf);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_set_eeprom_user_data(
                    _ctx,
                    Z_STRVAL_P(buf),
                    (int)Z_STRLEN_P(buf)
                );
            }
        
	RETURN_LONG(result);
}

/**
 * Encode FT232H CBUS EEPROM bytes via libftdi's set_ft232h_cbus.
 * Requires a decoded EEPROM (ftdi->eeprom); returns the five raw bytes
 * written at offsets 0x18–0x1c of the EEPROM image buffer, or empty string
 * if the context or eeprom pointer is missing.
 */
PHP_METHOD(Ftdi_FTDI, setFT232HCbus)
{
	zend_long eepromHandle = 0;
	zval *eeprom = NULL, eeprom_sub, out, _0;

	ZVAL_UNDEF(&eeprom_sub);
	ZVAL_UNDEF(&out);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(eeprom, zephir_get_internal_ce(SL("ftdi\\ftdieeprom")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &eeprom);
	zephir_read_property(&_0, eeprom, ZEND_STRL("eepromHandle"), PH_NOISY_CC | PH_READONLY);
	eepromHandle = zephir_get_numberval(&_0);
	
            struct ftdi_eeprom *_eep = (struct ftdi_eeprom *)(uintptr_t)eepromHandle;
            unsigned char _buf[64] = {0};

            ZVAL_EMPTY_STRING(&out);
            if (_eep) {
                set_ft232h_cbus(_eep, _buf);
                ZVAL_STRINGL(&out, (char *)(_buf + 0x18), (size_t)5);
            }
        
	RETURN_CCTORW(&out);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadEepromLocation)
{
	zend_long eepromAddr, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *eepromAddr_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(eepromAddr)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &ftdi, &eepromAddr_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
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
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadEeprom)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_read_eeprom(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiReadChipId)
{
	zend_long handle = 0, ret = 0, chipid = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *ftdi = NULL, ftdi_sub, _0, _1;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	ret = -1;
	chipid = 0;
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            if (_ctx) {
                unsigned int _chipid_val = 0;
                ret    = (zend_long)ftdi_read_chipid(_ctx, &_chipid_val);
                chipid = (zend_long)_chipid_val;
            }
        
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, ret);
	zephir_array_update_string(return_value, SL("result"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, chipid);
	zephir_array_update_string(return_value, SL("chipid"), &_1, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Ftdi_FTDI, ftdiWriteEepromLocation)
{
	zend_long eepromAddr, eepromVal, handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, *eepromAddr_param = NULL, *eepromVal_param = NULL, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
		Z_PARAM_LONG(eepromAddr)
		Z_PARAM_LONG(eepromVal)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(3, 0, &ftdi, &eepromAddr_param, &eepromVal_param);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_write_eeprom_location(
                    _ctx,
                    (int)eepromAddr,
                    (unsigned short)eepromVal
                );
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiWriteEeprom)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_write_eeprom(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiEraseEeprom)
{
	zend_long handle = 0, result = 0;
	zval *ftdi = NULL, ftdi_sub, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            result = (zend_long)-1;
            if (_ctx) {
                result = (zend_long)ftdi_erase_eeprom(_ctx);
            }
        
	RETURN_LONG(result);
}

PHP_METHOD(Ftdi_FTDI, ftdiGetErrorString)
{
	zend_long handle = 0;
	zval *ftdi = NULL, ftdi_sub, out, _0;

	ZVAL_UNDEF(&ftdi_sub);
	ZVAL_UNDEF(&out);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(ftdi, zephir_get_internal_ce(SL("ftdi\\ftdicontext")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &ftdi);
	zephir_read_property(&_0, ftdi, ZEND_STRL("handle"), PH_NOISY_CC | PH_READONLY);
	handle = zephir_get_numberval(&_0);
	
            struct ftdi_context *_ctx = (struct ftdi_context *)(uintptr_t)handle;
            const char *_err = NULL;
            if (_ctx) {
                _err = ftdi_get_error_string(_ctx);
            }
            ZVAL_STRING(&out, _err ? _err : "");
        
	RETURN_CCTORW(&out);
}

