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
		for (int i=0; i<argc; ++i) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			(dest->val)[i] = argv; \
		} \
	} while (0)

#define ASSIGN(TYPE) \
	(dest->val)[dest->len - sizeof(TYPE)] = src

#define IF_NEED_MEM if (dest->size < 2 * dest->len)

#define JARR_CAT(STRUCT, TYPE, TYPE2, FUNC_NAME) \
int FUNC_NAME(STRUCT *dest, int argc, ...) \
{ \
	printf("len is %zu\n", dest->len); \
	printf("size is %zu\n", dest->size); \
	dest->len += argc; \
	printf("len is %zu\n", dest->len); \
	printf("size is %zu\n", dest->size); \
	dest->len += argc; \
	va_list ap; \
	IF_NEED_MEM \
		ERROR_IF(REALLOC_FAILS); \
	va_start(ap, argc); \
	LOOP_ASSIGN(TYPE, TYPE2); \
	va_end(ap); \
	return dest->size; \
ERROR: \
	perror(""); \
	return 0; \
}

int _jarrCat(Jarr *dest, int argc, ...)
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

JARR_CAT(JarrFl, float, double, _jarrCatFl)
JARR_CAT(JarrDb, double, double, _jarrCatDb)

int _jarrAddArr(Jarr *dest, int *arr, size_t arrLen)
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

#define JARR_ADD_ARR(STRUCT, TYPE, FUNC_NAME) \
int FUNC_NAME(STRUCT *dest, TYPE *arr, size_t arrLen) \
{ \
	dest->len+= arrLen; \
	IF_NEED_MEM \
		ERROR_IF(REALLOC_FAILS); \
	memcpy(dest->val, arr, arrLen * dest->typeSize); \
	return dest->size; \
ERROR: \
	perror(""); \
	return 0; \
}

JARR_ADD_ARR(JarrFl, float, _jarrAddArrFl)
JARR_ADD_ARR(JarrDb, double, _jarrAddArrDb)

int _jarrAdd(Jarr *dest, int src)
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

#define JARR_ADD(STRUCT, TYPE, FUNC_NAME) \
int FUNC_NAME(STRUCT *dest, TYPE src) \
{ \
	dest->len += 1; \
	IF_NEED_MEM \
		ERROR_IF(REALLOC_FAILS); \
	ASSIGN(TYPE); \
	return dest->size; \
ERROR: \
	perror(""); \
	return 0; \
}

JARR_ADD(JarrFl, float, _jarrAddFl)
JARR_ADD(JarrDb, double, _jarrAddDb)

int isJarr(Jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
