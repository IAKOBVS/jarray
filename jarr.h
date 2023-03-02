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
#endif

#define JARR_IGNORE_IF ,1

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
	jarray_char_t*: JARR_IS_JARRAY,              \
	jarray_uchar_t*: JARR_IS_JARRAY,             \
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
	jarray_char_t: JARR_IS_JARRAY,               \
	jarray_uchar_t: JARR_IS_JARRAY,              \
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
	unsigned short*: JARR_IS_ARRAY,              \
	int: JARR_IS_ARRAY,                          \
	unsigned int: JARR_IS_ARRAY,                 \
	long: JARR_IS_ARRAY,                         \
	long long: JARR_IS_ARRAY,                    \
	unsigned long: JARR_IS_ARRAY,                \
	unsigned long long: JARR_IS_ARRAY,           \
	double: JARR_IS_ARRAY,                       \
	long double: JARR_IS_ARRAY,                  \
	float: JARR_IS_ARRAY,                        \
	short: JARR_IS_ARRAY,                        \
	unsigned short: JARR_IS_ARRAY,               \
	unsigned char: JARR_IS_ARRAY                 \
	char: JARR_IS_ARRAY                          \
	)

#define JARR_JARRAY_INT_T 1
#define JARR_JARRAY_UINT_T 2
#define JARR_JARRAY_LONG_T 3
#define JARR_JARRAY_LONG_LONG_T 4
#define JARR_JARRAY_ULONG_T 5
#define JARR_JARRAY_ULONG_LONG_T 6
#define JARR_JARRAY_SIZE_T_T 7
#define JARR_JARRAY_DOUBLE_T 8
#define JARR_JARRAY_LONG_DOUBLE_T 9
#define JARR_JARRAY_FLOAT_T 10
#define JARR_JARRAY_SHORT_T 11
#define JARR_JARRAY_USHORT_T 12
#define JARR_INT_PTR 13
#define JARR_UNSIGNED_INT_PTR 14
#define JARR_LONG_PTR 15
#define JARR_LONG_LONG_PTR 16
#define JARR_UNSIGNED_LONG_PTR 17
#define JARR_UNSIGNED_LONG_LONG_PTR 18
#define JARR_DOUBLE_PTR 19
#define JARR_LONG_DOUBLE_PTR 20
#define JARR_FLOAT_PTR 21
#define JARR_SHORT_PTR 22
#define JARR_UNSIGNED_SHORT_PTR 23
#define JARR_SIZE_T_PTR 24
#define JARR_INT 25
#define JARR_UNSIGNED_INT 26
#define JARR_LONG 27
#define JARR_LONG_LONG 28
#define JARR_UNSIGNED_LONG 29
#define JARR_UNSIGNED_LONG_LONG 30
#define JARR_DOUBLE 31
#define JARR_LONG_DOUBLE 32
#define JARR_FLOAT 33
#define JARR_SHORT 34
#define JARR_UNSIGNED_SHORT 35
#define JARR_SIZE_T 36

