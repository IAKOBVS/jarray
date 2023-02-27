#include <stdio.h>

#include "jarr.h"

#define MIN_SIZE 8

ALWAYS_INLINE int qsortAscend(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(int *)x  - *(int *)y;
}

ALWAYS_INLINE float qsortAscendFl(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(float *)x  - *(float *)y;
}

ALWAYS_INLINE double qsortAscendDb(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(double *)x  - *(double *)y;
}

ALWAYS_INLINE int qsortDescend(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(int *)y  - *(int *)x;
}

ALWAYS_INLINE float qsortDescendFl(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(float *)y  - *(float *)x;
}

ALWAYS_INLINE double qsortDescendDb(const void *RESTRICT x, const void *RESTRICT y)
{
	return *(double *)y  - *(double *)x;
}

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	jarray_int_t x;
	jarr_init(&x);
	jarr_new(&x, 100);
	jarr_cat(&x, 1, 2, 3, 4, 5);
	jarr_foreach_index(i, &x)
		printf("--%d\n", x.data[i]);
	int end = jarr_end(x);
	printf("%d\n", end);
}
