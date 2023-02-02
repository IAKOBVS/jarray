#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8
#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2
#define ALLOC_JARR(JARR, JARR_TYPE, ...) \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.itemInt = malloc(JARR.size * sizeof (int)))) { \
		perror(""); exit(EXIT_FAILURE); } \
	_jarrJoin(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define initJarr(JARR, JARR_TYPE) \
	Jarr JARR; \
	switch (JARR_TYPE) { \
	case 'f': \
		JARR.typeSize = sizeof(float); \
		break; \
	case 'd': \
		JARR.typeSize = sizeof(double); \
		break; \
	default: \
		JARR.typeSize = sizeof(int); \
	}
#define newJarr(JARR, JARR_TYPE, ...) \
	initJarr(JARR_JARR_TYPE) \
	ALLOC_JARR(JARR, JARR_TYPE, __VA_ARGS__)
#define freeJarr(JARR) \
	if (JARR.size) free(JARR.itemInt)
#define jarrPr(JARR, INDEX) \
	printf("arr is %d: \n	size is %zu\n		len is %zu\n", (JARR.itemInt)[INDEX], JARR.size, JARR.len)

typedef struct Jarr {
	size_t size;
	size_t len;
	int typeSize;
	int *itemInt;
	float *itemFl;
	double *itemDbl;
} Jarr;

int _jarrCat(Jarr *dest, int argc, ...);
#define jarrCat(JARR, ...) _jarrCat(JARR, PP_NARG(__VA_ARGS__), ...)
int _jarrAddArr(Jarr *dest, int *arr, size_t arrSize);
#define jarrAddArr(JARR, ADDED_ARR) jarrAddArr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAdd(Jarr *dest, int src);
#define jarrAdd(JARR, JARR_NUM) _jarrAdd(&JARR, JARR_NUM)
int isJarr(Jarr *structPtr);

#endif
