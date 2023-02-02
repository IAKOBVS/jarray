#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>

#define JARR_ALLOC(JARR_NAME, JARR) \
	JARR_NAME.len = sizeof JARR / sizeof(int) \
	JARR_NAME.size = 2 * JARR_NAME.len \
	JARR_NAME.itemInt = malloc(2 * JARR_NAME.len); \
	memcpy(JARR_NAME.str, JARR, JARR_NAME.len)
#define newjarr(_NAME_OF_ARRAY, _TYPE_OF_ARRAY) \
	Jarr _NAME_OF_ARRAY = {.size = 0, .len = 0, .type = _TYPE_OF_ARRAY}
#define jarrCatInt(JSTR, ...) \
	private_jarrCatInt(&JSTR, __VA_ARGS__, 'Z')
#define jarrAddInt(JSTR) \
	private_jarrAddInt(&JSTR)

typedef struct Jarr {
	size_t size;
	size_t len;
	int type;
	int *itemInt;
	float *itemFl;
	double *itemDbl;
} Jarr;

int private_jarrCatInt(Jarr *dest, ...);
int private_JarrAddInt(Jarr *dest, int src);
int is_Jarr(Jarr *structPtr);

#endif
