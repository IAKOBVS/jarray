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

#include "/home/james/c/vargc.h"
#include "macros.h"

#include <stddef.h>

#ifdef JARR_INCLUDE
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif

#if defined(__GNUC__) || defined(__clang__)
	#define JARR_NEAR_POW2_32(x) \
		((x) : 1UL << (sizeof((x)) * 8 - __builtin_clz((x) - 1)))

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
#endif

#else
	#define JARR_NEAR_POW2(x) (x)
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
	/* #define JARR_ASSERT(expr, msg) typedef char static_assertion_##__LINE__[(expr) ? 1 : -1] */
#endif

#define JARR_IGNORE_IF ,1

unsigned int near_pow2_64(unsigned int x);
unsigned int near_pow2_32(unsigned int x);

int qsort_descend(const void *RESTRICT x, const void *RESTRICT y);
int qsort_ascend(const void *RESTRICT y, const void *RESTRICT x);
float qsort_descend_fl(const void *RESTRICT x, const void *RESTRICT y);
float qsort_ascend_fl(const void *RESTRICT y, const void *RESTRICT x);
double qsort_descend_db(const void *RESTRICT x, const void *RESTRICT y);
double qsort_ascend_db(const void *RESTRICT y, const void *RESTRICT x);

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

#define jarr_init(jarr)                 \
		((jarr)->capacity) = 0, \
		((jarr)->size) = 0,     \
		((jarr)->data) = NULL;

/*
   _nocheck macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc;

   _noalloc macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.
*/

#define private_jarr_delete(jarr)                            \
	JARR_MACRO_START                                     \
		if (((jarr)->data)                           \
			free((jarr)->data), jarr_init(jarr); \
	JARR_MACRO_END

#define jarr_delete(jarr) private_jarr_delete(jarr)

#define jarr_delete_nocheck(jarr) private_jarr_delete(jarr) \
	JARR_MACRO_START                                    \
		free((jarr)->data);                         \
		jarr_init(jarr);                            \
	JARR_MACRO_END

#define jarr_new_alloc(jarr, cap)                                                     \
JARR_TERNARY_START\
	(((jarr)->capacity) = MAX(((cap)), JARR_MIN_CAP)),                            \
	((likely((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr)))))) \
		?                                                                     \
			1                                                             \
		:                                                                     \
			(((jarr)->capacity) = 0,                                      \
			perror("jarr_new malloc failed"),                             \
			0)                                                            \
JARR_TERNARY_END

#define JARR_NOCHECK ,1
#define JARR_NOCHECK_OFF

#define JARR_POW2 1
#define JARR_POW2_OFF 0

#define private_jarr_reserve(tmp_jarray, jarr, cap, pow2_, nocheck_)                                                                         \
JARR_TERNARY_START                                                                                                                           \
	JARR_TMP_DECLARE(tmp_jarray)\
	(((cap) > ((jarr)->capacity)) nocheck_)                                                                                              \
		?                                                                                                                            \
			 ((likely((tmp_jarray = realloc(((jarr)->data), JARR_T_SIZE(jarr) * ((pow2_) ? JARR_NEAR_POW2(cap) : (cap)))))) \
				?                                                                                                            \
					(((jarr)->data) = tmp_jarray,                                                                        \
					((jarr)->capacity) = (cap),                                                                          \
					1)                                                                                                   \
				:                                                                                                            \
					(perror("jarr_reserve realloc failed"),                                                              \
					0))                                                                                                  \
		:                                                                                                                            \
			0                                                                                                                    \
JARR_TERNARY_END

#define jarr_reserve(jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2_OFF, JARR_NOCHECK_OFF)
#define jarr_reserve_align(tmp_jarray, jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2, JARR_NOCHECK_OFF)

#define jarr_reserve_nocheck(tmp_jarray, jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2_OFF, JARR_NOCHECK)
#define jarr_reserve_nocheck_align(tmp_jarray, jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2, JARR_NOCHECK)

