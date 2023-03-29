#ifndef JARR_H_DEF__
#define JARR_H_DEF__

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
#	undef JARR_DEBUG
#else
#	define JARR_DEBUG
#endif // JARR_RELEASE

#include "/home/james/c/pp_macros/pp_va_args_macros.h" // gch
#include "macros.h" // gch
/* #include "types.h" // gch */
/* #include "generic.h" // gch */

#define JARR_ASSERT_RIGHT_TYPE(T, expr) JARR_ASSERT_TYPECHECK(*((T)->data), expr)

#ifdef JARR_INCLUDE
#	include <stdio.h>
#	include <string.h>
#	include <stdlib.h>
#	include <assert.h>
#endif // JARR_INCLUDE

#define JARR_MIN_CAP 8

ALWAYS_INLINE static int private_jarr_realloc_exact(void **RESTRICT data, size_t *RESTRICT cap, const size_t target_cap, const size_t sizeof_data) JARR_WARN_UNUSED;
ALWAYS_INLINE static int private_jarr_realloc_grow(void **RESTRICT data, size_t *RESTRICT cap, const size_t target_cap, const size_t sizeof_data) JARR_WARN_UNUSED;

#define jarray(T)                \
	struct {                 \
		size_t size;     \
		size_t capacity; \
		T *data;         \
	}

#define jarr_st(T, capacity)                      \
	struct {                                  \
		size_t size;                      \
		T data[JARR_NEXT_POW2(capacity)]; \
	}

#define jarr_st_get_capacity(jarr_st)      \
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
	jarr_init(this_jarr)     \
)

#define private_jarr_new_alloc(this_jarr, cap)                                                     \
JARR_MACRO_START                                                                                   \
	JARR_ASSERT_SIZE(cap)                                                                      \
	((this_jarr)->size) = 0,                                                                   \
	(((this_jarr)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP)),                    \
	(likely(((this_jarr)->data) = malloc(((this_jarr)->capacity) * JARR_SIZEOF_T(this_jarr)))) \
	|| (jarr_init(this_jarr), 0)                                                               \
JARR_MACRO_END

#define jarr_reserve_nocheck_exact(this_jarr, cap)                                                                             \
JARR_MACRO_START                                                                                                               \
	JARR_ASSERT_SIZE(cap)                                                                                                  \
	private_jarr_realloc_exact((void **)&((this_jarr)->data), &((this_jarr)->capacity), cap, sizeof(*((this_jarr)->data))) \
JARR_MACRO_END

#define jarr_reserve_nocheck(this_jarr, cap)                                                                                  \
JARR_MACRO_START                                                                                                              \
	JARR_ASSERT_SIZE(cap)                                                                                                 \
	private_jarr_realloc_grow((void **)&((this_jarr)->data), &((this_jarr)->capacity), cap, sizeof(*((this_jarr)->data))) \
JARR_MACRO_END

#define jarr_reserve(this_jarr, cap)                                                   \
JARR_MACRO_START                                                                       \
	JARR_ASSERT_SIZE(cap)                                                          \
	((cap) > ((this_jarr)->capacity)) ? (jarr_reserve_nocheck(this_jarr, cap)) : 1 \
JARR_MACRO_END

#define private_jarr_reserve_x(this_jarr, multiplier)                                   \
JARR_MACRO_START                                                                        \
	JARR_ASSERT_SIZE(multiplier)                                                    \
	jarr_reserve_nocheck_exact(this_jarr, ((multiplier) * ((this_jarr)->capacity))) \
JARR_MACRO_END

#define jarr_reserve_2x(this_jarr) private_jarr_reserve_x(this_jarr, 2)
#define jarr_reserve_4x(this_jarr) private_jarr_reserve_x(this_jarr, 4)
#define jarr_reserve_8x(this_jarr) private_jarr_reserve_x(this_jarr, 8)
#define jarr_reserve_16x(this_jarr) private_jarr_reserve_x(this_jarr, 16)
#define jarr_reserve_32x(this_jarr) private_jarr_reserve_x(this_jarr, 32)
#define jarr_reserve_64x(this_jarr) private_jarr_reserve_x(this_jarr, 64)

