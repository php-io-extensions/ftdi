
extern zend_class_entry *ftdi_ftdieeprom_ce;

ZEPHIR_INIT_CLASS(Ftdi_FTDIEeprom);

PHP_METHOD(Ftdi_FTDIEeprom, toArray);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdieeprom_toarray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ftdi_ftdieeprom_method_entry) {
	PHP_ME(Ftdi_FTDIEeprom, toArray, arginfo_ftdi_ftdieeprom_toarray, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
