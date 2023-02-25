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

#define JARR_STRUCT(NAME, TYPE) \
	typedef struct NAME {   \
		TYPE *data;     \
		size_t len;     \
		size_t size;    \
	} NAME

JARR_STRUCT(JarrInt, int);
JARR_STRUCT(JarrDouble, double);
JARR_STRUCT(JarrFloat, float);

#define jarrInit(JARR)            \
	do {                      \
		JARR.size = 0;    \
		JARR.len = 0;     \
		JARR.data = NULL; \
	} while (0)

#define jarrInitPtr(JARR)          \
	do {                       \
		JARR->size = 0;    \
		JARR->len = 0;     \
		JARR->data = NULL; \
	} while (0)

#define jarrNew(thisJarr, ...)                                                                       \
	do {                                                                                         \
		thisJarr.size = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_SIZE);                        \
		if (unlikely(!(thisJarr.data = malloc(sizeof(thisJarr.data[0]) * thisJarr.size)))) { \
			thisJarr.size = 0;                                                           \
			perror("jarrNew malloc failed");                                             \
			return -1;                                                                   \
		}                                                                                    \
		thisJarr.len = PP_NARG(__VA_ARGS__);                                                 \
		typeof(thisJarr.data[0]) tmp[] = { __VA_ARGS__ };                                    \
		memcpy(thisJarr.data, tmp, thisJarr.len);                                            \
	} while (0)

#define jarrNewPtr(thisJarr, ...)                                                                       \
	do {                                                                                            \
		thisJarr->size = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_SIZE);                          \
		if (unlikely(!(thisJarr->data = malloc(sizeof(thisJarr->data[0]) * thisJarr->size)))) { \
			thisJarr.size = 0;                                                              \
			perror("jarrNew malloc failed");                                                \
			return -1;                                                                      \
		}                                                                                       \
		thisJarr->len = PP_NARG(__VA_ARGS__);                                                   \
		typeof(thisJarr->data[0]) tmp[] = { __VA_ARGS__ };                                      \
		memcpy(thisJarr->data, tmp, thisJarr->len);                                             \
	} while (0)

#define jarrDeleteFast(thisJarr)     \
	do {                         \
		free(thisJarr.data); \
		jarrInit(thisJarr);  \
	} while (0)

#define jarrDeletePtrFast(thisJarr)    \
	do {                           \
		free(thisJarr->data);  \
		jarrInitPtr(thisJarr); \
	} while (0)

#define jarrDelete(thisJarr)                 \
	do {                                 \
		if (thisJarr.data) {         \
			free(thisJarr.data); \
			jarrInit(thisJarr);  \
		}                            \
	} while (0)

#define jarrDeletePtr(thisJarr)                \
	do {                                   \
		if (thisJarr.data) {           \
			free(thisJarr->data);  \
			jarrInitPtr(thisJarr); \
		}                              \
	} while (0)

#define jarrPopback(thisJarr) --thisJarr.len
#define jarrPopbackPtr(thisJarr) --thisJarr->len

#define jarrShrink(thisJarr)                                                                               \
	do {                                                                                               \
		if ((thisJarr->data = realloc(thisJarr->data, thisJarr->len * sizeof(thisJarr->data[0])))) \
			thisJarr->size = thisJarr->len;                                                    \
		else {                                                                                     \
			free(thisJarr->data);                                                              \
			perror("jarrShrink realloc failed");                                               \
			return -1;                                                                         \
		}                                                                                          \
	} while (0)

#define jarrShrinkPtr(thisJarr)                                                                            \
	do {                                                                                               \
		if ((thisJarr->data = realloc(thisJarr->data, thisJarr->len * sizeof(thisJarr->data[0])))) \
			thisJarr->size = thisJarr->len;                                                    \
		else {                                                                                     \
			free(thisJarr->data);                                                              \
			perror("jarrShrink realloc failed");                                               \
			return -1;                                                                         \
		}                                                                                          \
	} while (0)

