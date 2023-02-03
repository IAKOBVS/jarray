#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2

#define GET_ALLOC_SIZE(VAR, FUNC_NAME) \
	VAR = MAX(2 * FUNC_NAME(thisJarr)->size, 2 * FUNC_NAME(thisJarr)->len)

#define IF_NEED_MEM(FUNC_NAME) \
	if (FUNC_NAME(thisJarr)->size < 2 * FUNC_NAME(thisJarr)->len)

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

#define REALLOC_FAILS(FUNC_NAME) \
	!(FUNC_NAME(thisJarr)->val = realloc(FUNC_NAME(thisJarr)->val, FUNC_NAME(thisJarr)->typeSize * (GET_ALLOC_SIZE(FUNC_NAME(thisJarr)->size, FUNC_NAME))))


int _jarrCat(void *thisJarr, int type, int argc, ...)
{
#define LOOP_ASSIGN(TYPE, TYPE_TMP, FUNC_NAME) \
	do { \
		for (int i=0; i<argc; ++i) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			FUNC_NAME(thisJarr)->val[i] = argv; \
		} \
	} while (0)
	va_list ap;
	va_start(ap, argc);
	switch (type) {
	case 'i':
		INT(thisJarr)->len += argc;
		IF_NEED_MEM(INT)
			ERROR_IF(REALLOC_FAILS(INT));
		LOOP_ASSIGN(int, int, INT);
		va_end(ap);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len += argc;
		IF_NEED_MEM(FLOAT)
			ERROR_IF(REALLOC_FAILS(FLOAT));
		LOOP_ASSIGN(float, double, FLOAT);
		va_end(ap);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len += argc;
		IF_NEED_MEM(DOUBLE)
			ERROR_IF(REALLOC_FAILS(DOUBLE));
		LOOP_ASSIGN(double, double, DOUBLE);
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
#define MEMCPY(FUNC_NAME) \
		memcpy(FUNC_NAME(thisJarr)->val, arr, arrLen * FUNC_NAME(thisJarr)->typeSize)
	switch (type) {
	case 'i':
		INT(thisJarr)->len+= arrLen;
		IF_NEED_MEM(INT)
			ERROR_IF(REALLOC_FAILS(INT));
		MEMCPY(INT);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len+= arrLen;
		IF_NEED_MEM(FLOAT)
			ERROR_IF(REALLOC_FAILS(FLOAT));
		MEMCPY(FLOAT);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len+= arrLen;
		IF_NEED_MEM(DOUBLE)
			ERROR_IF(REALLOC_FAILS(DOUBLE));
		MEMCPY(DOUBLE);
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
		IF_NEED_MEM(INT)
			ERROR_IF(REALLOC_FAILS(INT));
		ASSIGN_TO_TYPE(int, INT);
		return INT(thisJarr)->size;
	case 'f':
		FLOAT(thisJarr)->len += 1;
		IF_NEED_MEM(FLOAT)
			ERROR_IF(REALLOC_FAILS(FLOAT));
		ASSIGN_TO_TYPE(float, FLOAT);
		return FLOAT(thisJarr)->size;
	case 'd':
		DOUBLE(thisJarr)->len += 1;
		IF_NEED_MEM(DOUBLE)
			ERROR_IF(REALLOC_FAILS(DOUBLE));
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
