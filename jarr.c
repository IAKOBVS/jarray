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

#define __jarr_new_alloc(jarr, size)                                                                    \
do {                                                                                          \
	((jarr)->capacity) = MAX((2 * (size)), JARR_MIN_CAP);                                 \
	if ((unlikely(!(((jarr)->data) = malloc(((jarr)->capacity) * JARR_T_SIZE(jarr)))))) { \
		((jarr)->capacity) = 0;                                                       \
		perror("jarr_new malloc failed");                                             \
		return -1;                                                                    \
	}                                                                                     \
} while (0)

int func_1(int x, int y)
{
	return (!!x & !!y) ? 1 : 0;
}

int func_2(int x, int y)
{
	return (x && y) ? 1 : 0;
}

#ifdef JARR_DEBUG
int main()
{
	int var1 = 1;
	int var2 = 99;
}
#endif
