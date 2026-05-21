
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


ZEPHIR_INIT_CLASS(Ftdi_FTDIEeprom)
{
	ZEPHIR_REGISTER_CLASS(Ftdi, FTDIEeprom, ftdi, ftdieeprom, ftdi_ftdieeprom_method_entry, 0);

	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("eepromHandle"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("vendorId"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("productId"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("selfPowered"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("remoteWakeup"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("isNotPnp"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("suspendDbus7"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("inIsIsochronous"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("outIsIsochronous"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("suspendPullDowns"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("useSerial"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("usbVersion"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("useUsbVersion"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("maxPower"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelAType"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelBType"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelADriver"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelBDriver"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction0"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction1"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction2"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction3"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction4"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction5"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction6"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction7"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction8"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("cbusFunction9"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("highCurrent"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("highCurrentA"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("highCurrentB"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("invert"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group0Drive"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group0Schmitt"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group0Slew"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group1Drive"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group1Schmitt"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group1Slew"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group2Drive"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group2Schmitt"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group2Slew"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group3Drive"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group3Schmitt"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("group3Slew"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("chipSize"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("chipType"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("powerSave"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("clockPolarity"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("dataOrder"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("flowControl"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelCDriver"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelDDriver"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelARs485"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelBRs485"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelCRs485"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("channelDRs485"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("releaseNumber"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("externalOscillator"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_long(ftdi_ftdieeprom_ce, SL("userDataAddr"), 0, ZEND_ACC_PUBLIC);
	zend_declare_property_string(ftdi_ftdieeprom_ce, SL("manufacturer"), "", ZEND_ACC_PUBLIC);
	zend_declare_property_string(ftdi_ftdieeprom_ce, SL("product"), "", ZEND_ACC_PUBLIC);
	zend_declare_property_string(ftdi_ftdieeprom_ce, SL("serial"), "", ZEND_ACC_PUBLIC);
	return SUCCESS;
}

PHP_METHOD(Ftdi_FTDIEeprom, toArray)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 61, 0);
	zephir_memory_observe(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("vendorId"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("vendorId"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("productId"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("productId"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("selfPowered"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("selfPowered"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("remoteWakeup"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("remoteWakeup"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("isNotPnp"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("isNotPnp"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("suspendDbus7"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("suspendDbus7"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("inIsIsochronous"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("inIsIsochronous"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("outIsIsochronous"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("outIsIsochronous"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("suspendPullDowns"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("suspendPullDowns"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("useSerial"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("useSerial"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("usbVersion"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("usbVersion"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("useUsbVersion"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("useUsbVersion"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("maxPower"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("maxPower"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelAType"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelAType"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelBType"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelBType"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelADriver"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelADriver"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelBDriver"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelBDriver"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction0"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction0"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction1"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction1"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction2"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction2"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction3"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction3"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction4"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction4"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction5"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction5"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction6"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction6"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction7"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction7"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction8"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction8"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("cbusFunction9"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("cbusFunction9"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("highCurrent"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("highCurrent"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("highCurrentA"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("highCurrentA"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("highCurrentB"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("highCurrentB"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("invert"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("invert"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group0Drive"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group0Drive"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group0Schmitt"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group0Schmitt"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group0Slew"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group0Slew"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group1Drive"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group1Drive"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group1Schmitt"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group1Schmitt"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group1Slew"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group1Slew"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group2Drive"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group2Drive"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group2Schmitt"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group2Schmitt"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group2Slew"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group2Slew"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group3Drive"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group3Drive"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group3Schmitt"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group3Schmitt"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("group3Slew"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("group3Slew"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("chipSize"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("chipSize"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("chipType"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("chipType"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("powerSave"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("powerSave"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("clockPolarity"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("clockPolarity"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("dataOrder"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("dataOrder"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("flowControl"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("flowControl"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelCDriver"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelCDriver"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelDDriver"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelDDriver"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelARs485"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelARs485"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelBRs485"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelBRs485"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelCRs485"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelCRs485"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("channelDRs485"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("channelDRs485"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("releaseNumber"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("releaseNumber"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("externalOscillator"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("externalOscillator"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("userDataAddr"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("userDataAddr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("manufacturer"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("manufacturer"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("product"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("product"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("serial"), PH_NOISY_CC);
	zephir_array_update_string(return_value, SL("serial"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

