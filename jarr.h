#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stddef.h>

#include "/home/james/c/vargc.h"
#include "macros.h"

#define JARR_INCLUDE
#define JARR_ALIGN_POWER_OF_TWO

#ifdef JARR_INCLUDE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#ifdef JARR_ALIGN_POWER_OF_TWO
#define JARR_NEAR_POWER_OF_TWO(x) \
    ({ \
        size_t p = 1; \
        while (p < (size_t)(x)) p <<= 1; \
        p; \
    })
#else
#define JARR_NEAR_POWER_OF_TWO(x) (x)
#endif

#define JARR_MIN_CAP (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_T_SIZE(var) (sizeof(*((var).data)))
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

#define JARR_COMMENT //

/*
   _Generic will determine whether a jarray is passed.

   If NULL is passed as array size (src_arr_size),
   it will expect a jarray or stack array.
   You need to pass the size if it's a heap array.
*/

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t size;     \
	} NAME

#define static_jarray_init(T, name, capacity)             \
	struct {                                          \
		T data[JARR_NEAR_POWER_OF_TWO(capacity)]; \
		size_t size;                              \
	}

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

#define jarr_init(jarr)                \
	do {                           \
		((jarr).capacity) = 0; \
		((jarr).size) = 0;     \
		((jarr).data) = NULL;  \
	} while (0)

/*
   _nocheck macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc;

   _noalloc macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.
*/

#define private_jarr_delete(jarr, nocheck_)                                                        \
	do {                                                                                       \
		JARR_ASSERT(!((jarr).data), "jarr_delete is trying to delete a NULL ptr."); \
/* nocheck_	if (((jarr).data) {         \ */                                                   \
			free((jarr).data);                                                         \
			jarr_init(jarr);                                                           \
/* nocheck_	}                           \ */                                                   \
	} while (0)

#define jarr_delete(jarr) private_jarr_delete(jarr, )
#define jarr_delete_nocheck(jarr) private_jarr_delete(jarr, )

/* static ALWAYS_INLINE int dummy_arr_new(jarray_int_t jarr, size_t size) { */

