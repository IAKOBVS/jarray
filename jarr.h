#ifndef JARR_H_DEF
#define JARR_H_DEF

/* #define JARR_RELEASE */
#define JARR_INCLUDE
#define JARR_ALIGN_POWER_OF_TWO
#define JARR_64_BIT

#ifdef JARR_RELEASE
	#undef JARR_DEBUG
#else
	#define JARR_DEBUG
#endif

#include "/home/james/c/macros/vargc.h" // gch
#include "macros.h" // gch
#include "types.h" //gch
#include <stddef.h>

#ifdef JARR_INCLUDE
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdint.h>
#endif

#define JARR_MIN_CAP 8

#if defined(__GNUC__) || defined(__clang__)
	#define JARR_NEAR_POW2_32(x) \
		((x) ? 1 : 1UL << (sizeof((x)) * 8 - __builtin_clz((x) - 1)))
	#define JARR_NEAR_POW2_64(x) \
		((x) ? 1 : 1ULL << (sizeof((x)) * 8 - __builtin_clzll((x) - 1)))
#else
	#define JARR_NEAR_POW2_32(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		++x)
	#define JARR_NEAR_POW2_64(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		x |= x >> 32,        \
		++x)
#endif

#ifdef JARR_ALIGN_POWER_OF_TWO
	#ifdef JARR_64_BIT
		#define JARR_NEAR_POW2(x) JARR_NEAR_POW2_64(x)
	#elif JARR_32_BIT
		#define JARR_NEAR_POW2(x) JARR_NEAR_POW2_32(x)
	#else
		#define JARR_NEAR_POW2(x) (x)
	#endif
#endif

/*
   _Generic will determine whether a jarray is passed.

   If 0 is passed as array size (src_arr_size),
   it will expect a jarray or stack array.

   You must pass the size if it's a heap array.
*/

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t size;     \
		size_t capacity; \
	} NAME

#define static_jarray_init(T, name, capacity)     \
	struct {                                  \
		T data[JARR_NEAR_POW2(capacity)]; \
		size_t size;                      \
	} name

JARR_STRUCT(jarray_int_t, int);
JARR_STRUCT(jarray_uint_t, unsigned int);
JARR_STRUCT(jarray_long_t, long);
JARR_STRUCT(jarray_long_long_t, long long);
JARR_STRUCT(jarray_ulong_t, unsigned long);
JARR_STRUCT(jarray_ulong_long_t, unsigned long long);
JARR_STRUCT(jarray_size_t_t, size_t);
JARR_STRUCT(jarray_double_t, double);
JARR_STRUCT(jarray_long_double_t, long double);
JARR_STRUCT(jarray_float_t, float);
JARR_STRUCT(jarray_short_t, short);
JARR_STRUCT(jarray_ushort_t, unsigned short);
JARR_STRUCT(jarray_char_t, char);
JARR_STRUCT(jarray_uchar_t, unsigned char);

/* jarray_int_t, int */
/* jarray_uint_t, unsigned int */
/* jarray_long_t, long */
/* jarray_long_long_t, long long */
/* jarray_ulong_t, unsigned long */
/* jarray_ulong_long_t, unsigned long long */
/* jarray_size_t_t, size_t */
/* jarray_double_t, double */
/* jarray_long_double_t, long double */
/* jarray_float_t, float */
/* jarray_short_t, short */
/* jarray_ushort_t, unsigned short */
/* jarray_char_t, char */
/* jarray_uchar_t, unsigned char */

/* jarray_int_t */
/* jarray_uint_t */
/* jarray_long_t */
/* jarray_long_long_t */
/* jarray_ulong_t */
/* jarray_ulong_long_t */
/* jarray_size_t_t */
/* jarray_double_t */
/* jarray_long_double_t */
/* jarray_float_t */
/* jarray_short_t */
/* jarray_ushort_t */
/* jarray_char_t */
/* jarray_uchar_t */


