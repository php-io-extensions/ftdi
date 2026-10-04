/*
 * ftdi: libftdi1 bindings. Global ftdi_* functions under the names microscrap/ftdi
 * exported, Ftdi\FTDIContext / FTDIDevice / FTDITransferControl objects that own
 * their C pointers, Ftdi\FTDIVersionInfo / FTDIEeprom value snapshots, the
 * Ftdi\FtdiVendorId / FtdiProductId enums, and every ftdi.h enum member and
 * numeric #define as a constant.
 *
 * A context tracks the transfers and devices made from it. Before anything tears
 * down its libusb state (ftdi_usb_close, ftdi_deinit, ftdi_free, ftdi_init over an
 * initialised context, or the object being released) it cancels its pending
 * transfers, and before its libusb context goes it unreferences its devices, so
 * no dependent ever touches freed libusb memory.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "Zend/zend_enum.h"
#include "Zend/zend_exceptions.h"
#include "php_ftdi.h"

#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <ftdi.h>
#include <libusb.h>

#include "ftdi_arginfo.h"

/* Exported by libftdi but absent from ftdi.h: the baud rate divisor calculation, exported for its unit tests. */
extern int convert_baudrate_UT_export(int baudrate, struct ftdi_context *ftdi, unsigned short *value, unsigned short *index);
/* Exported by libftdi but absent from ftdi.h: encodes the FT232H CBUS functions into an EEPROM image. */
extern void set_ft232h_cbus(struct ftdi_eeprom *eeprom, unsigned char *output);

static zend_class_entry *ftdi_context_ce;
static zend_class_entry *ftdi_device_ce;
static zend_class_entry *ftdi_transfer_ce;
static zend_class_entry *ftdi_version_ce;
static zend_class_entry *ftdi_eeprom_ce;

static zend_object_handlers ftdi_context_handlers;
static zend_object_handlers ftdi_device_handlers;
static zend_object_handlers ftdi_transfer_handlers;

typedef struct {
	struct ftdi_context *ctx;  /* NULL once ftdi_free() released it */
	bool initialized;          /* false between ftdi_deinit() and ftdi_init() */
	bool strings[3];           /* which of the EEPROM manufacturer, product, serial strings libftdi holds (see ftdi_eeprom_strings_into) */
	HashTable dependents;      /* object handle => zend_object* of each live FTDIDevice / FTDITransferControl */
	zend_object std;
} ftdi_context_obj;

typedef struct {
	struct libusb_device *dev; /* referenced; NULL once released */
	zend_object *context;      /* owning FTDIContext, referenced; NULL once that context is gone */
	zend_object std;
} ftdi_device_obj;

typedef struct {
	struct ftdi_transfer_control *tc; /* NULL once collected or cancelled */
	unsigned char *buf;               /* the transfer's buffer, owned until then */
	zend_long size;
	zend_long offset;                 /* bytes moved, kept once tc is gone */
	zend_object *context;             /* owning FTDIContext, referenced; NULL once that context is gone */
	zend_object std;
} ftdi_transfer_obj;

#define FTDI_FROM(type, obj) ((type *) ((char *) (obj) - XtOffsetOf(type, std)))

/* {{{ dependents */

static void ftdi_transfer_finish(ftdi_transfer_obj *t)
{
	if (t->tc) {
		struct timeval zero = { 0, 0 };

		t->offset = t->tc->offset;
		/* Cancels a pending transfer, waits for libusb to confirm, frees tc. */
		ftdi_transfer_data_cancel(t->tc, &zero);
		t->tc = NULL;
	}
	if (t->buf) {
		efree(t->buf);
		t->buf = NULL;
	}
}

static void ftdi_device_release(ftdi_device_obj *d)
{
	if (d->dev) {
		libusb_unref_device(d->dev);
		d->dev = NULL;
	}
}

/* Cancels every pending transfer; with devices, also drops every device reference (before libusb_exit). */
static void ftdi_release_dependents(ftdi_context_obj *c, bool devices)
{
	zend_object *dep;

	ZEND_HASH_FOREACH_PTR(&c->dependents, dep) {
		if (dep->ce == ftdi_transfer_ce) {
			ftdi_transfer_finish(FTDI_FROM(ftdi_transfer_obj, dep));
		} else if (devices) {
			ftdi_device_release(FTDI_FROM(ftdi_device_obj, dep));
		}
	} ZEND_HASH_FOREACH_END();
}

static void ftdi_adopt(zend_object *context, zend_object *dep, zend_object **slot)
{
	*slot = context;
	GC_ADDREF(context);
	zend_hash_index_add_new_ptr(&FTDI_FROM(ftdi_context_obj, context)->dependents, dep->handle, dep);
}

static void ftdi_disown(zend_object *dep, zend_object **slot)
{
	if (*slot) {
		zend_hash_index_del(&FTDI_FROM(ftdi_context_obj, *slot)->dependents, dep->handle);
		OBJ_RELEASE(*slot);
		*slot = NULL;
	}
}

/* }}} */

/* {{{ objects */

static zend_object *ftdi_context_create(zend_class_entry *ce)
{
	ftdi_context_obj *c = zend_object_alloc(sizeof(ftdi_context_obj), ce);

	zend_object_std_init(&c->std, ce);
	c->std.handlers = &ftdi_context_handlers;
	zend_hash_init(&c->dependents, 4, NULL, NULL, 0);
	return &c->std;
}

static void ftdi_context_free(zend_object *obj)
{
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);
	zend_object *dep;

	/*
	 * Outside shutdown and GC a context outlives its dependents, which reference
	 * it. Both of those can free it first, so dependents are finished here and
	 * told the context is gone.
	 */
	ftdi_release_dependents(c, true);
	ZEND_HASH_FOREACH_PTR(&c->dependents, dep) {
		if (dep->ce == ftdi_transfer_ce) {
			FTDI_FROM(ftdi_transfer_obj, dep)->context = NULL;
		} else {
			FTDI_FROM(ftdi_device_obj, dep)->context = NULL;
		}
	} ZEND_HASH_FOREACH_END();
	zend_hash_destroy(&c->dependents);

	if (c->ctx) {
		ftdi_free(c->ctx);
		c->ctx = NULL;
	}
	zend_object_std_dtor(obj);
}

static zend_object *ftdi_device_create(zend_class_entry *ce)
{
	ftdi_device_obj *d = zend_object_alloc(sizeof(ftdi_device_obj), ce);

	zend_object_std_init(&d->std, ce);
	d->std.handlers = &ftdi_device_handlers;
	return &d->std;
}

static void ftdi_device_free(zend_object *obj)
{
	ftdi_device_obj *d = FTDI_FROM(ftdi_device_obj, obj);

	if (d->context) {
		ftdi_device_release(d);
		ftdi_disown(obj, &d->context);
	}
	zend_object_std_dtor(obj);
}

static zend_object *ftdi_transfer_create(zend_class_entry *ce)
{
	ftdi_transfer_obj *t = zend_object_alloc(sizeof(ftdi_transfer_obj), ce);

	zend_object_std_init(&t->std, ce);
	t->std.handlers = &ftdi_transfer_handlers;
	return &t->std;
}

static void ftdi_transfer_free(zend_object *obj)
{
	ftdi_transfer_obj *t = FTDI_FROM(ftdi_transfer_obj, obj);

	if (t->context) {
		ftdi_transfer_finish(t);
		ftdi_disown(obj, &t->context);
	}
	zend_object_std_dtor(obj);
}

/* }}} */

/* {{{ live read-only properties */

static const char *const ftdi_context_fields[] = {
	"chipType", "usbReadTimeout", "usbWriteTimeout", "interfaceIndex", "baudrate", "bitbangEnabled",
	"bitbangMode", "channel", "inEndpoint", "outEndpoint", "readBufferChunkSize", "writeBufferChunkSize",
	"maxPacketSize", "moduleDetachMode", "errorStr",
};

