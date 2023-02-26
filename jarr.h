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

#define JARR_MIN_SIZE (8)
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_SIZEOF_TYPE(jarr) (sizeof(*jarr->data)
#define JARR_SIZEOF_ARR(arr) (sizeof(arr) / sizeof(arr[0]))

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t capacity; \
		size_t size;     \
	} NAME

JARR_STRUCT(JarrayInt, int);
JARR_STRUCT(JarrayDouble, double);
JARR_STRUCT(JarrayFloat, float);

#define jarrInit(jarr)              \
	do {                        \
		jarr->capacity = 0; \
		jarr->size = 0;     \
		jarr->data = NULL;  \
	} while (0)

#define jarrNew(jarr, ...)                                                          \
	do {                                                                        \
		jarr->capacity = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_SIZE);      \
		if ((jarr->data = malloc(JARR_SIZEOF_TYPE(jarr) * jarr->capacity)); \
		else {                                                              \
			jarr->capacity = 0;                                         \
			perror("jarrNew malloc failed");                            \
			return -1;                                                  \
		}                                                                   \
		jarr->size = PP_NARG(__VA_ARGS__);                                  \
		typeof(jarrAccess(jarr, data[0])) tmp[] = { ##__VA_ARGS__ };        \
		memcpy(jarr->data, tmp, jarr, size);                                \
	} while (0)

#define jarrDeleteFast(jarr)     \
	do {                     \
		free(jarr->data; \
		JARR_INIT(jarr); \
	} while (0)

#define jarrDelete(jarr)                 \
	do {                             \
		if (jarr->data {         \
			free(jarr->data; \
			JARR_INIT(jarr); \
		}                        \
	} while (0)

#define jarrShrink(jarr)                                                                      \
	do {                                                                                  \
		if ((jarr->data = realloc(jarr->data, jarr->size * JARR_SIZEOF_TYPE(jarr)))); \
		else {                                                                        \
			jarrDeleteFast(jarr);                                                 \
			perror("jarrShrink realloc failed");                                  \
			return -1;                                                            \
		}                                                                             \
		jarr->capacity = jarr->size;                                                  \
	} while (0)

#define jarrAppend(jarr, srcArr, srcArrSize)                                                      \
	do {                                                                                      \
		const int newSize = jarr->capacity + srcArrSize;                                  \
		if (newSize > jarr->capacity {                                                    \
			size_t tmpCap = dest.capacity;                                            \
			do {                                                                      \
				tmpCap *= 2;                                                      \
			} while (newSize > tmpCap);                                               \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_TYPE(jarr) * tmpCap))); \
			else {                                                                    \
				perror("jarrCat realloc fails");                                  \
				return -1;                                                        \
			}                                                                         \
			jarr->capacity = tmpCap;                                                  \
		}                                                                                 \
		memcpy(jarr->data + jarr->size, srcArr, srcArrSize);                              \
		jarr->size = newSize;                                                             \
	} while (0)

#define jarrAppendAuto(jarr, srcArr) jarrAppend(jarr, srcArr, JARR_SIZEOF_ARR(srcArr))

#define jarrCat(jarr, ...)                                                                        \
	do {                                                                                      \
		const int newSize = jarr->size + PP_NARG(__VA_ARGS__);                            \
		if (newSize > jarr->capacity {                                                    \
			size_t tmpCap = dest.capacity;                                            \
			do {                                                                      \
				tmpCap *= 2;                                                      \
			} while (newSize > tmpCap);                                               \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_TYPE(jarr) * tmpCap))); \
			else {                                                                    \
				jarrDeleteFast(jarr);                                             \
				perror("jarrCat realloc fails");                                  \
				return -1;                                                        \
			}                                                                         \
			jarr->capacity = tmpCap;                                                  \
		}                                                                                 \
		typeof(jarr) tmp[] = { ##__VA_ARGS__ };                                           \
		memcpy(jarr->data + jarr->size, tmp, PP_NARG(__VA_ARGS__));                       \
		jarr->size = newSize;                                                             \
	} while (0)

#define jarrPushback(jarr, src)                                                                                  \
	do {                                                                                                     \
		if (jarr->capacity >= jarr->size;                                                                \
		else {                                                                                           \
			if ((jarr->data = realloc(jarr->data, JARR_SIZEOF_TYPE(jarr) * (jarr->capacity *= 2)))); \
			else {                                                                                   \
				jarrDeleteFast(jarr);                                                            \
				perror("jarrPush realloc fails");                                                \
				return -1;                                                                       \
			}                                                                                        \
			jarr->capacity *= 2;                                                                     \
		}                                                                                                \
		++jarr->size;                                                                                    \
		jarr->data[jarr->size] = src;                                                                    \
	} while (0)

#define jarrPopback(jarr) --jarr->size

int qsortDescend(const void *x, const void *y);
int qsortAscend(const void *y, const void *x);
float qsortDescendFl(const void *x, const void *y);
float qsortAscendFl(const void *y, const void *x);
double qsortDescendDb(const void *x, const void *y);
double qsortAscendDb(const void *y, const void *x);

#endif
