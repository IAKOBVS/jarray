#include "jarr.h"

/* ALWAYS_INLINE static int debug() */
/* { */
/* 	jarray(int) arr; */
/* 	jarray(int) tmp; */
/* 	jarr_init(&arr); */
/* 		assert(!arr.data); */
/* 		assert(!arr.size); */
/* 		assert(!arr.capacity); */
/* 	jarr_new(&arr, 10, 1, 2); */
/* 	assert(jarr_cat(&arr, 4, 5, 6)); */
/* 	assert(jarr_push_back(&arr, 7)); */
/* 	assert(jarr_reserve(&arr, 100)); */
/* 	assert(jarr_shrink_to(&arr, 90)); */
/* 	assert(jarr_shrink_to_fit(&arr)); */
/* 	jarr_pop_front(&arr); */
/* 	assert(jarr_push_front(&arr, 99)); */
/* 	assert(jarr_shrink_to_fit(&arr)); */
/* 		assert(arr.capacity == arr.size); */
/* 	jarr_cmp(&arr, &tmp); */
/* 	jarr_delete(&arr); */
/* 		assert(!arr.data); */
/* 		assert(!arr.size); */
/* 		assert(!arr.capacity); */
/* 	return 1; */
/* } */

const int *f(int *p)
{
	return p;
}

int main()
{
	jarray(int) arr;
	int *p = jarr_cbegin(&arr);
}
