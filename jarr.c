#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define MIN_SIZE 8

int jarrCatInt(Jarr *dest, ...)
{
	/* *dest->size must be initialized with 0 if empty */
	va_list ap;
	va_start(ap, dest);
	int argNum=0;
	for (;;) {
		int argvStr = va_arg(ap, int);
		if (!argvStr)
			break;
		++argNum;
	}
	va_end(ap);
	if (!dest->size) {
		int *tmp = dest->itemInt;
		dest->size
			= (MIN_SIZE > 2 * dest->len)
			? MIN_SIZE
			: (2 * dest->len);
		if (!(dest->itemInt = malloc(dest->size * sizeof(int))))
			goto ERR;
		memcpy(dest->itemInt, tmp, dest->len * sizeof(int));
	} else if (dest->size < 2 * dest->len) {
		dest->size *= 2;
		if (!(dest->itemInt = realloc(dest->itemInt, dest->size)))
			goto ERR;
	}
	va_start(ap, dest);
	for (;;) {
		int argvStr = va_arg(ap, int);
		if (!argvStr)
			break;
		dest->itemInt = &argvStr;
	}
	va_end(ap);
	return dest->size;
ERR:
	perror("int jarrCatInt(jarr *dest, jarr *src): ");
	return 0;
}

int jarrAddInt(Jarr *dest, int src)
{
	/* *dest->size must be initialized with 0 if empty */
	if (!dest->size) {
		dest->size = MIN_SIZE;
		if (!(dest->itemInt = malloc(dest->size)))
			goto ERR;
	} else if (dest->size < 2 * (dest->len + 1)) {
		dest->size *= 2;
		if (!(dest->itemInt = realloc(dest->itemInt, dest->size * sizeof src)))
			goto ERR;
	}
	(dest->itemInt)[dest->len] = src;
	dest->len += 1;
	return dest->size;

ERR:
	perror("int jarrAddInt(jarr *dest, jarr *src): ");
	return 0;
}

int isJarr(Jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
