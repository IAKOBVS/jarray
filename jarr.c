#include "jarr.h"
#include <stdarg.h>

#define PRIVATE_JARR_NEW(T, t)                                                         \
static int jarr_new_##T(T *jarr, size_t size, ...)                                     \
{                                                                                      \
	jarr->capacity = MAX(2 * JARR_NEAR_POW2(size), JARR_MIN_CAP);                  \
	if (likely(jarr->data = malloc((jarr->capacity) * sizeof(*jarr->data)))) {     \
		va_list ap;                                                            \
		va_start(ap, size);                                                    \
		for (void* argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *)) \
			jarr->data[jarr->size++] = *(t*)argv;                          \
		va_end(ap);                                                            \
		return 1;                                                              \
	}                                                                              \
	jarr_init(jarr);                                                               \
	return 0;                                                                      \
}

PRIVATE_JARR_NEW(jarray_int_t, int)
PRIVATE_JARR_NEW(jarray_uint_t, unsigned int)
PRIVATE_JARR_NEW(jarray_long_t, long)
PRIVATE_JARR_NEW(jarray_long_long_t, long long)
PRIVATE_JARR_NEW(jarray_ulong_t, unsigned long)
PRIVATE_JARR_NEW(jarray_ulong_long_t, unsigned long long)
PRIVATE_JARR_NEW(jarray_size_t_t, size_t)
PRIVATE_JARR_NEW(jarray_double_t, double)
PRIVATE_JARR_NEW(jarray_long_double_t, long double)
PRIVATE_JARR_NEW(jarray_float_t, float)
PRIVATE_JARR_NEW(jarray_short_t, short)
PRIVATE_JARR_NEW(jarray_ushort_t, unsigned short)
PRIVATE_JARR_NEW(jarray_char_t, char)
PRIVATE_JARR_NEW(jarray_uchar_t, unsigned char)

#ifdef JARR_DEBUG
int main() {}
#endif
