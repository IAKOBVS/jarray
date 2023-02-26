#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stddef.h>

#include "/home/james/c/vargc.h"
#include "macros.h"

#define JARR_MIN_CAP (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_SIZEOF_T(var) (sizeof(*var->data))
#define JARR_SIZEOF_ARR(arr) (sizeof(arr)/sizeof(arr[0]))

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t capacity; \
		size_t size;     \
	} NAME

JARR_STRUCT(jarray_int_t, int);
JARR_STRUCT(jarray_double_t, double);
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

#define jarr_delete(jarr)                \
	do {                             \
		if (jarr->data {         \
			free(jarr.data); \
			jarr_init(jarr); \
		}                        \
	} while (0)

#define jarr_delete_ptr(jarr)                \
	do {                                 \
		if (jarr->data {             \
			free(jarr->data);    \
			jarr_init_ptr(jarr); \
		}                            \
	} while (0)

/* static inline void dummy_arr_new(jarray_int_t *thisJarr) { */
#define jarr_new(thisJarr, ...)                                                          \
	do {                                                                             \
		typeof(*(thisJarr)) *RESTRICT jarr = (thisJarr);                         \
		jarr->capacity = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_CAP);            \
		if ((jarr->data = malloc(jarr->capacity * JARR_SIZEOF_T(jarr))));        \
		else {                                                                   \
			jarr->capacity = 0;                                              \
			perror("jarr_new malloc failed");                                \
			return -1;                                                       \
		}                                                                        \
		jarr->size = PP_NARG(__VA_ARGS__);                                       \
		typeof(*jarr->data) tmp[] = { __VA_ARGS__ };                             \
		memcpy(jarr->data, tmp, PP_NARG(__VA_ARGS__) * sizeof(tmp[0])); \
	} while (0)
/* } */

/* static ALWAYS_INLINE int dummy_arr_shrink(jarray_int_t *jarr) { */
#define jarr_shrink(thisJarr)                                                                \
	do {                                                                                 \
		typeof(*(thisJarr)) *RESTRICT jarr = (thisJarr);                             \
		if ((jarr->data = realloc(jarr->data, jarr->size * sizeof(jarr->data[0])))); \
		else {                                                                       \
			perror("jarr_shrink realloc failed");                                \
			return -1;                                                           \
		}                                                                            \
		jarr->capacity = jarr->size;                                                 \
	} while (0)
/* } */

/* static ALWAYS_INLINE int dummy_arr_append(jarray_int_t *dest, int *src_arr, size_t src_arr_size) { */
#define dummy_arr_append(dest, src_arr, src_arr_size)                                              \
	do {                                                                                       \
		typeof(*(dest)) *RESTRICT jarr = (dest);                                           \
		const int new_size = jarr->capacity + src_arr_size;                                \
		if (new_size > jarr->capacity) {                                                   \
			size_t tmp_cap = jarr->capacity;                                           \
			do {                                                                       \
				tmp_cap *= 2;                                                      \
			} while (new_size > tmp_cap);                                              \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_T(jarr) * tmp_cap)));    \
			else {                                                                     \
				jarr_delete_fast_ptr(jarr);                                        \
				perror("jarr_append realloc failed");                              \
				return -1;                                                         \
			}                                                                          \
			jarr->capacity = tmp_cap;                                                  \
		}                                                                                  \
		memcpy(jarr->data + jarr->size, src_arr, src_arr_size * JARR_SIZEOF_ARR(src_arr)); \
		jarr->size = new_size;                                                             \
	} while (0)
/* } */

#define jarr_append(jarr, src_arr) dummy_arr_append(jarr, src_arr, JARR_SIZEOF_ARR(src_arr))
#define jarr_append_jarr(jarr, src_jarr) dummy_arr_append(jarr, src_jarr, )

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t *thisJarr, ...) { */
#define jarr_cat(thisJarr, ...)                                                                 \
	do {                                                                                    \
		typeof(*(thisJarr)) *RESTRICT jarr = (thisJarr);                                \
		const int new_size = jarr->size + PP_NARG(__VA_ARGS__);                         \
		if (new_size > jarr->capacity) {                                                \
			size_t tmp_cap = jarr->capacity;                                        \
			do {                                                                    \
				tmp_cap *= 2;                                                   \
			} while (new_size > tmp_cap);                                           \
			if ((jarr->data = realloc(jarr->data, tmp_cap * JARR_SIZEOF_T(jarr)))); \
			else {                                                                  \
				jarr_delete_fast_ptr(jarr);                                     \
				perror("jarr_cat realloc failed");                              \
				return -1;                                                      \
			}                                                                       \
			jarr->capacity = tmp_cap;                                               \
		}                                                                               \
		typeof(*jarr->data) tmp[] = { __VA_ARGS__ };                                    \
		memcpy(jarr->data + jarr->size, tmp, PP_NARG(__VA_ARGS__) * sizeof(tmp[0]));    \
		jarr->size = new_size;                                                          \
	} while (0)
/* } */

/* static ALWAYS_INLINE int dummy_arr_cat(jarray_int_t *thisJarr, int src) { */
#define jarr_push_back(thisJarr, src)                                                                                \
	do {                                                                                                         \
		typeof(*(thisJarr)) *RESTRICT jarr = (thisJarr);                                                     \
		if (jarr->capacity >= jarr->size);                                                                   \
		else {                                                                                               \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_T(jarr) * (jarr->capacity *= 2)))); \
			else {                                                                                       \
				jarr_delete_fast_ptr(jarr);                                                          \
				perror("jarr_push realloc failed");                                                  \
				return -1;                                                                           \
			}                                                                                            \
			jarr->capacity *= 2;                                                                         \
		}                                                                                                    \
		++jarr->size;                                                                                        \
		jarr->data[jarr->size] = src;                                                                        \
	} while (0)
/* } */

#define jarr_pop_back(jarr) --jarr->size

int qsort_descend(const void *RESTRICT x, const void *RESTRICT y);
int qsort_ascend(const void *RESTRICT y, const void *RESTRICT x);
float qsort_descend_fl(const void *RESTRICT x, const void *RESTRICT y);
float qsort_ascend_fl(const void *RESTRICT y, const void *RESTRICT x);
double qsort_descend_db(const void *RESTRICT x, const void *RESTRICT y);
double qsort_ascend_db(const void *RESTRICT y, const void *RESTRICT x);

#endif
