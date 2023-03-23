#include "jarr.h"
#include <stdio.h>
#include <stdarg.h>

/* #define JARR_DEBUG */
#ifdef JARR_DEBUG

#include <assert.h>
ALWAYS_INLINE static int debug()
{
	jarray_int_t arr;
	jarr_new(&arr, 10, 1, 2);
	printf("size %zu\n", arr.size);
	printf("cap %zu\n", arr.capacity);
	jarr_foreach(i, &arr) {
		pp_cout(*i);
	}
	assert(jarr_cat(&arr, 4, 5, 6));
	assert(jarr_push_back(&arr, 7));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink_to_fit(&arr));
	jarr_pop_front(&arr);
	assert(jarr_push_front(&arr, 99));
	jarr_delete(&arr);
	return 1;
}

int main()
{
	assert(debug());
	return 0;
}

#endif // JARR_DEBUG
