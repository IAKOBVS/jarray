#include "jarr.h"
#include <stdio.h>
#include <stdarg.h>

/* #define JARR_DEBUG */
#ifdef JARR_DEBUG

#include <assert.h>
static ALWAYS_INLINE int debug()
{
	char a[100];
	jarray_int_t arr;
	jarr_init(&arr);
	assert(jarr_new_auto(&arr, 1, 2, 3));
	assert(jarr_append(&arr, a, 10));
	assert(jarr_cat(&arr, 4, 5, 6));
	assert(jarr_push_back(&arr, 7));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink_to_fit(&arr));
	jarr_pop_front(&arr);
	assert(jarr_push_front(&arr, 99));
	jarr_foreach(i, &arr) {
		pp_cout(*i);
	}
	jarr_delete(&arr);
	return 1;
}

int main()
{
	/* assert(debug()); */
	/* return 0; */
}

#endif // JARR_DEBUG