#define jarr_new(jarr, ...)                                                                                                                      \
	do {                                                                                                                                     \
		JARR_ASSERT(!((jarr).capacity) || !((jarr).size) || !((jarr).data), "jarr_new is trying to malloc an already allocated ptr.\n"); \
		if (PP_NARG(__VA_ARGS__) == 1 && PP_ISDIGIT(__VA_ARGS__))                                                                        \
			((jarr).capacity) = MAX(JARR_NEAR_POWER_OF_TWO(2 * PP_NARG(__VA_ARGS__)), JARR_MIN_CAP);                                 \
		else                                                                                                                             \
			((jarr).capacity) = MAX(JARR_NEAR_POWER_OF_TWO(2 * PP_NARG(__VA_ARGS__)), JARR_MIN_CAP);                                 \
		if ((unlikely(!(((jarr).data) = malloc(((jarr).capacity) * JARR_T_SIZE(jarr)))))) {                                              \
			((jarr).capacity) = 0;                                                                                                   \
			perror("jarr_new malloc failed");                                                                                        \
			return -1;                                                                                                               \
		}                                                                                                                                \
		if (PP_NARG(__VA_ARGS__) == 1 && !PP_ISDIGIT(__VA_ARGS__)) {                                                                     \
			typeof(*((jarr).data)) tmp[] = { __VA_ARGS__ };                                                                          \
			memcpy(((jarr).data) + ((jarr).size), tmp, sizeof(tmp));                                                                 \
			((jarr).size) = PP_NARG(__VA_ARGS__);                                                                                    \
		}                                                                                                                                \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_jarr_shrink(jarray_int_t jarr) { */

#define private_jarr_shrink(jarr, nocheck_)                                                                                                      \
	do {                                                                                                                                     \
		JARR_ASSERT(((jarr).capacity) || ((jarr).size) || ((jarr).ptr), "jarr_shrink is trying to shrink a freed or unallocated ptr.\n"); \
		JARR_ASSERT(((jarr).capacity) != ((jarr).size), "jarray can not be further shrunk.\n");                                           \
/* nocheck_	if (((jarr).capacity) != ((jarr).size)) {                                                                       \ */             \
			typeof(((jarr).data)) tmp;                                                                                               \
			if (likely((tmp = realloc(((jarr).data), ((jarr).size) * JARR_T_SIZE(jarr))))) {                                         \
				((jarr).data) = tmp;                                                                                             \
				((jarr).capacity) = ((jarr).size);                                                                               \
			} else {                                                                                                                 \
				perror("jarr_shrink realloc failed");                                                                            \
				return -1;                                                                                                       \
			}                                                                                                                        \
/* nocheck_	}                                                                                                               \ */             \
	} while (0)

/* } */

#define jarr_shrink(jarr) private_jarr_shrink(jarr, )
#define jarr_shrink_nocheck(jarr) private_jarr_shrink(jarr, )

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append(jarr, src_arr, src_arr_size, noalloc_)                                    \
	do {                                                                                          \
		const size_t new_size = ((jarr).size) + (src_arr_size);                               \
noalloc_	if (new_size > ((jarr).capacity)) {                                                   \
noalloc_		size_t tmp_cap = ((jarr).capacity);                                           \
noalloc_		do {                                                                          \
noalloc_			tmp_cap *= 2;                                                         \
noalloc_		} while (new_size > tmp_cap);                                                 \
noalloc_		jarr_reserve_nocheck(jarr, tmp_cap);                                          \
noalloc_	}                                                                                     \
		memcpy(((jarr).data) + ((jarr).size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)); \
		((jarr).size) = new_size;                                                             \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append_typecheck(jarr, src_arr, src_arr_size, noalloc_)                                                       \
	do {                                                                                                                       \
		switch (JARR_TYPE_CHECK(src_arr)) {                                                                                \
		case JARR_IS_ARRAY:                                                                                                \
			(#src_arr_size[0] == 'N' && #src_arr_size[1] == 'U' && #src_arr_size[2] == 'L' && #src_arr_size[3] == 'L') \
				? private_jarr_append(jarr, (src_arr), JARR_ARR_SIZE(src_arr), noalloc_)                           \
				: private_jarr_append(jarr, (src_arr), src_arr_size, noalloc_);                                    \
		case JARR_IS_JARRAY:                                                                                               \
			private_jarr_append(jarr, ((src_arr).data), ((src_arr).size), noalloc_);                                   \
		case JARR_IS_JARRAY_PTR:                                                                                           \
			private_jarr_append(jarr, ((src_arr).data), ((src_arr).size), noalloc_);                                   \
		}                                                                                                                  \
	} while (0)

/* } */

#define jarr_append(jarr, src_arr, src_arr_size) private_jarr_append_typecheck(jarr, src_arr, src_arr_size, )
#define jarr_noalloc(jarr, src_arr, src_arr_size) private_jarr_append_typecheck(jarr, src_arr, src_arr_size, JARR_COMMENT)

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t jarr, ...) { */

#define private_jarr_cat(jarr, noalloc_, ...)                              \
	do {                                                               \
		const int new_size = ((jarr).size) + PP_NARG(__VA_ARGS__); \
noalloc_	if (new_size > ((jarr).capacity)) {                        \
noalloc_		size_t tmp_cap = ((jarr).capacity);                \
noalloc_		do {                                               \
noalloc_			tmp_cap *= 2;                              \
noalloc_		} while (new_size > tmp_cap);                      \
noalloc_		jarr_reserve_nocheck(jarr, tmp_cap);               \
noalloc_	}                                                          \
		typeof(*((jarr).data)) tmp[] = { __VA_ARGS__ };            \
		memcpy(((jarr).data) + ((jarr).size), tmp, sizeof(tmp));   \
		((jarr).size) = new_size;                                  \
	} while (0)

/* } */

#define jarr_cat(jarr, ...) private_jarr_cat(jarr, , __VA_ARGS__)
#define jarr_cat_noalloc(jarr, ...) private_jarr_cat(jarr, JARR_COMMENT, __VA_ARGS__)

/* static ALWAYS_INLINE int dummy_jarr_push_back(jarray_int_t jarr, int src) { */

#define private_jarr_push_back(jarr, src, nocheck_)                          \
	do {                                                                 \
nocheck_	if (unlikely(((jarr).capacity) == ((jarr).size)));           \
nocheck_		jarr_reserve_nocheck(jarr, (((jarr).capacity) * 2)); \
		((jarr).data)[((jarr).size)++] = src;                        \
	} while (0)

#define jarr_push_back(jarr, src) private_jarr_push_back(jarr, src, )
#define jarr_push_back_noalloc(jarr, src) private_jarr_push_back(jarr, src, JARR_COMMENT)

/* } */

#define jarr_pop_back(jarr) --((jarr).size);

#define private_jarr_reserve(jarr, cap, nocheck_)                                                                                \
	do {                                                                                                                     \
		/* if ((cap) > (jarr.capacity)) {                                                                           \ */ \
			JARR_ASSERT((cap) > ((jarr).capacity), "jarr_reserve: illegal cap.\n");                                   \
			typeof(((jarr).data)) tmp;                                                                               \
			if (likely((tmp = realloc(((jarr).data), JARR_T_SIZE(jarr) * (JARR_NEAR_POWER_OF_TWO(cap)))))) {         \
				((jarr).data) = tmp;                                                                             \
				((jarr).capacity) = (JARR_NEAR_POWER_OF_TWO(cap));                                               \
			} else {                                                                                                 \
				perror("jarr_reserve realloc failed");                                                           \
				return -1;                                                                                       \
			}                                                                                                        \
		/* }                                                                                                        \ */ \
	} while (0)

#define jarr_reserve(jarr, cap) private_jarr_reserve(jarr, cap, )
#define jarr_reserve_nocheck(jarr, cap) private_jarr_reserve(jarr, cap, )

#define jarr_cmp(jarr_dest, jarr_src)                                                                                       \
	((((jarr_dest).size) != ((jarr_src).size)) ? 1 : memcmp(((jarr_dest).data), ((jarr_src).data), ((jarr_dest).size)))
#define jarr_cmp_nocheck(jarr_dest, jarr_src)                               \
	(memcmp(((jarr_dest).data), ((jarr_src).data), ((jarr_dest).size)))

#define jarr_foreach_index(elem, jarr)                                   \
	for (size_t elem = 0, size = ((jarr).size); elem < size; ++elem)

#define jarr_foreach(elem, jarr)                                                                                              \
	for (typeof(*((jarr).data)) *elem = ((jarr).data), *RESTRICT end = ((jarr).data) + ((jarr).size); elem < end; ++elem)

#define jarr_foreach(elem, jarr)                                                                                              \
	for (typeof(*((jarr).data)) *elem = ((jarr).data), *RESTRICT end = ((jarr).data) + ((jarr).size); elem < end; ++elem)

#define jarr_end(jarr) (*(((jarr).data) + ((jarr).size) - 1))

#define jarr_auto_elem(jarr) typeof(*((jarr).data))

#define jarr_auto(jarr) typeof((*(jarr)))

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

int qsort_descend(const void *RESTRICT x, const void *RESTRICT y);
int qsort_ascend(const void *RESTRICT y, const void *RESTRICT x);
float qsort_descend_fl(const void *RESTRICT x, const void *RESTRICT y);
float qsort_ascend_fl(const void *RESTRICT y, const void *RESTRICT x);
double qsort_descend_db(const void *RESTRICT x, const void *RESTRICT y);
double qsort_ascend_db(const void *RESTRICT y, const void *RESTRICT x);

#endif
