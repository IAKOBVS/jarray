#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "jarr.h"

#define MIN_SIZE 8

int addToJarr(jarr *dest, int src)
{
	/* *dest->size must be initialized with 0 if empty */
	if (!dest->size) {
		dest->size = MIN_SIZE;
		if (!(dest->itemInt = malloc(dest->size)))
			goto ERR;
	} else if (dest->size < 2 * (dest->len + 1)) {
		dest->size *= 2;
		int *tmp = dest->itemInt;
		if (!(dest->itemInt = realloc(dest->itemInt, dest->size * sizeof src)))
			goto ERR;
		memcpy(dest->itemInt, tmp, dest->len);
	}
	(dest->itemInt)[dest->len] = src;
	dest->len += 1;
	return dest->size;

ERR:
	perror("int addjarr(jarr *dest, jarr *src): ");
	return 0;
}

int isJarr(jarr *structPtr)
{
	if (!*((unsigned char *)&*structPtr))
		return 0;
	return 1;
}
