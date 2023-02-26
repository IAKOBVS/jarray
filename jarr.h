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

#define JARR_STRUCT(NAME, T)  \
	typedef struct NAME { \
		T *data;      \
		size_t len;   \
		size_t size;  \
	} NAME

JARR_STRUCT(JarrayInt, int);
JARR_STRUCT(JarrayDouble, double);
JARR_STRUCT(JarrayFloat, float);

#define jarrAccess(jarr, member) _Generic((jarr), \
	struct: (jarr).member,                    \
	struct*: (jarr)->member                   \
	)

#define jarrInit(jarr)                         \
	do {                                   \
		jarrAccess(jarr, size) = 0;    \
		jarrAccess(jarr, len) = 0;     \
		jarrAccess(jarr, data) = NULL; \
	} while (0)

#define jarrNew(jarr, ...)                                                                                            \
	do {                                                                                                          \
		jarrAccess(jarr, size) = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_SIZE);                                \
		if ((jarrAccess(jarr, data) = malloc(sizeof(jarrAccess(jarr, data[0])) * jarrAccess(jarr, size)))); { \
		else {                                                                                                \
			jarrAccess(jarr, size) = 0;                                                                   \
			perror("jarrNew malloc failed");                                                              \
			return -1;                                                                                    \
		}                                                                                                     \
		jarrAccess(jarr, len) = PP_NARG(__VA_ARGS__);                                                         \
		typeof(jarrAccess(jarr, data[0])) tmp[] = { ##__VA_ARGS__ };                                          \
		memcpy(jarrAccess(jarr, data), tmp, jarr, len);                                                       \
	} while (0)

#define jarrDelete(jarr)                      \
	do {                                  \
		free(jarrAccess(jarr, data)); \
		JARR_INIT(jarr);              \
	} while (0)

#define jarrDeleteFast(jarr)                          \
	do {                                          \
		if (jarrAccess(jarr, data)) {         \
			free(jarrAccess(jarr, data)); \
			JARR_INIT(jarr);              \
		}                                     \
	} while (0)

#define jarrShrink(jarr)                                                                                                                    \
	do {                                                                                                                                \
		if ((jarrAccess(jarr, data) = realloc(jarrAccess(jarr, data), jarrAccess(jarr, len) * sizeof(jarrAccess(jarr, data)[0])))); \
		else {                                                                                                                      \
			free(jarrAccess(jarr, data));                                                                                       \
			perror("jarrShrink realloc failed");                                                                                \
			return -1;                                                                                                          \
		}                                                                                                                           \
		jarrAccess(jarr, size) = jarrAccess(jarr, len);                                                                             \
	} while (0)

#define jarrAppend(jarr, srcArr)                                                                                       \
	do {                                                                                                           \
		const int newLen = jarrAccess(jarr, size) + (sizeof(srcArr) / sizeof(srcArr[0]));                      \
		if (newLen > jarrAccess(jarr, size)) {                                                                 \
			int tmpSize = dest.size;                                                                       \
			do {                                                                                           \
				tmpSize *= 2;                                                                          \
			} while (newLen > tmpSize);                                                                    \
			if ((jarrAccess(jarr, data) = realloc(jarr).data, sizeof(*jarrAccess(jarr, data)) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; }                                           \
			jarrAccess(jarr, size) = tmpSize;                                                              \
		}                                                                                                      \
		memcpy(jarrAccess(jarr, data) + jarrAccess(jarr, len), srcArr, sizeof(srcArr) / sizeof(srcArr[0]));    \
		jarrAccess(jarr, len) = newLen;                                                                        \
	} while (0)

#define jarrCat(jarr, ...)                                                                                             \
	do {                                                                                                           \
		const int newLen = jarrAccess(jarr, len) + PP_NARG(__VA_ARGS__);                                       \
		if (newLen > jarrAccess(jarr, size)) {                                                                 \
			int tmpSize = dest.size;                                                                       \
			do {                                                                                           \
				tmpSize *= 2;                                                                          \
			} while (newLen > tmpSize);                                                                    \
			if ((jarrAccess(jarr, data) = realloc(jarr).data, sizeof(*jarrAccess(jarr, data)) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; }                                           \
			jarrAccess(jarr, size) = tmpSize;                                                              \
		}                                                                                                      \
		typeof(jarr) tmp[] = { ##__VA_ARGS__ };                                                                \
		memcpy(jarrAccess(jarr, data) + jarrAccess(jarr, len), tmp, PP_NARG(__VA_ARGS__));                     \
		jarrAccess(jarr, len) = newLen;                                                                        \
	} while (0)

#define jarrPushback(jarr, src)                                                                                                           \
	do {                                                                                                                              \
		if (jarrAccess(jarr, size) - jarrAccess(jarr, len));                                                                      \
		else {                                                                                                                    \
			if ((jarrAccess(jarr, data) = realloc(jarr).data, sizeof(*jarrAccess(jarr, data)) * 2 * jarrAccess(jarr, size))); \
			else {                                                                                                            \
				perror("jarrPush realloc fails");                                                                         \
				return -1;                                                                                                \
			}                                                    \
			jarrAccess(jarr, data)[jarrAccess(jarr, len)] = src; \
			jarrAccess(jarr, size) *= 2;                         \
			++jarrAccess(jarr, len);                             \
		}                                                            \
	} while (0)

#define jarrPopback(jarr) --jarrAccess(jarr, len)

int qsortDescend(const void *x, const void *y);
int qsortAscend(const void *y, const void *x);
float qsortDescendFl(const void *x, const void *y);
float qsortAscendFl(const void *y, const void *x);
double qsortDescendDb(const void *x, const void *y);
double qsortAscendDb(const void *y, const void *x);

#endif
