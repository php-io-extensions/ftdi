#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ext.h"
#include "ftdi-eeprom.h"
#include <stdint.h>
#include <libftdi1/ftdi.h>

void ftdi_read_chip_id(zval *return_value, zval *ctx_handle)
{
    struct ftdi_context *_ctx =
        (struct ftdi_context *)(uintptr_t)Z_LVAL_P(ctx_handle);
    unsigned int _chipid = 0;
    int _rc = -1;

    array_init(return_value);

    if (_ctx) {
        _rc = ftdi_read_chipid(_ctx, &_chipid);
        add_assoc_long(return_value, "status", (zend_long)_rc);
        if (_rc == 0) {
            add_assoc_long(return_value, "chipId", (zend_long)_chipid);
        }
    } else {
        add_assoc_long(return_value, "status", (zend_long)-1);
    }
}
