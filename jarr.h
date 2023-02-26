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

#define JARR_MIN_SIZE 8
#define MAX(a,b) ((a)>(b)?(a):(b))

#define JARR_STRUCT(NAME, T)     \
	typedef struct NAME {    \
		T *data;         \
		size_t capacity; \
		size_t size;     \
	} NAME

JARR_STRUCT(JarrayInt, int);
JARR_STRUCT(JarrayDouble, double);
JARR_STRUCT(JarrayFloat, float);

#define jarrAccess(jarr, member) _Generic((jarr), \
	struct: (jarr).member,                    \
	struct*: (jarr)->member                   \
	)

#define jarrInit(jarr)                          \
	do {                                    \
		jarrAccess(jarr, capacity) = 0; \
		jarrAccess(jarr, size) = 0;     \
		jarrAccess(jarr, data) = NULL;  \
	} while (0)

#define jarrNew(jarr, ...)                                                                                                \
	do {                                                                                                              \
		jarrAccess(jarr, capacity) = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_SIZE);                                \
		if ((jarrAccess(jarr, data) = malloc(sizeof(jarrAccess(jarr, data[0])) * jarrAccess(jarr, capacity)))); { \
		else {                                                                                                    \
			jarrAccess(jarr, capacity) = 0;                                                                   \
			perror("jarrNew malloc failed");                                                                  \
			return -1;                                                                                        \
		}                                                                                                         \
		jarrAccess(jarr, size) = PP_NARG(__VA_ARGS__);                                                            \
		typeof(jarrAccess(jarr, data[0])) tmp[] = { ##__VA_ARGS__ };                                              \
		memcpy(jarrAccess(jarr, data), tmp, jarr, size);                                                          \
	} while (0)

#define jarrDeleteFast(jarr)                  \
	do {                                  \
		free(jarrAccess(jarr, data)); \
		JARR_INIT(jarr);              \
	} while (0)

#define jarrDelete(jarr)                              \
	do {                                          \
		if (jarrAccess(jarr, data)) {         \
			free(jarrAccess(jarr, data)); \
			JARR_INIT(jarr);              \
		}                                     \
	} while (0)

#define jarrShrink(jarr)                                                                                                                     \
	do {                                                                                                                                 \
		if ((jarrAccess(jarr, data) = realloc(jarrAccess(jarr, data), jarrAccess(jarr, size) * sizeof(jarrAccess(jarr, data)[0])))); \
		else {                                                                                                                       \
			jarrDeleteFast(jarr);                                                                                                \
			perror("jarrShrink realloc failed");                                                                                 \
			return -1;                                                                                                           \
		}                                                                                                                            \
		jarrAccess(jarr, capacity) = jarrAccess(jarr, size);                                                                         \
	} while (0)

#define jarrAppend(jarr, srcArr)                                                                                      \
	do {                                                                                                          \
		const int newLen = jarrAccess(jarr, capacity) + (sizeof(srcArr) / sizeof(srcArr[0]));                 \
		if (newLen > jarrAccess(jarr, capacity)) {                                                            \
			size_t tmpCap = dest.capacity;                                                                \
			do {                                                                                          \
				tmpCap *= 2;                                                                          \
			} while (newLen > tmpCap);                                                                    \
			if ((jarrAccess(jarr, data) = realloc(jarr).data, sizeof(*jarrAccess(jarr, data)) * tmpCap)); \
			else {                                                                                        \
				perror("jarrCat realloc fails");                                                      \
				return -1;                                                                            \
			}                                                                                             \
			jarrAccess(jarr, capacity) = tmpCap;                                                          \
		}                                                                                                     \
		memcpy(jarrAccess(jarr, data) + jarrAccess(jarr, size), srcArr, sizeof(srcArr) / sizeof(srcArr[0]));  \
		jarrAccess(jarr, size) = newLen;                                                                      \
	} while (0)

#define jarrCat(jarr, ...)                                                                                            \
	do {                                                                                                          \
		const int newLen = jarrAccess(jarr, size) + PP_NARG(__VA_ARGS__);                                     \
		if (newLen > jarrAccess(jarr, capacity)) {                                                            \
			size_t tmpCap = dest.capacity;                                                                \
			do {                                                                                          \
				tmpCap *= 2;                                                                          \
			} while (newLen > tmpCap);                                                                    \
			if ((jarrAccess(jarr, data) = realloc(jarr).data, sizeof(*jarrAccess(jarr, data)) * tmpCap)); \
			else {                                                                                        \
				jarrDeleteFast(jarr);                                                                 \
				perror("jarrCat realloc fails");                                                      \
				return -1;                                                                            \
			}                                                                                             \
			jarrAccess(jarr, capacity) = tmpCap;                                                          \
		}                                                                                                     \
		typeof(jarr) tmp[] = { ##__VA_ARGS__ };                                                               \
		memcpy(jarrAccess(jarr, data) + jarrAccess(jarr, size), tmp, PP_NARG(__VA_ARGS__));                   \
		jarrAccess(jarr, size) = newLen;                                                                      \
	} while (0)

#define jarrPushback(jarr, src)                                                                                                               \
	do {                                                                                                                                  \
		if (jarrAccess(jarr, capacity) - jarrAccess(jarr, size));                                                                     \
		else {                                                                                                                        \
			if ((jarrAccess(jarr, data) = realloc(jarr).data, sizeof(*jarrAccess(jarr, data)) * 2 * jarrAccess(jarr, capacity))); \
			else {                                                                                                                \
				jarrDeleteFast(jarr);                                                                                         \
				perror("jarrPush realloc fails");                                                                             \
				return -1;                                                                                                    \
			}                                                                                                                     \
			jarrAccess(jarr, data)[jarrAccess(jarr, size)] = src;                                                                 \
			jarrAccess(jarr, capacity) *= 2;                                                                                      \
			++jarrAccess(jarr, size);                                                                                             \
		}                                                                                                                             \
	} while (0)

#define jarrPopback(jarr) --jarrAccess(jarr, size)

int qsortDescend(const void *x, const void *y);
int qsortAscend(const void *y, const void *x);
float qsortDescendFl(const void *x, const void *y);
float qsortAscendFl(const void *y, const void *x);
double qsortDescendDb(const void *x, const void *y);
double qsortAscendDb(const void *y, const void *x);

#endif
