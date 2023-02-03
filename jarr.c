#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"


#define SWITCH(FUNC_INT, INT, FUNC_FLOAT, FLOAT, FUNC_DOUBLE, DOUBLE) \
	do { \
	switch (thisJarr->type) { \
	case INT: \
		FUNC_INT; \
	case FLOAT: \
		FUNC_FLOAT; \
	case DOUBLE: \
		FUNC_DOUBLE; \
	} \
	} while (0)

#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2

#define GET_ALLOC_SIZE(VAR1) \
	VAR1 = MAX(2 * thisJarr->size, 2 * thisJarr->len)

#define IF_NEED_MEM \
	if (thisJarr->size < 2 * thisJarr->len)

#define ERROR_IF(STATE) \
	if (STATE) \
		goto ERROR

#define REALLOC_FAILS(TYPE_NAME) \
	!(thisJarr->value.TYPE_NAME = realloc(thisJarr->value.TYPE_NAME, thisJarr->typeSize * (GET_ALLOC_SIZE(thisJarr->size))))

int _jarrCat(Jarr *thisJarr, int argc, ...)
{
	thisJarr->len += argc;
	va_list ap;
	IF_NEED_MEM
		SWITCH(ERROR_IF(REALLOC_FAILS(i)), 'i', ERROR_IF(REALLOC_FAILS(f)), 'f', ERROR_IF(REALLOC_FAILS(d)), 'd');
	va_start(ap, argc);
#define LOOP_ASSIGN(TYPE, TYPE_TMP, TYPE_NAME) \
	do { \
		for (int i=0; i<argc; ++i) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			thisJarr->value.TYPE_NAME[i] = argv; \
		} \
	} while (0)
	SWITCH(LOOP_ASSIGN(int, int, i), 'i', LOOP_ASSIGN(float, double, f), 'f', LOOP_ASSIGN(double, double, d), 'd');
	va_end(ap);
	return thisJarr->size;
ERROR:
	perror("");
	return 0;
}

int _jarrAddArr(Jarr *thisJarr, void *arr, size_t arrLen)
{
	thisJarr->len+= arrLen;
	IF_NEED_MEM
		SWITCH(ERROR_IF(REALLOC_FAILS(i)), 'i', ERROR_IF(REALLOC_FAILS(f)), 'f', ERROR_IF(REALLOC_FAILS(d)), 'd');
#define MEMCPY(TYPE) \
	memcpy(thisJarr->value.TYPE, arr, arrLen * thisJarr->typeSize)
	SWITCH(MEMCPY(i), 'i', MEMCPY(f), 'f', MEMCPY(d), 'd');
	return thisJarr->size;
ERROR:
	perror("");
	return 0;
}

int _jarrAdd(Jarr *thisJarr, void *src)
{
	thisJarr->len += 1;
	IF_NEED_MEM
		SWITCH(ERROR_IF(REALLOC_FAILS(i)), 'i', ERROR_IF(REALLOC_FAILS(f)), 'f', ERROR_IF(REALLOC_FAILS(d)), 'd');
#define ASSIGN_TO_TYPE(TYPE_NAME, TYPE) \
	thisJarr->value.TYPE_NAME[thisJarr->len - 1] = *(TYPE *)src
	SWITCH(ASSIGN_TO_TYPE(i, int), 'i', ASSIGN_TO_TYPE(f, float), 'f', ASSIGN_TO_TYPE(d, double), 'd');
	return thisJarr->size;
ERROR:
	perror("");
	return 0;
}

int isJarr(Jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