#define jarr_shrink_to_fit_nocheck(this_jarr)                      \
JARR_MACRO_START                                                   \
	jarr_reserve_nocheck_exact(this_jarr, ((this_jarr)->size)) \
JARR_MACRO_END

#define jarr_shrink_to_fit(this_jarr)                            \
JARR_MACRO_START                                                 \
	(likely(((this_jarr)->capacity) != ((this_jarr)->size))) \
		? (jarr_shrink_to_fit_nocheck(this_jarr))        \
		: 1                                              \
JARR_MACRO_END

#define jarr_shrink_to_size_nocheck(this_jarr, size__) \
(void)                                                 \
JARR_MACRO_START                                       \
	((this_jarr)->size) = size__                   \
JARR_MACRO_END

#define jarr_shrink_to_size(this_jarr, size__)                 \
(void)                                                         \
JARR_MACRO_START                                               \
	(size__ < ((this_jarr)->size))                         \
	&& (jarr_shrink_to_size_nocheck(this_jarr, size__), 0) \
JARR_MACRO_END

#define jarr_shrink_to_nocheck(this_jarr, cap)     \
JARR_MACRO_START                                   \
	jarr_reserve_nocheck_exact(this_jarr, cap) \
	&& (((this_jarr)->size) = cap, 1)          \
JARR_MACRO_END

#define jarr_shrink_to(this_jarr, cap)                     \
JARR_MACRO_START                                           \
	(cap < ((this_jarr)->size))                        \
		? (jarr_shrink_to_nocheck(this_jarr, cap)) \
		: 1                                        \
JARR_MACRO_END

#define jarr_push_back_noalloc(this_jarr, value)             \
(void)                                                       \
JARR_MACRO_START                                             \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value)             \
	(((this_jarr)->data)[((this_jarr)->size)++] = value) \
JARR_MACRO_END

#define jarr_push_back_nocheck(this_jarr, value)                             \
JARR_MACRO_START                                                             \
	(jarr_reserve_nocheck_exact(this_jarr, ((this_jarr)->capacity) * 2)) \
	&& (jarr_push_back_noalloc(this_jarr, value), 1)                     \
JARR_MACRO_END

#define jarr_push_back(this_jarr, value)                           \
JARR_MACRO_START                                                   \
	 (((this_jarr)->capacity) > ((this_jarr)->size))           \
		 ? ((jarr_push_back_noalloc(this_jarr, value)), 1) \
		 : (jarr_push_back_nocheck(this_jarr, value))      \
JARR_MACRO_END

#define jarr_st_push_back(this_jarr , value)     \
JARR_MACRO_START                                 \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value) \
	jarr_push_back_noalloc(this_jarr, value) \
JARR_MACRO_END

#define jarr_append(this_jarr, src_arr, src_arr_size)                                        \
JARR_MACRO_START                                                                             \
	JARR_ASSERT_SIZE(src_arr_size)                                                        \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, *src_arr)                                          \
	(((this_jarr)->size) + (src_arr_size) > ((this_jarr)->capacity))                     \
	?                                                                                    \
		(jarr_reserve_nocheck(this_jarr, ((this_jarr)->size) + (src_arr_size))       \
		&& (memcpy(((this_jarr)->data), src_arr, (src_arr_size) * sizeof(*src_arr)), \
		((this_jarr)->size) += (src_arr_size), 1))                                   \
	:                                                                                    \
		(memcpy(((this_jarr)->data), src_arr, (src_arr_size) * sizeof(*src_arr)),    \
		((this_jarr)->size) += (src_arr_size), 1)                                    \
JARR_MACRO_END

#define private_jarr_cat_noalloc(this_jarr, argc, ...)                       \
(void)                                                                       \
JARR_MACRO_START                                                             \
	JARR_ASSERT_SIZE(argc)                                               \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, PP_FIRST_ARG(__VA_ARGS__))         \
	PP_LOOP_FROM(((this_jarr)->data), ((this_jarr)->size), __VA_ARGS__), \
	(((this_jarr)->size) += argc)                                        \
