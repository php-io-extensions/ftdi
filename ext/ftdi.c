
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "ftdi.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *ftdi_ftdi_ce;
zend_class_entry *ftdi_ftdicontext_ce;
zend_class_entry *ftdi_ftdieeprom_ce;
zend_class_entry *ftdi_ftditransfercontrol_ce;
zend_class_entry *ftdi_ftdiversioninfo_ce;

ZEND_DECLARE_MODULE_GLOBALS(ftdi)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(ftdi)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Ftdi_FTDI);
	ZEPHIR_INIT(Ftdi_FTDIContext);
	ZEPHIR_INIT(Ftdi_FTDIEeprom);
	ZEPHIR_INIT(Ftdi_FTDITransferControl);
	ZEPHIR_INIT(Ftdi_FTDIVersionInfo);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(ftdi)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_ftdi_globals *ftdi_globals)
{
	ftdi_globals->initialized = 0;

	/* Cache Enabled */
	ftdi_globals->cache_enabled = 1;

	/* Recursive Lock */
	ftdi_globals->recursive_lock = 0;

	/* Static cache */
	memset(ftdi_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_ftdi_globals *ftdi_globals)
{
	
}

static PHP_RINIT_FUNCTION(ftdi)
{
	zend_ftdi_globals *ftdi_globals_ptr;
	ftdi_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(ftdi_globals_ptr);
	zephir_initialize_memory(ftdi_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(ftdi)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(ftdi)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_FTDI_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_FTDI_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_FTDI_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_FTDI_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_FTDI_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(ftdi)
{
#if defined(COMPILE_DL_FTDI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(ftdi_globals);
	php_zephir_init_module_globals(ftdi_globals);
}

static PHP_GSHUTDOWN_FUNCTION(ftdi)
{
	
}


zend_function_entry php_ftdi_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_ftdi_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry ftdi_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_ftdi_deps,
	PHP_FTDI_EXTNAME,
	php_ftdi_functions,
	PHP_MINIT(ftdi),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(ftdi),
#else
	NULL,
#endif
	PHP_RINIT(ftdi),
	PHP_RSHUTDOWN(ftdi),
	PHP_MINFO(ftdi),
	PHP_FTDI_VERSION,
	ZEND_MODULE_GLOBALS(ftdi),
	PHP_GINIT(ftdi),
	PHP_GSHUTDOWN(ftdi),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(ftdi),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_FTDI
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(ftdi)
#endif
