#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8

#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2

#define ALLOC_JARR(JARR, FUNC_CAT, ...) \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.val = malloc(JARR.size * JARR.typeSize))) { \
		perror(""); exit(EXIT_FAILURE); } \
	FUNC_CAT(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarrNew(JARR, ...) \
	Jarr JARR; \
	JARR.typeSize = sizeof(int); \
	ALLOC_JARR(JARR, _jarrCat, __VA_ARGS__)

#define jarrNewDb(JARR, ...) \
	JarrDb JARR; \
	JARR.typeSize = sizeof(double); \
	ALLOC_JARR(JARR, _jarrCatDb, __VA_ARGS__)

#define jarrNewFl(JARR, ...) \
	JarrFl JARR; \
	JARR.typeSize = sizeof(float); \
	ALLOC_JARR(JARR, _jarrCatFl, __VA_ARGS__)

#define freeJarr(JARR) \
	if (JARR.size) \
		if (JARR.type == 'i' \
			free(JARR.val); \
		else if (JARR.type == 'd') \
			free(JARR.iDbl)

#define jarrPr(JARR) \
	for (int i=0; i<JARR.len; ++i) \
		printf("%f\n", *(double *)JARR.val)

#define JARR_STRUCT(NAME, TYPE) \
typedef struct NAME { \
	TYPE *val; \
	size_t len; \
	size_t size; \
	size_t typeSize; \
} NAME;

JARR_STRUCT(Jarr, int)
JARR_STRUCT(JarrFl, float)
JARR_STRUCT(JarrDb, double)

#define jarrCat(JARR, ...) \
_jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCat(Jarr *dest, int argc, ...);

#define jarrCatDb(JARR, ...) \
_jarrCatDb(&JARR , PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCatDb(JarrDb *dest, int argc, ...);

#define jatCatFl(JARR, ...) \
_jarrCatFl(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCatFl(JarrFl *dest, int argc, ...);

#define jarrAddArr(JARR, ADDED_ARR) \
_jarrAddArr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAddArr(Jarr *dest, int *arr, size_t arrLen);

#define jarrAddArrDb(JARR, ADDED_ARR) \
_jarrAddArrDb(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAddArrDb(JarrDb *dest, double *arr, size_t arrLen);

#define jarrAddArrFl(JARR, ADDED_ARR) \
_jarrAddArrFl(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAddArrFl(JarrFl *dest, float *arr, size_t arrLen);

#define jarrAdd(JARR, JARR_NUM) \
_jarrAdd(&JARR, JARR_NUM)
int _jarrAdd(Jarr *dest, int src);

#define jarrAddDb(JARR, JARR_NUM)\
_jarrAddDb(&JARR, JARR_NUM)
int _jarrAddDb(JarrDb *dest, double src);

#define jarrAddFl(JARR, JARR_NUM)\
_jarrAddFl(&JARR, JARR_NUM)
int _jarrAddFl(JarrFl *dest, float src);

#endif
