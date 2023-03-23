#ifndef JARR_H_DEF
#define JARR_H_DEF

/*
   you shall check non-noalloc macros for non-zero value
   and decide how to error-handle malloc or realloc failures.

   _nocheck macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc.

   _noalloc macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.
*/

#define JARR_RELEASE
#define JARR_INCLUDE
#define JARR_ALIGN_POWER_OF_TWO
#define JARR_64_BIT

#ifdef JARR_RELEASE
	#undef JARR_DEBUG
#else
	#define JARR_DEBUG
#endif // JARR_RELEASE

#include <stddef.h>
#include "/home/james/c/macros/vargc.h" // gch
#include "macros.h" // gch
#include "types.h" // gch
#include "generic.h" // gch

#ifdef JARR_INCLUDE
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif // JARR_INCLUDE

#define JARR_MIN_CAP 8

#ifdef JARR_ALIGN_POWER_OF_TWO
	#ifdef JARR_64_BIT
		#define JARR_NEXT_POW2(x) private_jarr_next_pow2_64(x)
	#elif JARR_32_BIT
		#define JARR_NEXT_POW2(x) private_jarr_next_pow2_32(x)
	#else
		#define JARR_NEXT_POW2(x) (x)
	#endif // JARR_64_BIT
#endif // JARR_ALIGN_POWER_OF_TWO

#define JARR_STRUCT(T, t)        \
	typedef struct T {       \
		t *data;         \
		size_t size;     \
		size_t capacity; \
	} T;

JARR_TEMPLATE_T_t(JARR_STRUCT)

#define jarr_st_init(T, name, capacity)           \
	struct {                                  \
		T data[JARR_NEXT_POW2(capacity)]; \
		size_t size;                      \
	} name = { .size = 0 }

#define jarr_st_get_capacity(jarr_st)\
	(sizeof(jarr_st)/sizeof(*jarr_st))

#define jarr_init(this_jarr)         \
(void)(                              \
	((this_jarr)->capacity) = 0, \
	((this_jarr)->size) = 0,     \
	((this_jarr)->data) = NULL   \
)

#define jarr_delete(this_jarr)   \
(void)(                          \
	free((this_jarr)->data), \
	jarr_init(this_jarr), 0  \
)                                \

#define jarr_new_alloc(this_jarr, cap)                                                         \
(                                                                                              \
	(((this_jarr)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP)),                \
	(likely(((this_jarr)->data) = malloc(this_jarr->capacity * JARR_SIZEOF_T(this_jarr)))) \
		? ((((this_jarr)->size) = 0), 1)                                               \
		: (jarr_init(this_jarr), 0)                                                    \
)

#define jarr_reserve_nocheck(this_jarr, cap)                                                 \
(                                                                                            \
	 private_jarr_realloc((void **)&((this_jarr)->data), cap * JARR_SIZEOF_T(this_jarr)) \
	 && ((((this_jarr)->capacity) = cap), 1)                                             \
)

#define jarr_reserve(this_jarr, cap) (((cap) > ((this_jarr)->capacity)) ? (jarr_reserve_nocheck(this_jarr, cap)) : 1)

#define private_jarr_reserve_x(this_jarr, multiplier) jarr_reserve_nocheck(this_jarr, (multiplier * ((this_jarr)->capacity)))

#define jarr_reserve_2x(this_jarr) private_jarr_reserve_x(this_jarr, 2)
#define jarr_reserve_4x(this_jarr) private_jarr_reserve_x(this_jarr, 4)
#define jarr_reserve_8x(this_jarr) private_jarr_reserve_x(this_jarr, 8)
#define jarr_reserve_16x(this_jarr) private_jarr_reserve_x(this_jarr, 16)
#define jarr_reserve_32x(this_jarr) private_jarr_reserve_x(this_jarr, 32)
#define jarr_reserve_64x(this_jarr) private_jarr_reserve_x(this_jarr, 64)

#define jarr_shrink_to_fitnocheck(this_jarr)                   \
	(jarr_reserve_nocheck(this_jarr, ((this_jarr)->size)))

