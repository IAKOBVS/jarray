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
	JARR_INIT(jarr);                                                           \
	return 0;                                                                  \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_NEW)

#define PRIVATE_JARR_CAT(T, t)                                                                      \
int jarr_cat_##T(T *jarr, size_t size, ...)                                                         \
{                                                                                                   \
	if (jarr->size + size > jarr->capacity) {                                                   \
		do { jarr->capacity *= 2; } while (jarr->size + size > jarr->capacity);             \
		t *tmp;                                                                             \
		jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);                       \
		if (unlikely(!(tmp = realloc(jarr->data, (jarr->capacity) * sizeof(*jarr->data))))) \
			goto ERROR;                                                                 \
		jarr->data = tmp;                                                                   \
	}                                                                                           \
	PRIVATE_JARR_CONCAT(T, jarr, t, argv, size);                                                \
	return 1;                                                                                   \
ERROR:                                                                                              \
	JARR_INIT(jarr);                                                                            \
	return 0;                                                                                   \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_CAT)

#define PRIVATE_JARR_APPEND(T, t)                                                               \
int jarr_append_##T(T *jarr, t *src_arr, size_t src_arr_size)                                   \
{                                                                                               \
	if (jarr->size + src_arr_size > jarr->capacity) {                                       \
		do { jarr->capacity *= 2; } while (jarr->size + src_arr_size > jarr->capacity); \
		t* tmp;                                                                         \
		if (unlikely(!(tmp = realloc(jarr->data, jarr->capacity * sizeof(*src_arr)))))  \
			goto ERROR;                                                             \
	}                                                                                       \
	memcpy(jarr->data, src_arr, src_arr_size * sizeof(*src_arr));                           \
	return 1;                                                                               \
ERROR:                                                                                          \
	return (JARR_INIT(jarr), 0);                                                            \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_APPEND)

#define PRIVATE_JARR_SHRINK(T, t)                                                        \
int jarr_shrink_##T(T *jarr)                                                             \
{                                                                                        \
	t *tmp;                                                                          \
	return (likely(jarr->capacity != jarr->size))                                    \
		? ((likely(tmp = realloc(jarr->data, jarr->size * sizeof(*jarr->data)))) \
			 ? (jarr->capacity = jarr->size, jarr->data = tmp, 1)            \
			 : (JARR_INIT(jarr), 0))                                         \
		: 1;                                                                     \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_SHRINK)

#ifdef JARR_DEBUG
int main()
{
	return 0;
}
#endif
