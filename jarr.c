#include <stdio.h>
#include "jarr.h"

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

#include <string.h>
#include <stdlib.h>

int main()
{
	jarray_int_t x;
	jarr_init(x);
	jarr_new(x, 100);
	jarr_cat(x, 3, 1, 3, 4, 5);
	jarr_push_back(x, 99);
	jarr_foreach_index(i, &x)
		printf("--%d\n", x.data[i]);
}