#define jarr_shrink_to_fit(this_jarr)                            \
(                                                                \
	(likely(((this_jarr)->capacity) != ((this_jarr)->size))) \
		? (jarr_shrink_to_fitnocheck(this_jarr))         \
		: 1                                              \
)

#define jarr_shrink_nocheck(this_jarr, size) \
(void)(                                      \
	((this_jarr)->size) = size           \
)

#define jarr_shrink(this_jarr, size)                 \
(void)(                                              \
	(likely(size < ((this_jarr)->size)))         \
	&& (jarr_shrink_nocheck(this_jarr, size), 0) \
)

#define jarr_push_back_noalloc(this_jarr, value)             \
(void)(                                                      \
	(((this_jarr)->data)[((this_jarr)->size)++] = value) \
)

#define jarr_push_back_nocheck(this_jarr, value)                       \
(                                                                      \
	(jarr_reserve_nocheck(this_jarr, ((this_jarr)->capacity) * 2)) \
	&& (jarr_push_back_noalloc(this_jarr, value), 1)               \
)

#define jarr_push_back(this_jarr, value)                           \
(                                                                  \
	 (((this_jarr)->capacity) > ((this_jarr)->size))           \
		 ? ((jarr_push_back_noalloc(this_jarr, value)), 1) \
		 : (jarr_push_back_nocheck(this_jarr, value))      \
)

#define jarr_st_push_back(jarr_st, value)\
	(jarr_push_back_noalloc(jarr_st, value))

#define jarr_append(this_jarr, src_arr, src_arr_size)                                                                                        \
(                                                                                                                                            \
	(((this_jarr)->size) + (src_arr_size) > ((this_jarr)->capacity))                                                                     \
	?                                                                                                                                    \
		((private_jarr_grow_cap((void *)&((this_jarr)->data), (void *)&((this_jarr)->capacity), ((this_jarr)->size) + src_arr_size), \
		jarr_reserve_nocheck(this_jarr, ((this_jarr)->capacity)))                                                                    \
		&& (memcpy(((this_jarr)->data), src_arr, (src_arr_size) * sizeof(*src_arr)),                                                 \
		((this_jarr)->size) += (src_arr_size), 1))                                                                                   \
	:                                                                                                                                    \
		(memcpy(((this_jarr)->data), src_arr, (src_arr_size) * sizeof(*src_arr)),                                                    \
		((this_jarr)->size) += (src_arr_size), 1)                                                                                    \
)

#define private_jarr_cat_noalloc(this_jarr, argc, ...)                       \
(void)(                                                                      \
	PP_LOOP_FROM(((this_jarr)->data), ((this_jarr)->size), __VA_ARGS__), \
	((((this_jarr)->size) += argc), 0)                                   \
)