#define private_jarr_reserve_x(tmp_jarray, jarr, multiplier) private_jarr_reserve(tmp_jarray, jarr, (tmp_jarray, (tmp_jarray, (tmp_jarray, jarr)->capacity) * multiplier), 0, JARR_COMMENT)
#define jarr_reserve_2x(tmp_jarray, jarr) private_jarr_reserve_x(tmp_jarray, jarr, 2)
#define jarr_reserve_4x(tmp_jarray, jarr) private_jarr_reserve_x(tmp_jarray, jarr, 4)
#define jarr_reserve_8x(tmp_jarray, jarr) private_jarr_reserve_x(tmp_jarray, jarr, 8)
#define jarr_reserve_16x(tmp_jarray, jarr) private_jarr_reserve_x(tmp_jarray, jarr, 16)
#define jarr_reserve_32x(tmp_jarray, jarr) private_jarr_reserve_x(tmp_jarray, jarr, 32)
#define jarr_reserve_64x(tmp_jarray, jarr) private_jarr_reserve_x(tmp_jarray, jarr, 64)

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_reserve(jarray_int_t jarr)
{
	jarr_reserve(&jarr, 0);
}
#endif

#define private_jarr_push_back(tmp_jarray, jarr, src)                                                                          \
JARR_TERNARY_START                                                                                                             \
	JARR_RET_DECLARE(jarray_ret)                                                                                           \
	JARR_TMP_DECLARE(tmp_jarray)                                                                                           \
	(unlikely(((jarr)->capacity) == ((jarr)->size)))                                                                       \
		?                                                                                                              \
			JARR_RET_IS_EXPR(jarray_ret, ((jarr_reserve_nocheck_align(tmp_jarray, jarr, (((jarr)->capacity) * 2))) \
			&& ((((jarr)->data)[((jarr)->size)++] = src, 1), 1)))                                                  \
		:                                                                                                              \
			(JARR_RET_IS_EXPR(jarray_ret, (((jarr)->data)[((jarr)->size)++] = src, 1))),                           \
	JARR_RET_END(tmp_jarray)                                                                                               \
JARR_TERNARY_END

#define jarr_push_back(jarr, src) private_jarr_push_back(tmp_jarray, jarr, src)

#define jarr_push_back_noalloc(jarr, src) \
	((jarr)->data)[((jarr)->size)++] = src

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_push_back(jarray_int_t jarr, int src)
{
	jarr_push_back(&jarr, src);
}
#endif

#define private_jarr_new(jarray_ret, jarr, size_, ...)                                             \
	JARR_MACRO_START                                                                           \
		JARR_RET_DECLARE(jarray_ret)                                                       \
		((jarr)->capacity) = MAX(2 * JARR_NEAR_POW2((size_)), JARR_MIN_CAP);               \
		if ((likely((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr)))))) { \
			if (PP_NARG(__VA_ARGS__) > 1) {                                            \
				typeof(*((jarr)->data)) tmp[] = { PP_OTHER_ARGS(__VA_ARGS__) };    \
				memcpy(((jarr)->data) + ((jarr)->size), tmp, sizeof(tmp));         \
				((jarr)->size) = JARR_ARR_SIZE(tmp);                               \
			} else if (PP_NARG(__VA_ARGS__) == 1) {                                    \
				jarr_push_back_noalloc(jarr, PP_GET_FIRST_ARG(__VA_ARGS__));       \
			}                                                                          \
			JARR_RET_SUCCESS(jarray_ret)                                               \
		} else {                                                                           \
			((jarr)->capacity) = 0;                                                    \
			perror("jarr_new malloc failed");                                          \
			JARR_RET_FAIL(jarray_ret)                                                  \
		}                                                                                  \
		JARR_RET_END(jarray_ret)                                                           \
	JARR_MACRO_END

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_new(jarr, ...) private_jarr_new(jarray_ret, jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
	#define jarr_new_auto(jarr, ...) private_jarr_new(jarray_ret, jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#else
	#define jarr_new(jarray_ret, jarr, ...) private_jarr_new(jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
	#define jarr_new_auto(jarr, ...) private_jarr_new(jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_arr_new(jarray_return_t jarray_ret, jarray_int_t *jarr, size_t _size)
{
	return jarr_new(jarr, 1, 3);
}
#endif

#define private_jarr_shrink(jarr, tmp_jarray, nocheck_)                                                         \
JARR_TERNARY_START                                                                                              \
	JARR_TMP_DECLARE(tmp_jarray)                                                                            \
	((((jarr)->capacity) != ((jarr)->size)) nocheck_)                                                       \
		?                                                                                               \
			((likely(((tmp_jarray) = realloc(((jarr)->data), ((jarr)->size) * JARR_T_SIZE(jarr))))) \
				?                                                                               \
					(((jarr)->data) = (tmp_jarray),                                         \
					((jarr)->capacity) = ((jarr)->size),                                    \
					1)                                                                      \
				:                                                                               \
					(perror("jarr_shrink realloc failed"),                                   \
					0))                                                                     \
		 :                                                                                              \
			0                                                                                       \
JARR_TERNARY_END

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_shrink(jarr) private_jarr_shrink(jarr, tmp_jarray, )
	#define jarr_shrink_nocheck(jarr) private_jarr_shrink(jarr, tmp_jarray, JARR_IGNORE_IF)
#else
	#define jarr_shrink(tmp_jarray, jarr) private_jarr_shrink(jarr, tmp_jarray, )
	#define jarr_shrink_nocheck(tmp_jarray, jarr) private_jarr_shrink(jarr, tmp_jarray, JARR_IGNORE_IF)
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_shrink(jarray_tmp_t tmp_jarray, jarray_int_t jarr)
{
	return jarr_shrink(&jarr);
}
#endif

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append(tmp_jarray, jarr, src_arr, src_arr_size)                                    \
	JARR_MACRO_START                                                                                \
		if ((((jarr)->size) + (src_arr_size)) > ((jarr)->capacity)) {                           \
			do {                                                                            \
				((jarr)->capacity) *= 2;                                                \
			} while ((((jarr)->size) + (src_arr_size)) > ((jarr)->capacity));               \
			jarr_reserve_nocheck(tmp_jarray, jarr, tmp_cap);                                \
		}                                                                                       \
		memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)); \
		((jarr)->size) = new_size;                                                              \
	JARR_MACRO_END

