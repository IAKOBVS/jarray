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

#include "/home/james/c/macros/vargc.h"
#include "macros.h"
#include "types.h"

#include <stddef.h>

#ifdef JARR_INCLUDE
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdint.h>
#endif

#define JARR_IGNORE_IF ,1
#define JARR_NOALLOC ,1
#define JARR_NOCHECK ,1
#define JARR_FORCE_CMP ,1

#define JARR_NOALLOC_OFF
#define JARR_NOCHECK_OFF
#define JARR_FORCE_CMP_OFF


#if defined(__GNUC__) || defined(__clang__)
	#define JARR_NEAR_POW2_32(x) \
		((x) ? 1 : 1UL << (sizeof((x)) * 8 - __builtin_clz((x) - 1)))

	static ALWAYS_INLINE unsigned int private_jarr_near_pow_32(unsigned int x) { return JARR_NEAR_POW2_32(x); }

	#define JARR_NEAR_POW2_64(x) \
		((x) ? 1 : 1ULL << (sizeof((x)) * 8 - __builtin_clzll((x) - 1)))

	static ALWAYS_INLINE uint64_t private_jarr_near_pow_64(unsigned int x) { return JARR_NEAR_POW2_64(x); }
#else
	#define JARR_NEAR_POW2_32(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		++x)
	static ALWAYS_INLINE unsigned int private_jarr_near_pow_32(unsigned int x) { return JARR_NEAR_POW2_32(x); }

	#define JARR_NEAR_POW2_64(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		x |= x >> 32,        \
		++x)
	static ALWAYS_INLINE unsigned int private_jarr_near_pow_64(unsigned int x) { return JARR_NEAR_POW2_64(x); }
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

#if (defined(__GNUC__) || defined(__clang__))
	#define JARR_USING_STATEMENT_EXPRESSIONS