JARR_MACRO_END

#define jarr_st_cat(jarr_st, ...)                                            \
	private_jarr_cat_noalloc(jarr_st, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define private_jarr_cat_nocheck(this_jarr, argc, ...)                   \
JARR_MACRO_START                                                         \
	jarr_reserve_nocheck(this_jarr, ((this_jarr)->size) + (argc))    \
	&& (private_jarr_cat_noalloc(this_jarr, (argc), __VA_ARGS__), 1) \
JARR_MACRO_END

#define private_jarr_cat(this_jarr, argc, ...)                                  \
JARR_MACRO_START                                                                \
	(((this_jarr)->size) + argc > ((this_jarr)->capacity))                  \
		? (private_jarr_cat_nocheck(this_jarr, (argc), __VA_ARGS__))    \
		: (private_jarr_cat_noalloc(this_jarr, (argc), __VA_ARGS__), 1) \
JARR_MACRO_END

#define private_cat(F, this_jarr, ...) F(this_jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_cat(this_jarr, ...) private_cat(private_jarr_cat, this_jarr, __VA_ARGS__)
#define jarr_cat_noalloc(this_jarr, ...) private_cat(private_jarr_cat_noalloc, this_jarr, __VA_ARGS__)
#define jarr_cat_nocheck(this_jarr, ...) private_cat(private_jarr_cat_nocheck, this_jarr, __VA_ARGS__)

#define jarr_new(this_jarr, ...)                                                 \
JARR_MACRO_START                                                                 \
	(PP_NARG(__VA_ARGS__) == 1)                                              \
		? private_jarr_new_alloc(this_jarr, PP_FIRST_ARG(__VA_ARGS__))   \
		: private_jarr_new(this_jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__) \
JARR_MACRO_END

#define jarr_new_auto(this_jarr, ...)                                  \
JARR_MACRO_START                                                       \
	private_jarr_new(this_jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__) \
JARR_MACRO_END

#define private_jarr_new(this_jarr, cap, ...)                                                         \
JARR_MACRO_START                                                                                      \
	JARR_ASSERT_SIZE(cap)                                                                         \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, PP_FIRST_ARG(__VA_ARGS__))                                  \
	((((this_jarr)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP)),                      \
	(likely(((this_jarr)->data) = malloc((((this_jarr)->capacity)) * JARR_SIZEOF_T(this_jarr))))) \
	?                                                                                             \
		((PP_LOOP_FROM(((this_jarr)->data), 0, __VA_ARGS__)),                                 \
		(((this_jarr)->size) = PP_NARG(__VA_ARGS__)), 1)                                      \
	:                                                                                             \
		(jarr_init(this_jarr), 0)                                                             \
JARR_MACRO_END

#define jarr_swap(this_jarr, other_jarr)                                                                                                                                                    \
JARR_MACRO_START                                                                                                                                                                           \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, *((other_jarr)->data))                                                                                                                           \
	private_jarr_swap((void **)&((this_jarr)->data), &((this_jarr)->capacity), &((this_jarr)->size), (void **)&((other_jarr)->data), &((other_jarr)->capacity), &((other_jarr)->size)) \
JARR_MACRO_END

#define jarr_pop_back(this_jarr) --((this_jarr)->size)

#define jarr_pop_front(this_jarr)                                                    \
(void)                                                                               \
JARR_MACRO_START                                                                     \
	memmove(((this_jarr)->data), ((this_jarr)->data + 1), --((this_jarr)->size)) \
JARR_MACRO_END

#define jarr_push_front_noalloc(this_jarr, value)                                     \
(void)                                                                                \
JARR_MACRO_START                                                                      \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value)                                      \
	memmove(((this_jarr)->data) + 1, ((this_jarr)->data), ((this_jarr)->size)++), \
	(*(((this_jarr)->data)) = value)                                              \
