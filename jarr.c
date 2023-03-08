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

#define JARR_DELETE_NOCHECK(T)                                   \
ALWAYS_INLINE void jarr_delete_nocheck_##T(T *RESTRICT jarr_ptr) \
{                                                                \
	jarr_delete_nocheck(jarr_ptr);                           \
}

JARR_TEMPLATE_T(JARR_DELETE_NOCHECK)

#define f_jarr_delete_nocheck(jarr_ptr) JARR_GENERIC(jarr_delete_nocheck, jarr_ptr, )

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

#define JARR_RESERVE_NOCHECK(T, t)                                                  \
ALWAYS_INLINE int jarr_reserve_nocheck_##T(T *RESTRICT jarr_ptr, size_t cap)        \
{                                                                                   \
	t *tmp;                                                                     \
	if (likely(tmp = realloc(jarr_ptr->data, cap * sizeof(*jarr_ptr->data)))) { \
		jarr_ptr->data = tmp;                                               \
		return 1;                                                           \
	}                                                                           \
	return 0;                                                                   \
}

JARR_TEMPLATE_T_t(JARR_RESERVE_NOCHECK)

#define JARR_CAT_NOALLOC(T, t)                                                          \
ALWAYS_INLINE void jarr_cat_noalloc_##T(T *RESTRICT jarr_ptr, int argc, ...)            \
{                                                                                       \
	va_list ap;                                                                     \
	va_start(ap, argc);                                                             \
	t *RESTRICT tmpJarr = jarr_ptr->data;                                           \
	for (void *RESTRICT argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *)) \
		*tmpJarr++ = *(t*)argv;                                                 \
	va_end(ap);                                                                     \
}

JARR_TEMPLATE_T_t(JARR_CAT_NOALLOC)

#define f_jarr_cat_noalloc(jarr_ptr, argc, ...) JARR_GENERIC(jarr_cat_noalloc, jarr_ptr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define JARR_CAT_NOCHECK(T, t)                                                              \
ALWAYS_INLINE int jarr_cat_nocheck_##T(T *RESTRICT jarr_ptr, int argc, ...)                 \
{                                                                                           \
	do { jarr_ptr->capacity *= 2; } while (jarr_ptr->size + argc > jarr_ptr->capacity); \
	if (unlikely(jarr_reserve_nocheck_##T(jarr_ptr, jarr_ptr->capacity))) {             \
		jarr_ptr->capacity = 0;                                                     \
		return 0;                                                                   \
	}                                                                                   \
	va_list ap;                                                                         \
	va_start(ap, argc);                                                                 \
	t *RESTRICT tmpJarr = jarr_ptr->data;                                               \
	for (void *RESTRICT argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *))     \
		*tmpJarr++ = *(t*)argv;                                                     \
	va_end(ap);                                                                         \
	return 1;                                                                           \
}

JARR_TEMPLATE_T_t(JARR_CAT_NOCHECK)

#define f_jarr_cat_nocheck(jarr_ptr, argc, ...) JARR_GENERIC(jarr_cat_nocheck, jarr_ptr, PP_NARG(__VA_ARGS__), __VA_ARGS__)


#define JARR_CAT(T, t)                                                                              \
ALWAYS_INLINE int jarr_cat_##T(T *RESTRICT jarr_ptr, int argc, ...)                                 \
{                                                                                                   \
	if (jarr_ptr->size + argc > jarr_ptr->capacity) {                                           \
		do { jarr_ptr->capacity *= 2; } while (jarr_ptr->size + argc > jarr_ptr->capacity); \
		if (unlikely(jarr_reserve_nocheck_##T(jarr_ptr, jarr_ptr->capacity))) {             \
			jarr_ptr->capacity = 0;                                                     \
			return 0;                                                                   \
		}                                                                                   \
	}                                                                                           \
	va_list ap;                                                                                 \
	va_start(ap, argc);                                                                         \
	t *RESTRICT tmpJarr = jarr_ptr->data;                                                       \
	for (void *RESTRICT argv = va_arg(ap, void *); argv; argv = va_arg(ap, void *))             \
		*tmpJarr++ = *(t*)argv;                                                             \
	va_end(ap);                                                                                 \
	return 1;                                                                                   \
}

JARR_TEMPLATE_T_t(JARR_CAT)

#define f_jarr_cat(jarr_ptr, argc, ...) JARR_GENERIC(jarr_cat, jarr_ptr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#endif // end of JARR_TEMPLATES

/* ALWAYS_INLINE void jarr_pop_front(jarray_int_t *jarr_ptr) */
/* { */
/* 	int* end = jarr_ptr->data + jarr_ptr->size; */ 
/* 	int* start = jarr_ptr->data; */
/* 	for ( ; start < end; ++start) */
/* 		*(start) = *(start + 1); */
/* } */

#define JARR_DEBUG
#ifdef JARR_DEBUG

#include <assert.h>
static ALWAYS_INLINE int debug()
{
	int ret;
	char a[100];
	jarray_int_t arr;
	jarr_init(&arr);
	assert(jarr_new(&arr, 1, 2, 3));
	assert(jarr_append(&arr, a, 10));
	assert(jarr_cat(&arr, 1, 3, 4));
	assert(jarr_push_back(&arr, 3));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink(&arr));
	/* jarr_pop_front(&arr); */
	jarr_delete(&arr);
	return 1;
}

int main()
{
	assert(debug());
	return 0;
}

#endif // end of JARR_DEBUG
