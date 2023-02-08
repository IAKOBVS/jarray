#ifndef JARR_H_DEF
#define JARR_H_DEF

#include <stdlib.h>
#include <stdarg.h>
#include "/home/james/c/vargc.h"

#define MIN_SIZE 8

#define MAX(NUM1, NUM2) \
	((NUM1 > NUM2) ? (NUM1) : (NUM2))

#define JARR_NEW(JARR, TYPE, TYPE_NAME, ...) \
	do { \
	JARR.len = 0 \
	JARR.type = TYPE_NAME \
	JARR.size = MAX(2 * PP_NARG(__VA_ARGS__), MIN_SIZE); \
	if (!(JARR.val = malloc(sizeof(TYPE) * JARR.typeSize))) { \
		perror(""); exit(EXIT_FAILURE); } \
	_jarrCat(&JARR, TYPE_NAME, PP_NARG(__VA_ARGS__), __VA_ARGS__) \
	} while (0)

#define jarrNew(JARR, ...) \
	JARR_NEW(JARR, int, 'i', __VA_ARGS__)
#define jarrNewDb(JARR, ...) \
	JARR_NEW(JARR, double, 'd', __VA_ARGS__)
#define jarrNewFl(JARR, ...) \
	JARR_NEW(JARR, float, 'f', __VA_ARGS__)

#define JARR_INIT(JARR, JARR_STRUCT, TYPE_NAME) \
	JARR_STRUCT JARR = { \
		.size = 0, \
		.len = 0, \
		.type = TYPE_NAME \
	}
#define jarrInit(JARR) \
	JARR_INIT(JARR, Jarr, 'i')
#define jarrInitFl(JARR) \
	JARR_INIT(JARR, JarrFl, 'f')
#define jarrInitDb(JARR) \
	JARR_INIT(JARR, JarrDb, 'd')

#define jarrDelete(JARR) \
	do { \
		if (JARR.size) \
			if (JARR.type == 'i' \
				free(JARR.val); \
			else if (JARR.type == 'd') \
				free(JARR.iDbl) \
	} while (0)
#define jarrDeletePtr(JARR) \
	do { \
		if (JARR->size) \
			if (JARR->type == 'i' \
				free(JARR->val); \
			else if (JARR->type == 'd') \
				free(JARR->iDbl) \
	} while (0)

#define jarrPr(JARR) \
	for (int i=0; i<JARR.len; ++i) \
		printf("%f\n", *(double *)JARR.val)

#define JARR_STRUCT(JARR_NAME, TYPE) \
typedef struct JARR_NAME { \
	int type; \
	TYPE *val; \
	size_t len; \
	size_t size; \
} JARR_NAME

#define jarrCat(JARR, ...) \
	_jarrCat(&JARR, JARR.type, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarrAddJarr(JARR, ADDED_ARR) \
	_jarrAddArr(&JARR, &ADDED_ARR, ADDED_ARR.len, JARR.type)
#define jarrAddarr(JARR, ADDED_ARR) \
	_jarrAddarr(&JARR, &ADDED_ARR, sizeof(ADDED_ARR) / sizeof(ADDED_ARR[0]), JARR.type)

#define jarrAdd(JARR, JARR_NUM) \
	_jarrAdd(&JARR, JARR_NUM, JARR.type)

#define jarrMinimize(JARR) \
	JARR.str = realloc(JARR.str, JARR.len)

JARR_STRUCT(Jarr, int);
JARR_STRUCT(JarrDb, double);
JARR_STRUCT(JarrFl, float);

int _jarrCat(void *thisJarr, int type, int argc, ...);
int _jarrAddJarr(void *thisJarr, void* arr, size_t arrLen, int type);
int _jarrAdd(void *thisJarr, void *src, int type);
int qsortDescend(const void *x, const void *y);
int qsortAscend(const void *y, const void *x);
float qsortDescendFl(const void *x, const void *y);
float qsortAscendFl(const void *y, const void *x);
double qsortDescendDb(const void *x, const void *y);
double qsortAscendDb(const void *y, const void *x);

#endif
