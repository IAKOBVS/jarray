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

ALWAYS_INLINE int qsortAscend(const void *x, const void *y)
{
	return *(int *)x  - *(int *)y;
}

ALWAYS_INLINE float qsortAscendFl(const void *x, const void *y)
{
	return *(float *)x  - *(float *)y;
}

ALWAYS_INLINE double qsortAscendDb(const void *x, const void *y)
{
	return *(double *)x  - *(double *)y;
}

ALWAYS_INLINE int qsortDescend(const void *x, const void *y)
{
	return *(int *)y  - *(int *)x;
}

ALWAYS_INLINE float qsortDescendFl(const void *x, const void *y)
{
	return *(float *)y  - *(float *)x;
}

ALWAYS_INLINE double qsortDescendDb(const void *x, const void *y)
{
	return *(double *)y  - *(double *)x;
}

int main()
{
	JarrInt hello;
	jarrInit(hello);
	jarrNew(hello, 9, 3, 3 ,4);
	printf("%d\n", hello.data[0]);
}