/* } */

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append_typecheck(tmp_jarray, jarr, src_arr, src_arr_size, noalloc_)                              \
	JARR_MACRO_START                                                                                              \
		switch (JARR_TYPE_CHECK(src_arr)) {                                                                   \
		case JARR_IS_ARRAY:                                                                                   \
			(src_arr_size)                                                                                \
				? private_jarr_append(tmp_jarray, jarr, (src_arr), JARR_ARR_SIZE(src_arr), noalloc_), \
				: private_jarr_append(tmp_jarray, jarr, (src_arr), src_arr_size, noalloc_);           \
		case JARR_IS_JARRAY:                                                                                  \
			private_jarr_append(tmp_jarray, jarr, ((src_arr)->data), ((src_arr)->size), noalloc_);        \
		case JARR_IS_JARRAY_PTR:                                                                              \
			private_jarr_append(tmp_jarray, jarr, ((src_arr)->data), ((src_arr)->size), noalloc_);        \
		}                                                                                                     \
	JARR_MACRO_END

/* } */

#define jarr_append(tmp_jarray, jarr, src_arr, src_arr_size) private_jarr_append_typecheck(tmp_jarray, jarr, src_arr, src_arr_size, )

#define jarr_append_noalloc(jarr, src_arr, src_arr_size)                                                \
	JARR_MACRO_START                                                                                \
		memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)); \
		((jarr)->size) += src_arr_size;                                                         \
	JARR_MACRO_END

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t jarr, ...) { */

#define private_jarr_cat(jarr, size_, noalloc_, ...)                               \
	JARR_MACRO_START                                                           \
		const size_t new_size = ((jarr)->size) + (size_);                  \
noalloc_	if (new_size > ((jarr)->capacity)) {                               \
noalloc_		size_t tmp_cap = ((jarr)->capacity);                       \
			do {                                                       \
noalloc_			tmp_cap *= 2;                                      \
noalloc_		} while (new_size > tmp_cap);                              \
noalloc_		jarr_reserve_nocheck(jarr, tmp_cap);                       \
noalloc_	}                                                                  \
		if (PP_NARG(__VA_ARGS__) == 1) {                                   \
			((jarr)->data)[((jarr)->size)++] = __VA_ARGS__;            \
		} else {                                                           \
			typeof(*((jarr)->data)) tmp[] = { __VA_ARGS__ };           \
			memcpy(((jarr)->data) + ((jarr)->size), tmp, sizeof(tmp)); \
			((jarr)->size) = new_size;                                 \
		}                                                                  \
	JARR_MACRO_END

/* } */

#define jarr_cat(jarr, ...) private_jarr_cat(jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define jarr_cat_noalloc(jarr, ...) private_jarr_cat(jarr, PP_NARG(__VA_ARGS__), JARR_COMMENT, __VA_ARGS__)

#define jarr_pop_back(jarr) --((jarr)->size);

#define jarr_cmp(jarr_dest, jarr_src)                                                                                       \
	((((jarr_dest)->size) != ((jarr_src)->size)) ? 1 : memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp_nocheck(jarr_dest, jarr_src)                               \
	(memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))

#define jarr_foreach_index(elem, jarr)                                   \
	for (size_t elem = 0, size = ((jarr)->size); elem < size; ++elem)

#define jarr_foreach(elem, jarr)                                                                                              \
	for (typeof(*((jarr)->data)) *elem = ((jarr)->data), *RESTRICT end = ((jarr)->data) + ((jarr)->size); elem < end; ++elem)

#define jarr_end(jarr) (*(((jarr)->data) + ((jarr)->size) - 1))

#define jarr_auto_elem(jarr) typeof(*((jarr)->data))

#define jarr_auto(jarr) typeof((*(jarr)))

#define JARR_SAME_TYPE(x, y) _Generic((x), \
	typeof(y): 1,                       \
	default: 0)