#define jarrAppend(thisJarr, srcArr)                                                                     \
	do {                                                                                             \
		const int newLen = thisJarr.size + (sizeof(srcArr) / sizeof(srcArr[0]));                 \
		if (newLen > thisJarr.size) {                                                            \
			int tmpSize = dest.size;                                                         \
			do {                                                                             \
				tmpSize *= 2;                                                            \
			} while (newLen > tmpSize);                                                      \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; }                             \
			thisJarr.size = tmpSize;                                                         \
		}                                                                                        \
		memcpy(thisJarr.data + thisJarr.len, srcArr, sizeof(srcArr) / sizeof(srcArr[0]));        \
		thisJarr.len = newLen;                                                                   \
	} while (0)

#define jarrAppendPtr(thisJarr, srcArr)                                                                     \
	do {                                                                                                \
		const int newLen = thisJarr->size + (sizeof(srcArr) / sizeof(srcArr[0]));                   \
		if (newLen > thisJarr->size) {                                                              \
			int tmpSize = dest->size;                                                           \
			do {                                                                                \
				tmpSize *= 2;                                                               \
			} while (newLen > tmpSize);                                                         \
			if ((thisJarr->data = realloc(thisJarr)->data, sizeof(*thisJarr->data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; }                                \
			thisJarr->size = tmpSize;                                                           \
		}                                                                                           \
		memcpy(thisJarr->data + thisJarr->len, srcArr, sizeof(srcArr) / sizeof(srcArr[0]));         \
		thisJarr->len = newLen;                                                                     \
	} while (0)


#define jarrCat(thisJarr, ...)                                                                           \
	do {                                                                                             \
		const int newLen = thisJarr.len + PP_NARG(__VA_ARGS__);                                  \
		if (newLen > thisJarr.size) {                                                            \
			int tmpSize = dest.size;                                                         \
			do {                                                                             \
				tmpSize *= 2;                                                            \
			} while (newLen > tmpSize);                                                      \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; }                             \
			thisJarr.size = tmpSize;                                                         \
		}                                                                                        \
		typeof(thisJarr) tmp[] = { __VA_ARGS__ };                                                \
		memcpy(thisJarr.data + thisJarr.len, tmp, PP_NARG(__VA_ARGS__));                         \
		thisJarr.len = newLen;                                                                   \
	} while (0)

#define jarrCatPtr(thisJarr, ...)                                                                           \
	do {                                                                                                \
		const int newLen = thisJarr->len + PP_NARG(__VA_ARGS__);                                    \
		if (newLen > thisJarr->size) {                                                              \
			int tmpSize = dest->size;                                                           \
			do {                                                                                \
				tmpSize *= 2;                                                               \
			} while (newLen > tmpSize);                                                         \
			if ((thisJarr->data = realloc(thisJarr)->data, sizeof(*thisJarr->data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; }                                \
			thisJarr->size = tmpSize;                                                           \
		}                                                                                           \
		typeof(thisJarr) tmp[] = { __VA_ARGS__ };                                                   \
		memcpy(thisJarr->data + thisJarr->len, tmp, PP_NARG(__VA_ARGS__));                          \
		thisJarr->len = newLen;                                                                     \
	} while (0)

#define jarrPushback(thisJarr, src)                                                                                \
	do {                                                                                                       \
		if (thisJarr.size - thisJarr.len);                                                                 \
		else {                                                                                             \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * 2 * thisJarr.size)); \
			else { perror("jarrPush realloc fails"); return -1; }                                      \
		}                                                                                                  \
		thisJarr.data[thisJarr.len] = src;                                                                 \
		thisJarr.size *= 2;                                                                                \
		++thisJarr.len;                                                                                    \
	} while (0)

#define jarrPushbackPtr(thisJarr, src)                                                                                 \
	do {                                                                                                           \
		if (thisJarr->size - thisJarr->len);                                                                   \
		else {                                                                                                 \
			if ((thisJarr->data = realloc(thisJarr)->data, sizeof(*thisJarr->data) * 2 * thisJarr->size)); \
			else { perror("jarrPush realloc fails"); return -1; }                                          \
		}                                                                                                      \
		thisJarr->data[thisJarr->len] = src;                                                                   \
		thisJarr->size *= 2;                                                                                   \
		++thisJarr->len;                                                                                       \
	} while (0)

int qsortDescend(const void *x, const void *y);
int qsortAscend(const void *y, const void *x);
float qsortDescendFl(const void *x, const void *y);
float qsortAscendFl(const void *y, const void *x);
double qsortDescendDb(const void *x, const void *y);
double qsortAscendDb(const void *y, const void *x);

#endif
