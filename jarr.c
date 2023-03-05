#include "jarr.h"
#include <stdio.h>

#ifdef JARR_DEBUG

#include <assert.h>
static ALWAYS_INLINE int debug()
{
	int ret;
	char a[100];
	jarray_int_t arr;
	jarr_init(&arr);
	assert(jarr_new(&arr, 1, 2));
	assert(jarr_append(&arr, a, 10));
	assert(jarr_cat(&arr, 1, 3, 4));
	assert(jarr_push_back(&arr, 3));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink(&arr));
	(jarr_delete(&arr), 0);
	return 1;
}

int main()
{
	assert(debug());
	return 0;
}

#endif
