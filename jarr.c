#include "jarr.h"

#ifdef JARR_DEBUG
static void ALWAYS_INLINE f()
{
	jarray_int_t arr;
	jarr_new(&arr, 1, 2);
	char a[100];
	jarr_append(&arr, a, 10);
	jarr_delete(&arr);
}

int main()
{
	return 0;
}
#endif
