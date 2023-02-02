#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define ERROR_IF(STATE) \
	if (STATE) \
		goto ERROR
#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2
#define GET_SIZE(VAR1) \
	VAR1 = MAX(2 * dest->size, 2 * dest->len)
#define REALLOC_FAILS \
	!(dest->item = realloc(dest->item, dest->typeSize * (GET_SIZE(dest->size))))
#define LOOP_ASSIGN(TYPE, TYPE_TMP) \
	do { \
		for (int i=0; i<argc; i += sizeof(TYPE)) { \
			TYPE argv = va_arg(ap, TYPE_TMP); \
			((TYPE *)dest->item)[i] = argv; \
		} \
	} while (0)
#define ASSIGN(TYPE) \
	((TYPE *)dest->item)[dest->len - sizeof(TYPE)] = *(TYPE *)src;

int _jarrCat(Jarr *dest, int argc, ...)
{
	dest->len+= argc;
	if (dest->size < 2 * dest->len)
		ERROR_IF(REALLOC_FAILS);
	va_list ap;
	va_start(ap, argc);
	switch (dest->type) {
		case 'f':
			LOOP_ASSIGN(float, double);
			break;
		case 'd':
			LOOP_ASSIGN(double, double);
			break;
		default:
			LOOP_ASSIGN(int, int);
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
		ASSIGN(float);
		break;
	case 'd':
		ASSIGN(double);
		break;
	default:
		ASSIGN(int);
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
