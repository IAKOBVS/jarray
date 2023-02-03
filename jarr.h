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

#define JARR_NEW(JARR, TYPE, TYPE_NAME, ...) \
	Jarr JARR; \
	Jarr.type = TYPE_NAME \
	JARR.typeSize = sizeof(TYPE); \
	ALLOC_JARR(JARR, __VA_ARGS__)

#define jarrNew(JARR, ...) \
	JARR_NEW(JARR, int, 'i')

#define jarrNewDb(JARR, ...) \
	JARR_NEW(JARR, double, 'd')

#define jarrNewFl(JARR, ...) \
	JARR_NEW(JARR, float, 'f')

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

#define JARR_STRUCT(JARR_NAME, TYPE) \
typedef struct JARR_NAME { \
	TYPE *val; \
	size_t len; \
	size_t size; \
	size_t typeSize; \
} JARR_NAME

JARR_STRUCT(Jarr, int);
JARR_STRUCT(JarrDb, double);
JARR_STRUCT(JarrFl, float);

#define jarrCat(JARR, ...) \
_jarrCat(&JARR, JARR.type, PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCat(void *thisJarr, int type, int argc, ...);

#define jarrAddJarr(JARR, ADDED_ARR) \
_jarrAddArr(&JARR, &ADDED_ARR, ADDED_ARR.len, JARR.type)
#define jarrAddarr(JARR, ADDED_ARR) \
_jarrAddarr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR) / sizeof(ADDED_ARR[0]), JARR.type)
int _jarrAddJarr(void *thisJarr, void* arr, size_t arrLen, int type);

#define jarrAdd(JARR, JARR_NUM) \
_jarrAdd(&JARR, JARR_NUM, JARR.type)
int _jarrAdd(void *thisJarr, void *src, int type);

#endif
