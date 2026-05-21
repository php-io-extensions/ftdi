
extern zend_class_entry *ftdi_ftdiversioninfo_ce;

ZEPHIR_INIT_CLASS(Ftdi_FTDIVersionInfo);

PHP_METHOD(Ftdi_FTDIVersionInfo, toArray);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdiversioninfo_toarray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ftdi_ftdiversioninfo_method_entry) {
	PHP_ME(Ftdi_FTDIVersionInfo, toArray, arginfo_ftdi_ftdiversioninfo_toarray, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
