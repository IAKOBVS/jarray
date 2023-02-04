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

#define NEED_MEM_TYPE(CAST) \
	(CAST(thisJarr)->size < 2 * (CAST(thisJarr)->len))

#define REALLOC_FAILS(CAST, TYPE) \
	(!(CAST(thisJarr)->val = realloc(CAST(thisJarr)->val, sizeof(TYPE) * ASSIGN_MAX_TO(CAST(thisJarr)->size, CAST))))
#define MALLOC_FAILS(CAST, TYPE) \
	(!(CAST(thisJarr)->val = malloc(sizeof(TYPE) * ASSIGN_OR_MIN_TO(CAST(thisJarr)->size, CAST))))

int _jarrCat(void *thisJarr, int type, int argc, ...)
{
#define JARR_CAT(STRUCT, TYPE, TYPE_TMP) \
	STRUCT(thisJarr)->len += argc; \
	ERROR_IF((!STRUCT(thisJarr)->size && !(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * (STRUCT(thisJarr)->size = MAX(8, 2 * STRUCT(thisJarr)->len + argc))))) \
	|| (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len) && (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * ASSIGN_MAX_TO(STRUCT(thisJarr)->size, STRUCT)))))); \
	for (int i=STRUCT(thisJarr)->len - argc, j = i + argc; i<j; ++i) { \
		TYPE argv = va_arg(ap, TYPE_TMP); \
		STRUCT(thisJarr)->val[i] = argv; \
	} \
	va_end(ap); \
	return STRUCT(thisJarr)->size
	va_list ap;
	va_start(ap, argc);
	switch (type) {
	case 'i':
		INT(thisJarr)->len += argc;
		ERROR_IF((!INT(thisJarr)->size && !(INT(thisJarr)->val = malloc(sizeof(int) * (INT(thisJarr)->size = MAX(8, 2 * INT(thisJarr)->len + argc)))))
		|| (INT(thisJarr)->size < 2 * (INT(thisJarr)->len) && (!(INT(thisJarr)->val = realloc(INT(thisJarr)->val, sizeof(int) * ASSIGN_MAX_TO(INT(thisJarr)->size, INT))))));
		for (int i=INT(thisJarr)->len - argc, j = i + argc; i<j; ++i) {
			int argv = va_arg(ap, int);
			INT(thisJarr)->val[i] = argv;
		}
		va_end(ap);
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

int _jarrAddArr(void *thisJarr, void *arr, size_t arrLen, int type)
{
#define MEMCPY(TYPE, CAST) \
		memcpy(CAST(thisJarr)->val, arr, arrLen * sizeof(TYPE))
	switch (type) {
	case 'i':
		INT(thisJarr)->len+= arrLen;
		ERROR_IF((!INT(thisJarr)->size && MALLOC_FAILS(INT, int)) || (NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int)));
		MEMCPY(int, INT);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len+= arrLen;
		ERROR_IF((!INT(thisJarr)->size && MALLOC_FAILS(INT, int)) || (NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int)));
		MEMCPY(float, FLOAT);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len+= arrLen;
		ERROR_IF((!INT(thisJarr)->size && MALLOC_FAILS(INT, int)) || (NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int)));
		MEMCPY(double, DOUBLE);
		return DOUBLE(thisJarr)->size;
	}

ERROR:
	perror("");
	return 0;
}

int _jarrAdd(void *thisJarr, void *src, int type)
{
#define ASSIGN_TO_TYPE(TYPE, CAST) \
	CAST(thisJarr)->val[CAST(thisJarr)->len - 1] = *(TYPE *)src
	switch (type) {
	case 'i':
		INT(thisJarr)->len += 1;
		ERROR_IF((!INT(thisJarr)->size && MALLOC_FAILS(INT, int)) || (NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int)));
		ASSIGN_TO_TYPE(int, INT);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len += 1;
		ERROR_IF((!INT(thisJarr)->size && MALLOC_FAILS(INT, int)) || (NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int)));
		ASSIGN_TO_TYPE(float, FLOAT);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len += 1;
		ERROR_IF((!INT(thisJarr)->size && MALLOC_FAILS(INT, int)) || (NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int)));
		ASSIGN_TO_TYPE(double, DOUBLE);
		return DOUBLE(thisJarr)->size;
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