#define jarr_st_cat(jarr_st, ...)                                            \
	private_jarr_cat_noalloc(jarr_st, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define private_jarr_cat_nocheck(this_jarr, argc, ...)                                                                    \
(                                                                                                                         \
	private_jarr_grow_cap((void *)&((this_jarr)->data), (void *)&((this_jarr)->capacity), ((this_jarr)->size) + argc) \
	&& (private_jarr_cat_noalloc(this_jarr, (argc), __VA_ARGS__), 1)                                                  \
)

#define private_jarr_cat(this_jarr, argc, ...)                                  \
(                                                                               \
	(((this_jarr)->size) + argc > ((this_jarr)->capacity))                  \
		? (private_jarr_cat_nocheck(this_jarr, (argc), __VA_ARGS__))    \
		: (private_jarr_cat_noalloc(this_jarr, (argc), __VA_ARGS__), 1) \
)

#define private_cat(F, this_jarr, ...) F(this_jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_cat(this_jarr, ...) private_cat(private_jarr_cat, this_jarr, __VA_ARGS__)
#define jarr_cat_noalloc(this_jarr, ...) private_cat(private_jarr_cat_noalloc, this_jarr, __VA_ARGS__)
#define jarr_cat_nocheck(this_jarr, ...) private_cat(private_jarr_cat_nocheck, this_jarr, __VA_ARGS__)

#define private_jarr_new(this_jarr, cap, ...)                                                         \
(                                                                                                     \
	((((this_jarr)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP)),                      \
	(likely(((this_jarr)->data) = malloc((((this_jarr)->capacity)) * JARR_SIZEOF_T(this_jarr))))) \
	?                                                                                             \
		((PP_LOOP_FROM(((this_jarr)->data), 0, __VA_ARGS__)),                                 \
		(((this_jarr)->size) = PP_NARG(__VA_ARGS__)), 1)                                      \
	:                                                                                             \
		(jarr_init(this_jarr), 0)                                                             \
)

#define jarr_new(this_jarr, cap, ...) private_jarr_new(this_jarr, cap, __VA_ARGS__)
#define jarr_new_auto(this_jarr, ...) private_jarr_new(this_jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_pop_back(this_jarr) --((this_jarr)->size)

#define jarr_pop_front(this_jarr)                                                    \
(void)(                                                                              \
	memmove(((this_jarr)->data), ((this_jarr)->data + 1), --((this_jarr)->size)) \
)

#define jarr_push_front_noalloc(this_jarr, value)                                     \
(void)(                                                                               \
	memmove(((this_jarr)->data) + 1, ((this_jarr)->data), ((this_jarr)->size)++), \
	(*(((this_jarr)->data)) = value)                                              \
)

#define jarr_push_front_nocheck(this_jarr, value)         \
(                                                         \
	(likely(jarr_reserve_2x(this_jarr)))              \
	&& (jarr_push_front_noalloc(this_jarr, value), 1) \
)

#define jarr_push_front(this_jarr, value)                          \
(                                                                  \
	(unlikely(((this_jarr)->capacity) == ((this_jarr)->size))) \
	? jarr_push_front_nocheck(this_jarr, value)          \
	: (jarr_push_front_noalloc(this_jarr, value), 1)     \
)

#define jarr_cmp_nocheck(jarr_dest, jarr_src) (memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp(jarr_dest, jarr_src) ((((jarr_dest)->size) != ((jarr_src)->size)) || jarr_cmp_nocheck(jarr_dest, jarr_src))

#define jarr_foreach_index(elem, this_jarr)                      \
	for (size_t elem = 0, jarr_size__ = ((this_jarr)->size); \
		elem < jarr_size__; ++elem)

#define jarr_foreach(elem, this_jarr)                                                                                                              \
	for (typeof(*((this_jarr)->data)) *elem = ((this_jarr)->data), *const RESTRICT jarr_end__ = ((this_jarr)->data) + ((this_jarr)->size) - 1; \
		elem <= jarr_end__; ++elem)

#define jarr_st_foreach(elem, arr)                                                                       \
	for (typeof(*arr) *elem = &(arr[0]), *const RESTRICT jarr_end__ = (&(JARR_SIZEOF_ARR(arr) - 1)); \
		elem <= jarr_end__; ++elem)

#define jarr_foreach_cout(elem, this_jarr)\
	jarr_foreach(elem, this_jarr) pp_cout(*(elem))

#define jarr_end(this_jarr) (*(((this_jarr)->data) + ((this_jarr)->size) - 1))
#define jarr_start(this_jarr) (*(((this_jarr)->data)))

#define jarr_typeof_elem(this_jarr) typeof(*((this_jarr)->data))
#define jarr_typeof(this_jarr) typeof((*(this_jarr)))

#define JARR_SAME_TYPE(x, y) _Generic((x), \
	typeof(y): 1,                      \
	default: 0                         \
	)

#define JARR_TYPE_IS(type, x) _Generic((x), \
	type: 1,                            \
	default: 0                          \
	)

ALWAYS_INLINE static int private_jarr_realloc(void **RESTRICT data, const size_t cap)
{
	void *RESTRICT tmp;
	if (unlikely(!(tmp = realloc(*data, cap))))
		return 0;
	*data = tmp;
	return 1;
}

ALWAYS_INLINE static int private_jarr_grow_cap(void **RESTRICT data, size_t *RESTRICT cap, const size_t size)
{
	size_t tmp = *cap * 2;
	while (size > tmp)
		tmp *= 2;
	if (unlikely(!private_jarr_realloc(data, tmp)))
		return 0;
	*cap = tmp;
	return 1;
}

#endif // JARR_H_DEF
