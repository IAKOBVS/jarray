#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define ERROR_IF(STATE) \
	if (STATE) \
		goto ERROR

int _jarrJoin(Jarr *dest, int argc, ...)
{
	dest->len+= argc;
	if (dest->size < 2 * dest->len) {
		ERROR_IF( !(dest->itemInt
			= realloc(dest->itemInt,
			dest->typeSize
			* (dest->size
				= (2 * dest->size > 2 * dest->len)
				? 2 * dest->size : 2 * dest->len))));
	}
	va_list ap;
	va_start(ap, argc);
	for (int i=0; i<argc; ++i) {
		int argvStr = va_arg(ap, int);
		(dest->itemInt)[i] = argvStr;
	}
	va_end(ap);
	return dest->size;

ERROR:
	perror("int jarr_cat_int(jarr *dest, jarr *src): ");
	return 0;
}

int _jarrJoinInt(Jarr *dest, int argc, ...)
{
	int argNum=0;
	va_list ap;
	va_start(ap, argc);
	for (int i=0; i<argc; ++i) {
		char *argvStr = va_arg(ap, char *);
		if (argvStr[0] == 'Z')
			break;
		++argNum;
	}
	va_end(ap);
	dest->len+= argNum;
	if (dest->size < 2 * dest->len) {
		ERROR_IF( !(dest->itemInt
			= realloc(dest->itemInt,
			sizeof(int)
			* (dest->size
				= (dest->size * 2 > 2 * dest->len)
				? dest->size : 2 * dest->len))));
	}
	va_start(ap, argc);
	do {
		int argvStr = va_arg(ap, int);
		dest->itemInt = &argvStr;
	} while (argNum--);
	va_end(ap);
	return dest->size;

ERROR:
	perror("int jarr_cat_int(jarr *dest, jarr *src): ");
	return 0;
}

int _jarrAddInt(Jarr *dest, int src)
{
	if (dest->size < 2 * (dest->len + 1)) {
		dest->size *= 2;
		ERROR_IF( !(dest->itemInt
			= realloc(dest->itemInt,
			sizeof(int)
			* (dest->size
				= (dest->size *= 2 > 2 * dest->len)
				? dest->size : 2 * dest->len))));
	}
	(dest->itemInt)[dest->len] = src;
	dest->len += 1;
	return dest->size;

ERROR:
	perror("int jarrAddInt(jarr *dest, jarr *src): ");
	return 0;
}

int isJarr(Jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
