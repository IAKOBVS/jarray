#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define MIN_SIZE 8

int jarr_cat_int(Jarr *dest, ...)
{
	int argNum=0;
	va_list ap;
	va_start(ap, dest);
	for (;;) {
		char *argvStr = va_arg(ap, char*);
		if (argvStr[0] == 'Z')
			break;
		++argNum;
	}
	va_end(ap);
	dest->len+= argNum;
	if (dest->size < 2 * dest->len) {
		if (!(dest->itemInt = realloc(dest->itemInt,
			sizeof(int)
			* ((dest->size *= 2 > 2 * dest->len)
			? dest->size
			: 2 * dest->len))))
			goto ERR;
	}
	va_start(ap, dest);
	do {
		int argvStr = va_arg(ap, int);
		dest->itemInt = &argvStr;
	} while (argNum--);
	va_end(ap);
	return dest->size;
ERR:
	perror("int jarr_cat_int(jarr *dest, jarr *src): ");
	return 0;
}

int jarraddint(Jarr *dest, int src)
{
	if (dest->size < 2 * (dest->len + 1)) {
		dest->size *= 2;
		if (!(dest->itemInt = realloc(dest->itemInt,
			sizeof(int)
			* ((dest->size *= 2 > 2 * dest->len)
			? dest->size
			: 2 * dest->len))))
			goto ERR;
	}
	(dest->itemInt)[dest->len] = src;
	dest->len += 1;
	return dest->size;

ERR:
	perror("int jarrAddInt(jarr *dest, jarr *src): ");
	return 0;
}

int isjarr(Jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
