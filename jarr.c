#include "jarr.h"
#include <stdarg.h>

#define PRIVATE_JARR_CONCAT(T, jarr, t, argv)                                  \
	va_list ap;                                                            \
	va_start(ap, size);                                                    \
	for (void* argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *)) \
		jarr->data[jarr->size++] = *(t*)argv;                          \
	va_end(ap)

#define PRIVATE_JARR_NEW(T, t)                                                     \
int jarr_new_##T(T *jarr, size_t size, ...)                                        \
{                                                                                  \
	jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);              \
	if (likely(jarr->data = malloc((jarr->capacity) * sizeof(*jarr->data)))) { \
		PRIVATE_JARR_CONCAT(T, jarr, t, argv);                             \
		return 1;                                                          \
	}                                                                          \
	return (JARR_INIT(jarr), 0);                                               \
}

JARR_DEFINE_F_T_t(PRIVATE_JARR_NEW)

#define PRIVATE_JARR_CAT(T, t)                                                     \
int jarr_cat_##T(T *jarr, size_t size, ...)                                        \
{                                                                                  \
	jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);              \
	if (likely(jarr->data = malloc((jarr->capacity) * sizeof(*jarr->data)))) { \
		PRIVATE_JARR_CONCAT(T, jarr, t, argv);                             \
		return 1;                                                          \
	}                                                                          \
	return (JARR_INIT(jarr), 0);                                               \
}

JARR_DEFINE_F_T_t(PRIVATE_JARR_CAT)

#ifdef DEUG
int main()
{

}
#endif