static const char *const ftdi_transfer_fields[] = { "completed", "size", "offset" };

static int ftdi_field_index(const char *const *fields, size_t count, const zend_string *name)
{
	for (size_t i = 0; i < count; i++) {
		if (zend_string_equals_cstr(name, fields[i], strlen(fields[i]))) {
			return (int) i;
		}
	}
	return -1;
}

static void ftdi_context_field(struct ftdi_context *ctx, int i, zval *rv)
{
	switch (i) {
		case 0: ZVAL_LONG(rv, ctx->type); break;
		case 1: ZVAL_LONG(rv, ctx->usb_read_timeout); break;
		case 2: ZVAL_LONG(rv, ctx->usb_write_timeout); break;
		case 3: ZVAL_LONG(rv, ctx->index); break;
		case 4: ZVAL_LONG(rv, ctx->baudrate); break;
		case 5: ZVAL_LONG(rv, ctx->bitbang_enabled); break;
		case 6: ZVAL_LONG(rv, ctx->bitbang_mode); break;
		case 7: ZVAL_LONG(rv, ctx->interface); break;
		case 8: ZVAL_LONG(rv, ctx->in_ep); break;
		case 9: ZVAL_LONG(rv, ctx->out_ep); break;
		case 10: ZVAL_LONG(rv, ctx->readbuffer_chunksize); break;
		case 11: ZVAL_LONG(rv, ctx->writebuffer_chunksize); break;
		case 12: ZVAL_LONG(rv, ctx->max_packet_size); break;
		case 13: ZVAL_LONG(rv, ctx->module_detach_mode); break;
		default: ZVAL_STRING(rv, ctx->error_str ? ctx->error_str : ""); break;
	}
}

static void ftdi_transfer_field(ftdi_transfer_obj *t, int i, zval *rv)
{
	switch (i) {
		case 0: ZVAL_LONG(rv, t->tc ? t->tc->completed : 1); break;
		case 1: ZVAL_LONG(rv, t->size); break;
		default: ZVAL_LONG(rv, t->tc ? t->tc->offset : t->offset); break;
	}
}

/* Fills rv from obj's live fields; false when obj is a context ftdi_free() released (an Error is thrown). */
static bool ftdi_read_field(zend_object *obj, int i, zval *rv)
{
	if (obj->ce == ftdi_context_ce) {
		ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);

		if (c->ctx == NULL) {
			zend_throw_error(NULL, "This FTDIContext was released by ftdi_free()");
			return false;
		}
		ftdi_context_field(c->ctx, i, rv);
		return true;
	}
	ftdi_transfer_field(FTDI_FROM(ftdi_transfer_obj, obj), i, rv);
	return true;
}

static int ftdi_fields_of(zend_object *obj, const char *const **fields)
{
	if (obj->ce == ftdi_context_ce) {
		*fields = ftdi_context_fields;
		return (int) (sizeof(ftdi_context_fields) / sizeof(*ftdi_context_fields));
	}
	*fields = ftdi_transfer_fields;
	return (int) (sizeof(ftdi_transfer_fields) / sizeof(*ftdi_transfer_fields));
}

static zval *ftdi_read_property(zend_object *obj, zend_string *name, int type, void **cache_slot, zval *rv)
{
	const char *const *fields;
	size_t count = (size_t) ftdi_fields_of(obj, &fields);
	int i = ftdi_field_index(fields, count, name);

	if (i >= 0) {
		if (type == BP_VAR_W || type == BP_VAR_RW) {
			zend_throw_error(NULL, "Cannot modify read-only property %s::$%s", ZSTR_VAL(obj->ce->name), ZSTR_VAL(name));
			return &EG(uninitialized_zval);
		}
		return ftdi_read_field(obj, i, rv) ? rv : &EG(uninitialized_zval);
	}
	return zend_std_read_property(obj, name, type, cache_slot, rv);
}

static zval *ftdi_write_property(zend_object *obj, zend_string *name, zval *value, void **cache_slot)
{
	zend_throw_error(NULL, "Cannot modify read-only property %s::$%s", ZSTR_VAL(obj->ce->name), ZSTR_VAL(name));
	return &EG(error_zval);
}

static zval *ftdi_get_property_ptr_ptr(zend_object *obj, zend_string *name, int type, void **cache_slot)
{
	/* No direct slots: reads go through ftdi_read_property, writes fail there or in ftdi_write_property. */
	return NULL;
}

static int ftdi_has_property(zend_object *obj, zend_string *name, int check_empty, void **cache_slot)
{
	const char *const *fields;
	size_t count = (size_t) ftdi_fields_of(obj, &fields);
	int i = ftdi_field_index(fields, count, name);
	zval rv;
	int result;

	if (i < 0) {
		return zend_std_has_property(obj, name, check_empty, cache_slot);
	}
	if (check_empty == ZEND_PROPERTY_EXISTS) {
		return 1;
	}
	if (!ftdi_read_field(obj, i, &rv)) {
		return 0;
	}
	result = check_empty == ZEND_PROPERTY_NOT_EMPTY ? zend_is_true(&rv) : 1;
	zval_ptr_dtor(&rv);
	return result;
}

static void ftdi_unset_property(zend_object *obj, zend_string *name, void **cache_slot)
{
	zend_throw_error(NULL, "Cannot unset read-only property %s::$%s", ZSTR_VAL(obj->ce->name), ZSTR_VAL(name));
}

/* The live fields as an array; empty for a context ftdi_free() released. */
static void ftdi_fields_array(zend_object *obj, zval *out)
{
	const char *const *fields;
	int count = ftdi_fields_of(obj, &fields);

	array_init_size(out, (uint32_t) count);
	if (obj->ce == ftdi_context_ce && FTDI_FROM(ftdi_context_obj, obj)->ctx == NULL) {
		return;
	}
	for (int i = 0; i < count; i++) {
		zval v;

		ftdi_read_field(obj, i, &v);
		add_assoc_zval(out, fields[i], &v);
	}
}

static HashTable *ftdi_get_properties_for(zend_object *obj, zend_prop_purpose purpose)
{
	zval props;

	switch (purpose) {
		case ZEND_PROP_PURPOSE_DEBUG:
		case ZEND_PROP_PURPOSE_ARRAY_CAST:
		case ZEND_PROP_PURPOSE_VAR_EXPORT:
		case ZEND_PROP_PURPOSE_JSON:
			ftdi_fields_array(obj, &props);
			return Z_ARR(props);
		default:
			return zend_std_get_properties_for(obj, purpose);
	}
}

/* }}} */

/* {{{ argument helpers */

/*
 * The libftdi context behind an FTDIContext argument; NULL with an Error thrown when
 * ftdi_free() released it, or, when initialized is required, when ftdi_deinit()
 * left it without its libusb context and EEPROM image.
 */
static struct ftdi_context *ftdi_ctx_of(zend_object *obj, bool initialized)
{
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);

	if (UNEXPECTED(c->ctx == NULL)) {
		zend_throw_error(NULL, "This FTDIContext was released by ftdi_free()");
		return NULL;
	}
	if (initialized && UNEXPECTED(!c->initialized)) {
		zend_throw_error(NULL, "This FTDIContext was deinitialised by ftdi_deinit(); call ftdi_init() first");
		return NULL;
	}
	return c->ctx;
}

static bool ftdi_in_range(zend_long value, zend_long low, zend_long high, uint32_t argnum)
{
	if (value < low || value > high) {
		zend_argument_value_error(argnum, "must be between " ZEND_LONG_FMT " and " ZEND_LONG_FMT, low, high);
		return false;
	}
	return true;
}

/* "" means "any" to libftdi's open and string functions: NULL. */
static const char *ftdi_optional_str(zend_string *s)
{
	return ZSTR_LEN(s) > 0 ? ZSTR_VAL(s) : NULL;
}

