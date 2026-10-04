#ifndef PHP_FTDI_H
#define PHP_FTDI_H

extern zend_module_entry ftdi_module_entry;
#define phpext_ftdi_ptr &ftdi_module_entry

#define PHP_FTDI_VERSION "0.10.0"

#if defined(ZTS) && defined(COMPILE_DL_FTDI)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif /* PHP_FTDI_H */