/* int */
/* unsigned int */
/* long */
/* long long */
/* unsigned long */
/* unsigned long long */
/* size_t */
/* double */
/* long double */
/* float */
/* short */
/* unsigned short */
/* char */
/* unsigned char */

/* int: jarray_int_t, */
/* unsigned int: jarray_uint_t, */
/* long: jarray_long_t, */
/* long long: jarray_long_long_t, */
/* unsigned long: jarray_ulong_t, */
/* unsigned long long: jarray_ulong_long_t, */
/* size: jarray_size_t_t_t, */
/* double: jarray_double_t, */
/* long double: jarray_long_double_t, */
/* *jarray_float_t: jarray_float_t, */
/* short: jarray_short_t, */
/* unsigned short: jarray_ushort_t, */
/* char: jarray_char_t, */
/* *jarray_unsigned_char_t: jarray_uchar_t, */

#define JARR_TEMPLATE_T(F) \
F(jarray_int_t)            \
F(jarray_uint_t)           \
F(jarray_long_t)           \
F(jarray_long_long_t)      \
F(jarray_ulong_t)          \
F(jarray_ulong_long_t)     \
F(jarray_size_t_t)         \
F(jarray_double_t)         \
F(jarray_long_double_t)    \
F(jarray_float_t)          \
F(jarray_short_t)          \
F(jarray_ushort_t)         \
F(jarray_char_t)           \
F(jarray_uchar_t)          \

#define JARR_TEMPLATE_T_t(F)               \
F(jarray_int_t, int)                       \
F(jarray_uint_t, unsigned int)             \
F(jarray_long_t, long)                     \
F(jarray_long_long_t, long long)           \
F(jarray_ulong_t, unsigned long)           \
F(jarray_ulong_long_t, unsigned long long) \
F(jarray_size_t_t, size_t)                 \
F(jarray_double_t, double)                 \
F(jarray_long_double_t, long double)       \
F(jarray_float_t, float)                   \
F(jarray_short_t, short)                   \
F(jarray_ushort_t, unsigned short)         \
F(jarray_char_t, char)                     \
F(jarray_uchar_t, unsigned char)           \

#define JARR_GENERIC(F, T, ...) _Generic((T),                                  \
	*jarray_int_t: F##_jarray_int_t(jarr_ptr, __VA_ARGS__),                 \
	*jarray_uint_t: F##_jarray_uint_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_long_t F##_jarray_long_t(jarr_ptr, __VA_ARGS__),                \
	*jarray_long_long_t: F##_jarray_long_long_t(jarr_ptr, __VA_ARGS__),     \
	*jarray_ulong_t: F##_jarray_ulong_t(jarr_ptr, __VA_ARGS__),             \
	*jarray_ulong_long_t F##_jarray_ulong_long_t(jarr_ptr, __VA_ARGS__),    \
	*jarray_size_t_t: F##_jarray_size_t_t(jarr_ptr, __VA_ARGS__),           \
	*jarray_double_t: F##_jarray_double_t(jarr_ptr, __VA_ARGS__),           \
	*jarray_long_double_t: F##_jarray_long_double_t(jarr_ptr, __VA_ARGS__), \
	*jarray_float_t: F##_jarray_float_t(jarr_ptr, __VA_ARGS__),             \
	*jarray_short: F##_jarray_short_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_ushort_t F##_jarray_ushort_t(jarr_ptr, __VA_ARGS__),            \
	*jarray_char_t: F##_jarray_char_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_unsigned_char_t: F##_jarray_uchar_t(jarr_ptr, __VA_ARGS__)      \
		)

#define PRIVATE_JARR_GET_DATA(T, t)                                               \
static ALWAYS_INLINE t* private_jarr_get_data_##T(T *jarr) { return jarr->data; }

JARR_TEMPLATE_T_t(PRIVATE_JARR_GET_DATA)
#define jarr_get_data(jarr_ptr) JARR_GENERIC(jarr_get_data, jarr_ptr, )

#define PRIVATE_JARR_GET_SIZE(T)                                                        \
static ALWAYS_INLINE size_t private_jarr_get_size_##T(T *jarr) { return jarr->size; }