#define FTDI_CTX_ARG(obj) Z_PARAM_OBJ_OF_CLASS(obj, ftdi_context_ce)

#define FTDI_CTX_OR_THROW(ctx, obj) \
	struct ftdi_context *ctx = ftdi_ctx_of(obj, true); \
	if (ctx == NULL) { \
		RETURN_THROWS(); \
	}

#define FTDI_RANGE_OR_THROW(value, low, high, argnum) \
	if (!ftdi_in_range((value), (low), (high), (argnum))) { \
		RETURN_THROWS(); \
	}

/* fn(FTDIContext $ftdi): int over call(ctx). */
#define FTDI_CTX_INT_FUNCTION(fn, call) \
	ZEND_FUNCTION(fn) \
	{ \
		zend_object *obj; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			FTDI_CTX_ARG(obj) \
		ZEND_PARSE_PARAMETERS_END(); \
		FTDI_CTX_OR_THROW(ctx, obj) \
		RETURN_LONG(call(ctx)); \
	}

/* fn(FTDIContext $ftdi): int over an out-parameter call; the value on success, else the negative libftdi code. */
#define FTDI_CTX_OUT_FUNCTION(fn, type, call) \
	ZEND_FUNCTION(fn) \
	{ \
		zend_object *obj; \
		type out = 0; \
		ZEND_PARSE_PARAMETERS_START(1, 1) \
			FTDI_CTX_ARG(obj) \
		ZEND_PARSE_PARAMETERS_END(); \
		FTDI_CTX_OR_THROW(ctx, obj) \
		int rc = call(ctx, &out); \
		RETURN_LONG(rc == 0 ? (zend_long) out : rc); \
	}

/* }}} */

/* {{{ context lifecycle */

ZEND_FUNCTION(ftdi_new)
{
	ZEND_PARSE_PARAMETERS_NONE();

	struct ftdi_context *ctx = ftdi_new();
	if (ctx == NULL) {
		RETURN_NULL();
	}
	object_init_ex(return_value, ftdi_context_ce);
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, Z_OBJ_P(return_value));
	c->ctx = ctx;
	c->initialized = true;
}

/* ftdi_init() over an initialised context would leak its libusb context: that context is deinitialised first. */
ZEND_FUNCTION(ftdi_init)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	struct ftdi_context *ctx = ftdi_ctx_of(obj, false);
	if (ctx == NULL) {
		RETURN_THROWS();
	}
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);
	if (c->initialized) {
		ftdi_release_dependents(c, true);
		ftdi_deinit(ctx);
		c->initialized = false;
	}
	int rc = ftdi_init(ctx);
	c->initialized = rc == 0;
	memset(c->strings, 0, sizeof(c->strings));
	RETURN_LONG(rc);
}

ZEND_FUNCTION(ftdi_deinit)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	struct ftdi_context *ctx = ftdi_ctx_of(obj, false);
	if (ctx == NULL) {
		RETURN_THROWS();
	}
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);
	if (c->initialized) {
		ftdi_release_dependents(c, true);
		ftdi_deinit(ctx);
		c->initialized = false;
		memset(c->strings, 0, sizeof(c->strings));
	}
}

/* Releasing a context ftdi_free() already released is a no-op. */
ZEND_FUNCTION(ftdi_free)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);
	if (c->ctx) {
		ftdi_release_dependents(c, true);
		ftdi_free(c->ctx);
		c->ctx = NULL;
		c->initialized = false;
	}
}

ZEND_FUNCTION(ftdi_set_interface)
{
	zend_object *obj;
	zend_long iface;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(iface)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(iface, INTERFACE_ANY, INTERFACE_D, 2)
	RETURN_LONG(ftdi_set_interface(ctx, (enum ftdi_interface) iface));
}

ZEND_FUNCTION(ftdi_get_library_version)
{
	ZEND_PARSE_PARAMETERS_NONE();

	struct ftdi_version_info v = ftdi_get_library_version();
	object_init_ex(return_value, ftdi_version_ce);
	zend_object *obj = Z_OBJ_P(return_value);
	zend_update_property_long(ftdi_version_ce, obj, "major", sizeof("major") - 1, v.major);
	zend_update_property_long(ftdi_version_ce, obj, "minor", sizeof("minor") - 1, v.minor);
	zend_update_property_long(ftdi_version_ce, obj, "micro", sizeof("micro") - 1, v.micro);
	zend_update_property_string(ftdi_version_ce, obj, "versionStr", sizeof("versionStr") - 1, v.version_str ? v.version_str : "");
	zend_update_property_string(ftdi_version_ce, obj, "snapshotStr", sizeof("snapshotStr") - 1, v.snapshot_str ? v.snapshot_str : "");
}

ZEND_FUNCTION(ftdi_get_error_string)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	struct ftdi_context *ctx = ftdi_ctx_of(obj, false);
	if (ctx == NULL) {
		RETURN_THROWS();
	}
	const char *err = ftdi_get_error_string(ctx);
	RETURN_STRING(err ? err : "");
}

/* }}} */

/* {{{ finding and opening devices */

/* The libusb device behind an FTDIDevice that came from ctx_obj; NULL with an exception thrown otherwise. */
static struct libusb_device *ftdi_device_of(zend_object *dev_obj, zend_object *ctx_obj, uint32_t argnum)
{
	ftdi_device_obj *d = FTDI_FROM(ftdi_device_obj, dev_obj);

	if (d->context != ctx_obj) {
		zend_argument_value_error(argnum, "must come from ftdi_usb_find_all() on the same FTDIContext");
		return NULL;
	}
	if (d->dev == NULL) {
		zend_throw_error(NULL, "This FTDIDevice was released when its FTDIContext was deinitialised");
		return NULL;
	}
	return d->dev;
}

ZEND_FUNCTION(ftdi_usb_find_all)
{
	zend_object *obj;
	zend_long vendor, product;
	struct ftdi_device_list *list = NULL;
	zval devices;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(vendor, 0, 0xFFFF, 2)
	FTDI_RANGE_OR_THROW(product, 0, 0xFFFF, 3)

	int count = ftdi_usb_find_all(ctx, &list, (int) vendor, (int) product);

	/* Each FTDIDevice takes its own libusb reference; the list itself is freed here. */
	array_init(&devices);
	for (struct ftdi_device_list *node = list; node != NULL; node = node->next) {
		zval dev;

		object_init_ex(&dev, ftdi_device_ce);
		ftdi_device_obj *d = FTDI_FROM(ftdi_device_obj, Z_OBJ(dev));
		d->dev = libusb_ref_device(node->dev);
		ftdi_adopt(obj, Z_OBJ(dev), &d->context);
		add_next_index_zval(&devices, &dev);
	}
	if (list) {
		ftdi_list_free(&list);
	}

	array_init_size(return_value, 2);
	add_assoc_long(return_value, "count", count);
	add_assoc_zval(return_value, "devices", &devices);
}

static void ftdi_usb_strings(INTERNAL_FUNCTION_PARAMETERS, bool second)
{
	zend_object *obj, *dev_obj;
	char manufacturer[256] = { 0 }, description[256] = { 0 }, serial[256] = { 0 };

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_OBJ_OF_CLASS(dev_obj, ftdi_device_ce)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	struct libusb_device *dev = ftdi_device_of(dev_obj, obj, 2);
	if (dev == NULL) {
		RETURN_THROWS();
	}

	int rc = (second ? ftdi_usb_get_strings2 : ftdi_usb_get_strings)(ctx, dev,
		manufacturer, sizeof(manufacturer), description, sizeof(description), serial, sizeof(serial));

	array_init_size(return_value, 4);
	add_assoc_long(return_value, "result", rc);
	add_assoc_string(return_value, "manufacturer", manufacturer);
	add_assoc_string(return_value, "description", description);
	add_assoc_string(return_value, "serial", serial);
}

