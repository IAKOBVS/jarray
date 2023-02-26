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
	jarray_int_t t;
	(&t)->capacity = MAX(2 * PP_NARG(__VA_ARGS__), JARR_MIN_CAP);   \
	if (((&t)->data = malloc((&t)->capacity * JARR_T_SIZE((&t))))); \
	else {                                                          \
		(&t)->capacity = 0;                                     \
		perror("(&t)_new malloc failed");                       \
		return -1;                                              \
	}                                                               \
	(&t)->size = PP_NARG(__VA_ARGS__);                              \
	typeof(*(&t)->data) tmp[] = { 1, 2 };                    \
	memcpy((&t)->data, tmp, sizeof(tmp));                           \
	printf("%d\n", t.data[0]);
	printf("%d\n", t.data[1]);
}