#define JARR_GET_T(var) _Generic(((var)),                     \
	jarray_int_t*: JARR_JARRAY_INT_T_PTR,                 \
	jarray_uint_t*: JARR_JARRAY_UINT_T_PTR,               \
	jarray_long_t*: JARR_JARRAY_LONG_T_PTR,               \
	jarray_long_long_t*: JARR_JARRAY_LONG_LONG_T_PTR,     \
	jarray_ulong_t*: JARR_JARRAY_ULONG_T_PTR,             \
	jarray_ulong_long_t*: JARR_JARRAY_ULONG_LONG_T_PTR,   \
	jarray_size_t_t*: JARR_JARRAY_SIZE_T_T_PTR,           \
	jarray_double_t*: JARR_JARRAY_DOUBLE_T_PTR,           \
	jarray_long_double_t*: JARR_JARRAY_LONG_DOUBLE_T_PTR, \
	jarray_float_t*: JARR_JARRAY_FLOAT_T_PTR,             \
	jarray_short_t*: JARR_JARRAY_SHORT_T_PTR,             \
	jarray_ushort_t*: JARR_JARRAY_USHORT_T_PTR,           \
	jarray_int_t: JARR_JARRAY_INT_T,                      \
	jarray_uint_t: JARR_JARRAY_UINT_T,                    \
	jarray_long_t: JARR_JARRAY_LONG_T,                    \
	jarray_long_long_t: JARR_JARRAY_LONG_LONG_T,          \
	jarray_ulong_t: JARR_JARRAY_ULONG_T,                  \
	jarray_ulong_long_t: JARR_JARRAY_ULONG_LONG_T,        \
	jarray_size_t_t: JARR_JARRAY_SIZE_T_T,                \
	jarray_double_t: JARR_JARRAY_DOUBLE_T,                \
	jarray_long_double_t: JARR_JARRAY_LONG_DOUBLE_T,      \
	jarray_float_t: JARR_JARRAY_FLOAT_T,                  \
	jarray_short_t: JARR_JARRAY_SHORT_T,                  \
	jarray_ushort_t: JARR_JARRAY_USHORT_T,                \
	int*: JARR_INT_PTR,                                   \
	unsigned int*: JARR_UNSIGNED INT_PTR,                 \
	long*: JARR_LONG_PTR,                                 \
	long long*: JARR_LONG LONG_PTR,                       \
	unsigned long*: JARR_UNSIGNED LONG_PTR,               \
	unsigned long long*: JARR_UNSIGNED LONG LONG_PTR,     \
	double*: JARR_DOUBLE_PTR,                             \
	long double*: JARR_LONG DOUBLE_PTR,                   \
	float*: JARR_FLOAT_PTR,                               \
	short*: JARR_SHORT_PTR,                               \
	unsigned short*: JARR_UNSIGNED SHORT_PTR,             \
	size_t*: JARR_SIZE_T_PTR,                             \
	int: JARR_INT,                                        \
	unsigned int: JARR_UNSIGNED INT,                      \
	long: JARR_LONG,                                      \
	long long: JARR_LONG LONG,                            \
	unsigned long: JARR_UNSIGNED LONG,                    \
	unsigned long long: JARR_UNSIGNED LONG LONG,          \
	double: JARR_DOUBLE,                                  \
	long double: JARR_LONG DOUBLE,                        \
	float: JARR_FLOAT,                                    \
	short: JARR_SHORT,                                    \
	unsigned short: JARR_UNSIGNED SHORT,                  \
	size_t: JARR_SIZE_T                                   \
	)

#define JARR_CAST_TO(var) _Generic(((var)),                \
	jarray_int_t*: (jarray_int_t*)var,                 \
	jarray_uint_t*: (jarray_uint_t*)var,               \
	jarray_long_t*: (jarray_long_t*)var,               \
	jarray_long_long_t*: (jarray_long_long_t*)var,     \
	jarray_ulong_t*: (jarray_ulong_t*)var,             \
	jarray_ulong_long_t*: (jarray_ulong_long_t*)var,   \
	jarray_size_t_t*: (jarray_size_t_t*)var,           \
	jarray_double_t*: (jarray_double_t*)var,           \
	jarray_long_double_t*: (jarray_long_double_t*)var, \
	jarray_float_t*: (jarray_float_t*)var,             \
	jarray_short_t*: (jarray_short_t*)var,             \
	jarray_ushort_t*: (jarray_ushort_t*)var,           \
	jarray_int_t: (jarray_int_t)var,                   \
	jarray_uint_t: (jarray_uint_t)var,                 \
	jarray_long_t: (jarray_long_t)var,                 \
	jarray_long_long_t: (jarray_long_long_t)var,       \
	jarray_ulong_t: (jarray_ulong_t)var,               \
	jarray_ulong_long_t: (jarray_ulong_long_t)var,     \
	jarray_size_t_t: (jarray_size_t_t)var,             \
	jarray_double_t: (jarray_double_t)var,             \
	jarray_long_double_t: (jarray_long_double_t)var,   \
	jarray_float_t: (jarray_float_t)var,               \
	jarray_short_t: (jarray_short_t)var,               \
	jarray_ushort_t: (jarray_ushort_t)var,             \
	jarray_char_t: (jarray_char_t)var,                 \
	jarray_uchar_t: (jarray_uchar_t)var,               \
	int*: (int*)var,                                   \
	unsigned int*: (unsigned int*)var,                 \
	long*: (long*)var,                                 \
	long long*: (long long*)var,                       \
	unsigned long*: (unsigned long*)var,               \
	unsigned long long*: (unsigned long long*)var,     \
	double*: (double*)var,                             \
	long double*: (long double*)var,                   \
	float*: (float*)var,                               \
	short*: (short*)var,                               \
	unsigned short*: (unsigned short*)var,             \
	size_t*: (size_t*)var,                             \
	int: (int)var,                                     \
	unsigned int: (unsigned int)var,                   \
	long: (long)var,                                   \
	long long: (long long)var,                         \
	unsigned long: (unsigned long)var,                 \
	unsigned long long: (unsigned long long)var,       \
	double: (double)var,                               \
	long double: (long double)var,                     \
	float: (float)var,                                 \
	short: (short)var,                                 \
	unsigned short: (unsigned short)var,               \
	size_t: (size_t)var,                               \
	)