#define JARR_TYPE_CHECK(src_arr) _Generic((src_arr), \
	jarray_int_t*: JARR_IS_JARRAY_PTR,           \
	jarray_uint_t*: JARR_IS_JARRAY_PTR,          \
	jarray_long_t*: JARR_IS_JARRAY_PTR,          \
	jarray_long_long_t*: JARR_IS_JARRAY_PTR,     \
	jarray_ulong_t*: JARR_IS_JARRAY_PTR,         \
	jarray_ulong_long_t*: JARR_IS_JARRAY_PTR,    \
	jarray_size_t_t*: JARR_IS_JARRAY_PTR,        \
	jarray_double_t*: JARR_IS_JARRAY_PTR,        \
	jarray_long_double_t*: JARR_IS_JARRAY_PTR,   \
	jarray_float_t*: JARR_IS_JARRAY_PTR,         \
	jarray_short_t*: JARR_IS_JARRAY_PTR,         \
	jarray_ushort_t*: JARR_IS_JARRAY_PTR,        \
	jarray_int_t: JARR_IS_JARRAY,                \
	jarray_uint_t: JARR_IS_JARRAY,               \
	jarray_long_t: JARR_IS_JARRAY,               \
	jarray_long_long_t: JARR_IS_JARRAY,          \
	jarray_ulong_t: JARR_IS_JARRAY,              \
	jarray_ulong_long_t: JARR_IS_JARRAY,         \
	jarray_size_t_t: JARR_IS_JARRAY,             \
	jarray_double_t: JARR_IS_JARRAY,             \
	jarray_long_double_t: JARR_IS_JARRAY,        \
	jarray_float_t: JARR_IS_JARRAY,              \
	jarray_short_t: JARR_IS_JARRAY,              \
	jarray_ushort_t: JARR_IS_JARRAY,             \
	int*: JARR_IS_ARRAY,                         \
	unsigned int*: JARR_IS_ARRAY,                \
	long*: JARR_IS_ARRAY,                        \
	long long*: JARR_IS_ARRAY,                   \
	unsigned long*: JARR_IS_ARRAY,               \
	unsigned long long*: JARR_IS_ARRAY,          \
	double*: JARR_IS_ARRAY,                      \
	long double*: JARR_IS_ARRAY,                 \
	float*: JARR_IS_ARRAY,                       \
	short*: JARR_IS_ARRAY,                       \
	)

	/* unsigned short*: JARR_IS_ARRAY,              \ */
	/* int: JARR_IS_ARRAY,                          \ */
	/* unsigned int: JARR_IS_ARRAY,                 \ */
	/* long: JARR_IS_ARRAY,                         \ */
	/* long long: JARR_IS_ARRAY,                    \ */
	/* unsigned long: JARR_IS_ARRAY,                \ */
	/* unsigned long long: JARR_IS_ARRAY,           \ */
	/* double: JARR_IS_ARRAY,                       \ */
	/* long double: JARR_IS_ARRAY,                  \ */
	/* float: JARR_IS_ARRAY,                        \ */
	/* short: JARR_IS_ARRAY,                        \ */
	/* unsigned short: JARR_IS_ARRAY                \ */

#endif