#endif

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define JARR_MACRO_START ({
	#define JARR_MACRO_END })

	#define JARR_TERNARY_START JARR_MACRO_START
	#define JARR_TERNARY_END ;JARR_MACRO_END

	#define JARR_RET_DECLARE(x) jarray_return_t x;
	#define JARR_RET_IS(RET_VAR, RET) RET_VAR = RET;
	#define JARR_RET_IS_EXPR(RET_VAR, RET) RET_VAR = RET
	#define JARR_RET_SUCCESS(RET_VAR) JARR_RET_IS(RET_VAR, 1)
	#define JARR_RET_FAIL(RET_VAR) JARR_RET_IS(RET_VAR, 0)
	#define JARR_RET_END(x) (x);

	#define JARR_TMP_DECLARE(x) jarray_tmp_t x;
	#define JARR_TMP_IS(tmp, value) (x) = (value);
#else
	#define JARR_MACRO_START do {
	#define JARR_MACRO_END } while (0)
	
	#define JARR_TERNARY_START (
	#define JARR_TERNARY_END )

	#define JARR_RET_DECLARE
	#define JARR_RET_IS(RET_VAR, RET) RET_VAR = RET;
	#define JARR_RET_IS_EXPR(RET_VAR, RET) RET_VAR = RET
	#define JARR_RET_SUCCESS(RET_VAR) JARR_RET_IS(RET_VAR, 1)
	#define JARR_RET_FAIL(RET_VAR) JARR_RET_IS(RET_VAR, 0)
	#define JARR_RET_END

	#define JARR_TMP_DECLARE(x) jarray_tmp_t x;
	#define JARR_TMP_IS(tmp, value) (x) = (value);
#endif

#define JARR_MIN_CAP (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_T_SIZE(var) (sizeof(*((var)->data)))
#define JARR_ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define jarr_sizeof_arr(arr) (JARR_ARR_SIZE(arr))

#define JARR_IS_ARRAY 1
#define JARR_IS_ARRAY_PTR 2
#define JARR_IS_JARRAY 3
#define JARR_IS_JARRAY_PTR 4

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_STATIC_ASSERT__) && defined(_Static_assert)
	#define JARR_ASSERT(expr, msg) _Static_assert(expr, msg)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_STATIC_ASSERT__)
	#define JARR_ASSERT(expr, msg) static_assert(expr, msg)
#else
	#define JARR_ASSERT(expr, msg)
#endif

unsigned int near_pow2_64(unsigned int x);
unsigned int near_pow2_32(unsigned int x);

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

typedef int jarray_return_t;
typedef void *jarray_tmp_t;

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

#define JARR_DEFINE_F_T_t(F)               \
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

#define JARR_DEFINE_F_T(F) \
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

#define JARR_DEFINE_G(F, T, ...) _Generic((T),                                  \
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

JARR_DEFINE_F_T_t(PRIVATE_JARR_GET_DATA)
#define jarr_get_data(jarr_ptr) JARR_DEFINE_G(jarr_get_data, jarr_ptr, )

#define PRIVATE_JARR_GET_SIZE(T)                                                        \
static ALWAYS_INLINE size_t private_jarr_get_size_##T(T *jarr) { return jarr->size; }

JARR_DEFINE_F_T(PRIVATE_JARR_GET_SIZE)
#define jarr_get_size(jarr_ptr) JARR_DEFINE_G(jarr_get_size, jarr_ptr, )

#define PRIVATE_JARR_GET_CAPACITY(T)                                                           \
static ALWAYS_INLINE size_t private_jarr_get_capacity_##T(T *jarr) { return jarr->capacity; }

JARR_DEFINE_F_T(PRIVATE_JARR_GET_CAPACITY)
#define jarr_get_capacity(jarr_ptr) JARR_DEFINE_G(jarr_get_capacity, jarr_ptr, )

#define PRIVATE_JARR_INIT(T)                                   \
static ALWAYS_INLINE void jarr_init_##T(T *jarr)               \
{                                                              \
	jarr->data = NULL, jarr->capacity = 0, jarr->size = 0; \
}                                                              \

JARR_DEFINE_F_T(PRIVATE_JARR_INIT)
#define jarr_init(jarr_ptr) JARR_DEFINE_G(jarr_init, jarr_ptr, )

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

JARR_DEFINE_F_T(PRIVATE_JARR_DELETE)
#define jarr_delete(jarr_ptr) JARR_DEFINE_G(jarr_delete, jarr_ptr, )

#define PRIVATE_JARR_DELETE_NOCHECK(T)                     \
static ALWAYS_INLINE void jarr_delete_nocheck_##T(T *jarr) \
{                                                          \
	free(jarr->data), jarr_init_##T(jarr);             \
}

JARR_DEFINE_F_T(PRIVATE_JARR_DELETE_NOCHECK)
#define jarr_delete_nocheck(jarr_ptr) JARR_DEFINE_G(jarr_delete_nocheck, jarr_ptr, )

#define private_jarr_delete(jarr, nocheck_)                                      \
(                                                                                \
	(((jarr)->data) nocheck_) && (void)(free((jarr)->data), jarr_init(jarr), \
	0)                                                                       \
)

#define JARR_DELETE(jarr) private_jarr_delete(jarr, JARR_NOCHECK_OFF)
#define JARR_DELETE_NOCHECK(jarr) private_jarr_delete(jarr, JARR_NOCHECK)

#define PRIVATE_JARR_NEW_ALLOC(T)                                                               \
static ALWAYS_INLINE int jarr_new_alloc_##T(T *jarr, size_t cap)                                \
{                                                                                               \
	jarr->capacity = MAX(cap, JARR_MIN_CAP);                                                \
	return (likely((jarr->data) = malloc(jarr->capacity * sizeof(*(jarr->data))))) ? 1 : 0; \
}

JARR_DEFINE_F_T(PRIVATE_JARR_NEW_ALLOC)
#define jarr_new_alloc(jarr_ptr, cap) JARR_DEFINE_G(jarr_ptr, jarr_new_alloc, cap)

#define JARR_NEW_ALLOC(jarr, cap)                                                    \
(                                                                                    \
	((((jarr)->capacity) = MAX(((cap)), JARR_MIN_CAP)),                          \
	(likely((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr)))))) \
	|| (((jarr)->capacity) = 0,                                                  \
	0)                                                                           \
)

static ALWAYS_INLINE int private_jarr_tmp_realloc(void **jarr, size_t size)
{
	void *RESTRICT tmp;
	return (likely(tmp = realloc(*jarr, size))) ? (*jarr = tmp, 1) : 0;
}

