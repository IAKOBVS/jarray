#ifndef JARR_H_DEF
#define JARR_H_DEF

#define newJarr(_NAME_OF_ARRAY, _TYPE_OF_ARRAY) jarr _NAME_OF_ARRAY = {.size = 0, .len = 0, .type = _TYPE_OF_ARRAY}

typedef struct Jarr {
	int size;
	int len;
	int type;
	int *itemInt;
	float *itemFl;
	double *itemDbl;
} Jarr;

int addToJarr(Jarr *dest, int src);

#endif
