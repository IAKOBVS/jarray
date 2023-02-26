#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stddef.h>

#include "/home/james/c/vargc.h"
#include "macros.h"

#define JARR_MIN_CAP (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_T_SIZE(var) (sizeof(*var->data))
#define JARR_ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

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

#define jarr_init(jarr)            \
	do {                       \
		jarr.capacity = 0; \
		jarr.size = 0;     \
		jarr.data = NULL;  \
	} while (0)

#define jarr_init_ptr(jarr)         \
	do {                        \
		jarr->capacity = 0; \
		jarr->size = 0;     \
		jarr->data = NULL;  \
	} while (0)

#define jarr_delete_fast(jarr)   \
	do {                     \
		free(jarr.data); \
		jarr_init(jarr); \
	} while (0)

#define jarr_delete_fast_ptr(jarr)   \
	do {                         \
		free(jarr->data);    \
		jarr_init_ptr(jarr); \
	} while (0)

#define jarr_delete(jarr)                 \
	do {                              \
		if (jarr->data {          \
			free(jarr->data); \
			jarr_init(jarr);  \
		}                         \
	} while (0)

#define jarr_delete_ptr(jarr)                \
	do {                                 \
		if (jarr->data {             \
			free(jarr->data);    \
			jarr_init_ptr(jarr); \
		}                            \
	} while (0)

/* static ALWAYS_INLINE int dummy_arr_new(jarray_int_t *thisJarr) { */
#define jarr_new(thisJarr, ...)                                                 \
	do {                                                                    \
		typeof(*(thisJarr)) *jarr = (thisJarr);                         \
		jarr->capacity = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_CAP);   \
		if ((jarr->data = malloc(jarr->capacity * JARR_T_SIZE(jarr)))); \
		else {                                                          \
			jarr->capacity = 0;                                     \
			perror("jarr_new malloc failed");                       \
			return -1;                                              \
		}                                                               \
		jarr->size = PP_NARG(__VA_ARGS__);                              \
		typeof(*jarr->data) tmp[] = { __VA_ARGS__ };                    \
		memcpy(jarr->data, tmp, sizeof(tmp));                           \
	} while (0)
/* } */

/* static ALWAYS_INLINE int dummy_arr_shrink(jarray_int_t *thisJarr) { */
#define jarr_shrink(thisJarr)                                                     \
	do {                                                                      \
		typeof(*(thisJarr)) *jarr = (thisJarr);                           \
		typeof(jarr->data) tmp;                                           \
		if ((tmp = realloc(jarr->data, jarr->size * JARR_T_SIZE(jarr)))); \
		else {                                                            \
			perror("jarr_shrink realloc failed");                     \
			return -1;                                                \
		}                                                                 \
		jarr->data = tmp;                                                 \
		jarr->capacity = jarr->size;                                      \
	} while (0)
/* } */

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t *dest, int *src_arr, size_t src_arr_size) { */
#define impl_jarr_append(dest, src_arr, src_arr_size)                                  \
	do {                                                                           \
		typeof(*(dest)) *jarr = (dest);                                        \
		const int new_size = jarr->size + src_arr_size;                        \
		if (new_size > jarr->capacity) {                                       \
			size_t tmp_cap = jarr->capacity;                               \
			do {                                                           \
				tmp_cap *= 2;                                          \
			} while (new_size > tmp_cap);                                  \
			typeof(jarr->data) tmp;                                        \
			if ((tmp = realloc(jarr->data, tmp_cap * JARR_T_SIZE(jarr)))); \
			else {                                                         \
				perror("jarr_append realloc failed");                  \
				return -1;                                             \
			}                                                              \
			jarr->data = tmp;                                              \
			jarr->capacity = tmp_cap;                                      \
		}                                                                      \
		memcpy(jarr->data + jarr->size, src_arr, sizeof(src_arr));             \
		jarr->size = new_size;                                                 \
	} while (0)
/* } */

#define jarr_append(jarr, src_arr) impl_jarr_append(jarr, src_arr, JARR_ARR_SIZE(src_arr))
#define jarr_append_jarr(jarr, src_jarr)                   \
	typeof(*(src_arr)) tmpSrc = *(src_arr);            \
	impl_jarr_append(jarr, tmpSrc->data, tmpSrc->size)

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t *thisJarr, ...) { */
#define jarr_cat(thisJarr, ...)                                                        \
	do {                                                                           \
		typeof(*(thisJarr)) *jarr = (thisJarr);                                \
		const int new_size = jarr->size + PP_NARG(__VA_ARGS__);                \
		if (new_size > jarr->capacity) {                                       \
			size_t tmp_cap = jarr->capacity;                               \
			do {                                                           \
				tmp_cap *= 2;                                          \
			} while (new_size > tmp_cap);                                  \
			typeof(jarr->data) tmp;                                        \
			if ((tmp = realloc(jarr->data, tmp_cap * JARR_T_SIZE(jarr)))); \
			else {                                                         \
				perror("jarr_cat realloc failed");                     \
				return -1;                                             \
			}                                                              \
			jarr->data = tmp;                                              \
			jarr->capacity = tmp_cap;                                      \
		}                                                                      \
		typeof(*jarr->data) tmp[] = { __VA_ARGS__ };                           \
		memcpy(jarr->data + jarr->size, tmp, sizeof(tmp));                     \
		jarr->size = new_size;                                                 \
	} while (0)
/* } */

/* static ALWAYS_INLINE int dummy_jarr_push_back(jarray_int_t *thisJarr, int src) { */
#define jarr_push_back(thisJarr, src)                                                             \
	do {                                                                                      \
		typeof(*(thisJarr)) *jarr = (thisJarr);                                           \
		if (jarr->capacity >= jarr->size);                                                \
		else {                                                                            \
			typeof(jarr->data) tmp;                                                   \
			if ((tmp = realloc(jarr->data, JARR_T_SIZE(jarr) * jarr->capacity * 2))); \
			else {                                                                    \
				perror("jarr_push realloc failed");                               \
				return -1;                                                        \
			}                                                                         \
			jarr->data = tmp;                                                         \
			jarr->capacity *= 2;                                                      \
		}                                                                                 \
		jarr->data[jarr->size++] = src;                                                   \
	} while (0)
/* } */

#define jarr_pop_back(thisJarr)                         \
	do {                                            \
		typeof(*(thisJarr)) *jarr = (thisJarr); \
		--jarr->size;                           \
	} while (0)

#define jarr_reserve(thisJarr, size)                                                \
	do {                                                                        \
		typeof(*(thisJarr)) *jarr = (thisJarr);                             \
		if (jarr->capacity < size) {                                        \
			typeof(jarr->data) tmp;                                     \
			if ((tmp = realloc(jarr->data, JARR_T_SIZE(jarr) * size))); \
			else {                                                      \
				perror("jarr_reserve realloc failed");              \
				return -1;                                          \
			}                                                           \
			jarr->data = tmp;                                           \
			jarr->size = size;                                          \
		}                                                                   \
	} while (0)

#define jarr_reserve_fast(jarr, size)                                       \
	do {                                                                \
		typeof(jarr->data) tmp;                                     \
		if ((tmp = realloc(jarr->data, JARR_T_SIZE(jarr) * size))); \
		else {                                                      \
			perror("jarr_reserve realloc failed");              \
			return -1;                                          \
		}                                                           \
		jarr->data = tmp;                                           \
		jarr->size = size;                                          \
	} while (0)

#define jarr_reserve_fast_ptr(jarr, size)                                   \
	do {                                                                \
		typeof(jarr->data) tmp;                                     \
		if ((tmp = realloc(jarr->data, JARR_T_SIZE(jarr) * size))); \
		else {                                                      \
			perror("jarr_reserve realloc failed");              \
			return -1;                                          \
		}                                                           \
		jarr->data = tmp;                                           \
		jarr->size = size;                                          \
	} while (0)

int qsort_descend(const void *RESTRICT x, const void *RESTRICT y);
int qsort_ascend(const void *RESTRICT y, const void *RESTRICT x);
float qsort_descend_fl(const void *RESTRICT x, const void *RESTRICT y);
float qsort_ascend_fl(const void *RESTRICT y, const void *RESTRICT x);
double qsort_descend_db(const void *RESTRICT x, const void *RESTRICT y);
double qsort_ascend_db(const void *RESTRICT y, const void *RESTRICT x);

#endif