#define private_jarr_reserve(jarr, cap, pow2_, nocheck_)                                                                               \
(                                                                                                                                      \
	(((cap) > ((jarr)->capacity)) nocheck_)                                                                                        \
	&& (likely((private_jarr_tmp_realloc((void **)&((jarr)->data), JARR_T_SIZE(jarr) * ((pow2_) ? JARR_NEAR_POW2(cap) : (cap)))))) \
	&& ((((jarr)->capacity) = (cap)),                                                                                              \
	1)                                                                                                                             \
)

/* static ALWAYS_INLINE int private_jarr_reserve_T(jarray_int_t *jarr, size_t cap) */

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

JARR_DEFINE_F_T(PRIVATE_JARR_RESERVE)
#define jarr_reserve(jarr_ptr, cap) JARR_DEFINE_G(jarr_reserve, jarr_ptr, cap)

JARR_DEFINE_F_T(PRIVATE_JARR_RESERVE_NOCHECK)
#define jarr_reserve_nocheck(jarr_ptr, cap) JARR_DEFINE_G(jarr_reserve_nocheck, jarr_ptr, cap)

#define JARR_RESERVE(jarr, cap) private_jarr_reserve(jarr, cap, JARR_POW2_OFF, JARR_NOCHECK_OFF)
#define JARR_RESERVE_ALIGN(jarr, cap) private_jarr_reserve(jarr, cap, JARR_POW2, JARR_NOCHECK_OFF)

#define JARR_RESERVE_NOCHECK(jarr, cap) private_jarr_reserve(jarr, cap, JARR_POW2_OFF, JARR_NOCHECK)
#define JARR_RESERVE_NOCHECK_ALIGN(jarr, cap) private_jarr_reserve(jarr, cap, JARR_POW2, JARR_NOCHECK)

#define private_jarr_reserve_x(jarr, multiplier) private_jarr_reserve(jarr, (((jarr)->capacity) * multiplier), 0, JARR_COMMENT)
#define jarr_reserve_2x(jarr) private_jarr_reserve_x(jarr, 2)
#define jarr_reserve_4x(jarr) private_jarr_reserve_x(jarr, 4)
#define jarr_reserve_8x(jarr) private_jarr_reserve_x(jarr, 8)
#define jarr_reserve_16x(jarr) private_jarr_reserve_x(jarr, 16)
#define jarr_reserve_32x(jarr) private_jarr_reserve_x(jarr, 32)
#define jarr_reserve_64x(jarr) private_jarr_reserve_x(jarr, 64)

#define private_jarr_push_back(jarr, src)                                                                      \
(                                                                                                              \
	(unlikely(((jarr)->capacity) == ((jarr)->size)))                                                       \
		?                                                                                              \
			((private_jarr_reserve(jarr, ((jarr)->capacity) * 2, JARR_POW2_OFF, JARR_NOCHECK_OFF)) \
			&& ((((jarr)->data)[((jarr)->size)++] = src),                                          \
			1))                                                                                    \
		:                                                                                              \
			(((jarr)->data)[((jarr)->size)++] = src,                                               \
			1)                                                                                     \
)

