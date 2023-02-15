#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"
#include "/home/james/c/jString/jstr.h"

#define MIN_SIZE 8

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
	if ((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * (STRUCT(thisJarr)->len + argc))))) && (STRUCT(thisJarr)->size = 0, 1)) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len + argc)))))))) \
		goto ERROR; \
	{ \
	int i = STRUCT(thisJarr)->len; \
	for (void *argv = va_arg(ap, void *); argv != NULL; argv = va_arg(ap, void *), ++i) \
		STRUCT(thisJarr)->val[i] = *(TYPE_TMP *)argv; \
	} \
	va_end(ap); \
	STRUCT(thisJarr)->len += argc; \
	return STRUCT(thisJarr)->size \

int _jarrCat(void *thisJarr, int type, int argc, ...)
{
	va_list ap;
	va_start(ap, argc);
	switch (type) {
	case 'i':
		JARR_CAT(INT, int, int);
	case 'f':
		JARR_CAT(FLOAT, float, double);
	case 'd':
		JARR_CAT(DOUBLE, double, double);
	/* case 's': */
	/* 	if ((!JSTR(thisJarr)->size && !(JSTR(thisJarr)->val = malloc(sizeof(Jstr) * (JSTR(thisJarr)->size = MAX(MIN_SIZE, 2 * (JSTR(thisJarr)->len + argc))))) && (JSTR(thisJarr)->size = 0, 1)) */
	/* 	|| (JSTR(thisJarr)->size < 2 * (JSTR(thisJarr)->len) && (!(JSTR(thisJarr)->val = realloc(JSTR(thisJarr)->val, sizeof(Jstr) * (JSTR(thisJarr)->size = MAX(2 * JSTR(thisJarr)->size, 2 * (JSTR(thisJarr)->len + argc)))))))) */
	/* 		goto ERROR; */
	/* 	for (int i = JSTR(thisJarr)->len, j = i + argc; i<j; ++i) { */
	/* 		Jstr argv = va_arg(ap, Jstr); */
	/* 		JSTR(thisJarr)->val[i] = argv; */
	/* 		JSTR(thisJarr)->val[i].len = argv.len; */
	/* 		JSTR(thisJarr)->val[i].size = argv.size; */
	/* 	} */
	/* 	va_end(ap); */
	/* 	JSTR(thisJarr)->len += argc; */
	/* 	return JSTR(thisJarr)->size; */
	}

ERROR:
	va_end(ap);
	perror("");
	return 0;
}

#define JARR_ADD_ARR(STRUCT, TYPE) \
	STRUCT(thisJarr)->len+= arrLen; \
	if ((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * STRUCT(thisJarr)->len)))) && (STRUCT(thisJarr)->size = 0, 1)) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)))))))) \
		goto ERROR; \
	memcpy(STRUCT(thisJarr)->val, arr, arrLen * sizeof(TYPE)); \
	return STRUCT(thisJarr)->size

int _jarrAddArr(void *thisJarr, void *arr, size_t arrLen, int type)
{
	switch (type) {
	case 'i':
		JARR_ADD_ARR(INT, int);
	case 'f':
		JARR_ADD_ARR(FLOAT, float);
	case 'd':
		JARR_ADD_ARR(DOUBLE, double);
	}

ERROR:
	perror("");
	return 0;
}

#define JARR_ADD(STRUCT, TYPE) \
	STRUCT(thisJarr)->len += 1; \
	if ((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * STRUCT(thisJarr)->len))))) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)))))))) \
		goto ERROR; \
	STRUCT(thisJarr)->val[STRUCT(thisJarr)->len - 1] = *(TYPE *)src; \
	return STRUCT(thisJarr)->size

int _jarrAdd(void *thisJarr, void *src, int type)
{
	switch (type) {
	case 'i':
		JARR_ADD(INT, int);
	case 'f':
		JARR_ADD(FLOAT, float);
	case 'd':
		JARR_ADD(DOUBLE, double);
	}

ERROR:
	perror("");
	return 0;
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

int isJarr(Jarr *thisJarr)
{
	if (!*((unsigned char *)&*thisJarr))
		return 0;
	return 1;
}
