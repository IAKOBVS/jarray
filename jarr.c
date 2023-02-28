#include "jarr.h"
#include <assert.h>
#include <stdint.h>

int qsortAscend(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(int *)x  - *(int *)y;
}

float qsortAscendFl(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(float *)x  - *(float *)y;
}

double qsortAscendDb(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(double *)x  - *(double *)y;
}

int qsortDescend(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(int *)y  - *(int *)x;
}

float qsortDescendFl(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(float *)y  - *(float *)x;
}

double qsortDescendDb(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(double *)y  - *(double *)x;
}

#if (defined(__GNUC__) || defined(__clang__))

ALWAYS_INLINE size_t near_powoftwo64(unsigned int x)
{
    return (1ULL << (sizeof(x) * 8 - __builtin_clzll((x) - 1)));
}

ALWAYS_INLINE size_t near_powoftwo32(unsigned int x)
{
    return (1UL << (sizeof(x) * 8 - __builtin_clz((x) - 1)));
}

#else

ALWAYS_INLINE size_t near_powoftwo64(unsigned int x)
{
	uint64_t p = 1;
	while (p < (uint64_t)(x)) p <<= 1;
	return p;
}

ALWAYS_INLINE size_t near_powoftwo32(unsigned int x)
{
	size_t p = 1; \
        while (p < (size_t)(x)) p <<= 1; \
        p; \
}

#endif

/* unsigned int nearest_power_of_two(unsigned int x) { */
/*     x--; */
/*     x |= x >> 1; */
/*     x |= x >> 2; */
/*     x |= x >> 4; */
/*     x |= x >> 8; */
/*     x |= x >> 16; */
/*     return x+1; */
/* } */

/* int main() */
/* { */
/* } */
