#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define MIN_SIZE 8

#define ERROR_IF(STATE) \
	if (STATE) \
		goto ERROR

#define CAST_TO(VOID, TYPE) \
	((TYPE)VOID)
#define INT(VOID) \
	CAST_TO(VOID, struct Jarr *)
#define FLOAT(VOID) \
	CAST_TO(VOID, struct JarrFl *)
#define DOUBLE(VOID) \
	CAST_TO(VOID, struct JarrDb *)

#define JARR_CAT(STRUCT, TYPE, TYPE_TMP) \
	ERROR_IF((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * (STRUCT(thisJarr)->len + argc)))))) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len + argc)))))))); \
	for (int i=STRUCT(thisJarr)->len, j = i + argc; i<j; ++i) { \
		TYPE argv = va_arg(ap, TYPE_TMP); \
		STRUCT(thisJarr)->val[i] = argv; \
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
	}
ERROR:
	va_end(ap);
	perror("");
	return 0;
}

#define JARR_ADD_ARR(STRUCT, TYPE) \
	STRUCT(thisJarr)->len+= arrLen; \
	ERROR_IF((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * STRUCT(thisJarr)->len))))) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)))))))); \
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
	ERROR_IF((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * STRUCT(thisJarr)->len))))) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)))))))); \
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

int isJarr(Jarr *thisJarr)
{
	if (!*((unsigned char *)&*thisJarr))
		return 0;
	return 1;
}
