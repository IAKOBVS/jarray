#include "jarr.h"

/* int qsortAscend(const void *RESTRICT x, const void *RESTRICT y) */
/* { */
/* 	return *(int *)x  - *(int *)y; */
/* } */

/* float qsortAscendFl(const void *RESTRICT x, const void *RESTRICT y) */
/* { */
/* 	return *(float *)x  - *(float *)y; */
/* } */

/* double qsortAscendDb(const void *RESTRICT x, const void *RESTRICT y) */
/* { */
/* 	return *(double *)x  - *(double *)y; */
/* } */

/* int qsortDescend(const void *RESTRICT x, const void *RESTRICT y) */
/* { */
/* 	return *(int *)y  - *(int *)x; */
/* } */

/* float qsortDescendFl(const void *RESTRICT x, const void *RESTRICT y) */
/* { */
/* 	return *(float *)y  - *(float *)x; */
/* } */

/* double qsortDescendDb(const void *RESTRICT x, const void *RESTRICT y) */
/* { */
/* 	return *(double *)y  - *(double *)x; */
/* } */
#include <stdarg.h>

int private_jarr_assign_va_args(void* jarr, ...)
{
	va_list ap;
	va_start(ap, jarr);
	va_arg(ap, void*);
	va_end(ap);
}

#ifdef JARR_DEBUG
int main ()
{
}
#endif