ZEND_FUNCTION(ftdi_usb_get_strings)
{
	ftdi_usb_strings(INTERNAL_FUNCTION_PARAM_PASSTHRU, false);
}

ZEND_FUNCTION(ftdi_usb_get_strings2)
{
	ftdi_usb_strings(INTERNAL_FUNCTION_PARAM_PASSTHRU, true);
}

ZEND_FUNCTION(ftdi_usb_open_dev)
{
	zend_object *obj, *dev_obj;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_OBJ_OF_CLASS(dev_obj, ftdi_device_ce)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	struct libusb_device *dev = ftdi_device_of(dev_obj, obj, 2);
	if (dev == NULL) {
		RETURN_THROWS();
	}
	RETURN_LONG(ftdi_usb_open_dev(ctx, dev));
}

ZEND_FUNCTION(ftdi_usb_open)
{
	zend_object *obj;
	zend_long vendor, product;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(vendor, 0, 0xFFFF, 2)
	FTDI_RANGE_OR_THROW(product, 0, 0xFFFF, 3)
	RETURN_LONG(ftdi_usb_open(ctx, (int) vendor, (int) product));
}

ZEND_FUNCTION(ftdi_usb_open_desc)
{
	zend_object *obj;
	zend_long vendor, product;
	zend_string *description, *serial;

	ZEND_PARSE_PARAMETERS_START(5, 5)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
		Z_PARAM_STR(description)
		Z_PARAM_STR(serial)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(vendor, 0, 0xFFFF, 2)
	FTDI_RANGE_OR_THROW(product, 0, 0xFFFF, 3)
	RETURN_LONG(ftdi_usb_open_desc(ctx, (int) vendor, (int) product, ftdi_optional_str(description), ftdi_optional_str(serial)));
}

ZEND_FUNCTION(ftdi_usb_open_desc_index)
{
	zend_object *obj;
	zend_long vendor, product, index;
	zend_string *description, *serial;

	ZEND_PARSE_PARAMETERS_START(6, 6)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(vendor)
		Z_PARAM_LONG(product)
		Z_PARAM_STR(description)
		Z_PARAM_STR(serial)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(vendor, 0, 0xFFFF, 2)
	FTDI_RANGE_OR_THROW(product, 0, 0xFFFF, 3)
	FTDI_RANGE_OR_THROW(index, 0, UINT_MAX, 6)
	RETURN_LONG(ftdi_usb_open_desc_index(ctx, (int) vendor, (int) product,
		ftdi_optional_str(description), ftdi_optional_str(serial), (unsigned int) index));
}

ZEND_FUNCTION(ftdi_usb_open_bus_addr)
{
	zend_object *obj;
	zend_long bus, addr;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(bus)
		Z_PARAM_LONG(addr)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(bus, 0, UINT8_MAX, 2)
	FTDI_RANGE_OR_THROW(addr, 0, UINT8_MAX, 3)
	RETURN_LONG(ftdi_usb_open_bus_addr(ctx, (uint8_t) bus, (uint8_t) addr));
}

ZEND_FUNCTION(ftdi_usb_open_string)
{
	zend_object *obj;
	zend_string *description;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_STR(description)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	RETURN_LONG(ftdi_usb_open_string(ctx, ZSTR_VAL(description)));
}

/* Pending transfers are cancelled before the device handle closes under them. */
ZEND_FUNCTION(ftdi_usb_close)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	ftdi_release_dependents(FTDI_FROM(ftdi_context_obj, obj), false);
	RETURN_LONG(ftdi_usb_close(ctx));
}

FTDI_CTX_INT_FUNCTION(ftdi_usb_reset, ftdi_usb_reset)
FTDI_CTX_INT_FUNCTION(ftdi_tci_flush, ftdi_tciflush)
FTDI_CTX_INT_FUNCTION(ftdi_tco_flush, ftdi_tcoflush)
FTDI_CTX_INT_FUNCTION(ftdi_tcio_flush, ftdi_tcioflush)

/* The purge functions are deprecated in ftdi.h in favour of the tc*flush family; they are bound as libftdi still exports them. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
FTDI_CTX_INT_FUNCTION(ftdi_usb_purge_rx_buffer, ftdi_usb_purge_rx_buffer)
FTDI_CTX_INT_FUNCTION(ftdi_usb_purge_tx_buffer, ftdi_usb_purge_tx_buffer)
FTDI_CTX_INT_FUNCTION(ftdi_usb_purge_buffers, ftdi_usb_purge_buffers)
#pragma GCC diagnostic pop

/* }}} */

/* {{{ line settings */

ZEND_FUNCTION(ftdi_convert_baudrate_ut_export)
{
	zend_long baudrate;
	zend_object *obj;
	unsigned short value = 0, index = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(baudrate)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_RANGE_OR_THROW(baudrate, 1, INT_MAX, 1)
	FTDI_CTX_OR_THROW(ctx, obj)

	int rc = convert_baudrate_UT_export((int) baudrate, ctx, &value, &index);
	array_init_size(return_value, 3);
	add_assoc_long(return_value, "result", rc);
	add_assoc_long(return_value, "value", value);
	add_assoc_long(return_value, "index", index);
}

ZEND_FUNCTION(ftdi_set_baudrate)
{
	zend_object *obj;
	zend_long baudrate;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(baudrate)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(baudrate, 1, INT_MAX, 2)
	RETURN_LONG(ftdi_set_baudrate(ctx, (int) baudrate));
}

static void ftdi_line_property(INTERNAL_FUNCTION_PARAMETERS, bool with_break)
{
	zend_object *obj;
	zend_long bits, sbit, parity, break_type = BREAK_OFF;

	ZEND_PARSE_PARAMETERS_START(with_break ? 5 : 4, with_break ? 5 : 4)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(bits)
		Z_PARAM_LONG(sbit)
		Z_PARAM_LONG(parity)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(break_type)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	if (bits != BITS_7 && bits != BITS_8) {
		zend_argument_value_error(2, "must be BITS_7 or BITS_8");
		RETURN_THROWS();
	}
	FTDI_RANGE_OR_THROW(sbit, STOP_BIT_1, STOP_BIT_2, 3)
	FTDI_RANGE_OR_THROW(parity, NONE, SPACE, 4)
	FTDI_RANGE_OR_THROW(break_type, BREAK_OFF, BREAK_ON, 5)

	RETURN_LONG(with_break
		? ftdi_set_line_property2(ctx, (enum ftdi_bits_type) bits, (enum ftdi_stopbits_type) sbit,
			(enum ftdi_parity_type) parity, (enum ftdi_break_type) break_type)
		: ftdi_set_line_property(ctx, (enum ftdi_bits_type) bits, (enum ftdi_stopbits_type) sbit,
			(enum ftdi_parity_type) parity));
}

ZEND_FUNCTION(ftdi_set_line_property)
{
	ftdi_line_property(INTERNAL_FUNCTION_PARAM_PASSTHRU, false);
}

ZEND_FUNCTION(ftdi_set_line_property2)
{
	ftdi_line_property(INTERNAL_FUNCTION_PARAM_PASSTHRU, true);
}

ZEND_FUNCTION(ftdi_set_bitmode)
{
	zend_object *obj;
	zend_long bitmask, mode;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(bitmask)
		Z_PARAM_LONG(mode)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(bitmask, 0, UINT8_MAX, 2)
	FTDI_RANGE_OR_THROW(mode, 0, UINT8_MAX, 3)
	RETURN_LONG(ftdi_set_bitmode(ctx, (unsigned char) bitmask, (unsigned char) mode));
}