#define JARR_VA_ARG_T(ap) _Generic(((var)),                       \
	jarray_int_t*: va_arg(ap, jarray_int_t*),                 \
	jarray_uint_t*: va_arg(ap, jarray_uint_t*),               \
	jarray_long_t*: va_arg(ap, jarray_long_t*),               \
	jarray_long_long_t*: va_arg(ap, jarray_long_long_t*),     \
	jarray_ulong_t*: va_arg(ap, jarray_ulong_t*),             \
	jarray_ulong_long_t*: va_arg(ap, jarray_ulong_long_t*),   \
	jarray_size_t_t*: va_arg(ap, jarray_size_t_t*),           \
	jarray_double_t*: va_arg(ap, jarray_double_t*),           \
	jarray_long_double_t*: va_arg(ap, jarray_long_double_t*), \
	jarray_float_t*: va_arg(ap, jarray_float_t*),             \
	jarray_short_t*: va_arg(ap, jarray_short_t*),             \
	jarray_ushort_t*: va_arg(ap, jarray_ushort_t*),           \
	jarray_int_t: va_arg(ap, jarray_int_t),                   \
	jarray_uint_t: va_arg(ap, jarray_uint_t),                 \
	jarray_long_t: va_arg(ap, jarray_long_t),                 \
	jarray_long_long_t: va_arg(ap, jarray_long_long_t),       \
	jarray_ulong_t: va_arg(ap, jarray_ulong_t),               \
	jarray_ulong_long_t: va_arg(ap, jarray_ulong_long_t),     \
	jarray_size_t_t: va_arg(ap, jarray_size_t_t),             \
	jarray_double_t: va_arg(ap, jarray_double_t),             \
	jarray_long_double_t: va_arg(ap, jarray_long_double_t),   \
	jarray_float_t: va_arg(ap, jarray_float_t),               \
	jarray_short_t: va_arg(ap, jarray_short_t),               \
	jarray_ushort_t: va_arg(ap, jarray_ushort_t),             \
	jarray_char_t: va_arg(ap, jarray_char_t),                 \
	jarray_uchar_t: va_arg(ap, jarray_uchar_t),               \
	int*: va_arg(ap, int*),                                   \
	unsigned int*: va_arg(ap, unsigned int*),                 \
	long*: va_arg(ap, long*),                                 \
	long long*: va_arg(ap, long long*),                       \
	unsigned long long*: va_arg(ap, unsigned long long*),     \
	double*: va_arg(ap, double*),                             \
	long double*: va_arg(ap, long double*),                   \
	float*: va_arg(ap, float*),                               \
	short*: va_arg(ap, short*),                               \
	unsigned short*: va_arg(ap, unsigned short*),             \
	size_t*: va_arg(ap, size_t*),                             \
	int: va_arg(ap, int),                                     \
	unsigned int: va_arg(ap, unsigned int),                   \
	long: va_arg(ap, long),                                   \
	long long: va_arg(ap, long long),                         \
	unsigned long long: va_arg(ap, unsigned long long),       \
	double: va_arg(ap, double),                               \
	long double: va_arg(ap, long double),                     \
	float: va_arg(ap, double),                                \
	short: va_arg(ap, int),                                   \
	unsigned short: va_arg(ap, int),                          \
	size_t: va_arg(ap, size_t)                                \


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
JARR_STRUCT(jarray_char_t, char);
JARR_STRUCT(jarray_uchar_t, unsigned char);

