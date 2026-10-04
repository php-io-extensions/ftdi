PHP_ARG_ENABLE([ftdi],
  [whether to enable ftdi support],
  [AS_HELP_STRING([--enable-ftdi], [Enable libftdi1 bindings])],
  [no])

if test "$PHP_FTDI" != "no"; then
  PKG_CHECK_MODULES([LIBFTDI1], [libftdi1 >= 1.5])
  PKG_CHECK_MODULES([LIBUSB1], [libusb-1.0 >= 1.0.16])
  PHP_EVAL_INCLINE([$LIBFTDI1_CFLAGS $LIBUSB1_CFLAGS])
  PHP_EVAL_LIBLINE([$LIBFTDI1_LIBS $LIBUSB1_LIBS], [FTDI_SHARED_LIBADD])
  PHP_SUBST([FTDI_SHARED_LIBADD])
  PHP_NEW_EXTENSION([ftdi], [ftdi.c], [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
fi