FTDI_CTX_INT_FUNCTION(ftdi_disable_bitbang, ftdi_disable_bitbang)
FTDI_CTX_OUT_FUNCTION(ftdi_read_pins, unsigned char, ftdi_read_pins)
FTDI_CTX_OUT_FUNCTION(ftdi_get_latency_timer, unsigned char, ftdi_get_latency_timer)
FTDI_CTX_OUT_FUNCTION(ftdi_poll_modem_status, unsigned short, ftdi_poll_modem_status)
FTDI_CTX_OUT_FUNCTION(ftdi_write_data_get_chunksize, unsigned int, ftdi_write_data_get_chunksize)
FTDI_CTX_OUT_FUNCTION(ftdi_read_data_get_chunksize, unsigned int, ftdi_read_data_get_chunksize)

ZEND_FUNCTION(ftdi_set_latency_timer)
{
	zend_object *obj;
	zend_long latency;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(latency)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(latency, 0, UINT8_MAX, 2)
	RETURN_LONG(ftdi_set_latency_timer(ctx, (unsigned char) latency));
}

/* Sets the struct's usb_read_timeout and usb_write_timeout (ms); libftdi has no setter for them. */
ZEND_FUNCTION(ftdi_set_timeouts)
{
	zend_object *obj;
	zend_long read_timeout, write_timeout;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(read_timeout)
		Z_PARAM_LONG(write_timeout)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(read_timeout, 0, INT_MAX, 2)
	FTDI_RANGE_OR_THROW(write_timeout, 0, INT_MAX, 3)
	ctx->usb_read_timeout = (int) read_timeout;
	ctx->usb_write_timeout = (int) write_timeout;
}

ZEND_FUNCTION(ftdi_setflowctrl)
{
	zend_object *obj;
	zend_long flowctrl;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(flowctrl)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(flowctrl, 0, UINT16_MAX, 2)
	RETURN_LONG(ftdi_setflowctrl(ctx, (int) flowctrl));
}

/* fn(FTDIContext $ftdi, int $a, int $b): int over call(ctx, (unsigned char) a, (unsigned char) b). */
#define FTDI_CTX_TWO_BYTES_FUNCTION(fn, call) \
	ZEND_FUNCTION(fn) \
	{ \
		zend_object *obj; \
		zend_long a, b; \
		ZEND_PARSE_PARAMETERS_START(3, 3) \
			FTDI_CTX_ARG(obj) \
			Z_PARAM_LONG(a) \
			Z_PARAM_LONG(b) \
		ZEND_PARSE_PARAMETERS_END(); \
		FTDI_CTX_OR_THROW(ctx, obj) \
		FTDI_RANGE_OR_THROW(a, 0, UINT8_MAX, 2) \
		FTDI_RANGE_OR_THROW(b, 0, UINT8_MAX, 3) \
		RETURN_LONG(call(ctx, (unsigned char) a, (unsigned char) b)); \
	}

FTDI_CTX_TWO_BYTES_FUNCTION(ftdi_setflowctrl_xonxoff, ftdi_setflowctrl_xonxoff)
FTDI_CTX_TWO_BYTES_FUNCTION(ftdi_set_event_char, ftdi_set_event_char)
FTDI_CTX_TWO_BYTES_FUNCTION(ftdi_set_error_char, ftdi_set_error_char)

ZEND_FUNCTION(ftdi_setdtr)
{
	zend_object *obj;
	zend_long state;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(state, 0, 1, 2)
	RETURN_LONG(ftdi_setdtr(ctx, (int) state));
}

ZEND_FUNCTION(ftdi_setrts)
{
	zend_object *obj;
	zend_long state;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(state)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(state, 0, 1, 2)
	RETURN_LONG(ftdi_setrts(ctx, (int) state));
}

ZEND_FUNCTION(ftdi_setdtr_rts)
{
	zend_object *obj;
	zend_long dtr, rts;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(dtr)
		Z_PARAM_LONG(rts)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(dtr, 0, 1, 2)
	FTDI_RANGE_OR_THROW(rts, 0, 1, 3)
	RETURN_LONG(ftdi_setdtr_rts(ctx, (int) dtr, (int) rts));
}

/* }}} */

/* {{{ synchronous data */

ZEND_FUNCTION(ftdi_write_data)
{
	zend_object *obj;
	zend_string *data;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_STR(data)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	if (size < 0 || (size_t) size > ZSTR_LEN(data) || size > INT_MAX) {
		zend_argument_value_error(3, "must be between 0 and the length of argument #2 ($data)");
		RETURN_THROWS();
	}
	RETURN_LONG(ftdi_write_data(ctx, (const unsigned char *) ZSTR_VAL(data), (int) size));
}

ZEND_FUNCTION(ftdi_read_data)
{
	zend_object *obj;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(size, 0, INT_MAX, 2)

	zend_string *buf = zend_string_alloc((size_t) size, 0);
	int n = ftdi_read_data(ctx, (unsigned char *) ZSTR_VAL(buf), (int) size);
	if (n < 0) {
		zend_string_efree(buf);
		RETURN_FALSE;
	}
	if ((zend_long) n < size) {
		buf = zend_string_truncate(buf, (size_t) n, 0);
	}
	ZSTR_VAL(buf)[n] = '\0';
	RETURN_NEW_STR(buf);
}

ZEND_FUNCTION(ftdi_write_data_set_chunksize)
{
	zend_object *obj;
	zend_long chunksize;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(chunksize)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(chunksize, 1, UINT_MAX, 2)
	RETURN_LONG(ftdi_write_data_set_chunksize(ctx, (unsigned int) chunksize));
}

ZEND_FUNCTION(ftdi_read_data_set_chunksize)
{
	zend_object *obj;
	zend_long chunksize;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(chunksize)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(chunksize, 1, UINT_MAX, 2)
	RETURN_LONG(ftdi_read_data_set_chunksize(ctx, (unsigned int) chunksize));
}

/* }}} */

/* {{{ asynchronous data and the libusb event pump */

/*
 * With no device open, libftdi's submit functions return NULL without setting
 * error_str, so ftdi_get_error_string() would report whatever failed before. They
 * fail here with the message libftdi's synchronous calls give (-666, "USB device
 * unavailable").
 */
static bool ftdi_has_device(struct ftdi_context *ctx)
{
	if (ctx->usb_dev == NULL) {
		ctx->error_str = "USB device unavailable";
		return false;
	}
	return true;
}

static void ftdi_transfer_wrap(zval *return_value, zend_object *ctx_obj, struct ftdi_transfer_control *tc, unsigned char *buf, zend_long size)
{
	object_init_ex(return_value, ftdi_transfer_ce);
	ftdi_transfer_obj *t = FTDI_FROM(ftdi_transfer_obj, Z_OBJ_P(return_value));
	t->tc = tc;
	t->buf = buf;
	t->size = size;
	ftdi_adopt(ctx_obj, Z_OBJ_P(return_value), &t->context);
}

ZEND_FUNCTION(ftdi_write_data_submit)
{
	zend_object *obj;
	zend_string *data;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_STR(data)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	if (size < 0 || (size_t) size > ZSTR_LEN(data) || size > INT_MAX) {
		zend_argument_value_error(3, "must be between 0 and the length of argument #2 ($data)");
		RETURN_THROWS();
	}
	if (!ftdi_has_device(ctx)) {
		RETURN_NULL();
	}

	/* The transfer reads from this copy until it is collected or cancelled. */
	unsigned char *buf = emalloc(size > 0 ? (size_t) size : 1);
	memcpy(buf, ZSTR_VAL(data), (size_t) size);
	struct ftdi_transfer_control *tc = ftdi_write_data_submit(ctx, buf, (int) size);
	if (tc == NULL) {
		efree(buf);
		RETURN_NULL();
	}
	ftdi_transfer_wrap(return_value, obj, tc, buf, size);
}

