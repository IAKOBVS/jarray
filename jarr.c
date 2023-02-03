#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define ERROR_IF(STATE) \
	if (STATE) \
		goto ERROR

#define GET_ALLOC_SIZE(VAR, FUNC_NAME) \
	(VAR = MAX(2 * FUNC_NAME(thisJarr)->size, 2 * FUNC_NAME(thisJarr)->len))

#define NEED_MEM_TYPE(FUNC_NAME) \
	(FUNC_NAME(thisJarr)->size < 2 * FUNC_NAME(thisJarr)->len)

#define CAST_TO(VOID, TYPE) \
	((TYPE)VOID)

#define INT(VOID) \
	CAST_TO(VOID, struct Jarr *)

#define FLOAT(VOID) \
	CAST_TO(VOID, struct JarrFl *)

#define DOUBLE(VOID) \
	CAST_TO(VOID, struct JarrDb *)

#define REALLOC_FAILS(FUNC_NAME, TYPE) \
	(!(FUNC_NAME(thisJarr)->val = realloc(FUNC_NAME(thisJarr)->val, sizeof(TYPE) * GET_ALLOC_SIZE(FUNC_NAME(thisJarr)->size, FUNC_NAME))))


int _jarrCat(void *thisJarr, int type, int argc, ...)
{
#define LOOP_ASSIGN(TYPE, TYPE_TMP, FUNC_NAME) \
	do { \
		for (int i=(FUNC_NAME(thisJarr)->len), j = i + argc; i<j; ++i) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			FUNC_NAME(thisJarr)->val[i] = argv; \
		} \
	} while (0)
	va_list ap;
	va_start(ap, argc);
	switch (type) {
	case 'i':
		ERROR_IF(NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int));
		LOOP_ASSIGN(int, int, INT);
		INT(thisJarr)->len += argc;
		va_end(ap);
		return INT(thisJarr)->size;
	case 'f':
		ERROR_IF(NEED_MEM_TYPE(FLOAT) && REALLOC_FAILS(FLOAT, float));
		LOOP_ASSIGN(float, double, FLOAT);
		FLOAT(thisJarr)->len += argc;
		va_end(ap);
		return FLOAT(thisJarr)->size;
	case 'd':
		ERROR_IF(NEED_MEM_TYPE(DOUBLE) && REALLOC_FAILS(DOUBLE, double));
		LOOP_ASSIGN(double, double, DOUBLE);
		DOUBLE(thisJarr)->len += argc;
		va_end(ap);
		return DOUBLE(thisJarr)->size;
	}
ERROR:
	va_end(ap);
	perror("");
	return 0;
}

int _jarrAddArr(void *thisJarr, void *arr, size_t arrLen, int type)
{
#define MEMCPY(TYPE, FUNC_NAME) \
		memcpy(FUNC_NAME(thisJarr)->val, arr, arrLen * sizeof(TYPE))
	switch (type) {
	case 'i':
		INT(thisJarr)->len+= arrLen;
		ERROR_IF(NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int));
		MEMCPY(int, INT);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len+= arrLen;
		ERROR_IF(NEED_MEM_TYPE(FLOAT) && REALLOC_FAILS(FLOAT, float));
		MEMCPY(float, FLOAT);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len+= arrLen;
		ERROR_IF(NEED_MEM_TYPE(DOUBLE) && REALLOC_FAILS(DOUBLE, double));
		MEMCPY(double, DOUBLE);
		return DOUBLE(thisJarr)->size;
	}

ERROR:
	perror("");
	return 0;
}

int _jarrAdd(void *thisJarr, void *src, int type)
{
#define ASSIGN_TO_TYPE(TYPE, FUNC_NAME) \
	FUNC_NAME(thisJarr)->val[FUNC_NAME(thisJarr)->len - 1] = *(TYPE *)src
	switch (type) {
	case 'i':
		INT(thisJarr)->len += 1;
		ERROR_IF(NEED_MEM_TYPE(INT) && REALLOC_FAILS(INT, int));
		ASSIGN_TO_TYPE(int, INT);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len += 1;
		ERROR_IF(NEED_MEM_TYPE(FLOAT) && REALLOC_FAILS(FLOAT, float));
		ASSIGN_TO_TYPE(float, FLOAT);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len += 1;
		ERROR_IF(NEED_MEM_TYPE(DOUBLE) && REALLOC_FAILS(DOUBLE, double));
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
