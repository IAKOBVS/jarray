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
#define REALLOC_FAILS(TYPE) \
	!(dest->TYPE = realloc(dest->TYPE, dest->typeSize * (GET_SIZE(dest->size))))
#define LOOP_ASSIGN(TYPE, TYPE_TMP, ITEM) \
	do { \
		for (int i=0; i<argc; i ++) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			((TYPE *)dest->ITEM)[i] = argv; \
		} \
	} while (0)
#define ASSIGN(TYPE, ITEM) \
	((TYPE *)dest->ITEM)[dest->len - sizeof(TYPE)] = *(TYPE *)src

int _jarrCat(Jarr *dest, int argc, ...)
{
	dest->len += argc;
	va_list ap;
	switch (dest->type) {
		case 'f':
			if (dest->size < 2 * dest->len)
				ERROR_IF(REALLOC_FAILS(itemFl));
			va_start(ap, argc);
			LOOP_ASSIGN(float, double, itemFl);
			break;
		case 'd':
			if (dest->size < 2 * dest->len)
				ERROR_IF(REALLOC_FAILS(itemDbl));
			va_start(ap, argc);
			LOOP_ASSIGN(double, double, itemDbl);
			break;
		default:
			if (dest->size < 2 * dest->len)
				ERROR_IF(REALLOC_FAILS(itemInt));
			va_start(ap, argc);
			LOOP_ASSIGN(int, int, itemInt);
	}
	va_end(ap);
	return dest->size;

ERROR:
	perror("int jarrCat(Jarr *dest, int argc, ...): ");
	return 0;
}

int _jarrAddArr(Jarr *dest, void *arr, size_t arrLen)
{
	dest->len+= arrLen;
	if (dest->size < 2 * dest->len)
		ERROR_IF(REALLOC_FAILS);
	memcpy(dest->item, arr, arrLen * dest->typeSize);
	return dest->size;

ERROR:
	perror("int jarrAddArr(Jarr *dest, void *arr, size_t arrLen): ");
	return 0;
}

int _jarrAdd(Jarr *dest, void *src)
{
	dest->len += 1;
	if (dest->size < 2 * (dest->len))
		ERROR_IF(REALLOC_FAILS);
	switch (dest->type) {
	case 'f':
		ASSIGN(float, itemFl);
		break;
	case 'd':
		ASSIGN(double, itemDbl);
		break;
	default:
		ASSIGN(int, itemInt);
	}
	return dest->size;

ERROR:
	perror("int jarrAdd(jarr *dest, void *src): ");
	return 0;
}

int isJarr(Jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
