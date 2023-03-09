#ifndef JARR_H_DEF
#define JARR_H_DEF

/*
   you shall check nonnoalloc macros for non-zero value
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
#endif

#include <stddef.h>
#include "/home/james/c/macros/vargc.h" // gch
#include "macros.h" // gch
#include "types.h" // gch
#include "generic.h" // gch

#ifdef JARR_INCLUDE
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif

#define JARR_MIN_CAP 8

#if defined(__GNUC__) || defined(__clang__)
	#define JARR_NEAR_POW2_32(x)                                          \
		((x) ? 1 : 1UL << (sizeof((x)) * 8 - __builtin_clz((x) - 1)))
	#define JARR_NEAR_POW2_64(x)                                             \
		((x) ? 1 : 1ULL << (sizeof((x)) * 8 - __builtin_clzll((x) - 1)))
#else
	#define JARR_NEAR_POW2_32(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		++x)
	#define JARR_NEAR_POW2_64(x) \
		(x--,                \
		x |= x >> 1,         \
		x |= x >> 2,         \
		x |= x >> 4,         \
		x |= x >> 8,         \
		x |= x >> 16,        \
		x |= x >> 32,        \
		++x)
#endif

#ifdef JARR_ALIGN_POWER_OF_TWO
	#ifdef JARR_64_BIT
		#define JARR_NEAR_POW2(x) JARR_NEAR_POW2_64(x)
	#elif JARR_32_BIT
		#define JARR_NEAR_POW2(x) JARR_NEAR_POW2_32(x)
	#else
		#define JARR_NEAR_POW2(x) (x)
	#endif
#endif

#define JARR_STRUCT(T, t)        \
	typedef struct T {       \
		t *data;         \
		size_t size;     \
		size_t capacity; \
	} T;

JARR_TEMPLATE_T_t(JARR_STRUCT)

#define jarr_st_init(T, name, capacity)           \
	struct {                                  \
		T data[JARR_NEAR_POW2(capacity)]; \
		size_t size;                      \
	} name = { .size = 0 }

#define jarr_st_get_capacity(jarr_st)\
	(sizeof(jarr_st)/sizeof(*jarr_st))

#define jarr_init(jarr_ptr)          \
(void)(                              \
	((jarr_ptr)->capacity) = 0,  \
	((jarr_ptr)->size) = 0,      \
	((jarr_ptr)->data) = NULL, 0 \
)

#define jarr_delete_nocheck(jarr_ptr) \
(void)(                               \
	free((jarr_ptr)->data),       \
	jarr_init(jarr_ptr), 0        \
)                                     \

#define jarr_delete(jarr_ptr)                 \
(void)(                                       \
	((jarr_ptr)->data)                    \
	&& (jarr_delete_nocheck(jarr_ptr), 0) \
)                                             \

#define jarr_new_alloc(jarr_ptr, cap)                                                               \
(                                                                                                   \
	((jarr_ptr)->capacity) = MAX(cap, JARR_MIN_CAP),                                            \
	(likely(((jarr_ptr)->data) = malloc(jarr_ptr->capacity * JARR_SIZEOF_T(jarr_ptr)))) ? 1 : 0 \
)

#define jarr_reserve_nocheck(jarr_ptr, cap) (private_jarr_realloc((void **)&((jarr_ptr)->data), cap * JARR_SIZEOF_T(jarr_ptr)))

#define jarr_reserve(jarr_ptr, cap) (((cap) > ((jarr_ptr)->capacity)) ? (jarr_reserve_nocheck(jarr_ptr, cap)) : 1)

#define private_jarr_reserve_x(jarr_ptr, multiplier) jarr_reserve_nocheck(jarr_ptr, (multiplier * ((jarr_ptr)->capacity)))

#define jarr_reserve_2x(jarr_ptr) private_jarr_reserve_x(jarr_ptr, 2)
#define jarr_reserve_4x(jarr_ptr) private_jarr_reserve_x(jarr_ptr, 4)
#define jarr_reserve_8x(jarr_ptr) private_jarr_reserve_x(jarr_ptr, 8)
#define jarr_reserve_16x(jarr_ptr) private_jarr_reserve_x(jarr_ptr, 16)
#define jarr_reserve_32x(jarr_ptr) private_jarr_reserve_x(jarr_ptr, 32)
#define jarr_reserve_64x(jarr_ptr) private_jarr_reserve_x(jarr_ptr, 64)

#define jarr_shrink_nocheck(jarr_ptr)                        \
	(jarr_reserve_nocheck(jarr_ptr, ((jarr_ptr)->size)))

#define jarr_shrink(jarr_ptr)                                  \
(                                                              \
	(likely(((jarr_ptr)->capacity) != ((jarr_ptr)->size))) \
		? (jarr_shrink_nocheck(jarr_ptr))              \
		: (1)                                          \
)

#define jarr_push_back_noalloc(jarr_ptr, value)                       \
	(void)((((jarr_ptr)->data)[((jarr_ptr)->size)++] = value), 0)

#define jarr_push_back_nocheck(jarr_ptr, value)                      \
(                                                                    \
	(jarr_reserve_nocheck(jarr_ptr, ((jarr_ptr)->capacity) * 2)) \
	&& (jarr_push_back_noalloc(jarr_ptr, value), 1)              \
)

#define jarr_push_back(jarr_ptr, value)                           \
(                                                                 \
	 (((jarr_ptr)->capacity) > ((jarr_ptr)->size))            \
		 ? ((jarr_push_back_noalloc(jarr_ptr, value)), 1) \
		 : (jarr_push_back_nocheck(jarr_ptr, value))      \
)

#define jarr_st_push_back(jarr_st, value)\
	(jarr_push_back_noalloc(jarr_st, value))

#define jarr_append(jarr_ptr, src_arr, src_arr_size)                                                                                      \
(                                                                                                                                         \
	(((jarr_ptr)->size) + (src_arr_size) > ((jarr_ptr)->capacity))                                                                    \
	?                                                                                                                                 \
		((private_jarr_grow_cap((void *)&((jarr_ptr)->data), (void *)&((jarr_ptr)->capacity), ((jarr_ptr)->size) + src_arr_size), \
		jarr_reserve_nocheck(jarr_ptr, ((jarr_ptr)->capacity)))                                                                   \
		&& (memcpy(((jarr_ptr)->data), src_arr, (src_arr_size) * sizeof(*src_arr)),                                               \
		((jarr_ptr)->size) += (src_arr_size), 1))                                                                                 \
	:                                                                                                                                 \
		(memcpy(((jarr_ptr)->data), src_arr, (src_arr_size) * sizeof(*src_arr)),                                                  \
		((jarr_ptr)->size) += (src_arr_size), 1)                                                                                  \
)

#define private_jarr_cat_noalloc(jarr_ptr, argc, ...)                      \
(void)(                                                                    \
	PP_LOOP_FROM(((jarr_ptr)->data), ((jarr_ptr)->size), __VA_ARGS__), \
	((((jarr_ptr)->size) += argc), 0)                                  \
)

#define jarr_st_cat(jarr_st, ...)                                            \
	private_jarr_cat_noalloc(jarr_st, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define private_jarr_cat_nocheck(jarr_ptr, argc, ...)                                                                  \
(                                                                                                                      \
	private_jarr_grow_cap((void *)&((jarr_ptr)->data), (void *)&((jarr_ptr)->capacity), ((jarr_ptr)->size) + argc) \
	&& (private_jarr_cat_noalloc(jarr_ptr, (argc), __VA_ARGS__), 1)                                                \
)

#define private_jarr_cat(jarr_ptr, argc, ...)                                  \
(                                                                              \
	(((jarr_ptr)->size) + argc > ((jarr_ptr)->capacity))                   \
		? (private_jarr_cat_nocheck(jarr_ptr, (argc), __VA_ARGS__))    \
		: (private_jarr_cat_noalloc(jarr_ptr, (argc), __VA_ARGS__), 1) \
)

#define private_cat(F, jarr_ptr, ...) F(jarr_ptr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_cat(jarr_ptr, ...) private_cat(private_jarr_cat, jarr_ptr, __VA_ARGS__)
#define jarr_cat_noalloc(jarr_ptr, ...) private_cat(private_jarr_cat_noalloc, jarr_ptr, __VA_ARGS__)
#define jarr_cat_nocheck(jarr_ptr, ...) private_cat(private_jarr_cat_nocheck, jarr_ptr, __VA_ARGS__)

#define private_jarr_new(jarr_ptr, cap, ...)                                                       \
(                                                                                                  \
	(((jarr_ptr)->size) = 0,                                                                   \
	((jarr_ptr)->capacity) = MAX(2 * JARR_NEAR_POW2(cap), JARR_MIN_CAP),                       \
	(likely(((jarr_ptr)->data) = malloc((((jarr_ptr)->capacity)) * JARR_SIZEOF_T(jarr_ptr))))) \
		? (private_jarr_cat_noalloc(jarr_ptr, cap, __VA_ARGS__), 1)                        \
		: (jarr_init(jarr_ptr), 0)                                                         \
)

#define jarr_new(jarr_ptr, cap, ...) private_jarr_new(jarr_ptr, cap, __VA_ARGS__)
#define jarr_new_auto(jarr_ptr, ...) private_jarr_new(jarr_ptr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_pop_back(jarr_ptr) --((jarr_ptr)->size)

#define jarr_pop_front(jarr_ptr)                                          \
(void)(                                                                   \
	(private_jarr_pop_front(&((jarr_ptr)->data), ((jarr_ptr)->size))) \
)

#define jarr_push_front_noalloc(jarr_ptr, value)                         \
(void)(                                                                  \
	private_jarr_push_front(((jarr_ptr)->data), ((jarr_ptr)->size)), \
	(*(((jarr_ptr)->data)) = value),                                 \
	++((jarr_ptr)->size), 0                                          \
)

#define jarr_push_front_nocheck(jarr_ptr, value)         \
(                                                        \
	(likely(jarr_reserve_2x(jarr_ptr)))              \
	&& (jarr_push_front_noalloc(jarr_ptr, value), 1) \
)

#define jarr_push_front(jarr_ptr, value)                         \
(                                                                \
	(unlikely(((jarr_ptr)->capacity) == ((jarr_ptr)->size))) \
	?                                                        \
		jarr_push_front_nocheck(jarr_ptr, value)         \
	:                                                        \
		(jarr_push_front_noalloc(jarr_ptr, value), 0)    \
)

#define jarr_cmp_nocheck(jarr_dest, jarr_src) (memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp(jarr_dest, jarr_src) ((((jarr_dest)->size) != ((jarr_src)->size)) || jarr_cmp_nocheck(jarr_dest, jarr_src))
#define jarr_st_cmp(jarr_st)

#define jarr_foreach_index(elem, jarr_ptr)               \
	for (size_t elem = 0, size = ((jarr_ptr)->size); \
		elem < size; ++elem)

#define jarr_foreach(elem, jarr_ptr)                                                                                                   \
	for (typeof(*((jarr_ptr)->data)) *RESTRICT elem = ((jarr_ptr)->data), *RESTRICT end = ((jarr_ptr)->data) + ((jarr_ptr)->size); \
		elem < end; ++elem)

#define jarr_foreach_arr(elem, arr)                                                                     \
	for (typeof(arr[0]) *RESTRICT elem = &(arr[0]), *RESTRICT end = (&(JARR_SIZEOF_ARR(arr) - 1])); \
		elem < end; ++elem)

#define jarr_foreach_cout(elem, jarr_ptr)\
	jarr_foreach(elem, jarr_ptr) pp_cout(*(elem))

#define jarr_end(jarr_ptr) (*(((jarr_ptr)->data) + ((jarr_ptr)->size) - 1))
#define jarr_start(jarr_ptr) (*(((jarr_ptr)->data)))

#define jarr_typeof_elem(jarr_ptr) typeof(*((jarr_ptr)->data))

#define jarr_typeof(jarr_ptr) typeof((*(jarr_ptr)))

#define JARR_SAME_TYPE(x, y) _Generic((x), \
	typeof(y): 1,                      \
	default: 0                         \
	)

#define JARR_TYPE_IS(type, x) _Generic((x), \
	type: 1,                            \
	default: 0                          \
	)

static ALWAYS_INLINE int private_jarr_realloc(void **RESTRICT jarr, size_t cap)
{
	void *RESTRICT tmp;
	if (likely(tmp = realloc(*jarr, cap))) {
		*jarr = tmp;
		return 1;
	}
	return 0;
}

static ALWAYS_INLINE int private_jarr_grow_cap(void **RESTRICT data, size_t *RESTRICT cap, size_t size)
{
	size_t tmp_cap = *cap * 2;
	while (size > tmp_cap)
		tmp_cap *= 2;
	if (likely(private_jarr_realloc(data, tmp_cap))) {
		*cap = tmp_cap;
		return 1;
	}
	return 0;
}

#define PRIVATE_JARR_POP_FRONT(typename, t)                                                 \
static ALWAYS_INLINE void private_jarr_pop_front_##typename(void **RESTRICT p, size_t size) \
{                                                                                           \
	t *RESTRICT start = *(t **)p;                                                       \
	t *RESTRICT end = start + size;                                                     \
	for ( ; start < end; ++start)                                                       \
		*(start) = *(start + 1);                                                    \
}

JARR_TEMPLATE_TYPENAME_t(PRIVATE_JARR_POP_FRONT)
	
#define private_jarr_pop_front(start, end) JARR_GENERIC_t(private_jarr_pop_front, start, end)

#define PRIVATE_JARR_PUSH_FRONT(typename, t)                                                 \
static ALWAYS_INLINE void private_jarr_push_front_##typename(void **RESTRICT p, size_t size) \
{                                                                                            \
	t *RESTRICT start = *(t **)*p;                                                       \
	t *RESTRICT end = start + size;                                                      \
	for ( ; start < end; ++start)                                                        \
		*(end) = *(end - 1);                                                         \
}

JARR_TEMPLATE_TYPENAME_t(PRIVATE_JARR_PUSH_FRONT)

#define private_jarr_push_front(start, end) JARR_GENERIC_t(private_jarr_push_front, start, end)

#endif
