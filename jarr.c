#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "jarr.h"

#define ERROR_IF(STATE) \
	if (STATE) \
		goto ERROR
#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2
#define GET_SIZE(VAR1) \
	VAR1 = MAX(2 * dest->size, 2 * dest->len)
#define REALLOC_FAILS \
	!(dest->val = realloc(dest->val, dest->typeSize * (GET_SIZE(dest->size))))
#define LOOP_ASSIGN(TYPE, TYPE_TMP) \
	do { \
		for (int i=0; i<argc; i ++) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			((TYPE *)dest->val)[i] = argv; \
		} \
	} while (0)
#define ASSIGN(TYPE) \
	((TYPE *)dest->val)[dest->len - sizeof(TYPE)] = src
#define IF_NEED_MEM if (dest->size < 2 * dest->len)

int _jarrCat(JarrInt *dest, int argc, ...)
{
	dest->len += argc;
	va_list ap;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	va_start(ap, argc);
	LOOP_ASSIGN(int, int);
	va_end(ap);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrCatDb(JarrDb *dest, int argc, ...)
{
	dest->len += argc;
	va_list ap;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	va_start(ap, argc);
	LOOP_ASSIGN(double, double);
	va_end(ap);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrCatFl(JarrFl *dest, int argc, ...)
{
	dest->len += argc;
	va_list ap;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	va_start(ap, argc);
	LOOP_ASSIGN(float, double);
	va_end(ap);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrAddArr(JarrInt *dest, int *arr, size_t arrLen)
{
	dest->len+= arrLen;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	memcpy(dest->val, arr, arrLen * dest->typeSize);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrAddArrDb(JarrDb *dest, double *arr, size_t arrLen)
{
	dest->len+= arrLen;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	memcpy(dest->val, arr, arrLen * dest->typeSize);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrAddArrFl(JarrFl *dest, float *arr, size_t arrLen)
{
	dest->len+= arrLen;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	memcpy(dest->val, arr, arrLen * dest->typeSize);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrAdd(JarrInt *dest, int src)
{
	dest->len += 1;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	ASSIGN(int);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrAddDb(JarrDb *dest, double src)
{
	dest->len += 1;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	ASSIGN(double);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int _jarrAddFl(JarrFl *dest, float src)
{
	dest->len += 1;
	IF_NEED_MEM
		ERROR_IF(REALLOC_FAILS);
	ASSIGN(float);
	return dest->size;

ERROR:
	perror("");
	return 0;
}

int isJarrInt(JarrInt *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