#define PRIVATE_JARR_PUSH_BACK(T, t)                                                                              \
static ALWAYS_INLINE int jarr_push_back_##T(T *jarr, t src)                                                       \
{                                                                                                                 \
	return (unlikely(jarr->capacity == jarr->size))                                                           \
		? ((jarr_reserve_nocheck_##T(jarr, jarr->capacity * 2)) && ((jarr->data[jarr->size++] = src), 1)) \
		: (jarr->data[jarr->size++] = src, 1);                                                            \
}

JARR_DEFINE_F_T_t(PRIVATE_JARR_PUSH_BACK)
#define jarr_push_back(jarr_ptr, value) JARR_DEFINE_G(jarr_push_back, jarr_ptr, value)

#define JARR_PUSH_BACK(jarr, src) private_jarr_push_back(jarr, src)
#define JARR_PUSH_BACK_NOALLOC(jarr, src) \
	(((jarr)->data)[((jarr)->size)++] = src)

/* #define private_jarr_new(jarr, size_, ...)                                                 \ */
/* (                                                                                                      \ */
/* 	(((jarr)->capacity) = MAX(2 * JARR_NEAR_POW2((size_)), JARR_MIN_CAP),                          \ */
/* 	(likely((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr))))))                   \ */
/* 		? ((PP_NARG(__VA_ARGS__) > 1)                                                          \ */
/* 			?                                                                              \ */
/* 				(PP_LOOP_FROM(((jarr)->data), 0, __VA_ARGS__),                         \ */
/* 				((jarr)->size) = PP_NARG(__VA_ARGS__),                                 \ */
/* 				1)                                                                     \ */
/* 			:                                                                              \ */
/* 				((PP_NARG(__VA_ARGS__) == 1)                                           \ */
/* 				&& (((jarr)->data)[0] = PP_GET_FIRST_ARG(__VA_ARGS__),                 \ */
/* 				((((jarr)->size)) = 1),                                                \ */
/* 				1)))                                                                   \ */
/* 		: (((jarr)->capacity) = 0,                                                             \ */
/* 		0)                                                                                     \ */
/* ) */

/* #ifdef JARR_USING_STATEMENT_EXPRESSIONS */
/* 	#define jarr_new(jarr, jarr_size, ...) private_jarr_new(jarr, jarr_size, __VA_ARGS__) */
/* 	#define jarr_new_auto(jarr, ...) private_jarr_new(jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__) */
/* #else */
/* 	#define jarr_new(jarr, ...) private_jarr_new(jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__) */
/* 	#define jarr_new_auto(jarr, ...) private_jarr_new(jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__) */
/* #endif */

#define private_jarr_shrink(jarr, nocheck_)                                                                     \
(                                                                                                               \
	((((jarr)->capacity) != ((jarr)->size)) nocheck_)                                                       \
	&& ((likely(private_jarr_tmp_realloc((void **)&((jarr)->data), (((jarr)->size) * JARR_T_SIZE(jarr)))))) \
	&& ((((jarr)->capacity) = ((jarr)->size)),                                                              \
	1)                                                                                                      \
)

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_shrink(jarr) private_jarr_shrink(jarr, )
	#define jarr_shrink_nocheck(jarr) private_jarr_shrink(jarr, JARR_IGNORE_IF)
#else
	#define jarr_shrink(jarr) private_jarr_shrink(jarr, )
	#define jarr_shrink_nocheck(jarr) private_jarr_shrink(jarr, JARR_IGNORE_IF)
#endif

static ALWAYS_INLINE void private_jarr_grow_while_size_gt_cap(size_t size, size_t *cap)
{
	do { (*cap) *= 2; } while (size > *cap);
}


#define private_jarr_append(jarr, src_arr, src_arr_size, nocheck_)                                                        \
(                                                                                                                         \
	((((jarr)->size) + (src_arr_size)) > ((jarr)->capacity))                                                          \
		?                                                                                                         \
			(((private_jarr_grow_while_size_gt_cap((((jarr)->size) + (src_arr_size)), &((jarr)->capacity))),  \
			(likely(private_jarr_reserve(jarr, (((jarr)->size) + (src_arr_size)), JARR_POW2, JARR_NOCHECK)))) \
			&& (memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)),       \
			((jarr)->size) += (src_arr_size)),                                                                \
			1)                                                                                                \
		:                                                                                                         \
			(memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)),          \
			((jarr)->size) += (src_arr_size),                                                                 \
			1)                                                                                                \
)

#define jarr_append(jarr, src_arr, src_arr_size) private_jarr_append(jarr, private_jarr_arr_get_data(src_arr), private_jarr_arr_get_size(src_arr, src_arr_size), JARR_NOALLOC_OFF)
#define jarr_append_noalloc(jarr, src_arr, src_arr_size) private_jarr_append(jarr, private_jarr_arr_get_data(src_arr), private_jarr_arr_get_size(src_arr, src_arr_size), JARR_NOALLOC)