#define jarr_init(jarr)                 \
		((jarr)->capacity) = 0, \
		((jarr)->size) = 0,     \
		((jarr)->data) = (void *)0;

#define JARR_NOCHECK ,1
#define JARR_NOCHECK_OFF

#define JARR_POW2 1
#define JARR_POW2_OFF 0

/*
   _nocheck macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc;

   _noalloc macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.
*/

#define private_jarr_delete(jarr, nocheck_)                                   \
(                                                                             \
	(((jarr)->data) nocheck_) && (free((jarr)->data), jarr_init(jarr), 0) \
)

#define jarr_delete(jarr) private_jarr_delete(jarr, JARR_NOCHECK_OFF)
#define jarr_delete_nocheck(jarr) private_jarr_delete(jarr, JARR_NOCHECK)

#ifdef JARR_DEBUG
static ALWAYS_INLINE void debug_jarr_new_alloc(jarray_int_t *jarr, size_t cap)
{
#endif

#define jarr_new_alloc(jarr, cap)                                                      \
(                                                                                      \
	((((jarr)->capacity) = MAX(((cap)), JARR_MIN_CAP)),                            \
	((likely((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr))))))) \
	|| (((jarr)->capacity) = 0, 0)                                                 \
)

#ifdef JARR_DEBUG
;}
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_new_alloc(jarray_int_t jarr)
{
	return jarr_new_alloc(&jarr, 0);
}
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE void debug_jarr_reserve(jarray_tmp_t tmp_jarray, jarray_int_t *jarr, size_t cap)
{
#define private_jarr_reserve(tmp_jarray, jarr, cap, pow2_, nocheck_)                                                     \
JARR_TERNARY_START                                                                                                       \
	JARR_TMP_DECLARE(tmp_jarray)                                                                                     \
	((((cap) > ((jarr)->capacity)) nocheck_)                                                                         \
	&& (likely((tmp_jarray = realloc(((jarr)->data), JARR_T_SIZE(jarr) * ((pow2_) ? JARR_NEAR_POW2(cap) : (cap)))))) \
	&& (((jarr)->data) = tmp_jarray, ((jarr)->capacity) = (cap), 1))                                                 \
JARR_TERNARY_END
;}
#endif

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_reserve(jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2_OFF, JARR_NOCHECK_OFF)
	#define jarr_reserve_align(jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2, JARR_NOCHECK_OFF)

	#define jarr_reserve_nocheck(jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2_OFF, JARR_NOCHECK)
	#define jarr_reserve_nocheck_align(jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2, JARR_NOCHECK)

	#define private_jarr_reserve_x(jarr, multiplier) private_jarr_reserve(tmp_jarray, jarr, (tmp_jarray, (tmp_jarray, (tmp_jarray, jarr)->capacity) * multiplier), 0, JARR_COMMENT)
	#define jarr_reserve_2x(jarr) private_jarr_reserve_x(tmp_jarray, jarr, 2)
	#define jarr_reserve_4x(jarr) private_jarr_reserve_x(tmp_jarray, jarr, 4)
	#define jarr_reserve_8x(jarr) private_jarr_reserve_x(tmp_jarray, jarr, 8)
	#define jarr_reserve_16x(jarr) private_jarr_reserve_x(tmp_jarray, jarr, 16)
	#define jarr_reserve_32x(jarr) private_jarr_reserve_x(tmp_jarray, jarr, 32)
	#define jarr_reserve_64x(jarr) private_jarr_reserve_x(tmp_jarray, jarr, 64)
#else
	#define jarr_reserve(tmp_jarray, jarr, cap) private_jarr_reserve(tmp_jarray, jarr, cap, JARR_POW2_OFF, JARR_NOCHECK_OFF)
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
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_reserve(jarray_int_t jarr)
{
	return jarr_reserve(&jarr, 0);
}
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE void debug_jarr_push_back(jarray_int_t *jarr, int src)
{
#endif

#define private_jarr_push_back(tmp_jarray, jarr, src)                                                                      \
JARR_TERNARY_START                                                                                                         \
	JARR_RET_DECLARE(jarray_ret)                                                                                       \
	JARR_TMP_DECLARE(tmp_jarray)                                                                                       \
	(unlikely(((jarr)->capacity) == ((jarr)->size)))                                                                   \
		?                                                                                                          \
			((private_jarr_reserve(tmp_jarray, jarr, ((jarr)->capacity) * 2, JARR_POW2_OFF, JARR_NOCHECK_OFF)) \
			&& ((((jarr)->data)[((jarr)->size)++] = src), 1))                                                  \
		:                                                                                                          \
			(((jarr)->data)[((jarr)->size)++] = src, 1)                                                        \
JARR_TERNARY_END

#ifdef JARR_DEBUG
;}
#endif

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_push_back(jarr, src) private_jarr_push_back(tmp_jarray, jarr, src)
	#define jarr_push_back_noalloc(jarr, src) \
		((jarr)->data)[((jarr)->size)++] = src
