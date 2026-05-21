
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
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/object.h"


/**
 * Data Transfer Object representing a libftdi1 context.
 *
 * Populated by FTDI::ftdiNew() after a successful ftdi_new() call.
 * The handle property carries the ftdi_context pointer as an opaque
 * integer -- pass it to every subsequent libftdi1 call.
 * A handle value of -1 indicates an uninitialised or failed context.
 */
ZEPHIR_INIT_CLASS(Ftdi_FTDIContext)
{
	ZEPHIR_REGISTER_CLASS(Ftdi, FTDIContext, ftdi, ftdicontext, ftdi_ftdicontext_method_entry, 0);

	/** Opaque pointer to struct ftdi_context cast to int. -1 = failed. */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("handle"), 0, ZEND_ACC_PUBLIC);
	/**
	 * Chip type (enum ftdi_chip_type):
	 *   0=TYPE_AM  1=TYPE_BM  2=TYPE_2232C  3=TYPE_R
	 *   4=TYPE_2232H  5=TYPE_4232H  6=TYPE_232H  7=TYPE_230X
	 */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("chipType"), 0, ZEND_ACC_PUBLIC);
	/** USB read timeout in milliseconds (libftdi1 default: 5000). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("usbReadTimeout"), 0, ZEND_ACC_PUBLIC);
	/** USB write timeout in milliseconds (libftdi1 default: 5000). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("usbWriteTimeout"), 0, ZEND_ACC_PUBLIC);
	/**
	 * Interface channel index (struct field: index, 1 or 2).
	 * Distinguishes channels on multi-interface chips (FT2232H/FT4232H).
	 */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("interfaceIndex"), 0, ZEND_ACC_PUBLIC);
	/** Configured baud rate (0 until ftdi_set_baudrate is called). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("baudrate"), 0, ZEND_ACC_PUBLIC);
	/** Non-zero when bitbang mode is active. */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("bitbangEnabled"), 0, ZEND_ACC_PUBLIC);
	/**
	 * Active bitbang/MPSSE mode (enum ftdi_mpsse_mode):
	 *   0x00=RESET  0x01=BITBANG  0x02=MPSSE  0x04=SYNCBB
	 *   0x08=MCU    0x10=OPTO     0x20=CBUS   0x40=SYNCFF  0x80=FT1284
	 */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("bitbangMode"), 0, ZEND_ACC_PUBLIC);
	/**
	 * Interface channel (struct field: interface, 0 or 1).
	 * Set via ftdi_set_interface(); 0=INTERFACE_ANY, 1=A, 2=B, 3=C, 4=D.
	 * Named 'channel' to avoid collision with the PHP/Zephir reserved word.
	 */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("channel"), 0, ZEND_ACC_PUBLIC);
	/** USB IN endpoint number (typically 1 or 2). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("inEndpoint"), 0, ZEND_ACC_PUBLIC);
	/** USB OUT endpoint number (typically 1 or 2). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("outEndpoint"), 0, ZEND_ACC_PUBLIC);
	/** Read buffer chunk size in bytes (libftdi1 default: 4096). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("readBufferChunkSize"), 0, ZEND_ACC_PUBLIC);
	/** Write buffer chunk size in bytes (libftdi1 default: 4096). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("writeBufferChunkSize"), 0, ZEND_ACC_PUBLIC);
	/** Maximum USB packet size (derived from device descriptor after open). */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("maxPacketSize"), 0, ZEND_ACC_PUBLIC);
	/**
	 * Kernel module detach mode (enum ftdi_module_detach_mode):
	 *   0=AUTO_DETACH_SIO_MODULE
	 *   1=DONT_DETACH_SIO_MODULE
	 *   2=AUTO_DETACH_REATACH_SIO_MODULE
	 */
	zend_declare_property_long(ftdi_ftdicontext_ce, SL("moduleDetachMode"), 0, ZEND_ACC_PUBLIC);
	/** Last error string from libftdi1 (empty string if none). */
	zend_declare_property_string(ftdi_ftdicontext_ce, SL("errorStr"), "", ZEND_ACC_PUBLIC);
	return SUCCESS;
}

/** Return all context fields as an associative array. */
PHP_METHOD(Ftdi_FTDIContext, toArray)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 16, 0);
	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("handle"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("handle"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("chipType"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("chipType"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("usbReadTimeout"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("usbReadTimeout"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("usbWriteTimeout"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("usbWriteTimeout"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("interfaceIndex"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("interfaceIndex"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("baudrate"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("baudrate"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("bitbangEnabled"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("bitbangEnabled"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("bitbangMode"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("bitbangMode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channel"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channel"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("inEndpoint"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("inEndpoint"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("outEndpoint"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("outEndpoint"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("readBufferChunkSize"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("readBufferChunkSize"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("writeBufferChunkSize"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("writeBufferChunkSize"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("maxPacketSize"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("maxPacketSize"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("moduleDetachMode"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("moduleDetachMode"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("errorStr"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("errorStr"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

