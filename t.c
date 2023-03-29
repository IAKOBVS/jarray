#include "jarr.h"

ALWAYS_INLINE static int debug()
{
	jarray(int) arr;
	jarr_new(&arr, 10, 1, 2);
	assert(jarr_cat(&arr, 4, 5, 6));
	assert(jarr_push_back(&arr, 7));
	assert(jarr_reserve(&arr, 100));
	assert(jarr_shrink_to_fit(&arr));
	jarr_pop_front(&arr);
	assert(jarr_push_front(&arr, 99));
	assert(jarr_shrink_to_fit(&arr));
	assert(arr.capacity == arr.size);
	jarr_delete(&arr);
	assert(!arr.data);
	assert(!arr.size);
	assert(!arr.capacity);
	return 1;
}

int main()
{
#define expr 1
	_Generic(1,
	int: expr,                         \
	unsigned int: expr,                \
	size_t: expr,                      \
	long: expr,                        \
	long long: expr,                   \
	unsigned long long: expr,          \
					   \
	const int: expr,                   \
	const unsigned int: expr,          \
	const size_t: expr,                \
	const long: expr,                  \
	const long long: expr,             \
	const unsigned long long: expr
	)
}
