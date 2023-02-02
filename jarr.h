#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8
#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2
#define ALLOC_JARR(JARR, JARR_TYPE, ...) \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.JARR_TYPE = malloc(JARR.size * JARR.typeSize))) { \
		perror(""); exit(EXIT_FAILURE); } \
	_jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define jarrNew(JARR, JARR_TYPE, ...) \
	Jarr JARR; \
	do { \
	switch (JARR_TYPE) { \
	case 'f': \
		JARR.type = 'f'; \
		JARR.typeSize = sizeof(float); \
		ALLOC_JARR(JARR, itemFl, __VA_ARGS__); \
		break; \
	case 'd': \
		JARR.type = 'd'; \
		JARR.typeSize = sizeof(double); \
		ALLOC_JARR(JARR, itemDbl, __VA_ARGS__); \
		break; \
	default: \
		 JARR.type = 'i'; \
		JARR.typeSize = sizeof(int); \
		ALLOC_JARR(JARR, itemInt, __VA_ARGS__); \
	} \
	while (0)
#define freeJarr(JARR) \
	if (JARR.size) \
		if (JARR.type == 'i' \
			free(JARR.itemInt); \
		else if (JARR.type == 'd') \
			free(JARR.itemDbl) \
		else \
			free(JARR.itemFl)
#define jarrPr(JARR) \
	for (int i=0; i<JARR.len; ++i) \
		printf("%f\n", *(double *)JARR.item)

typedef struct Jarr {
	void *item;
	int *itemInt;
	float *itemFl;
	double *itemDbl;
	int type;
	size_t len;
	size_t size;
	int typeSize;
} Jarr;

int _jarrCat(Jarr *dest, int argc, ...);
#define jarrCat(JARR, ...) _jarrCat(JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrAddArr(Jarr *dest, void *arr, size_t arrLen);
#define jarrAddArr(JARR, ADDED_ARR) jarrAddArr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAdd(Jarr *dest, void *src);
#define jarrAdd(JARR, JARR_NUM) _jarrAdd(&JARR, JARR_NUM)
int isJarr(Jarr *structPtr);

#endif
