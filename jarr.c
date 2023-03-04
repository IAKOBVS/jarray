#include "jarr.h"
#include <stdarg.h>

#define PRIVATE_JARR_CONCAT(T, jarr, t, argv, size)                            \
	va_list ap;                                                            \
	va_start(ap, size);                                                    \
	for (void* argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *)) \
		jarr->data[jarr->size++] = *(t*)argv;                          \
	va_end(ap)

#define PRIVATE_JARR_CAT_NOALLOC(T, t) \
void jarr_cat_noalloc_##T(T *jarr, size_t size, ...) { PRIVATE_JARR_CONCAT(T, jarr, t, argv, size); }

JARR_TEMPLATE_T_t(PRIVATE_JARR_CAT_NOALLOC)

#define PRIVATE_JARR_NEW(T, t)                                                     \
int jarr_new_##T(T *jarr, size_t size, ...)                                        \
{                                                                                  \
	jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);              \
	if (likely(jarr->data = malloc((jarr->capacity) * sizeof(*jarr->data)))) { \
		PRIVATE_JARR_CONCAT(T, jarr, t, argv, size);                       \
		return 1;                                                          \
	}                                                                          \
	jarr_init(jarr);                                                           \
	return 0;                                                                  \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_NEW)

#define PRIVATE_JARR_CAT(T, t)                                                                      \
int jarr_cat_##T(T *jarr, size_t size, ...)                                                         \
{                                                                                                   \
	if (jarr->size + size > jarr->capacity) {                                                   \
		do { jarr->capacity *= 2; } while (jarr->size + size > jarr->capacity);             \
		jarr_reserve_nocheck_##T(jarr, jarr->capacity);\
	}                                                                                           \
	PRIVATE_JARR_CONCAT(T, jarr, t, argv, size);                                                \
	return 1;                                                                                   \
ERROR:                                                                                              \
	jarr_init(jarr);                                                                            \
	return 0;                                                                                   \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_CAT)

#define PRIVATE_JARR_APPEND(T, t)                                                               \
int jarr_append_##T(T *jarr, t *src_arr, size_t src_arr_size)                                   \
{                                                                                               \
	if (jarr->size + src_arr_size > jarr->capacity) {                                       \
		do { jarr->capacity *= 2; } while (jarr->size + src_arr_size > jarr->capacity); \
		jarr_reserve_nocheck_##T(jarr, jarr->capacity);                                 \
	}                                                                                       \
	memcpy(jarr->data, src_arr, src_arr_size * sizeof(*src_arr));                           \
	return 1;                                                                               \
ERROR:                                                                                          \
	return (jarr_init(jarr), 0);                                                            \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_APPEND)

#define MAX_(a,b) ((a) > (b) ? (a) : (b))

static ALWAYS_INLINE int tmp_realloc(void **arr, size_t size)
{
	void *tmp;
	if ((tmp = realloc(*arr, size))) {
		*arr = tmp;
		return 1;
	}
	return 0;
}

static ALWAYS_INLINE void tmp_grow(size_t size, size_t *arr_cap)
{
	do {
		*arr_cap *= 2;
	} while (size > *arr_cap);
}

#define reserve(arr, size)                                                             \
	(size > ((arr)->capacity))                                                     \
		? (tmp_realloc(&((arr)->data), size * sizeof(*((arr)->data)))) ? 1 : 0 \
		: 1                                                                    \

#ifdef JARR_DEBUG
int main()
{
	jarray_int_t arr;
	int ret;
	printf("%d\n", ((ret = 1), ret++));
	return 0;
}
#endif
