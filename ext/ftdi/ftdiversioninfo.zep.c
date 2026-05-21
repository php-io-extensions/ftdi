
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
 * Data Transfer Object for libftdi1 library version information.
 *
 * Populated by FTDI::ftdiGetLibraryVersion() which wraps
 * ftdi_get_library_version(). No device handle is required.
 */
ZEPHIR_INIT_CLASS(Ftdi_FTDIVersionInfo)
{
	ZEPHIR_REGISTER_CLASS(Ftdi, FTDIVersionInfo, ftdi, ftdiversioninfo, ftdi_ftdiversioninfo_method_entry, 0);

	/** Major version number. */
	zend_declare_property_long(ftdi_ftdiversioninfo_ce, SL("major"), 0, ZEND_ACC_PUBLIC);
	/** Minor version number. */
	zend_declare_property_long(ftdi_ftdiversioninfo_ce, SL("minor"), 0, ZEND_ACC_PUBLIC);
	/** Micro (patch) version number. */
	zend_declare_property_long(ftdi_ftdiversioninfo_ce, SL("micro"), 0, ZEND_ACC_PUBLIC);
	/** Human-readable version string, e.g. "1.5". */
	zend_declare_property_string(ftdi_ftdiversioninfo_ce, SL("versionStr"), "", ZEND_ACC_PUBLIC);
	/** Snapshot/build identifier string (empty for release builds). */
	zend_declare_property_string(ftdi_ftdiversioninfo_ce, SL("snapshotStr"), "", ZEND_ACC_PUBLIC);
	return SUCCESS;
}

/** Return all fields as an associative array. */
PHP_METHOD(Ftdi_FTDIVersionInfo, toArray)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 5, 0);
	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("major"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("major"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("minor"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("minor"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("micro"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("micro"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("versionStr"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("versionStr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("snapshotStr"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("snapshotStr"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

