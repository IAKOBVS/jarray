#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include <stdarg.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8

#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2

#define ALLOC_JARR(JARR, ...) \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.val = malloc(JARR.size * JARR.typeSize))) { \
		perror(""); exit(EXIT_FAILURE); } \
	_jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarrNew(JARR, ...) \
	Jarr JARR; \
	Jarr.type = 'i' \
	JARR.typeSize = sizeof(int); \
	ALLOC_JARR(JARR, __VA_ARGS__)

#define jarrNewDb(JARR, ...) \
	Jarr JARR; \
	Jarr.type = 'd' \
	JARR.typeSize = sizeof(double); \
	ALLOC_JARR(JARR, __VA_ARGS__)

#define jarrNewFl(JARR, ...) \
	Jarr JARR; \
	Jarr.type = 'f' \
	JARR.typeSize = sizeof(float); \
	ALLOC_JARR(JARR, __VA_ARGS__)

#define freeJarr(JARR) \
	do { \
		if (JARR.size) \
			if (JARR.type == 'i' \
				free(JARR.val); \
			else if (JARR.type == 'd') \
				free(JARR.iDbl) \
	} while (0)

#define jarrPr(JARR) \
	for (int i=0; i<JARR.len; ++i) \
		printf("%f\n", *(double *)JARR.val)

typedef struct Jarr {
	int type;
	union {
		float *f;
		int *i;
		double *d;
	} value;
	size_t len;
	size_t size;
	size_t typeSize;
} Jarr;

#define jarrCat(JARR, ...) \
_jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCat(struct Jarr *thisJarr, int argc, ...);

#define jarrAddArr(JARR, ADDED_ARR) \
_jarrAddArr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAddArr(Jarr *thisJarr, void* arr, size_t arrLen);

#define jarrAdd(JARR, JARR_NUM) \
_jarrAdd(&JARR, JARR_NUM)
int _jarrAdd(Jarr *thisJarr, void *src);

#endif
