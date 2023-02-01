#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>

#define newJarr(_NAME_OF_ARRAY, _TYPE_OF_ARRAY) jarr _NAME_OF_ARRAY = {.size = 0, .len = 0, .type = _TYPE_OF_ARRAY}

typedef struct Jarr {
	size_t size;
	size_t len;
	int type;
	int *itemInt;
	float *itemFl;
	double *itemDbl;
} Jarr;

int addToJarr(Jarr *dest, int src);

#endif
