
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
 * Data Transfer Object for libftdi1 asynchronous transfer control state.
 *
 * Populated by FTDI::ftdiWriteDataSubmit() and FTDI::ftdiReadDataSubmit().
 * All pointer fields are stored as opaque integers.
 */
ZEPHIR_INIT_CLASS(Ftdi_FTDITransferControl)
{
	ZEPHIR_REGISTER_CLASS(Ftdi, FTDITransferControl, ftdi, ftditransfercontrol, ftdi_ftditransfercontrol_method_entry, 0);

	/** Opaque pointer to struct ftdi_transfer_control cast to int. */
	zend_declare_property_long(ftdi_ftditransfercontrol_ce, SL("handle"), 0, ZEND_ACC_PUBLIC);
	/** Transfer completion state from struct ftdi_transfer_control::completed. */
	zend_declare_property_long(ftdi_ftditransfercontrol_ce, SL("completed"), 0, ZEND_ACC_PUBLIC);
	/** Requested transfer size in bytes. */
	zend_declare_property_long(ftdi_ftditransfercontrol_ce, SL("size"), 0, ZEND_ACC_PUBLIC);
	/** Current transfer offset in bytes. */
	zend_declare_property_long(ftdi_ftditransfercontrol_ce, SL("offset"), 0, ZEND_ACC_PUBLIC);
	/** Opaque pointer to parent struct ftdi_context cast to int. */
	zend_declare_property_long(ftdi_ftditransfercontrol_ce, SL("contextHandle"), 0, ZEND_ACC_PUBLIC);
	/** Opaque pointer to transfer buffer cast to int. */
	zend_declare_property_long(ftdi_ftditransfercontrol_ce, SL("bufHandle"), 0, ZEND_ACC_PUBLIC);
	return SUCCESS;
}

/** Return all fields as an associative array. */
PHP_METHOD(Ftdi_FTDITransferControl, toArray)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 6, 0);
	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("handle"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("handle"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("completed"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("completed"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("size"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("size"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("offset"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("offset"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("contextHandle"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("contextHandle"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("bufHandle"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("bufHandle"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

