#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8
#define MAX(NUM1, NUM2) \
	(NUM1 > NUM2) ? NUM1 : NUM2
#define ALLOC_JARR(JARR, ...) \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.val = malloc(JARR.size * JARR.typeSize))) { \
		perror(""); exit(EXIT_FAILURE); } \
	_jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define jarrNew(JARR, JARR_TYPE, ...) \
	Jarr JARR; \
	do { \
	switch (JARR_TYPE) { \
	case 'f': \
		JARR.type = 'f'; \
		JARR.typeSize = sizeof(float); \
		ALLOC_JARR(JARR, __VA_ARGS__); \
		break; \
	case 'd': \
		JARR.type = 'd'; \
		JARR.typeSize = sizeof(double); \
		ALLOC_JARR(JARR, __VA_ARGS__); \
		break; \
	default: \
		 JARR.type = 'i'; \
		JARR.typeSize = sizeof(int); \
		ALLOC_JARR(JARR, __VA_ARGS__); \
	} \
	while (0)
#define freeJarr(JARR) \
	if (JARR.size) \
		if (JARR.type == 'i' \
			free(JARR.val); \
		else if (JARR.type == 'd') \
			free(JARR.iDbl)
#define jarrPr(JARR) \
	for (int i=0; i<JARR.len; ++i) \
		printf("%f\n", *(double *)JARR.val)

typedef struct Jarr {
	int *val;
	int type;
	size_t len;
	size_t size;
	size_t typeSize;
} JarrInt;

typedef struct JarrDb {
	int *val;
	int type;
	size_t len;
	size_t size;
	size_t typeSize;
} JarrDb;

typedef struct JarrFl {
	int *val;
	int type;
	size_t len;
	size_t size;
	size_t typeSize;
} JarrFl; 

int _jarrCat(JarrInt *dest, int argc, ...);
#define jarrCat(JARR, ...) _jarrCat(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCatDb(JarrDb *dest, int argc, ...);
#define jatCatDb(JARR, ...) _jarrCatDb(&JARR , PP_NARG(__VA_ARGS__), __VA_ARGS__)
int _jarrCatFl(JarrFl *dest, int argc, ...);
#define jatCatFl(JARR, ...) _jarrCatFl(&JARR, PP_NARG(__VA_ARGS__), __VA_ARGS__)

int _jarrAddArr(JarrInt *dest, int *arr, size_t arrLen);
#define jarrAddArr(JARR, ADDED_ARR) _jarrAddArr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAddArrDb(JarrDb *dest, double *arr, size_t arrLen);
#define jarrAddArrDb(JARR, ADDED_ARR) _jarrAddArrDb(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))
int _jarrAddArrFl(JarrFl *dest, float *arr, size_t arrLen);
#define jarrAddArrFl(JARR, ADDED_ARR) _jarrAddArrFl(&JARR, &ADDED_ARR, sizeof(ADDED_ARR)/sizeof(ADDED_ARR[0]))

int _jarrAdd(JarrInt *dest, int src);
#define jarrAdd(JARR, JARR_NUM) _jarrAdd(&JARR, JARR_NUM)
int _jarrAddDb(JarrDb *dest, double src);
#define jarrAddDb(JARR, JARR_NUM) _jarrAddDb(&JARR, JARR_NUM)
int _jarrAddFl(JarrFl *dest, float src);
#define jarrAddFl(JARR, JARR_NUM) _jarrAddFl(&JARR, JARR_NUM)

#endif
