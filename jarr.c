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
	!(dest->itemInt = realloc(dest->itemInt, dest->typeSize * (GET_SIZE(dest->size))))

int _jarrJoin(Jarr *dest, int argc, ...)
{
	dest->len+= argc;
	if (dest->size < 2 * dest->len)
		ERROR_IF(REALLOC_FAILS);
	va_list ap;
	va_start(ap, argc);
	for (int i=0; i<argc; ++i) {
		int argv = va_arg(ap, int);
		(dest->itemInt)[i] = argv;
	}
	va_end(ap);
	return dest->size;

ERROR:
	perror("int jarr_cat_int(jarr *dest, jarr *src): ");
	return 0;
}

int _jarrAdd(Jarr *dest, int src)
{
	dest->len += 1;
	if (dest->size < 2 * (dest->len))
		ERROR_IF(REALLOC_FAILS);
	(dest->itemInt)[dest->len - 1] = src;
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