ZEND_FUNCTION(ftdi_read_data_submit)
{
	zend_object *obj;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(size, 1, INT_MAX, 2)
	if (!ftdi_has_device(ctx)) {
		RETURN_NULL();
	}

	/* The transfer fills this buffer until it is collected or cancelled. */
	unsigned char *buf = emalloc((size_t) size);
	struct ftdi_transfer_control *tc = ftdi_read_data_submit(ctx, buf, (int) size);
	if (tc == NULL) {
		efree(buf);
		RETURN_NULL();
	}
	ftdi_transfer_wrap(return_value, obj, tc, buf, size);
}

/* Waits for the transfer, frees it, and returns the bytes moved (or the libftdi error); -1 once already collected or cancelled. */
static int ftdi_transfer_collect(ftdi_transfer_obj *t)
{
	if (t->tc == NULL) {
		return -1;
	}
	int n = ftdi_transfer_data_done(t->tc);
	t->tc = NULL;
	if (n >= 0) {
		t->offset = n;
	}
	return n;
}

ZEND_FUNCTION(ftdi_transfer_data_done)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(obj, ftdi_transfer_ce)
	ZEND_PARSE_PARAMETERS_END();

	ftdi_transfer_obj *t = FTDI_FROM(ftdi_transfer_obj, obj);
	int n = ftdi_transfer_collect(t);
	ftdi_transfer_finish(t);
	RETURN_LONG(n);
}

ZEND_FUNCTION(ftdi_transfer_read_done)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(obj, ftdi_transfer_ce)
	ZEND_PARSE_PARAMETERS_END();

	ftdi_transfer_obj *t = FTDI_FROM(ftdi_transfer_obj, obj);
	int n = ftdi_transfer_collect(t);
	if (n < 0 || t->buf == NULL) {
		ftdi_transfer_finish(t);
		RETURN_FALSE;
	}
	RETVAL_STRINGL((const char *) t->buf, (size_t) n);
	ftdi_transfer_finish(t);
}

ZEND_FUNCTION(ftdi_transfer_data_cancel)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(obj, ftdi_transfer_ce)
	ZEND_PARSE_PARAMETERS_END();

	ftdi_transfer_finish(FTDI_FROM(ftdi_transfer_obj, obj));
}

ZEND_FUNCTION(ftdi_transfer_completed)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJ_OF_CLASS(obj, ftdi_transfer_ce)
	ZEND_PARSE_PARAMETERS_END();

	ftdi_transfer_obj *t = FTDI_FROM(ftdi_transfer_obj, obj);
	RETURN_LONG(t->tc ? t->tc->completed : 1);
}

ZEND_FUNCTION(ftdi_get_pollfds)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	array_init(return_value);
	const struct libusb_pollfd **fds = libusb_get_pollfds(ctx->usb_ctx);
	if (fds == NULL) {
		return;
	}
	for (size_t i = 0; fds[i] != NULL; i++) {
		zval entry;

		array_init_size(&entry, 2);
		add_assoc_long(&entry, "fd", fds[i]->fd);
		add_assoc_long(&entry, "events", fds[i]->events);
		add_next_index_zval(return_value, &entry);
	}
	libusb_free_pollfds(fds);
}

ZEND_FUNCTION(ftdi_pollfds_handle_timeouts)
{
	zend_object *obj;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	RETURN_LONG(libusb_pollfds_handle_timeouts(ctx->usb_ctx));
}

ZEND_FUNCTION(ftdi_get_next_timeout)
{
	zend_object *obj;
	struct timeval tv = { 0, 0 };

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	int rc = libusb_get_next_timeout(ctx->usb_ctx, &tv);
	array_init_size(return_value, 2);
	add_assoc_long(return_value, "result", rc);
	add_assoc_long(return_value, "usec", rc == 1 ? (zend_long) tv.tv_sec * 1000000 + (zend_long) tv.tv_usec : 0);
}

ZEND_FUNCTION(ftdi_handle_events_timeout)
{
	zend_object *obj;
	zend_long timeout_us;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(timeout_us)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(timeout_us, 0, ZEND_LONG_MAX, 2)

	struct timeval tv = { .tv_sec = (time_t) (timeout_us / 1000000), .tv_usec = (suseconds_t) (timeout_us % 1000000) };
	RETURN_LONG(libusb_handle_events_timeout_completed(ctx->usb_ctx, &tv, NULL));
}

/* }}} */

/* {{{ EEPROM */

/* Every enum ftdi_eeprom_value and the FTDIEeprom property it fills. */
static const struct { enum ftdi_eeprom_value value; const char *property; } ftdi_eeprom_properties[] = {
	{ VENDOR_ID, "vendorId" },
	{ PRODUCT_ID, "productId" },
	{ SELF_POWERED, "selfPowered" },
	{ REMOTE_WAKEUP, "remoteWakeup" },
	{ IS_NOT_PNP, "isNotPnp" },
	{ SUSPEND_DBUS7, "suspendDbus7" },
	{ IN_IS_ISOCHRONOUS, "inIsIsochronous" },
	{ OUT_IS_ISOCHRONOUS, "outIsIsochronous" },
	{ SUSPEND_PULL_DOWNS, "suspendPullDowns" },
	{ USE_SERIAL, "useSerial" },
	{ USB_VERSION, "usbVersion" },
	{ USE_USB_VERSION, "useUsbVersion" },
	{ MAX_POWER, "maxPower" },
	{ CHANNEL_A_TYPE, "channelAType" },
	{ CHANNEL_B_TYPE, "channelBType" },
	{ CHANNEL_A_DRIVER, "channelADriver" },
	{ CHANNEL_B_DRIVER, "channelBDriver" },
	{ CBUS_FUNCTION_0, "cbusFunction0" },
	{ CBUS_FUNCTION_1, "cbusFunction1" },
	{ CBUS_FUNCTION_2, "cbusFunction2" },
	{ CBUS_FUNCTION_3, "cbusFunction3" },
	{ CBUS_FUNCTION_4, "cbusFunction4" },
	{ CBUS_FUNCTION_5, "cbusFunction5" },
	{ CBUS_FUNCTION_6, "cbusFunction6" },
	{ CBUS_FUNCTION_7, "cbusFunction7" },
	{ CBUS_FUNCTION_8, "cbusFunction8" },
	{ CBUS_FUNCTION_9, "cbusFunction9" },
	{ HIGH_CURRENT, "highCurrent" },
	{ HIGH_CURRENT_A, "highCurrentA" },
	{ HIGH_CURRENT_B, "highCurrentB" },
	{ INVERT, "invert" },
	{ GROUP0_DRIVE, "group0Drive" },
	{ GROUP0_SCHMITT, "group0Schmitt" },
	{ GROUP0_SLEW, "group0Slew" },
	{ GROUP1_DRIVE, "group1Drive" },
	{ GROUP1_SCHMITT, "group1Schmitt" },
	{ GROUP1_SLEW, "group1Slew" },
	{ GROUP2_DRIVE, "group2Drive" },
	{ GROUP2_SCHMITT, "group2Schmitt" },
	{ GROUP2_SLEW, "group2Slew" },
	{ GROUP3_DRIVE, "group3Drive" },
	{ GROUP3_SCHMITT, "group3Schmitt" },
	{ GROUP3_SLEW, "group3Slew" },
	{ CHIP_SIZE, "chipSize" },
	{ CHIP_TYPE, "chipType" },
	{ POWER_SAVE, "powerSave" },
	{ CLOCK_POLARITY, "clockPolarity" },
	{ DATA_ORDER, "dataOrder" },
	{ FLOW_CONTROL, "flowControl" },
	{ CHANNEL_C_DRIVER, "channelCDriver" },
	{ CHANNEL_D_DRIVER, "channelDDriver" },
	{ CHANNEL_A_RS485, "channelARs485" },
	{ CHANNEL_B_RS485, "channelBRs485" },
	{ CHANNEL_C_RS485, "channelCRs485" },
	{ CHANNEL_D_RS485, "channelDRs485" },
	{ RELEASE_NUMBER, "releaseNumber" },
	{ EXTERNAL_OSCILLATOR, "externalOscillator" },
	{ USER_DATA_ADDR, "userDataAddr" },
};

