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
	{ \
		if (!STRUCT(thisJarr)->size) { \
			size_t tmpSize = MAX(MIN_SIZE, 2 * (STRUCT(thisJarr)->len + argc)); \
			if (!(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * tmpSize))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} else if (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len)) { \
			size_t tmpSize = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len + argc)); \
			if (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * tmpSize))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} \
		int i = STRUCT(thisJarr)->len; \
		for (void *argv = va_arg(ap, void *); argv != NULL; argv = va_arg(ap, void *), ++i) \
			STRUCT(thisJarr)->val[i] = *(TYPE_TMP *)argv; \
	va_end(ap); \
	STRUCT(thisJarr)->len += argc; \
	} \
	return 1

int private_jarrCat(void *thisJarr, int type, int argc, ...)
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
	case 's':
		{
			if (JSTR(thisJarr)->size < 2 * (JSTR(thisJarr)->len)) {
				size_t tmpSize = MAX(MIN_SIZE, 2 * (JSTR(thisJarr)->len + argc));
				if (!(JSTR(thisJarr)->val = realloc(JSTR(thisJarr)->val, sizeof(Jstr) * tmpSize))) goto ERROR;
				JSTR(thisJarr)->size = tmpSize;
			}
			int i = JSTR(thisJarr)->len;
			for (char *argv = va_arg(ap, char *); argv != NULL; argv = va_arg(ap, void *), ++i) {
				JSTR(thisJarr)->val[i] = *(Jstr *)argv;
				JSTR(thisJarr)->val[i].len = (*(Jstr *)argv).len;
				JSTR(thisJarr)->val[i].size = (*(Jstr *)argv).size;
			}
		}
		va_end(ap);
		JSTR(thisJarr)->len += argc;
		return JSTR(thisJarr)->size;
	}

ERROR:
	va_end(ap);
	perror("");
	return 0;
}

#define JARR_ADD_ARR(STRUCT, TYPE) \
	{ \
		STRUCT(thisJarr)->len+= arrLen; \
		if (!STRUCT(thisJarr)->size) { \
			size_t tmpSize = MAX(MIN_SIZE, 2 * (STRUCT(thisJarr)->len)); \
			if (!(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * tmpSize))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} else if (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len)) { \
			size_t tmpSize = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)); \
			if (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * tmpSize))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} \
		memcpy(STRUCT(thisJarr)->val, arr, arrLen * sizeof(TYPE)); \
	} \
	return 1

int private_jarrPushArr(void *thisJarr, void *arr, size_t arrLen, int type)
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
	{ \
		STRUCT(thisJarr)->len += 1; \
		if (!STRUCT(thisJarr)->size) { \
			size_t tmpSize = MAX(MIN_SIZE, 2 * (STRUCT(thisJarr)->len)); \
			if (!(STRUCT(thisJarr)->val = malloc(sizeof(TYPE) * tmpSize))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} else if (STRUCT(thisJarr)->size < 2 * (STRUCT(thisJarr)->len)) { \
			size_t tmpSize = MAX(2 * STRUCT(thisJarr)->size, 2 * (STRUCT(thisJarr)->len)); \
			if (!(STRUCT(thisJarr)->val = realloc(STRUCT(thisJarr)->val, sizeof(TYPE) * tmpSize))) \
				goto ERROR; \
			STRUCT(thisJarr)->size = tmpSize; \
		} \
		STRUCT(thisJarr)->val[STRUCT(thisJarr)->len - 1] = *(TYPE *)src; \
	} \
	return STRUCT(thisJarr)->size

int private_jarrPush(void *thisJarr, void *src, int type)
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
