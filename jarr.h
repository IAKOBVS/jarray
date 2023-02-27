#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stddef.h>

#include "/home/james/c/vargc.h"
#include "macros.h"

#define JARR_MIN_CAP (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_T_SIZE(var) (sizeof(*((var)->data)))
#define JARR_ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define jarr_sizeof_arr(arr) JARR_ARR_SIZE(arr)

#define JARR_IS_ARRAY 1
#define JARR_IS_ARRAY_PTR 2
#define JARR_IS_JARRAY 2
#define JARR_IS_JARRAY_PTR 3

#define JARR_CMT \\

/* Further typechecking can be done with if (#param[0] == '&') */

/*
   _Generic will determine whether a jarray is passed.
   If NULL is passed, it will expect a jarray or stack array.
   You need to pass the size if it's a heap array.
*/

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

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t capacity; \
		size_t size;     \
	} NAME

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
	do {                            \
		((jarr)->capacity) = 0; \
		((jarr)->size) = 0;     \
		((jarr)->data) = NULL;  \
	} while (0)

/*
   _fast macros will skip some error checking;
   e.g., if (ptr) before delete,
   if (reserve_capacity > capacity) before realloc,

   but it will still check if (!ptr) after malloc or realloc
   and other errors not caused by the user.
*/

#define private_jarr_delete(jarr, if_)     \
	do {                               \
if_		if (((jarr)->data) {       \
			free((jarr).data); \
			jarr_init(jarr);   \
if_		}                          \
	} while (0)

#define jarr_delete(jarr) private_jarr_delete(jarr, )
#define jarr_delete_fast(jarr) private_jarr_delete(jarr, JARR_CMT)

/* static ALWAYS_INLINE int dummy_arr_new(jarray_int_t *jarr) { */

#define jarr_new(jarr, ...)                                                              \
	do {                                                                             \
		((jarr)->capacity) = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_CAP);        \
		if ((((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr)))) { \
			((jarr)->size) = PP_NARG(__VA_ARGS__);                           \
			typeof(*((jarr)->data)) tmp[] = { __VA_ARGS__ };                 \
			memcpy(((jarr)->data), tmp, sizeof(tmp));                        \
		} else {                                                                 \
			((jarr)->capacity) = 0;                                          \
			perror("jarr_new malloc failed");                                \
			return -1;                                                       \
		}                                                                        \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_jarr_shrink(jarray_int_t *jarr) { */

#define private_jarr_shrink(jarr, if_)                                                             \
	do {                                                                                       \
if_		if (((jarr)->capacity) != ((jarr)->size)) {                                        \
			typeof(((jarr)->data)) tmp;                                                \
			if ((tmp = realloc(((jarr)->data), ((jarr)->size) * JARR_T_SIZE(jarr)))) { \
				((jarr)->data) = tmp;                                              \
				((jarr)->capacity) = ((jarr)->size);                               \
			} else {                                                                   \
				perror("jarr_shrink realloc failed");                              \
				return -1;                                                         \
			}                                                                          \
if_		}                                                                                  \
	} while (0)

/* } */

#define jarr_shrink(jarr) private_jarr_shrink(jarr, )
#define jarr_shrink_fast(jarr) private_jarr_shrink(jarr, JARR_CMT)

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t *jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append(jarr, src_arr, src_arr_size, if_)                                           \
	do {                                                                                            \
		const size_t new_size = ((jarr)->size) + (src_arr_size);                                \
if_		if (new_size > ((jarr)->capacity)) {                                                    \
if_			size_t tmp_cap = ((jarr)->capacity);                                            \
if_			do {                                                                            \
if_				tmp_cap *= 2;                                                           \
if_			} while (new_size > tmp_cap);                                                   \
if_			jarr_reserve_fast(jarr, tmp_cap);                                               \
if_		}                                                                                       \
		memcpy(((jarr)->data) + ((jarr)->size), (src_arr), (src_arr_size) * JARR_T_SIZE(jarr)); \
		((jarr)->size) = new_size;                                                              \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t *jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append_typecheck(jarr, src_arr, src_arr_size, if_)                             \
	do {                                                                                        \
		switch (JARR_TYPE_CHECK(src_arr)) {                                                 \
		case JARR_IS_ARRAY:                                                                 \
			(#src_arr_size == "NULL")                                                   \
				? private_jarr_append(jarr, (src_arr), JARR_ARR_SIZE(src_arr), if_) \
				: private_jarr_append(jarr, (src_arr), src_arr_size, if_);          \
		case JARR_IS_JARRAY:                                                                \
			private_jarr_append(jarr, ((src_arr)->data), ((src_arr).size), if_);        \
		case JARR_IS_JARRAY_PTR:                                                            \
			private_jarr_append(jarr, ((src_arr).data), ((src_arr)->size), if_);        \
		}                                                                                   \
	} while (0)

/* } */

#define jarr_append(jarr, src_arr, src_arr_size) private_jarr_append_typecheck(jarr, src_arr, src_arr_size, )
#define jarr_append_fast(jarr, src_arr, src_arr_size) private_jarr_append_typecheck(jarr, src_arr, src_arr_size, JARR_CMT)

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t *jarr, ...) { */

#define jarr_cat(jarr, ...)                                                 \
	do {                                                                \
		const int new_size = ((jarr)->size) + PP_NARG(__VA_ARGS__); \
if_		if (new_size > ((jarr)->capacity)) {                        \
			size_t tmp_cap = ((jarr)->capacity);                \
			do {                                                \
				tmp_cap *= 2;                               \
			} while (new_size > tmp_cap);                       \
			jarr_reserve_fast(jarr, tmp_cap);                   \
if_		}                                                           \
		typeof(*((jarr)->data)) tmp[] = { __VA_ARGS__ };            \
		memcpy(((jarr)->data) + ((jarr)->size), tmp, sizeof(tmp));  \
		((jarr)->size) = new_size;                                  \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_jarr_push_back(jarray_int_t *jarr, int src) { */

#define private_jarr_push_back(jarr, src, if_)                             \
	do {                                                               \
if_		if (((jarr)->capacity) > ((jarr)->size));                  \
if_		else {                                                     \
if_			jarr_reserve_fast(jarr, (((jarr)->capacity) * 2)); \
if_		}                                                          \
		((jarr)->data)[((jarr)->size)++] = src;                    \
	} while (0)

#define jarr_push_back(jarr, src) private_jarr_push_back(jarr, src, , )
#define jarr_push_back_fast(jarr, src) private_jarr_push_back(jarr, src, JARR_CMT)

/* } */

#define jarr_pop_back(jarr) --((jarr)->size);

#define private_jarr_reserve(jarr, cap, if_)                                              \
	do {                                                                              \
if_		if ((cap) > ((jarr)->capacity)) {                                         \
			typeof(((jarr)->data)) tmp;                                       \
			if ((tmp = realloc(((jarr)->data), JARR_T_SIZE(jarr) * (cap)))) { \
				((jarr)->data) = tmp;                                     \
				((jarr)->capacity) = (cap);                               \
			} else {                                                          \
				perror("jarr_reserve realloc failed");                    \
				return -1;                                                \
			}                                                                 \
if_		}                                                                         \
	} while (0)

#define jarr_reserve(jarr, cap) private_jarr_reserve(jarr, cap, )
#define jarr_reserve_fast(jarr, cap) private_jarr_reserve(jarr, cap, JARR_CMT)

#endif
