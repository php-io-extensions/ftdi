
extern zend_class_entry *ftdi_ftdicontext_ce;

ZEPHIR_INIT_CLASS(Ftdi_FTDIContext);

PHP_METHOD(Ftdi_FTDIContext, toArray);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ftdi_ftdicontext_toarray, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(ftdi_ftdicontext_method_entry) {
	PHP_ME(Ftdi_FTDIContext, toArray, arginfo_ftdi_ftdicontext_toarray, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
