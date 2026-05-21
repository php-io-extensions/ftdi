
extern zend_class_entry *ftdi_ftditransfercontrol_ce;

ZEPHIR_INIT_CLASS(Ftdi_FTDITransferControl);

PHP_METHOD(Ftdi_FTDITransferControl, toArray);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftditransfercontrol_toarray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ftdi_ftditransfercontrol_method_entry) {
	PHP_ME(Ftdi_FTDITransferControl, toArray, arginfo_ftdi_ftditransfercontrol_toarray, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