JARR_TEMPLATE_T(PRIVATE_JARR_GET_SIZE)
#define jarr_get_size(jarr_ptr) JARR_GENERIC(jarr_get_size, jarr_ptr, )

#define PRIVATE_JARR_GET_CAPACITY(T)                                                           \
static ALWAYS_INLINE size_t private_jarr_get_capacity_##T(T *jarr) { return jarr->capacity; }

JARR_TEMPLATE_T(PRIVATE_JARR_GET_CAPACITY)
#define jarr_get_capacity(jarr_ptr) JARR_GENERIC(jarr_get_capacity, jarr_ptr, )

#define PRIVATE_JARR_INIT(T)                                   \
static ALWAYS_INLINE void jarr_init_##T(T *jarr)               \
{                                                              \
	jarr->data = NULL, jarr->capacity = 0, jarr->size = 0; \
}                                                              \

JARR_TEMPLATE_T(PRIVATE_JARR_INIT)
#define jarr_init(jarr_ptr) JARR_GENERIC(jarr_init, jarr_ptr, )

#define JARR_INIT(jarr)                                                          \
(void)(((jarr)->capacity) = 0, ((jarr)->size) = 0, ((((jarr)->data) = NULL), 0))

#define JARR_POW2 1
#define JARR_POW2_OFF 0

/*
   _nocheck macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc;

   _noalloc macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.
*/

#define PRIVATE_JARR_DELETE(T)                                   \
static ALWAYS_INLINE void jarr_delete_##T(T *jarr)               \
{                                                                \
	if (jarr->data) free((jarr)->data), jarr_init_##T(jarr); \
}

JARR_TEMPLATE_T(PRIVATE_JARR_DELETE)
#define jarr_delete(jarr_ptr) JARR_GENERIC(jarr_delete, jarr_ptr, )

#define PRIVATE_JARR_DELETE_NOCHECK(T)                     \
static ALWAYS_INLINE void jarr_delete_nocheck_##T(T *jarr) \
{                                                          \
	free(jarr->data), jarr_init_##T(jarr);             \
}

JARR_TEMPLATE_T(PRIVATE_JARR_DELETE_NOCHECK)
#define jarr_delete_nocheck(jarr_ptr) JARR_GENERIC(jarr_delete_nocheck, jarr_ptr, )

#define PRIVATE_JARR_NEW_ALLOC(T)                                                               \
static ALWAYS_INLINE int jarr_new_alloc_##T(T *jarr, size_t cap)                                \
{                                                                                               \
	jarr->capacity = MAX(cap, JARR_MIN_CAP);                                                \
	return (likely((jarr->data) = malloc(jarr->capacity * sizeof(*(jarr->data))))) ? 1 : 0; \
}

JARR_TEMPLATE_T(PRIVATE_JARR_NEW_ALLOC)
#define jarr_new_alloc(jarr_ptr, cap) JARR_GENERIC(jarr_ptr, jarr_new_alloc, cap)

#define PRIVATE_JARR_RESERVE(T)                                                                                               \
static ALWAYS_INLINE int jarr_reserve_##T(T *jarr, size_t cap)                                                                \
{                                                                                                                             \
	T *tmp;                                                                                                               \
	return (cap > jarr->capacity) ? ((tmp = (realloc(jarr->data, sizeof(*jarr->data) * cap))) ? (jarr = tmp, 1) : 0) : 0; \
}

#define PRIVATE_JARR_RESERVE_NOCHECK(T)                                                          \
static ALWAYS_INLINE int jarr_reserve_nocheck_##T(T *jarr, size_t cap)                           \
{                                                                                                \
	T *tmp;                                                                                  \
	return ((tmp = (realloc(jarr->data, sizeof(*jarr->data) * cap))) ? (jarr = tmp, 1) : 0); \
}

JARR_TEMPLATE_T(PRIVATE_JARR_RESERVE)
#define jarr_reserve(jarr_ptr, cap) JARR_GENERIC(jarr_reserve, jarr_ptr, cap)

