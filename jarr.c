#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

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

ALWAYS_INLINE void jarrDelete(Jarr *thisJarr)
{
	free(thisJarr->data);
}

ALWAYS_INLINE void jarrDeleteClean(Jarr *thisJarr)
{
	free(thisJarr->data);
	thisJarr->data = NULL;
	thisJarr->len = 0;
	thisJarr->size = 0;
}

ALWAYS_INLINE int jarrShrink(Jarr *thisJarr)
{
	if ((thisJarr->data = realloc(thisJarr->data, thisJarr->len * sizeof(thisJarr->data[0])))) {
		thisJarr->size = thisJarr->len;
		return 1;
	}
	perror("jarrShrink realloc failed");
	return 0;
}

ALWAYS_INLINE void jarrPopback(Jarr *thisJarr)
{
	--thisJarr->len;
}

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