/*
 * ftdi_eeprom_get_strings() strncpy()s from each EEPROM string with no NULL check,
 * and a fresh context, a deinitialised one, initdefaults or decode can each leave
 * any of them NULL. The context tracks which ones libftdi holds; only those are
 * asked for, the rest come back as "".
 */
static void ftdi_eeprom_strings_into(ftdi_context_obj *c, char *manufacturer, char *product, char *serial, int len)
{
	manufacturer[0] = product[0] = serial[0] = '\0';
	ftdi_eeprom_get_strings(c->ctx, c->strings[0] ? manufacturer : NULL, len, c->strings[1] ? product : NULL, len,
		c->strings[2] ? serial : NULL, len);
}

ZEND_FUNCTION(ftdi_get_eeprom)
{
	zend_object *obj;
	char manufacturer[256] = { 0 }, product[256] = { 0 }, serial[256] = { 0 };

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	object_init_ex(return_value, ftdi_eeprom_ce);
	zend_object *eeprom = Z_OBJ_P(return_value);

	for (size_t i = 0; i < sizeof(ftdi_eeprom_properties) / sizeof(*ftdi_eeprom_properties); i++) {
		int value = 0;

		if (ftdi_get_eeprom_value(ctx, ftdi_eeprom_properties[i].value, &value) != 0) {
			value = 0;
		}
		zend_update_property_long(ftdi_eeprom_ce, eeprom, ftdi_eeprom_properties[i].property,
			strlen(ftdi_eeprom_properties[i].property), value);
	}
	ftdi_eeprom_strings_into(FTDI_FROM(ftdi_context_obj, obj), manufacturer, product, serial, sizeof(manufacturer));
	zend_update_property_string(ftdi_eeprom_ce, eeprom, "manufacturer", sizeof("manufacturer") - 1, manufacturer);
	zend_update_property_string(ftdi_eeprom_ce, eeprom, "product", sizeof("product") - 1, product);
	zend_update_property_string(ftdi_eeprom_ce, eeprom, "serial", sizeof("serial") - 1, serial);
}

static void ftdi_eeprom_strings(INTERNAL_FUNCTION_PARAMETERS, bool defaults)
{
	zend_object *obj;
	zend_string *manufacturer, *product, *serial;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		FTDI_CTX_ARG(obj)
		Z_PARAM_STR(manufacturer)
		Z_PARAM_STR(product)
		Z_PARAM_STR(serial)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);
	const char *m = ftdi_optional_str(manufacturer), *p = ftdi_optional_str(product), *s = ftdi_optional_str(serial);
	bool open = ctx->usb_dev != NULL;
	int rc;

	if (defaults) {
		/* Clears the whole image first; with a device open sets manufacturer, then product (given or the chip default), then serial. */
		rc = ftdi_eeprom_initdefaults(ctx, (char *) m, (char *) p, (char *) s);
		c->strings[0] = open && m != NULL;
		c->strings[1] = open && rc == 0;
		c->strings[2] = open && rc == 0 && s != NULL;
	} else {
		/* With a device open, sets each string given and leaves the others. */
		rc = ftdi_eeprom_set_strings(ctx, m, p, s);
		if (rc == 0) {
			c->strings[0] = c->strings[0] || m != NULL;
			c->strings[1] = c->strings[1] || p != NULL;
			c->strings[2] = c->strings[2] || s != NULL;
		}
	}
	RETURN_LONG(rc);
}

ZEND_FUNCTION(ftdi_eeprom_initdefaults)
{
	ftdi_eeprom_strings(INTERNAL_FUNCTION_PARAM_PASSTHRU, true);
}

ZEND_FUNCTION(ftdi_eeprom_set_strings)
{
	ftdi_eeprom_strings(INTERNAL_FUNCTION_PARAM_PASSTHRU, false);
}

ZEND_FUNCTION(ftdi_eeprom_get_strings)
{
	zend_object *obj;
	char manufacturer[256] = { 0 }, product[256] = { 0 }, serial[256] = { 0 };

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	ftdi_eeprom_strings_into(FTDI_FROM(ftdi_context_obj, obj), manufacturer, product, serial, sizeof(manufacturer));
	array_init_size(return_value, 3);
	add_assoc_string(return_value, "manufacturer", manufacturer);
	add_assoc_string(return_value, "product", product);
	add_assoc_string(return_value, "serial", serial);
}

FTDI_CTX_INT_FUNCTION(ftdi_eeprom_build, ftdi_eeprom_build)
FTDI_CTX_INT_FUNCTION(ftdi_read_eeprom, ftdi_read_eeprom)
FTDI_CTX_INT_FUNCTION(ftdi_write_eeprom, ftdi_write_eeprom)
FTDI_CTX_INT_FUNCTION(ftdi_erase_eeprom, ftdi_erase_eeprom)

ZEND_FUNCTION(ftdi_eeprom_decode)
{
	zend_object *obj;
	zend_long verbose;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(verbose)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(verbose, 0, 1, 2)

	int rc = ftdi_eeprom_decode(ctx, (int) verbose);

	/* Decode sets each string from its length byte in the image (0x0F, 0x11, 0x13), NULL when that is under 2. */
	unsigned char image[256];
	ftdi_context_obj *c = FTDI_FROM(ftdi_context_obj, obj);
	if (ftdi_get_eeprom_buf(ctx, image, sizeof(image)) == 0) {
		c->strings[0] = image[0x0F] / 2 > 0;
		c->strings[1] = image[0x11] / 2 > 0;
		c->strings[2] = image[0x13] / 2 > 0;
	}
	RETURN_LONG(rc);
}

static bool ftdi_eeprom_value_ok(zend_long value_name, uint32_t argnum)
{
	return ftdi_in_range(value_name, VENDOR_ID, USER_DATA_ADDR, argnum);
}

ZEND_FUNCTION(ftdi_get_eeprom_value)
{
	zend_object *obj;
	zend_long value_name;
	int value = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(value_name)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	if (!ftdi_eeprom_value_ok(value_name, 2)) {
		RETURN_THROWS();
	}
	int rc = ftdi_get_eeprom_value(ctx, (enum ftdi_eeprom_value) value_name, &value);
	RETURN_LONG(rc == 0 ? value : rc);
}

ZEND_FUNCTION(ftdi_set_eeprom_value)
{
	zend_object *obj;
	zend_long value_name, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(value_name)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	if (!ftdi_eeprom_value_ok(value_name, 2)) {
		RETURN_THROWS();
	}
	FTDI_RANGE_OR_THROW(value, INT_MIN, INT_MAX, 3)
	RETURN_LONG(ftdi_set_eeprom_value(ctx, (enum ftdi_eeprom_value) value_name, (int) value));
}

ZEND_FUNCTION(ftdi_get_eeprom_buf)
{
	zend_object *obj;
	zend_long size;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(size)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(size, 1, INT_MAX, 2)

	zend_string *buf = zend_string_alloc((size_t) size, 0);
	if (ftdi_get_eeprom_buf(ctx, (unsigned char *) ZSTR_VAL(buf), (int) size) != 0) {
		zend_string_efree(buf);
		RETURN_FALSE;
	}
	ZSTR_VAL(buf)[size] = '\0';
	RETURN_NEW_STR(buf);
}

ZEND_FUNCTION(ftdi_set_eeprom_buf)
{
	zend_object *obj;
	zend_string *buf;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_STR(buf)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW((zend_long) ZSTR_LEN(buf), 0, INT_MAX, 2)
	RETURN_LONG(ftdi_set_eeprom_buf(ctx, (const unsigned char *) ZSTR_VAL(buf), (int) ZSTR_LEN(buf)));
}

