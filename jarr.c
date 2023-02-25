#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"
#include "/home/james/c/jString/jstr.h"

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
# define RESTRICT restrict
#elif defined(__GNUC__) || defined(__clang__)
# define RESTRICT __restrict__
#elif defined(_MSC_VER)
# define RESTRICT __restrict
#else
# define RESTRICT
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
    #define ALWAYS_INLINE __forceinline inline
#else
    #define ALWAYS_INLINE inline
#endif

#if defined(__PRETTY_FUNCTION__)
	#define CURR_FUNC __PRETTY_FUNCTION__
#elif defined(__FUNCTION__)
	#define CURR_FUNC __FUNCTION__
#elif defined(__func__)
	#define CURR_FUNC __func__
#else
	#define CURR_FUNC ""
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 3)) || (defined(__clang__) && __has_builtin(__builtin_expect))
  #define likely(x) __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else
  #define likely(x) (x)
  #define unlikely(x) (x)
#endif

#define MIN_SIZE 8
#define MAX(a,b) ((a)>(b)?(a):(b))

#define CAST_TO(VOID, TYPE) \
	((TYPE)VOID)
#define INT(VOID) \
	CAST_TO(VOID, struct Jarr *)
#define FLOAT(VOID) \
	CAST_TO(VOID, struct JarrFl *)
#define DOUBLE(VOID) \
	CAST_TO(VOID, struct JarrDb *)
#define JSTR(VOID) \
	CAST_TO(VOID, struct JarrJstr *)

