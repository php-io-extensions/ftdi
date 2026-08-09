
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_FTDI_H
#define PHP_FTDI_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_FTDI_NAME        "ftdi"
#define PHP_FTDI_VERSION     "0.7.0"
#define PHP_FTDI_EXTNAME     "ftdi"
#define PHP_FTDI_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_FTDI_ZEPVERSION  "0.19.0-$Id$"
#define PHP_FTDI_DESCRIPTION "The PHP FTDI Extension - bindings for libftdi1"



ZEND_BEGIN_MODULE_GLOBALS(ftdi)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(ftdi)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(ftdi)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(ftdi, v)
#else
	#define ZEPHIR_GLOBAL(v) (ftdi_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_ftdi_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(ftdi_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(ftdi_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def ftdi_globals
#define zend_zephir_globals_def zend_ftdi_globals

extern zend_module_entry ftdi_module_entry;
#define phpext_ftdi_ptr &ftdi_module_entry

#endif
