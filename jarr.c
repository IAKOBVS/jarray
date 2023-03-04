#include "jarr.h"

#ifdef JARR_DEBUG
static void ALWAYS_INLINE f()
{
	jarray_int_t arr;
	jarr_init(&arr);
	jarr_new(&arr, 1, 2);
	char a[100];
	jarr_append(&arr, a, 10);
	jarr_cat(&arr, 1, 3, 4);
	jarr_push_back(&arr, 3);
	jarr_reserve(&arr, 100);
	jarr_shrink(&arr);
	jarr_delete(&arr);
}

int main()
{
	return 0;
}
#endif