#else
	#define jarr_push_back(jarr, src) private_jarr_push_back(tmp_jarray, jarr, src)
	#define jarr_push_back_noalloc(jarr, src) \
		((jarr)->data)[((jarr)->size)++] = src
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_push_back(jarray_int_t jarr, int src)
{
	return jarr_push_back(&jarr, src);
}
#endif

#ifdef JARR_DEBUG
/* static ALWAYS_INLINE void dummy_arr_new(jarray_return_t jarray_ret, jarray_int_t *jarr, size_t size_) */
/* { */
#define private_jarr_new(jarray_ret, jarr, size_, ...)                                             \
JARR_MACRO_START                                                                                           \
	JARR_RET_DECLARE(jarray_ret)                                                                       \
	((jarr)->capacity) = MAX(2 * JARR_NEAR_POW2((size_)), JARR_MIN_CAP);                               \
	((likely((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr))))))                      \
		?                                                                                          \
			(PP_NARG(__VA_ARGS__) > 1)                                                         \
				?                                                                          \
					typeof(*((jarr)->data)) tmp[] = { PP_OTHER_ARGS(__VA_ARGS__) };    \
					memcpy(((jarr)->data) + ((jarr)->size), tmp, sizeof(tmp)),         \
					((jarr)->size) = JARR_ARR_SIZE(tmp),                               \
				:                                                                          \
			(PP_NARG(__VA_ARGS__) == 1)                                                        \
				jarr_push_back_noalloc(jarr, PP_GET_FIRST_ARG(__VA_ARGS__));               \
		:                                                                                          \
			JARR_RET_SUCCESS(jarray_ret)                                                       \
			((jarr)->capacity) = 0;                                                            \
			perror("jarr_new malloc failed");                                                  \
			JARR_RET_FAIL(jarray_ret)                                                          \
		JARR_RET_END(jarray_ret)                                                                   \
JARR_MACRO_END
/* ;} */
#endif


#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_new(jarr, ...) private_jarr_new(jarray_ret, jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
	#define jarr_new_auto(jarr, ...) private_jarr_new(jarray_ret, jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#else
	#define jarr_new(jarray_ret, jarr, ...) private_jarr_new(jarray_ret, jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
	#define jarr_new_auto(jarray_ret, jarr, ...) private_jarr_new(jarray_ret, jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#endif

#ifdef JARR_DEBUG
/* static ALWAYS_INLINE int dummy_arr_new(jarray_return_t jarray_ret, jarray_int_t *jarr, size_t _size) */
/* { */
/* 	return jarr_new(jarr, 1, 3); */
/* } */
#endif

#ifdef JARR_DEBUG
static ALWAYS_INLINE void debug_jarr_shrink(jarray_tmp_t tmp_jarray, jarray_int_t *jarr)
{
#define private_jarr_shrink(jarr, tmp_jarray, nocheck_)                                            \
JARR_TERNARY_START                                                                                 \
	JARR_TMP_DECLARE(tmp_jarray)                                                               \
	((((jarr)->capacity) != ((jarr)->size)) nocheck_)                                          \
	&& ((likely(((tmp_jarray) = realloc(((jarr)->data), ((jarr)->size) * JARR_T_SIZE(jarr))))) \
	&& (((jarr)->data) = (tmp_jarray)), (((jarr)->capacity) = ((jarr)->size)), 1)              \
JARR_TERNARY_END
;}
#endif

#ifdef JARR_USING_STATEMENT_EXPRESSIONS
	#define jarr_shrink(jarr) private_jarr_shrink(jarr, tmp_jarray, )
	#define jarr_shrink_nocheck(jarr) private_jarr_shrink(jarr, tmp_jarray, JARR_IGNORE_IF)
