#include "jarr.h"
#include <stdio.h>
#include <stdarg.h>

#define JARR_DEBUG
#ifdef JARR_DEBUG

#include <assert.h>
ALWAYS_INLINE static int debug()
{
	jarray_int_t arr;
	jarr_new(&arr, 10, 1, 2);
	assert(jarr_cat(&arr, 4, 5, 6));
	assert(jarr_push_back(&arr, 7));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink_to_fit(&arr));
	jarr_pop_front(&arr);
	assert(jarr_push_front(&arr, 99));
	jarr_delete(&arr);
	assert(!arr.data);
	assert(!arr.size);
	assert(!arr.capacity);
	pp_cout(arr.size);
	return 1;
}

int main()
{
	assert(debug());
	return 0;
}

#endif // JARR_DEBUG
