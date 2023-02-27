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

#define JARR_IS_STACK_ARRAY(SRC_ARR, TYPE_CHECK) (sizeof(SRC_ARR) != sizeof(SRC_ARR[0]))

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

#define jarr_delete_fast(jarr)     \
	do {                       \
		free((jarr).data); \
		jarr_init(jarr);   \
	} while (0)

#define jarr_delete(jarr)                     \
	do {                                  \
		if (((jarr)->data) {          \
			free(((jarr)->data)); \
			jarr_init(jarr);      \
		}                             \
	} while (0)

/* static ALWAYS_INLINE int dummy_arr_new(jarray_int_t *jarr) { */

#define private_jarr_new(jarr, ...)                                                      \
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

/* static ALWAYS_INLINE int dummy_arr_new(jarray_int_t *jarr) { */

#define jarr_new(jarr, ...)                                      \
	do {                                                     \
		if (#jarr[0] == '&') {                           \
			typeof(jarr) tmp_jarr = (jarr);          \
			private_jarr_new(tmp_jarr, __VA_ARGS__); \
		} else {                                         \
			private_jarr_new(jarr, __VA_ARGS__);     \
		}                                                \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_arr_shrink(jarray_int_t *jarr) { */

#define private_jarr_shrink(jarr)                                                          \
	do {                                                                               \
		typeof(((jarr)->data)) tmp;                                                \
		if ((tmp = realloc(((jarr)->data), ((jarr)->size) * JARR_T_SIZE(jarr)))) { \
			((jarr)->data) = tmp;                                              \
			((jarr)->capacity) = ((jarr)->size);                               \
		} else {                                                                   \
			perror("jarr_shrink realloc failed");                              \
			return -1;                                                         \
		}                                                                          \
	} while (0)

/* } */

#define jarr_shrink(jarr)                                           \
	do {                                                        \
		if (#jarr[0] == '&') {                              \
			typeof(jarr) tmp_jarr = (jarr);             \
			private_jarr_shrink(tmp_jarr, __VA_ARGS__); \
		} else {                                            \
			private_jarr_shrink(jarr, __VA_ARGS__);     \
		}                                                   \
	} while (0)

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t *jarr, int *src_arr, size_t src_arr_size) { */

#define private_jarr_append(jarr, src_arr, src_arr_size)                                    \
	do {                                                                                \
		const size_t new_size = ((jarr)->size) + src_arr_size;                      \
		if (new_size > ((jarr)->capacity)) {                                        \
			size_t tmp_cap = ((jarr)->capacity);                                \
			do {                                                                \
				tmp_cap *= 2;                                               \
			} while (new_size > tmp_cap);                                       \
			typeof(((jarr)->data)) tmp;                                         \
			if ((tmp = realloc(((jarr)->data), tmp_cap * JARR_T_SIZE(jarr)))) { \
				((jarr)->data) = tmp;                                       \
				((jarr)->capacity) = tmp_cap;                               \
			} else {                                                            \
				perror("jarr_append realloc failed");                       \
				return -1;                                                  \
			}                                                                   \
		}                                                                           \
		memcpy(((jarr)->data) + ((jarr)->size), src_arr, src_arr_size);             \
		((jarr)->size) = new_size;                                                  \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t *jarr, int *src_arr, size_t src_arr_size) { */

#define jarr_append(jarr, src_arr, src_arr_size)                                                       \
	do {                                                                                           \
		if (#jarr[0] == '&') {                                                                 \
			typeof(jarr) jarr = (jarr);                                                    \
			private_jarr_append(tmp_jarr, src_arr, src_arr_size);                          \
			switch (JARR_TYPE_CHECK(src_arr)) {                                            \
			case JARR_IS_ARRAY:                                                            \
				(JARR_IS_STACK_ARRAY)                                                  \
					? private_jarr_append(jarr, (src_arr), JARR_ARR_SIZE(src_arr)) \
					: private_jarr_append(jarr, (src_arr), src_arr_size);          \
			case JARR_IS_JARRAY:                                                           \
				private_jarr_append(jarr, ((src_arr)->data), ((src_arr)->size));       \
			case JARR_IS_JARRAY_PTR:                                                       \
				private_jarr_append(jarr, ((src_arr).data), ((src_arr).size));         \
			}                                                                              \
		} else {                                                                               \
			switch (JARR_TYPE_CHECK(src_arr)) {                                            \
			case JARR_IS_ARRAY:                                                            \
				(JARR_IS_STACK_ARRAY)                                                  \
					? private_jarr_append(jarr, (src_arr), JARR_ARR_SIZE(src_arr)) \
					: private_jarr_append(jarr, (src_arr), src_arr_size);          \
			case JARR_IS_JARRAY:                                                           \
				private_jarr_append(jarr, ((src_arr)->data), ((src_arr)->size));       \
			case JARR_IS_JARRAY_PTR:                                                       \
				private_jarr_append(jarr, ((src_arr).data), ((src_arr).size));         \
			}                                                                              \
		}                                                                                      \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t *jarr, ...) { */

#define jarr_cat(jarr, ...)                                                                 \
	do {                                                                                \
		const int new_size = ((jarr)->size) + PP_NARG(__VA_ARGS__);                 \
		if (new_size > ((jarr)->capacity)) {                                        \
			size_t tmp_cap = ((jarr)->capacity);                                \
			do {                                                                \
				tmp_cap *= 2;                                               \
			} while (new_size > tmp_cap);                                       \
			typeof(((jarr)->data)) tmp;                                         \
			if ((tmp = realloc(((jarr)->data), tmp_cap * JARR_T_SIZE(jarr)))) { \
				((jarr)->data) = tmp;                                       \
				((jarr)->capacity) = tmp_cap;                               \
			} else {                                                            \
				perror("jarr_cat realloc failed");                          \
				return -1;                                                  \
			}                                                                   \
		}                                                                           \
		typeof(*((jarr)->data)) tmp[] = { __VA_ARGS__ };                            \
		memcpy(((jarr)->data) + ((jarr)->size), tmp, sizeof(tmp));                  \
		((jarr)->size) = new_size;                                                  \
	} while (0)

/* } */

/* static ALWAYS_INLINE int dummy_jarr_push_back(jarray_int_t *jarr, int src) { */

#define jarr_push_back(jarr, src)                                                                          \
	do {                                                                                               \
		if (((jarr)->capacity) >= ((jarr)->size));                                                 \
		else {                                                                                     \
			typeof(((jarr)->data)) tmp;                                                        \
			if ((tmp = realloc(((jarr)->data), JARR_T_SIZE(jarr) * ((jarr)->capacity) * 2))) { \
				((jarr)->data) = tmp;                                                      \
				((jarr)->capacity) *= 2;                                                   \
			} else {                                                                           \
				perror("jarr_push realloc failed");                                        \
				return -1;                                                                 \
			}                                                                                  \
		}                                                                                          \
		((jarr)->data)[((jarr)->size)++] = src;                                                    \
	} while (0)

/* } */

#define jarr_pop_back(jarr) --((jarr)->size);

#define jarr_reserve(jarr, size)                                                         \
	do {                                                                             \
		if (((jarr)->capacity) < size) {                                         \
			typeof(((jarr)->data)) tmp;                                      \
			if ((tmp = realloc(((jarr)->data), JARR_T_SIZE(jarr) * size))) { \
				((jarr)->data) = tmp;                                    \
				((jarr)->size) = size;                                   \
			} else {                                                         \
				perror("jarr_reserve realloc failed");                   \
				return -1;                                               \
			}                                                                \
		}                                                                        \
	} while (0)


#define jarr_reserve_fast(jarr, size)                                            \
	do {                                                                     \
		typeof(((jarr)->data)) tmp;                                      \
		if ((tmp = realloc(((jarr)->data), JARR_T_SIZE(jarr) * size))) { \
			((jarr)->data) = tmp;                                    \
			((jarr)->size) = size;                                   \
		} else {                                                         \
			perror("jarr_reserve realloc failed");                   \
			return -1;                                               \
		}                                                                \
	} while (0)

#endif