#else
	#define jarr_shrink(tmp_jarray, jarr) private_jarr_shrink(jarr, tmp_jarray, )
	#define jarr_shrink_nocheck(tmp_jarray, jarr) private_jarr_shrink(jarr, tmp_jarray, JARR_IGNORE_IF)
#endif

static ALWAYS_INLINE void private_jarr_grow_while_size_gt_cap(size_t size, size_t *cap)
{
	do { (*cap) *= 2; } while (size > *cap);
}

#ifdef JARR_DEBUG
static ALWAYS_INLINE int dummy_jarr_shrink(jarray_tmp_t tmp_jarray, jarray_int_t jarr)
{
	return jarr_shrink(&jarr);
}
#endif

/* #define private_jarr_append(tmp_jarray, jarr, src_arr, src_arr_size)                                                 \ */
/* 	JARR_MACRO_START                                                                                             \ */
/* 		JARR_TMP_DECLARE(tmp_jarray)                                                                         \ */
/* 		if ((((jarr)->size) + (src_arr_size)) > ((jarr)->capacity)) {                                        \ */
/* 			private_jarr_grow_while_size_gt_cap((((jarr)->size) + (src_arr_size)), &((jarr)->capacity)); \ */
/* 			if (unlikely(!jarr_reserve_nocheck(tmp_jarray, jarr, (((jarr)->size) + (src_arr_size)))))    \ */
/* 				return 0;                                                                            \ */
/* 		}                                                                                                    \ */
/* 		memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr));              \ */
/* 		((jarr)->size) += (src_arr_size);                                                                    \ */
/* 	JARR_MACRO_END */

#define private_jarr_append(tmp_jarray, jarr, src_arr, src_arr_size)                                                                    \
	JARR_MACRO_START                                                                                                                \
		JARR_TMP_DECLARE(tmp_jarray)                                                                                            \
		((((jarr)->size) + (src_arr_size)) > ((jarr)->capacity))                                                                \
			?                                                                                                               \
				((private_jarr_grow_while_size_gt_cap((((jarr)->size) + (src_arr_size)), &((jarr)->capacity))),         \
				(likely(jarr_reserve_nocheck(tmp_jarray, jarr, (((jarr)->size) + (src_arr_size)))))                     \
					?                                                                                               \
						memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)), \
						((jarr)->size) += (src_arr_size)                                                        \
					:                                                                                               \
						0)                                                                                      \
			:                                                                                                               \
		memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr));                                 \
		((jarr)->size) += (src_arr_size);                                                                                       \
	JARR_MACRO_END

#define private_jarr_append_typecheck(tmp_jarray, jarr, src_arr, src_arr_size, noalloc_)                    \
	JARR_MACRO_START                                                                                    \
		switch (JARR_TYPE_CHECK(src_arr)) {                                                         \
		case JARR_IS_ARRAY:                                                                         \
			(src_arr_size)                                                                      \
				? private_jarr_append(tmp_jarray, jarr, (src_arr), src_arr_size)            \
				: private_jarr_append(tmp_jarray, jarr, (src_arr), JARR_ARR_SIZE(src_arr)), \
			break;                                                                              \
		case JARR_IS_JARRAY:                                                                        \
			private_jarr_append(tmp_jarray, jarr, ((src_arr)->data), ((src_arr)->size));        \
			break;                                                                              \
		case JARR_IS_JARRAY_PTR:                                                                    \
			private_jarr_append(tmp_jarray, jarr, ((src_arr)->data), ((src_arr)->size));        \
		}                                                                                           \
	JARR_MACRO_END

/* } */

#define jarr_append(jarr, src_arr, src_arr_size) private_jarr_append_typecheck(tmp_jarray, jarr, src_arr, src_arr_size, )

#define jarr_append_noalloc(jarr, src_arr, src_arr_size)                                                \
	JARR_MACRO_START                                                                                \
		memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)); \
		((jarr)->size) += src_arr_size;                                                         \
	JARR_MACRO_END

#ifdef JARR_DEBUG
/* static int dummy_arr_append(jarray_int_t jarr, jarray_int_t src_arr) */
/* { */
/* 	return jarr_append(&jarr, src_arr, 0); */
/* } */
#endif

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
#endif
