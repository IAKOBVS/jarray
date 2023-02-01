#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>

#define newJarr(_NAME_OF_ARRAY, _TYPE_OF_ARRAY) Jarr _NAME_OF_ARRAY = {.size = 0, .len = 0, .type = _TYPE_OF_ARRAY}
#define jarrcatint(STR, ...) jarr_cat_int(STR, __VA_ARGS__, "")

typedef struct Jarr {
	size_t size;
	size_t len;
	int type;
	int *itemInt;
	float *itemFl;
	double *itemDbl;
} Jarr;

int jarr_cat_int(Jarr *dest, ...);
int jarraddint(Jarr *dest, int src);
int isjarr(Jarr *structPtr);

#endif