JARR_MACRO_END

#define jarr_push_front_nocheck(this_jarr, value)         \
JARR_MACRO_START                                          \
	(likely(jarr_reserve_2x(this_jarr)))              \
	&& (jarr_push_front_noalloc(this_jarr, value), 1) \
JARR_MACRO_END

#define jarr_push_front(this_jarr, value)                          \
JARR_MACRO_START                                                   \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value)                   \
	(unlikely(((this_jarr)->capacity) == ((this_jarr)->size))) \
	? jarr_push_front_nocheck(this_jarr, value)                \
	: (jarr_push_front_noalloc(this_jarr, value), 1)           \
JARR_MACRO_END

#define jarr_cmp_nocheck(jarr_dest, jarr_src)                               \
	(memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp(jarr_dest, jarr_src)                                                        \
	((((jarr_dest)->size) != ((jarr_src)->size)) || jarr_cmp_nocheck(jarr_dest, jarr_src))

#define jarr_foreach_index(elem, this_jarr)                      \
	for (size_t elem = 0, jarr_size__ = ((this_jarr)->size); \
		elem < jarr_size__; ++elem)

#define jarr_foreach(elem, this_jarr)                                                                                                          \
	for (typeof(*((this_jarr)->data)) *elem = ((this_jarr)->data), *const RESTRICT jarr_end__ = ((this_jarr)->data) + ((this_jarr)->size); \
		elem < jarr_end__; ++elem)

#define jarr_st_foreach(elem, arr)                                                             \
	for (typeof(*(arr)) *elem = (arr), *const RESTRICT j(arr)_end__ = (&(JARR_SIZEOF_ARR((arr)))); \
		elem < j(arr)_end__; ++elem)

#define jarr_foreach_cout(elem, this_jarr)             \
	jarr_foreach(elem, this_jarr) pp_cout(*(elem))


#define jarr_begin(this_jarr) ((this_jarr)->data)
#define jarr_end(this_jarr) (((this_jarr)->data) + ((this_jarr)->size))

#ifdef JARR_HAS_TYPEOF
#	define jarr_typeof_data(this_jarr) typeof(((this_jarr)->data))
#	define jarr_typeof(this_jarr) typeof(((this_jarr)))
#	define jarr_cbegin(this_jarr) ((const typeof((this_jarr)->data))((this_jarr)->data))
#	define jarr_cend(this_jarr) ((const typeof((this_jarr)->data))(((this_jarr)->data) + ((this_jarr)->size)))
#endif // JARR_HAS_TYPEOF

ALWAYS_INLINE static int private_jarr_realloc_exact(void **RESTRICT data, size_t *RESTRICT cap, const size_t target_cap, const size_t sizeof_data)
{
	void *RESTRICT tmp;
	if (unlikely(!(tmp = realloc(*data, target_cap * sizeof_data))))
		return 0;
	*cap = target_cap;
	return 1;
}

ALWAYS_INLINE static int private_jarr_realloc_grow(void **RESTRICT data, size_t *RESTRICT cap, const size_t target_cap, const size_t sizeof_data)
{
	size_t tmp_cap = *cap * 2;
	while (tmp_cap < target_cap)
		tmp_cap *= 2;
	void *RESTRICT tmp;
	if (unlikely(!(tmp = realloc(*data, tmp_cap * sizeof_data))))
		return 0;
	*cap = tmp_cap;
	return 1;
}

ALWAYS_INLINE static void private_jarr_swap(void **RESTRICT data, size_t *RESTRICT cap, size_t *RESTRICT size, void **RESTRICT other_data, size_t *RESTRICT other_cap, size_t *RESTRICT other_size)
{
	const size_t tmp_size = *size;
	size_t tmp_cap = *cap;
	void *RESTRICT tmp_data = *data;
	*size = *other_size;
	*cap = *other_cap;
	*data = *other_data;
	*other_size = tmp_size;
	*other_cap = tmp_cap;
	*other_data = tmp_data;
}

#endif // JARR_H_DEF__
