#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8
#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2
#define ALLOC_JARR(JARR, JARR_TYPE, ...) \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.item = malloc(JARR.size * JARR.typeSize))) { \
		perror(""); exit(EXIT_FAILURE); } \
	_jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define initJarr(JARR, JARR_TYPE) \
	Jarr JARR; \
	switch (JARR_TYPE) { \
	case 'f': \
		JARR.type = 'f'; \
		JARR.typeSize = sizeof(float); \
		break; \
	case 'd': \
		JARR.type = 'd'; \
		JARR.typeSize = sizeof(double); \
		break; \
	default: \
		 JARR.type = 'i'; \
		JARR.typeSize = sizeof(int); \
	}
#define newJarr(JARR, JARR_TYPE, ...) \
	initJarr(JARR, JARR_TYPE) \
	ALLOC_JARR(JARR, JARR_TYPE, __VA_ARGS__)
#define freeJarr(JARR) \
	if (JARR.size) free(JARR.item)
#define jarrPr(JARR, INDEX) \
	for (int i; i<JARR.len; ++i) \
		printf("%d\n", JARR.item)

typedef struct Jarr {
	void *item;
	int type;
	size_t len;
	size_t size;
	int typeSize;
} Jarr;

int _jarrCat(Jarr *dest, int argc, ...);
#define jarrCat(JARR, ...) _jarrCat(JARR, PP_NARG(__VA_ARGS__), ...)
int _jarrAddArr(Jarr *dest, void *arr, size_t arrLen);
#define jarrAddArr(JARR, ADDED_ARR) jarrAddArr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAdd(Jarr *dest, void *src);
#define jarrAdd(JARR, JARR_NUM) _jarrAdd(&JARR, JARR_NUM)
int isJarr(Jarr *structPtr);

#endif
