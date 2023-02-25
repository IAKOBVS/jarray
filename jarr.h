#ifndef JARR_H_DEF
#define JARR_H_DEF

#include "/home/james/c/vargc.h"
#include <stddef.h>

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

#define JARR_NEW(JARR, TYPE, ...) \
	do { \
		JARR.len = PP_NARG(__VA_ARGS__); \
		const size_t tmpSize = MAX(2 * JARR.len, JARR_MIN_SIZE); \
		if (unlikely(!(JARR.data = malloc(sizeof(JARR.data[0]) * tmpSize)))) \
			{ perror("jarrNew malloc failed"); return -1; } \
		JARR.size = tmpSize; \
		typeof(JARR.data) = { __VA_ARGS__ }; \
		memcpy(jarr.data, tmp, JARR.len); \
	} while (0)

#define jarrNew(JARR, ...) \
	JARR_NEW(JARR, int, __VA_ARGS__)
#define jarrNewDb(JARR, ...) \
	JARR_NEW(JARR, double, __VA_ARGS__)
#define jarrNewFl(JARR, ...) \
	JARR_NEW(JARR, float, __VA_ARGS__)

#define JARR_INIT(JARR, JARR_STRUCT, TYPE_NAME) \
	JARR_STRUCT JARR = { \
		.size = 0, \
		.len = 0 \
	}

#define jarrInit(JARR) \
	JARR_INIT(JARR, Jarr, int)
#define jarrInitFl(JARR) \
	JARR_INIT(JARR, JarrFl, float)
#define jarrInitDb(JARR) \
	JARR_INIT(JARR, JarrDb, double)

#define jarrPr(JARR) \
	for (int i=0; i<JARR.len; ++i) \
		printf("%f\n", *(double *)JARR.data)

#define JARR_STRUCT(JARR_NAME, TYPE) \
typedef struct JARR_NAME { \
	int type; \
	TYPE *data; \
	size_t len; \
	size_t size; \
} JARR_NAME

JARR_STRUCT(Jarr, int);
JARR_STRUCT(JarrDb, double);
JARR_STRUCT(JarrFl, float);

#define jarrDelete(thisJarr) free(thisJarr.data)
#define jarrDeletePtr(thisJarr) free(thisJarr->data)

#define jarrDeleteClean(thisJarr) \
	do { \
		free(thisJarr.data); \
		thisJarr.data = NULL; \
		thisJarr.len = 0; \
		thisJarr.size = 0; \
	} while (0)

#define jarrDeleteCleanPtr(thisJarr) \
	do { \
		free(thisJarr->data); \
		thisJarr->data = NULL; \
		thisJarr->len = 0; \
		thisJarr->size = 0; \
	} while (0)

#define jarrPopback(thisJarr) --thisJarr.len
#define jarrPopbackPtr(thisJarr) --thisJarr->len

#define jarrShrink(thisJarr) \
	do { \
		if ((thisJarr->data = realloc(thisJarr->data, thisJarr->len * sizeof(thisJarr->data[0])))) \
			thisJarr->size = thisJarr->len; \
		else { \
			free(thisJarr->data); \
			perror("jarrShrink realloc failed"); \
			return -1; \
		} \
	} while (0)

#define jarrShrinkPtr(thisJarr) \
	do { \
		if ((thisJarr.data = realloc(thisJarr.data, thisJarr.len * sizeof(thisJarr.data[0])))) \
			thisJarr.size = thisJarr.len; \
		else { \
			free(thisJarr.data); \
			perror("jarrShrink realloc failed"); \
			return -1; \
		} \
	} while (0)

#define jarrAppend(thisJarr, srcArr) \
	do { \
		const int newLen = thisJarr.size + (sizeof(srcArr) / sizeof(srcArr[0])); \
		if (newLen > thisJarr.size) { \
			int tmpSize = dest.size; \
			do { \
				tmpSize *= 2; \
			} while (newLen > tmpSize); \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; } \
			thisJarr.size = tmpSize; \
		} \
		memcpy(thisJarr.data + thisJarr.len, srcArr, sizeof(srcArr) / sizeof(srcArr[0])); \
		thisJarr.len = newLen; \
	} while (0)

#define jarrAppendPtr(thisJarr, srcArr) \
	do { \
		const int newLen = thisJarr->size + (sizeof(srcArr) / sizeof(srcArr[0])); \
		if (newLen > thisJarr->size) { \
			int tmpSize = dest->size; \
			do { \
				tmpSize *= 2; \
			} while (newLen > tmpSize); \
			if ((thisJarr->data = realloc(thisJarr)->data, sizeof(*thisJarr->data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; } \
			thisJarr->size = tmpSize; \
		} \
		memcpy(thisJarr->data + thisJarr->len, srcArr, sizeof(srcArr) / sizeof(srcArr[0])); \
		thisJarr->len = newLen; \
	} while (0)


#define jarrCat(thisJarr, ...) \
	do { \
		const int newLen = thisJarr.len + PP_NARG(__VA_ARGS__); \
		if (newLen > thisJarr.size) { \
			int tmpSize = dest.size; \
			do { \
				tmpSize *= 2; \
			} while (newLen > tmpSize); \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; } \
			thisJarr.size = tmpSize; \
		} \
		typeof(thisJarr) tmp[] = { __VA_ARGS__ }; \
		memcpy(thisJarr.data + thisJarr.len, tmp, PP_NARG(__VA_ARGS__)); \
		thisJarr.len = newLen; \
	} while (0)

#define jarrCatPtr(thisJarr, ...) \
	do { \
		const int newLen = thisJarr->len + PP_NARG(__VA_ARGS__); \
		if (newLen > thisJarr->size) { \
			int tmpSize = dest->size; \
			do { \
				tmpSize *= 2; \
			} while (newLen > tmpSize); \
			if ((thisJarr->data = realloc(thisJarr)->data, sizeof(*thisJarr->data) * tmpSize)); \
			else { perror("jarrCat realloc fails"); return -1; } \
			thisJarr->size = tmpSize; \
		} \
		typeof(thisJarr) tmp[] = { __VA_ARGS__ }; \
		memcpy(thisJarr->data + thisJarr->len, tmp, PP_NARG(__VA_ARGS__)); \
		thisJarr->len = newLen; \
	} while (0)

#define jarrPushback(thisJarr, src) \
	do { \
		if (thisJarr.size - thisJarr.len); \
		else { \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * 2 * thisJarr.size)); \
			else { perror("jarrPush realloc fails"); return -1; } \
		} \
		thisJarr.data[thisJarr.len] = src; \
		thisJarr.size *= 2; \
		++thisJarr.len; \
	} while (0)

#define jarrPushbackPtr(thisJarr, src) \
	do { \
		if (thisJarr->size - thisJarr->len); \
		else { \
			if ((thisJarr->data = realloc(thisJarr)->data, sizeof(*thisJarr->data) * 2 * thisJarr->size)); \
			else { perror("jarrPush realloc fails"); return -1; } \
		} \
		thisJarr->data[thisJarr->len] = src; \
		thisJarr->size *= 2; \
		++thisJarr->len; \
	} while (0)

int qsortDescend(const void *x, const void *y);
int qsortAscend(const void *y, const void *x);
float qsortDescendFl(const void *x, const void *y);
float qsortAscendFl(const void *y, const void *x);
double qsortDescendDb(const void *x, const void *y);
double qsortAscendDb(const void *y, const void *x);

#endif
