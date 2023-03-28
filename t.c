#include "jarr.h"
#include "macros.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <assert.h>
#include <sys/cdefs.h>

/* ALWAYS_INLINE static int debug() */
/* { */
/* 	jarr_new(&arr, 10, 1, 2); */
/* 	assert(jarr_cat(&arr, 4, 5, 6)); */
/* 	assert(jarr_push_back(&arr, 7)); */
/* 	assert(jarr_reserve(&arr, 100)); */
/* 	assert(jarr_shrink_to_fit(&arr)); */
/* 	jarr_pop_front(&arr); */
/* 	assert(jarr_push_front(&arr, 99)); */
/* 	assert(jarr_shrink_to_fit(&arr)); */
/* 	assert(arr.capacity == arr.size); */
/* 	jarr_delete(&arr); */
/* 	assert(!arr.data); */
/* 	assert(!arr.size); */
/* 	assert(!arr.capacity); */
/* 	return 1; */
/* } */

int main()
{
	jarray(int) a;
	jarray(int) b;
	jarr_swap(&a, &b);
}
