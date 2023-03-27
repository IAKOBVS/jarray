#include "jarr.h" // .c
#include <assert.h>
ALWAYS_INLINE static int debug()
{
	jarray(int) arr;
	jarr_new(arr, 10, 1, 2);
	assert(jarr_cat(arr, 4, 5, 6));
	assert(jarr_push_back(arr, 7));
	assert(jarr_reserve(arr, 100));
	assert(jarr_shrink_to_fit(arr));
	jarr_pop_front(arr);
	assert(jarr_push_front(arr, 99));
	assert(jarr_shrink_to_fit(arr));
	assert(arr.capacity == arr.size);
	jarr_delete(arr);
	assert(!arr.data);
	assert(!arr.size);
	assert(!arr.capacity);
	return 1;
}

int main()
{
	assert(debug());
	jarray(int) arr;
	jarr_new(arr, 10, 3, 9, 3, 8, 99, 100);
	jarr_foreach(i, arr) {

	}
	jarr_delete(arr);
	return 0;
}