#define JARR_CAT(STRUCT, TYPE, TYPE_TMP) \
	do { \
		const size_t newLen = STRUCT(thisJarr)->len + argc; \
		if (!STRUCT(thisJarr)->size) { \
			const size_t tmpSize = MAX(MIN_SIZE, 2 * newLen); \
			if (unlikely(!(STRUCT(thisJarr)->data = malloc(sizeof(TYPE) * tmpSize)))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} else if (STRUCT(thisJarr)->size < newLen) { \
			size_t tmpSize = STRUCT(thisJarr)->size; \
			do { \
				tmpSize *= 2; \
			} while (STRUCT(thisJarr)->size < newLen); \
			if (unlikely(!(STRUCT(thisJarr)->data = realloc(STRUCT(thisJarr)->data, sizeof(TYPE) * tmpSize)))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} \
		void *RESTRICT argv; \
		for (size_t i = STRUCT(thisJarr)->len;; ++i) { \
			argv = va_arg(ap, void *); \
			if (argv) \
				STRUCT(thisJarr)->data[i] = *(TYPE_TMP *)argv; \
			else \
				break; \
		} \
		STRUCT(thisJarr)->len = newLen; \
	} while (0)

#define STRUCT_TYPE(TYPE) _Generic((TYPE), \
	int: DECLARE_JARR(jarrPtr), \
	double: DECLARE_JARRDB(jarrPtr), \
	float: DECLARE_JARRFL(jarrPtr); \
	)

#define DECLARE_JARR(PTR_NAME) Jarr PTR_NAME
#define DECLARE_JARRDB(PTR_NAME) JarrDb PTR_NAME
#define DECLARE_JARRFL(PTR_NAME) JarrFl PTR_NAME

/* int private_jarrCat(void *thisJarr, int type, int argc, ...) */
/* { */
/* 	va_list ap; */
/* 	va_start(ap, argc); */
/* 	switch (type) { */
/* 	case 'i': */
/* 		JARR_CAT(INT, int, int); */
/* 		break; */
/* 	case 'f': */
/* 		JARR_CAT(FLOAT, float, double); */
/* 		break; */
/* 	case 'd': */
/* 		JARR_CAT(DOUBLE, double, double); */
/* 	} */
/* 	va_end(ap); */
/* 	return 1; */

/* ERROR: */
/* 	va_end(ap); */
/* 	perror(""); */
/* 	return 0; */
/* } */

/* case 's': */
/* 	{ */
/* 		size_t tmpLen = JSTR(thisJarr)->len + argc; */
/* 		if (JSTR(thisJarr)->size < 2 * tmpLen) { */
/* 			size_t tmpSize = MAX(MIN_SIZE, tmpLen); */
/* 			if (unlikely(!(JSTR(thisJarr)->data = realloc(JSTR(thisJarr)->data, sizeof(Jstr) * tmpSize)))) */
/* 				goto ERROR; */
/* 			JSTR(thisJarr)->size = tmpSize; */
/* 		} */
/* 		for (size_t i = JSTR(thisJarr)->len;; ++i) { */
/* 			char *argv = va_arg(ap, char *); */
/* 			if (argv) { */
/* 				JSTR(thisJarr)->data[i] = *(Jstr *)argv; */
/* 				JSTR(thisJarr)->data[i].len = (*(Jstr *)argv).len; */
/* 				JSTR(thisJarr)->data[i].size = (*(Jstr *)argv).size; */
/* 			} else { */
/* 				break; */
/* 			} */
/* 		} */
/* 	} */

#define JARR_ADD_ARR(STRUCT, TYPE) \
	{ \
		size_t newLen = STRUCT(thisJarr)->len + arrLen; \
		if (!STRUCT(thisJarr)->size) { \
			const size_t tmpSize = MAX(MIN_SIZE, 2 * newLen); \
			if (unlikely(!(STRUCT(thisJarr)->data = malloc(sizeof(TYPE) * tmpSize)))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} else if (STRUCT(thisJarr)->size < newLen) { \
			size_t tmpSize = STRUCT(thisJarr)->size; \
			do { \
				tmpSize *= 2; \
			} while (STRUCT(thisJarr)->size < newLen); \
			if (unlikely(!(STRUCT(thisJarr)->data = realloc(STRUCT(thisJarr)->data, sizeof(TYPE) * tmpSize)))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} \
		memcpy(STRUCT(thisJarr)->data + STRUCT(thisJarr)->len, arr, arrLen * sizeof(TYPE)); \
		STRUCT(thisJarr)->len = newLen; \
	} \
	return 1

/* int private_jarrPushArr(void *thisJarr, void *arr, size_t arrLen, int type) */
/* { */
/* 	switch (type) { */
/* 	case 'i': */
/* 		JARR_ADD_ARR(INT, int); */
/* 	case 'f': */
/* 		JARR_ADD_ARR(FLOAT, float); */
/* 	case 'd': */
/* 		JARR_ADD_ARR(DOUBLE, double); */
/* 	} */

/* ERROR: */
/* 	perror(""); */
/* 	return 0; */
/* } */

#define JARR_ADD(STRUCT, TYPE) \
	{ \
		const size_t tmpLen = STRUCT(thisJarr)->len + 1; \
		if (!STRUCT(thisJarr)->size) { \
			const size_t tmpSize = MAX(MIN_SIZE, 2 * tmpLen); \
			if (!(STRUCT(thisJarr)->data = malloc(sizeof(TYPE) * tmpSize))) STRUCT(thisJarr)->size = tmpSize; \
				goto ERROR; \
		} else if (STRUCT(thisJarr)->size < 2 * tmpLen) { \
			const size_t tmpSize = MAX(2 * STRUCT(thisJarr)->size, 2 * tmpLen); \
			if (!(STRUCT(thisJarr)->data = realloc(STRUCT(thisJarr)->data, sizeof(TYPE) * tmpSize))) STRUCT(thisJarr)->size = tmpSize; \
				goto ERROR; \
		} \
		STRUCT(thisJarr)->data[STRUCT(thisJarr)->len - 1] = *(TYPE *)src; \
		STRUCT(thisJarr)->len = tmpLen; \
	} \
	return 1

/* int private_jarrPush(void *thisJarr, void *src, int type) */
/* { */
/* 	switch (type) { */
/* 	case 'i': */
/* 		JARR_ADD(INT, int); */
/* 	case 'f': */
/* 		JARR_ADD(FLOAT, float); */
/* 	case 'd': */
/* 		JARR_ADD(DOUBLE, double); */
/* 	} */

/* ERROR: */
/* 	perror(""); */
/* 	return 0; */
/* } */

#define jarrPush(thisJarr, src) \
	do { \
		if (thisJarr.size + 1 != thisJarr.len); \
		else { \
			if ((thisJarr.data = realloc(thisJarr).data, sizeof(*thisJarr.data) * 2 * thisJarr.size)) \
			else { perror("jarr realloc fails"); return -1; } \
		} \
		thisJarr.data[thisJarr.len] = src; \
		thisJarr.size *= 2; \
		++thisJarr.len; \
	} while (0)

int qsortAscend(const void *x, const void *y)
{
	return *(int *)x  - *(int *)y;
}

float qsortAscendFl(const void *x, const void *y)
{
	return *(float *)x  - *(float *)y;
}

double qsortAscendDb(const void *x, const void *y)
{
	return *(double *)x  - *(double *)y;
}

int qsortDescend(const void *x, const void *y)
{
	return *(int *)y  - *(int *)x;
}

float qsortDescendFl(const void *x, const void *y)
{
	return *(float *)y  - *(float *)x;
}

double qsortDescendDb(const void *x, const void *y)
{
	return *(double *)y  - *(double *)x;
}