ZEND_FUNCTION(ftdi_set_eeprom_user_data)
{
	zend_object *obj;
	zend_string *buf;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_STR(buf)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW((zend_long) ZSTR_LEN(buf), 0, INT_MAX, 2)
	RETURN_LONG(ftdi_set_eeprom_user_data(ctx, ZSTR_VAL(buf), (int) ZSTR_LEN(buf)));
}

/* The five CBUS bytes (EEPROM offsets 0x18 to 0x1C) set_ft232h_cbus() encodes from the context's EEPROM image. */
ZEND_FUNCTION(ftdi_set_ft232h_cbus)
{
	zend_object *obj;
	/* A whole EEPROM image: 256 bytes, libftdi's FTDI_MAX_EEPROM_SIZE from its private ftdi_i.h. */
	unsigned char output[256] = { 0 };

	ZEND_PARSE_PARAMETERS_START(1, 1)
		FTDI_CTX_ARG(obj)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	set_ft232h_cbus(ctx->eeprom, output);
	RETURN_STRINGL((const char *) output + 0x18, 5);
}

ZEND_FUNCTION(ftdi_read_eeprom_location)
{
	zend_object *obj;
	zend_long addr;
	unsigned short value = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(addr)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(addr, 0, INT_MAX, 2)
	int rc = ftdi_read_eeprom_location(ctx, (int) addr, &value);
	RETURN_LONG(rc == 0 ? value : rc);
}

ZEND_FUNCTION(ftdi_read_chip_id)
{
	zend_object *obj;
	zval *chip_id;
	unsigned int value = 0;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		FTDI_CTX_ARG(obj)
		Z_PARAM_ZVAL(chip_id)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	int rc = ftdi_read_chipid(ctx, &value);
	if (rc == 0) {
		ZEND_TRY_ASSIGN_REF_LONG(chip_id, (zend_long) value);
	}
	RETURN_LONG(rc);
}

ZEND_FUNCTION(ftdi_write_eeprom_location)
{
	zend_object *obj;
	zend_long addr, value;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		FTDI_CTX_ARG(obj)
		Z_PARAM_LONG(addr)
		Z_PARAM_LONG(value)
	ZEND_PARSE_PARAMETERS_END();

	FTDI_CTX_OR_THROW(ctx, obj)
	FTDI_RANGE_OR_THROW(addr, 0, INT_MAX, 2)
	FTDI_RANGE_OR_THROW(value, 0, UINT16_MAX, 3)
	RETURN_LONG(ftdi_write_eeprom_location(ctx, (int) addr, (unsigned short) value));
}

/* }}} */

/* {{{ methods */

ZEND_METHOD(Ftdi_FTDIContext, __construct) {}
ZEND_METHOD(Ftdi_FTDIDevice, __construct) {}
ZEND_METHOD(Ftdi_FTDITransferControl, __construct) {}

ZEND_METHOD(Ftdi_FTDIContext, toArray)
{
	ZEND_PARSE_PARAMETERS_NONE();

	if (FTDI_FROM(ftdi_context_obj, Z_OBJ_P(ZEND_THIS))->ctx == NULL) {
		zend_throw_error(NULL, "This FTDIContext was released by ftdi_free()");
		RETURN_THROWS();
	}
	ftdi_fields_array(Z_OBJ_P(ZEND_THIS), return_value);
}

ZEND_METHOD(Ftdi_FTDITransferControl, toArray)
{
	ZEND_PARSE_PARAMETERS_NONE();

	ftdi_fields_array(Z_OBJ_P(ZEND_THIS), return_value);
}

/* The declared properties of a value snapshot, in declaration order. */
static void ftdi_declared_properties_array(zend_object *obj, zval *out)
{
	zend_property_info *info;

	array_init(out);
	ZEND_HASH_FOREACH_PTR(&obj->ce->properties_info, info) {
		zval *value = OBJ_PROP(obj, info->offset);

		if (Z_TYPE_P(value) != IS_UNDEF) {
			Z_TRY_ADDREF_P(value);
			zend_hash_add_new(Z_ARRVAL_P(out), info->name, value);
		}
	} ZEND_HASH_FOREACH_END();
}

ZEND_METHOD(Ftdi_FTDIVersionInfo, toArray)
{
	ZEND_PARSE_PARAMETERS_NONE();

	ftdi_declared_properties_array(Z_OBJ_P(ZEND_THIS), return_value);
}

ZEND_METHOD(Ftdi_FTDIEeprom, toArray)
{
	ZEND_PARSE_PARAMETERS_NONE();

	ftdi_declared_properties_array(Z_OBJ_P(ZEND_THIS), return_value);
}

/* }}} */

static void ftdi_live_handlers(zend_object_handlers *h)
{
	h->read_property = ftdi_read_property;
	h->write_property = ftdi_write_property;
	h->get_property_ptr_ptr = ftdi_get_property_ptr_ptr;
	h->has_property = ftdi_has_property;
	h->unset_property = ftdi_unset_property;
	h->get_properties_for = ftdi_get_properties_for;
}

PHP_MINIT_FUNCTION(ftdi)
{
#if defined(COMPILE_DL_FTDI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	register_ftdi_symbols(module_number);

	ftdi_context_ce = register_class_Ftdi_FTDIContext();
	ftdi_context_ce->create_object = ftdi_context_create;
	memcpy(&ftdi_context_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	ftdi_context_handlers.offset = XtOffsetOf(ftdi_context_obj, std);
	ftdi_context_handlers.free_obj = ftdi_context_free;
	ftdi_context_handlers.clone_obj = NULL;
	ftdi_live_handlers(&ftdi_context_handlers);

	ftdi_device_ce = register_class_Ftdi_FTDIDevice();
	ftdi_device_ce->create_object = ftdi_device_create;
	memcpy(&ftdi_device_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	ftdi_device_handlers.offset = XtOffsetOf(ftdi_device_obj, std);
	ftdi_device_handlers.free_obj = ftdi_device_free;
	ftdi_device_handlers.clone_obj = NULL;

	ftdi_transfer_ce = register_class_Ftdi_FTDITransferControl();
	ftdi_transfer_ce->create_object = ftdi_transfer_create;
	memcpy(&ftdi_transfer_handlers, &std_object_handlers, sizeof(zend_object_handlers));
	ftdi_transfer_handlers.offset = XtOffsetOf(ftdi_transfer_obj, std);
	ftdi_transfer_handlers.free_obj = ftdi_transfer_free;
	ftdi_transfer_handlers.clone_obj = NULL;
	ftdi_live_handlers(&ftdi_transfer_handlers);

	ftdi_version_ce = register_class_Ftdi_FTDIVersionInfo();
	ftdi_eeprom_ce = register_class_Ftdi_FTDIEeprom();
	register_class_Ftdi_FtdiVendorId();
	register_class_Ftdi_FtdiProductId();

	return SUCCESS;
}

/* Each ZTS request thread fills the static TSRM cache EG() reads through. */
PHP_RINIT_FUNCTION(ftdi)
{
#if defined(COMPILE_DL_FTDI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_MINFO_FUNCTION(ftdi)
{
	struct ftdi_version_info v = ftdi_get_library_version();

	php_info_print_table_start();
	php_info_print_table_row(2, "ftdi support", "enabled");
	php_info_print_table_row(2, "Version", PHP_FTDI_VERSION);
	php_info_print_table_row(2, "libftdi1", v.version_str ? v.version_str : "");
	php_info_print_table_end();
}

zend_module_entry ftdi_module_entry = {
	STANDARD_MODULE_HEADER,
	"ftdi",
	ext_functions,
	PHP_MINIT(ftdi),
	NULL,
	PHP_RINIT(ftdi),
	NULL,
	PHP_MINFO(ftdi),
	PHP_FTDI_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_FTDI
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(ftdi)
#endif
