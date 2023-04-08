#include "/home/james/c/jstring/jstr.h"

#include "../jarr.h"
#include "../macros.h"
#include <assert.h>

/* JARR_INLINE__ static int debug() */
/* { */
	/* jarray(int, arr); */
	/* jarray(int, tmp); */
	/* private_jarr_swap(&(arr.data), &(arr.cap), &(arr.size), &(tmp.cap), &(arr.cap), &(tmp.size)); */
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

void jarr_jstr_delete(jstring_t *s)
{

}

#define jarr_jstr_delete(jarr)                              \
do {                                                        \
	for (int i = 0, sz = ((jarr)->size); i < sz; ++i) { \
		jstr_delete(&((jarr)->data)[i]);            \
	}                                                   \
} while (0)

int main()
{
	/* debug(); */

	jarray(jstring_t, n);

	/* jarr_new(&n, 10); */

	private_jarr_new_alloc(&n, 10);

	jstr_new(&n.data[0], "hello");

	jstr_new(&n.data[1], "world");

	puts(n.data[0].data);
	puts(n.data[1].data);

	jarr_jstr_delete(&n);
}