/* #define PRIVATE_JARR_CAT(jarr, size_, noalloc_, ...)                                                              \ */
/* (                                                                                                                 \ */
/* 	((((jarr)->size) + (size_) > ((jarr)->capacity)) noalloc_)                                                \ */
/* 		?                                                                                                 \ */
/* 			(((private_jarr_grow_while_size_gt_cap((((jarr)->size) + (size_)), &((jarr)->capacity))), \ */
/* 			jarr_reserve_nocheck(jarr, ((jarr)->capacity)))                                           \ */
/* 			&& (PP_NARG(__VA_ARGS__) > 1)                                                             \ */
/* 				?                                                                                 \ */
/* 					(PP_LOOP_FROM(((jarr)->data), 0, __VA_ARGS__),                            \ */
/* 					((jarr)->size) = PP_NARG(__VA_ARGS__),                                    \ */
/* 					1)                                                                        \ */
/* 				:                                                                                 \ */
/* 					((PP_NARG(__VA_ARGS__) == 1)                                              \ */
/* 					&& jarr_push_back_noalloc(jarr, PP_GET_FIRST_ARG(__VA_ARGS__)),           \ */
/* 					1))                                                                       \ */
/* 		:                                                                                                 \ */
/* 			((PP_NARG(__VA_ARGS__) > 1)                                                               \ */
/* 				?                                                                                 \ */
/* 					(PP_LOOP_FROM(((jarr)->data), 0, __VA_ARGS__),                            \ */
/* 					((jarr)->size) = PP_NARG(__VA_ARGS__),                                    \ */
/* 					1)                                                                        \ */
/* 				:                                                                                 \ */
/* 					((PP_NARG(__VA_ARGS__) == 1)                                              \ */
/* 					&& jarr_push_back_noalloc(jarr, PP_GET_FIRST_ARG(__VA_ARGS__)),           \ */
/* 					1))                                                                       \ */
/* ) */

/* #define JARR_CAT(jarr, ...) PRIVATE_JARR_CAT(jarr, PP_NARG(__VA_ARGS__), JARR_NOALLOC_OFF, __VA_ARGS__) */
/* #define JARR_CAT_noalloc(jarr, ...) PRIVATE_JARR_CAT(jarr, PP_NARG(__VA_ARGS__), JARR_NOALLOC, __VA_ARGS__) */

#define jarr_new(jarr_ptr, ...) JARR_DEFINE_G(jarr_new, jarr_ptr, __VA_ARGS__)

#define jarr_cat(jarr_ptr, ...) \
	((jarr_ptr)->dest == capacity) JARR_DEFINE_G(jarr_cat, jarr_ptr, PP_NARG(__VA_ARGS__), ...)

#define jarr_cat_noalloc(jarr_ptr, ...) JARR_DEFINE_G(jarr_cat, jarr_ptr, PP_NARG(__VA_ARGS__), ...)

#define jarr_pop_back(jarr) --((jarr)->size);

#define private_jarr_cmp(jarr_dest, jarr_src, nocheck_)                                                                                \
	((((jarr_dest)->size) != ((jarr_src)->size) nocheck_) || memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))

#define jar_cmp(jarr_dest, jarr_src) private_jarr_cmp(jarr_dest, jarr_src, JARR_FORCE_CMP_OFF)

#define jarr_cmp_nocheck(jarr_dest, jarr_src) private_jarr_cmp(jarr_dest, jarr_src, JARR_FORCE_CMP)

#define jarr_foreach_index(elem, jarr)                                   \
	for (size_t elem = 0, size = ((jarr)->size); elem < size; ++elem)

#define jarr_foreach(elem, jarr)                                                                                                           \
	for (typeof(*((jarr)->data)) *RESTRICT elem = ((jarr)->data), *RESTRICT end = ((jarr)->data) + ((jarr)->size); elem < end; ++elem)

#define jarr_foreach_arr(elem, arr)                                                                                                        \
	for (typeof(arr[0]) *RESTRICT elem = &(arr[0]), *RESTRICT end = (&((arr)[(sizeof(arr)/sizeof(arr[0])) - 1])); elem < end; ++elem)

#define jarr_end(jarr) (*(((jarr)->data) + ((jarr)->size) - 1))

#define jarr_auto_elem(jarr) typeof(*((jarr)->data))

#define jarr_auto(jarr) typeof((*(jarr)))

#define JARR_SAME_TYPE(x, y) _Generic((x), \
	typeof(y): 1,                      \
	default: 0)

#endif
