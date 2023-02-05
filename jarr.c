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

#define ASSIGN_MAX_TO(VAR, CAST) \
	(VAR = MAX(2 * CAST(thisJarr)->size, 2 * CAST(thisJarr)->len))
#define ASSIGN_OR_MIN_TO(VAR, CAST) \
	(VAR = MAX(8, 2 * CAST(thisJarr)->len))

#define JARR_CAT(STRUCT, TYPE, TYPE_TMP) \
	if ((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(8, 2 * STRUCT(thisJarr)->len + argc))))) \
	|| (INT(thisJarr)->size < 2 * (INT(thisJarr)->len) && (!(INT(thisJarr)->val = realloc(INT(thisJarr)->val, sizeof(int) * (INT(thisJarr)->size = MAX(2 * INT(thisJarr)->size, 2 * (INT(thisJarr)->len + argc)))))))) \
		goto ERROR; \
	for (size_t i=STRUCT(thisJarr)->len, j = i + argc; i<j; ++i) { \
		TYPE argv = va_arg(ap, TYPE_TMP); \
		STRUCT(thisJarr)->val[i] = argv; \
	} \
	va_end(ap); \
	STRUCT(thisJarr)->len += argc; \
	return STRUCT(thisJarr)->size

int _jarrCat(void *thisJarr, int type, int argc, ...)
{
	va_list ap;
	va_start(ap, argc);
	switch (type) {
	case 'i':
		if ((!INT(thisJarr)->size && !(INT(thisJarr)->val = malloc(sizeof(int) * (INT(thisJarr)->size = MAX(MIN_SIZE, 2 * (INT(thisJarr)->len + argc))))))
		|| (INT(thisJarr)->size < 2 * (INT(thisJarr)->len) && (!(INT(thisJarr)->val = realloc(INT(thisJarr)->val, sizeof(int) * (INT(thisJarr)->size = MAX(2 * INT(thisJarr)->size, 2 * (INT(thisJarr)->len + argc))))))))
			goto ERROR;
		for (int i=INT(thisJarr)->len, j = i + argc; i<j; ++i) {
			int argv = va_arg(ap, int);
			INT(thisJarr)->val[i] = argv;
		}
		va_end(ap);
		INT(thisJarr)->len += argc;
		return INT(thisJarr)->size;
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
	if ((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(MIN_SIZE, 2 * STRUCT(thisJarr)->len))))) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)))))))) \
		goto ERROR; \
	memcpy(STRUCT(thisJarr)->val, arr, arrLen * sizeof(TYPE)); \
	return STRUCT(thisJarr)->size;

int _jarrAddArr(void *thisJarr, void *arr, size_t arrLen, int type)
{
	switch (type) {
	case 'i':
		INT(thisJarr)->len+= arrLen;
		if ((!INT(thisJarr)->size && !(INT(thisJarr)->val = malloc(sizeof(int) * (INT(thisJarr)->size = MAX(MIN_SIZE, 2 * INT(thisJarr)->len)))))
		|| (INT(thisJarr)->size < 2 * (INT(thisJarr)->len) && (!(INT(thisJarr)->val = realloc(INT(thisJarr)->val, sizeof(int) * (INT(thisJarr)->size = MAX(2 * INT(thisJarr)->size, 2 * (INT(thisJarr)->len))))))))
			goto ERROR;
		memcpy(INT(thisJarr)->val, arr, arrLen * sizeof(int));
		return INT(thisJarr)->size;
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
	STRUCT(thisJarr)->val[STRUCT(thisJarr)->len - 1] = *(TYPE *)src

int _jarrAdd(void *thisJarr, void *src, int type)
{
	switch (type) {
	case 'i':
		INT(thisJarr)->len += 1;
		if ((!INT(thisJarr)->size && !(INT(thisJarr)->val = malloc(sizeof(int) * (INT(thisJarr)->size = MAX(MIN_SIZE, 2 * INT(thisJarr)->len)))))
		|| (INT(thisJarr)->size < 2 * (INT(thisJarr)->len) && (!(INT(thisJarr)->val = realloc(INT(thisJarr)->val, sizeof(int) * (INT(thisJarr)->size = MAX(2 * INT(thisJarr)->size, 2 * (INT(thisJarr)->len))))))))
			goto ERROR;
		INT(thisJarr)->val[INT(thisJarr)->len - 1] = *(int *)src;
		return INT(thisJarr)->size;
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
