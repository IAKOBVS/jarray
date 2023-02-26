#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stddef.h>
#include "/home/james/c/vargc.h"

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
# define RESTRICT_KEYWORD restrict
#elif defined(__GNUC__) || defined(__clang__)
# define RESTRICT_KEYWORD __restrict__
#elif defined(_MSC_VER)
# define RESTRICT_KEYWORD __restrict
#else
# define RESTRICT_KEYWORD
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 3)) || (defined(__clang__) && __has_builtin(__builtin_expect))
  #define likely(x) __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else
  #define likely(x) (x)
  #define unlikely(x) (x)
#endif

#define JARR_MIN_CAP (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_SIZEOF_TYPE(jarr) (sizeof(*jarr->data)
#define JARR_SIZEOF_ARR(arr) (sizeof(arr) / sizeof(arr[0]))

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t capacity; \
		size_t size;     \
	} NAME

JARR_STRUCT(jarray_int, int);
JARR_STRUCT(jarray_double, double);
JARR_STRUCT(jarray_float, float);

#define jarr_init(jarr)             \
	do {                        \
		jarr->capacity = 0; \
		jarr->size = 0;     \
		jarr->data = NULL;  \
	} while (0)

#define jarr_new(jarr, ...)                                                         \
	do {                                                                        \
		jarr->capacity = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_CAP);      \
		if ((jarr->data = malloc(JARR_SIZEOF_TYPE(jarr) * jarr->capacity)); \
		else {                                                              \
			jarr->capacity = 0;                                         \
			perror("jarr_new malloc failed");                           \
			return -1;                                                  \
		}                                                                   \
		jarr->size = PP_NARG(__VA_ARGS__);                                  \
		typeof(jarr_access(jarr, data[0])) tmp[] = { ##__VA_ARGS__ };       \
		memcpy(jarr->data, tmp, jarr, size);                                \
	} while (0)

#define jarr_delete_fast(jarr)   \
	do {                     \
		free(jarr->data; \
		JARR_INIT(jarr); \
	} while (0)

#define jarr_delete(jarr)                \
	do {                             \
		if (jarr->data {         \
			free(jarr->data; \
			JARR_INIT(jarr); \
		}                        \
	} while (0)

#define jarr_shrink(jarr)                                                                     \
	do {                                                                                  \
		if ((jarr->data = realloc(jarr->data, jarr->size * JARR_SIZEOF_TYPE(jarr)))); \
		else {                                                                        \
			jarr_delete_fast(jarr);                                               \
			perror("jarr_shrink realloc failed");                                 \
			return -1;                                                            \
		}                                                                             \
		jarr->capacity = jarr->size;                                                  \
	} while (0)

#define jarr_append(jarr, src_arr, src_arr_size)                                                   \
	do {                                                                                       \
		const int new_size = jarr->capacity + src_arr_size;                                \
		if (new_size > jarr->capacity {                                                    \
			size_t tmp_cap = dest.capacity;                                            \
			do {                                                                       \
				tmp_cap *= 2;                                                      \
			} while (new_size > tmp_cap);                                              \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_TYPE(jarr) * tmp_cap))); \
			else {                                                                     \
				perror("jarr_cat realloc fails");                                  \
				return -1;                                                         \
			}                                                                          \
			jarr->capacity = tmp_cap;                                                  \
		}                                                                                  \
		memcpy(jarr->data + jarr->size, src_arr, src_arr_size);                            \
		jarr->size = new_size;                                                             \
	} while (0)

#define jarr_append_auto(jarr, srcrrr) jarr_append(jarr, src_arr, JARR_SIZEOF_ARR(src_arr))

#define jarr_cat(jarr, ...)                                                                        \
	do {                                                                                       \
		const int new_size = jarr->size + PP_NARG(__VA_ARGS__);                            \
		if (new_size > jarr->capacity {                                                    \
			size_t tmp_cap = dest.capacity;                                            \
			do {                                                                       \
				tmp_cap *= 2;                                                      \
			} while (new_size > tmp_cap);                                              \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_TYPE(jarr) * tmp_cap))); \
			else {                                                                     \
				jarr_delete_fast(jarr);                                            \
				perror("jarr_cat realloc fails");                                  \
				return -1;                                                         \
			}                                                                          \
			jarr->capacity = tmp_cap;                                                  \
		}                                                                                  \
		typeof(jarr) tmp[] = { ##__VA_ARGS__ };                                            \
		memcpy(jarr->data + jarr->size, tmp, PP_NARG(__VA_ARGS__));                        \
		jarr->size = new_size;                                                             \
	} while (0)

#define jarr_push_back(jarr, src)                                                                                 \
	do {                                                                                                     \
		if (jarr->capacity >= jarr->size;                                                                \
		else {                                                                                           \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_TYPE(jarr) * (jarr->capacity *= 2)))); \
			else {                                                                                   \
				jarr_delete_fast(jarr);                                                          \
				perror("jarr_push realloc fails");                                               \
				return -1;                                                                       \
			}                                                                                        \
			jarr->capacity *= 2;                                                                     \
		}                                                                                                \
		++jarr->size;                                                                                    \
		jarr->data[jarr->size] = src;                                                                    \
	} while (0)

#define jarr_pop_back(jarr) --jarr->size

int qsort_descend(const void *x, const void *y);
int qsort_ascend(const void *y, const void *x);
float qsort_descend_fl(const void *x, const void *y);
float qsort_ascend_fl(const void *y, const void *x);
double qsort_descend_db(const void *x, const void *y);
double qsort_ascend_db(const void *y, const void *x);

#endif
