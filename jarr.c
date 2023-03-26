#include "jarr.h"
#include "macros.h"

/* ALWAYS_INLINE int private_jarr_new_alloc(const size_t new_size, void** data, size_t *size, size_t *capacity, const size_t sizeof_data) */
/* { */
/* 	*size = 0; */
/* 	*capacity = MAX(JARR_NEXT_POW2(2 * new_size), JARR_MIN_CAP); */
/* 	*data = malloc(*capacity * sizeof_data); */
/* 	if (unlikely(!*data)) { */
/* 		return 0; */
/* 		*capacity = 0; */
/* 		*data = NULL; */
/* 	} */
/* 	return 1; */
/* } */

/* int private_jarr_new_cat(const size_t new_size, void **RESTRICT data, size_t *size, size_t *capacity, const size_t sizeof_data, ...) */
/* { */
/* 	*size = new_size; */
/* 	*capacity = MAX(JARR_NEXT_POW2(2 * new_size), JARR_MIN_CAP); */
/* 	*data = malloc(*capacity * sizeof_data); */
/* 	if (unlikely(!*data)) { */
/* 		*size = 0; */
/* 		*capacity = 0; */
/* 		*data = NULL; */
/* 		return 0; */
/* 	} */
/* 	memset(*data, 0, *capacity); */
/* 	unsigned char *RESTRICT tmp = *data; */
/* 	va_list ap; */
/* 	va_start(ap, sizeof_data); */
/* 	for (const void *RESTRICT argv = va_arg(ap, const void *); argv; argv = va_arg(ap, const void *), tmp += sizeof_data) */
/* 		memcpy(tmp, argv, sizeof_data); */
/* 	va_end(ap); */
/* 	return 1; */
/* } */

#define JARR_DEBUG
#ifdef JARR_DEBUG

#include <assert.h>

/* #include <assert.h> */
/* ALWAYS_INLINE static int debug() */
/* { */
/* 	jarray(int) arr; */
/* 	jarr_new(arr, 10, 1, 2); */
/* 	assert(jarr_cat(arr, 4, 5, 6)); */
/* 	assert(jarr_push_back(arr, 7)); */
/* 	assert(jarr_reserve(arr, 100)); */
/* 	assert(jarr_shrink_to_fit(arr)); */
/* 	jarr_pop_front(arr); */
/* 	assert(jarr_push_front(arr, 99)); */
/* 	assert(jarr_shrink_to_fit(arr)); */
/* 	assert(arr.capacity == arr.size); */
/* 	jarr_delete(arr); */
/* 	assert(!arr.data); */
/* 	assert(!arr.size); */
/* 	assert(!arr.capacity); */
/* 	return 1; */
/* } */

int main()
{
	/* assert(debug()); */
	jarray(int) arr;
	jarr_new(arr, 10, 3, 9, 3, 8, 99, 100);
	jarr_delete(arr);
	return 0;
}

#endif // JARR_DEBUG
