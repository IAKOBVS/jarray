#include "jarr.h"
#include <stdio.h>
#include <stdarg.h>

/* #define JARR_TEMPLATES */
#ifdef JARR_TEMPLATES

#define JARR_INIT(T)                                   \
ALWAYS_INLINE void jarr_init_##T(T *RESTRICT jarr_ptr) \
{                                                      \
	jarr_init(jarr_ptr);                           \
}

JARR_TEMPLATE_T(JARR_INIT)

#define f_jarr_init(jarr_ptr) JARR_GENERIC(jarr_init, jarr_ptr, )

#define JARR_DELETE(T)                                   \
ALWAYS_INLINE void jarr_delete_##T(T *RESTRICT jarr_ptr) \
{                                                        \
	jarr_delete(jarr_ptr);                           \
}

JARR_TEMPLATE_T(JARR_DELETE)

#define f_jarr_delete(jarr_ptr) JARR_GENERIC(jarr_delete, jarr_ptr, )

#define JARR_NEW_ALLOC(T)                                              \
ALWAYS_INLINE int jarr_new_alloc_##T(T *RESTRICT jarr_ptr, size_t cap) \
{                                                                      \
	return jarr_new_alloc(jarr_ptr, cap);                          \
}

JARR_TEMPLATE_T(JARR_NEW_ALLOC)

#define f_jarr_new_alloc(jarr_ptr) JARR_GENERIC(jarr_new_alloc, jarr_ptr, cap)

#define JARR_PUSH_FRONT(T, t)                                        \
ALWAYS_INLINE int jarr_push_front_##T(T *RESTRICT jarr_ptr, t value) \
{                                                                    \
	if (unlikely(jarr_ptr->capacity == jarr_ptr->size))          \
		if (unlikely(!jarr_reserve_2x(jarr_ptr)))            \
			return 0;                                    \
	private_jarr_push_front(&(jarr_ptr->data), jarr_ptr->size);  \
	*jarr_ptr->data = value;                                     \
	++jarr_ptr->size;                                            \
}

JARR_TEMPLATE_T_t(JARR_PUSH_FRONT)

#define JARR_POP_FRONT(T, t)                                           \
ALWAYS_INLINE int jarr_pop_front_##T(T *RESTRICT jarr_ptr)             \
{                                                                      \
	return private_jarr_pop_front(jarr_ptr->data, jarr_ptr->size); \
}

JARR_TEMPLATE_T_t(JARR_POP_FRONT)

#define JARR_CAT(T, t)                                                                  \
ALWAYS_INLINE int jarr_cat_##T(T *RESTRICT jarr_ptr, int argc, ...)                     \
{                                                                                       \
	if (jarr_ptr->size + argc > jarr_ptr->capacity) {                               \
		size_t tmp_cap = jarr->capacity * 2;                                    \
		while (tmp_cap > jarr_ptr->capacity);                                   \
			tmp_cap *= 2;                                                   \
		if (unlikely(jarr_reserve_nocheck_##T(jarr_ptr, jarr_ptr->capacity))) { \
			return 0;                                                       \
		}                                                                       \
	}                                                                               \
	va_list ap;                                                                     \
	va_start(ap, argc);                                                             \
	t *RESTRICT tmpJarr = jarr_ptr->data;                                           \
	for (void *RESTRICT argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *)) \
		*tmpJarr++ = *(t*)argv;                                                 \
	va_end(ap);                                                                     \
	return 1;                                                                       \
}

JARR_TEMPLATE_T_t(JARR_CAT)

#define f_jarr_cat(jarr_ptr, argc, ...) JARR_GENERIC(jarr_cat, jarr_ptr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#endif // end of JARR_TEMPLATES

/* #define JARR_DEBUG */
#ifdef JARR_DEBUG

#include <assert.h>
static ALWAYS_INLINE int debug()
{
	int ret;
	char a[100];
	jarray_int_t arr;
	jarr_init(&arr);
	assert(jarr_new_auto(&arr, 1, 2, 3));
	assert(jarr_append(&arr, a, 10));
	assert(jarr_cat(&arr, 4, 5, 6));
	assert(jarr_push_back(&arr, 7));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink(&arr));
	jarr_pop_front(&arr);
	assert(jarr_push_front(&arr, 99));
	jarr_foreach(i, &arr) {
		pp_cout(*i);
	}
	jarr_delete(&arr);
	return 1;
}

int main()
{
	assert(debug());
	return 0;
}

#endif // end of JARR_DEBUG