JARR_TEMPLATE_T(PRIVATE_JARR_RESERVE_NOCHECK)
#define jarr_reserve_nocheck(jarr_ptr, cap) JARR_GENERIC(jarr_reserve_nocheck, jarr_ptr, cap)

#define jarr_reserve_2x(jarr) jarr_reserve_nocheck(jarr, (2 * ((jarr)->capacity)))
#define jarr_reserve_4x(jarr) jarr_reserve_nocheck(jarr, (4 * ((jarr)->capacity)))
#define jarr_reserve_8x(jarr) jarr_reserve_nocheck(jarr, (8 * ((jarr)->capacity)))
#define jarr_reserve_16x(jarr) jarr_reserve_nocheck(jarr, (16 * ((jarr)->capacity)))
#define jarr_reserve_32x(jarr) jarr_reserve_nocheck(jarr, (32 * ((jarr)->capacity)))
#define jarr_reserve_64x(jarr) jarr_reserve_nocheck(jarr, (64 * ((jarr)->capacity)))

#define PRIVATE_JARR_PUSH_BACK(T, t)                                                                              \
static ALWAYS_INLINE int jarr_push_back_##T(T *jarr, t src)                                                       \
{                                                                                                                 \
	return (unlikely(jarr->capacity == jarr->size))                                                           \
		? ((jarr_reserve_nocheck_##T(jarr, jarr->capacity * 2)) && ((jarr->data[jarr->size++] = src), 1)) \
		: (jarr->data[jarr->size++] = src, 1);                                                            \
}

JARR_TEMPLATE_T_t(PRIVATE_JARR_PUSH_BACK)
#define jarr_push_back(jarr_ptr, value) JARR_GENERIC(jarr_push_back, jarr_ptr, value)

#define jarr_shrink(jarr_ptr) JARR_GENERIC(jarr_shrink, jarr_ptr, )

#define jarr_new_auto(jarr_ptr, ...) JARR_GENERIC(jarr_new, jarr_ptr, __VA_ARGS__)
#define jarr_new(jarr_ptr, jarr_size, ...) JARR_GENERIC(jarr_new, jarr_ptr, jarr_size)

#define jarr_cat(jarr_ptr, ...) JARR_GENERIC(jarr_cat, jarr_ptr, PP_NARG(__VA_ARGS__), ...)
#define jarr_cat_noalloc(jarr_ptr, ...) JARR_GENERIC(jarr_cat_noalloc, jarr_ptr, PP_NARG(__VA_ARGS__), ...)

#define jarr_append(jarr_ptr, src_arr) JARR_GENERIC(jarr_append, jarr_ptr, src_arr)

#define jarr_pop_back(jarr) --((jarr)->size);

#define jarr_cmp(jarr_dest, jarr_src) ((((jarr_dest)->size) != ((jarr_src)->size)) || memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp_nocheck(jarr_dest, jarr_src) (memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))

#define jarr_foreach_index(elem, jarr) for (size_t elem = 0, size = ((jarr)->size); elem < size; ++elem)

#define jarr_foreach(elem, jarr) for (typeof(*((jarr)->data)) *RESTRICT elem = ((jarr)->data), *RESTRICT end = ((jarr)->data) + ((jarr)->size); elem < end; ++elem)

#define jarr_foreach_arr(elem, arr) for (typeof(arr[0]) *RESTRICT elem = &(arr[0]), *RESTRICT end = (&((arr)[(sizeof(arr)/sizeof(arr[0])) - 1])); elem < end; ++elem)

#define jarr_end(jarr) (*(((jarr)->data) + ((jarr)->size) - 1))

#define jarr_auto_elem(jarr) typeof(*((jarr)->data))

#define jarr_auto(jarr) typeof((*(jarr)))

#define JARR_SAME_TYPE(x, y) _Generic((x), \
	typeof(y): 1,                      \
	default: 0                         \
	)

#endif
