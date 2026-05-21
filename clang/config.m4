PHP_ARG_ENABLE(ftdi, whether to enable ftdi, [ --enable-ftdi   Enable Ftdi])

if test "$PHP_FTDI" = "yes"; then

	
	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
	if test "x$PKG_CONFIG" = "xno"; then
		AC_MSG_RESULT([pkg-config not found])
		AC_MSG_ERROR([Please reinstall the pkg-config distribution])
	fi


	AC_MSG_CHECKING([for libftdi1])
	if $PKG_CONFIG --exists libftdi1; then
		PHP_LIBFTDI1_VERSION=`$PKG_CONFIG libftdi1 --modversion`
		PHP_LIBFTDI1_PREFIX=`$PKG_CONFIG libftdi1 --variable=prefix`

		if $PKG_CONFIG --atleast-version=0.0.0 libftdi1; then
			AC_MSG_RESULT([found version $PHP_LIBFTDI1_VERSION, under $PHP_LIBFTDI1_PREFIX])
			PHP_LIBFTDI1_LIBS=`$PKG_CONFIG libftdi1 --libs`
			PHP_LIBFTDI1_INCLUDEDIR=`$PKG_CONFIG libftdi1 --variable=includedir`
			PHP_LIBFTDI1_INCS=-I`dirname $PHP_LIBFTDI1_INCLUDEDIR`

			PHP_EVAL_LIBLINE($PHP_LIBFTDI1_LIBS, FTDI_SHARED_LIBADD)
			PHP_EVAL_INCLINE($PHP_LIBFTDI1_INCS)
		else
			AC_MSG_ERROR(Requested 'libftdi1 >= 0.0.0' but version of libftdi1 is $PHP_LIBFTDI1_VERSION)
		fi
	else
		AC_MSG_ERROR(Unable to find libftdi1 installation)
	fi



	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, FTDI_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_FTDI, 1, [Whether you have Ftdi])
	ftdi_sources="ftdi.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c ftdi/ftdi.zep.c
	ftdi/ftdicontext.zep.c
	ftdi/ftdieeprom.zep.c
	ftdi/ftditransfercontrol.zep.c
	ftdi/ftdiversioninfo.zep.c
	src/ftdi-eeprom.c"
	PHP_NEW_EXTENSION(ftdi, $ftdi_sources, $ext_shared,,  $PHP_LIBFTDI1_INCS )
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "ftdi" "src"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done
	PHP_SUBST(FTDI_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([ftdi], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([ftdi], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/ftdi], [php_FTDI.h])

fi
