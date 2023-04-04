#ifndef JARR_H_DEF__
#define JARR_H_DEF__

/*
   _f (force / fast) macros will not error check user input,
   e.g., if (ptr) before delete,
   if (reserve_cap > capacity) before realloc.

   _u (unsafe) macros will skip allocation,
   i.e., it asserts that jarray has enough capacity.

   _s (safe) macros will do all the checks.

   you shall check non-_u macros for non-zero value
   and decide how to error-handle malloc or realloc failures.

   realloc is done to a temporary pointer first,
   so the original pointer will not be nullified.
*/

#define JARR_INCLUDE
#define JARR_ALIGN_POWER_OF_TWO
#define JARR_64_BIT

#include "/home/james/c/pp_macros/pp_va_args_macros.h" // .gch
#include "macros.h" // .gch

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

#define jarray(T, name)          \
	struct {                 \
		size_t size;     \
		size_t capacity; \
		T *data;         \
	} name = {0}

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

#define jarr_reserve_f_exact(this_jarr, cap)                                                                                   \
JARR_MACRO_START                                                                                                               \
	JARR_ASSERT_SIZE(cap)                                                                                                  \
	private_jarr_realloc_exact((void **)&((this_jarr)->data), &((this_jarr)->capacity), cap, sizeof(*((this_jarr)->data))) \
JARR_MACRO_END

#define jarr_reserve_f(this_jarr, cap)                                                                                        \
JARR_MACRO_START                                                                                                              \
	JARR_ASSERT_SIZE(cap)                                                                                                 \
	private_jarr_realloc_grow((void **)&((this_jarr)->data), &((this_jarr)->capacity), cap, sizeof(*((this_jarr)->data))) \
JARR_MACRO_END

#define jarr_reserve(this_jarr, cap)                                             \
JARR_MACRO_START                                                                 \
	JARR_ASSERT_SIZE(cap)                                                    \
	((cap) > ((this_jarr)->capacity)) ? (jarr_reserve_f(this_jarr, cap)) : 1 \
JARR_MACRO_END

#define private_jarr_reserve_x(this_jarr, multiplier)                             \
JARR_MACRO_START                                                                  \
	JARR_ASSERT_SIZE(multiplier)                                              \
	jarr_reserve_f_exact(this_jarr, ((multiplier) * ((this_jarr)->capacity))) \
JARR_MACRO_END

#define jarr_reserve_2x(this_jarr) private_jarr_reserve_x(this_jarr, 2)
#define jarr_reserve_4x(this_jarr) private_jarr_reserve_x(this_jarr, 4)
#define jarr_reserve_8x(this_jarr) private_jarr_reserve_x(this_jarr, 8)
#define jarr_reserve_16x(this_jarr) private_jarr_reserve_x(this_jarr, 16)
#define jarr_reserve_32x(this_jarr) private_jarr_reserve_x(this_jarr, 32)
#define jarr_reserve_64x(this_jarr) private_jarr_reserve_x(this_jarr, 64)

#define jarr_shrink_to_fit_f(this_jarr)                      \
JARR_MACRO_START                                             \
	jarr_reserve_f_exact(this_jarr, ((this_jarr)->size)) \
JARR_MACRO_END

#define jarr_shrink_to_fit(this_jarr)                            \
JARR_MACRO_START                                                 \
	(likely(((this_jarr)->capacity) != ((this_jarr)->size))) \
		? (jarr_shrink_to_fit_f(this_jarr))              \
		: 1                                              \
JARR_MACRO_END

#define jarr_shrink_to_size_f(this_jarr, size__) \
(void)                                           \
JARR_MACRO_START                                 \
	((this_jarr)->size) = size__             \
JARR_MACRO_END

#define jarr_shrink_to_size(this_jarr, size__)           \
(void)                                                   \
JARR_MACRO_START                                         \
	(size__ < ((this_jarr)->size))                   \
	&& (jarr_shrink_to_size_f(this_jarr, size__), 0) \
JARR_MACRO_END

#define jarr_shrink_to_f(this_jarr, cap)     \
JARR_MACRO_START                             \
	jarr_reserve_f_exact(this_jarr, cap) \
	&& (((this_jarr)->size) = cap, 1)    \
JARR_MACRO_END

#define jarr_shrink_to(this_jarr, cap)               \
JARR_MACRO_START                                     \
	(cap < ((this_jarr)->size))                  \
		? (jarr_shrink_to_f(this_jarr, cap)) \
		: 1                                  \
JARR_MACRO_END

#define jarr_push_back_u(this_jarr, value)                   \
(void)                                                       \
JARR_MACRO_START                                             \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value)             \
	(((this_jarr)->data)[((this_jarr)->size)++] = value) \
JARR_MACRO_END

#define jarr_push_back_f(this_jarr, value)                             \
JARR_MACRO_START                                                       \
	(jarr_reserve_f_exact(this_jarr, ((this_jarr)->capacity) * 2)) \
	&& (jarr_push_back_u(this_jarr, value), 1)                     \
JARR_MACRO_END

#define jarr_push_back(this_jarr, value)                     \
JARR_MACRO_START                                             \
	 (((this_jarr)->capacity) > ((this_jarr)->size))     \
		 ? ((jarr_push_back_u(this_jarr, value)), 1) \
		 : (jarr_push_back_f(this_jarr, value))      \
JARR_MACRO_END

#define jarr_st_push_back(this_jarr, value)      \
JARR_MACRO_START                                 \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value) \
	jarr_push_back_u(this_jarr, value)       \
JARR_MACRO_END

#define jarr_append(dest, ...)                                                                                 \
	(PP_NARG(__VA_ARGS__) == 2)                                                                            \
		? jarr_append_arr(dest, __VA_ARGS__, (size_t)0)                                                \
		: jarr_append_arr(dest, PP_FIRST_ARG(__VA_ARGS__), JARR_SIZEOF_ARR(PP_FIRST_ARG(__VA_ARGS__))) \

#define jarr_append_arr(dest, src_arr, src_arr_size, ...)                    \
JARR_MACRO_START                                                             \
	JARR_ASSERT_SIZE(src_arr_size)                                       \
	(((dest)->size) + (src_arr_size) > ((dest)->capacity))               \
	?                                                                    \
		(jarr_reserve_f(dest, ((dest)->size) + (src_arr_size)) \
		&& (memcpy(((dest)->data), src_arr, sizeof(src_arr)),        \
		((dest)->size) += (src_arr_size), 1))                        \
	:                                                                    \
		(memcpy(((dest)->data), src_arr, sizeof(src_arr)),           \
		((dest)->size) += (src_arr_size), 1)                         \
JARR_MACRO_END

#define jarr_append_jarr(dest, ...)                                         \
	(PP_NARG(__VA_ARGS__) == 1)                                         \
		? private_jarr_append_jarr(dest, PP_FIRST_ARG(__VA_ARGS__)) \
		: private_jarr_append_njarr(dest, __VA_ARGS__, 0)

#define private_jarr_append_jarr(dest, src)                                                        \
JARR_MACRO_START                                                                                   \
	JARR_ASSERT_TYPECHECK(((dest)->data), ((dest)->src))                                       \
	(((dest)->size) + ((src)->size) > ((dest)->capacity))                                      \
	?                                                                                          \
		(jarr_reserve_f(dest, ((dest)->size) + ((src)->size))                              \
		&& (memcpy(((dest)->data), ((src)->data), ((src)->size) * sizeof(*((src)->data))), \
		((dest)->size) += ((src)->size), 1))                                               \
	:                                                                                          \
		(memcpy(((dest)->data), ((src)->data), ((src)->size) * sizeof(*((src)->data))),    \
		((dest)->size) += ((src)->size), 1)                                                \
JARR_MACRO_END

#define private_jarr_append_njarr(dest, src, ...)                                        \
JARR_MACRO_START                                                                         \
	JARR_ASSERT_TYPECHECK(((dest)->data), ((dest)->src))                             \
	(((dest)->size) + (n) > ((dest)->capacity))                                      \
	?                                                                                \
		(jarr_reserve_f(dest, ((dest)->size) + (n))                              \
		&& (memcpy(((dest)->data), ((src)->data), (n) * sizeof(*((src)->data))), \
		((dest)->size) += (n), 1))                                               \
	:                                                                                \
		(memcpy(((dest)->data), ((src)->data), (n) * sizeof(*((src)->data))),    \
		((dest)->size) += (n), 1)                                                \
JARR_MACRO_END

#define private_jarr_cat_u(this_jarr, argc, ...)                             \
(void)                                                                       \
JARR_MACRO_START                                                             \
	JARR_ASSERT_SIZE(argc)                                               \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, PP_FIRST_ARG(__VA_ARGS__))         \
	PP_LOOP_FROM(((this_jarr)->data), ((this_jarr)->size), __VA_ARGS__), \
	(((this_jarr)->size) += argc)                                        \
JARR_MACRO_END

#define jarr_st_cat(jarr_st, ...)                                            \
	private_jarr_cat_u(jarr_st, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define private_jarr_cat_f(this_jarr, argc, ...)                   \
JARR_MACRO_START                                                   \
	jarr_reserve_f(this_jarr, ((this_jarr)->size) + (argc))    \
	&& (private_jarr_cat_u(this_jarr, (argc), __VA_ARGS__), 1) \
JARR_MACRO_END

#define private_jarr_cat(this_jarr, argc, ...)                            \
JARR_MACRO_START                                                          \
	(((this_jarr)->size) + argc > ((this_jarr)->capacity))            \
		? (private_jarr_cat_f(this_jarr, (argc), __VA_ARGS__))    \
		: (private_jarr_cat_u(this_jarr, (argc), __VA_ARGS__), 1) \
JARR_MACRO_END

#define private_cat(F, this_jarr, ...) F(this_jarr, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_cat(this_jarr, ...) private_cat(private_jarr_cat, this_jarr, __VA_ARGS__)
#define jarr_cat_u(this_jarr, ...) private_cat(private_jarr_cat_u, this_jarr, __VA_ARGS__)
#define jarr_cat_f(this_jarr, ...) private_cat(private_jarr_cat_f, this_jarr, __VA_ARGS__)

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

#define jarr_push_front_u(this_jarr, value)                                     \
(void)                                                                                \
JARR_MACRO_START                                                                      \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value)                                      \
	memmove(((this_jarr)->data) + 1, ((this_jarr)->data), ((this_jarr)->size)++), \
	(*(((this_jarr)->data)) = value)                                              \
JARR_MACRO_END

#define jarr_push_front_f(this_jarr, value)         \
JARR_MACRO_START                                    \
	(likely(jarr_reserve_2x(this_jarr)))        \
	&& (jarr_push_front_u(this_jarr, value), 1) \
JARR_MACRO_END

#define jarr_push_front(this_jarr, value)                          \
JARR_MACRO_START                                                   \
	JARR_ASSERT_RIGHT_TYPE(this_jarr, value)                   \
	(unlikely(((this_jarr)->capacity) == ((this_jarr)->size))) \
	? jarr_push_front_f(this_jarr, value)                      \
	: (jarr_push_front_u(this_jarr, value), 1)                 \
JARR_MACRO_END

#define jarr_cmp_f(jarr_dest, jarr_src)                                                  \
	(memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))
#define jarr_cmp(jarr_dest, jarr_src)                                                    \
	((((jarr_dest)->size) != ((jarr_src)->size)) || jarr_cmp_f(jarr_dest, jarr_src))

#define jarr_foreach_index(elem, this_jarr)                      \
	for (size_t elem = 0, jarr_size__ = ((this_jarr)->size); \
		elem < jarr_size__; ++elem)

#define jarr_foreach(elem, this_jarr)                                                                                                          \
	for (typeof(*((this_jarr)->data)) *elem = ((this_jarr)->data), *const RESTRICT jarr_end__ = ((this_jarr)->data) + ((this_jarr)->size); \
		elem < jarr_end__; ++elem)

#define jarr_st_foreach(elem, arr)                                                                   \
	for (typeof(*(arr)) *elem = (arr), *const RESTRICT jarr_end__ = (&(JARR_SIZEOF_ARR((arr)))); \
		elem < jarr_end__; ++elem)

#define jarr_foreach_cout(elem, this_jarr)             \
	jarr_foreach(elem, this_jarr) pp_cout(*(elem))


#define jarr_begin(this_jarr) ((this_jarr)->data)
#define jarr_end(this_jarr) (((this_jarr)->data) + ((this_jarr)->size))

#ifdef JARR_HAS_TYPEOF
#	define jarr_typeof_data(this_jarr) typeof(((this_jarr)->data))
#	define jarr_typeof(this_jarr) typeof(((this_jarr)))
// TOODO: make const ptr give a warning if assigned to non-const
/* #	define jarr_cbegin(this_jarr) ((const typeof((this_jarr)->data))((this_jarr)->data)) */
/* #	define jarr_cend(this_jarr) ((const typeof((this_jarr)->data))(((this_jarr)->data) + ((this_jarr)->size))) */
#endif // JARR_HAS_TYPEOF

ALWAYS_INLINE static int private_jarr_realloc_exact(void **RESTRICT data, size_t *RESTRICT cap, const size_t target_cap, const size_t sizeof_data)
{
	void *RESTRICT tmp;
	if (unlikely(!(tmp = realloc(*data, target_cap * sizeof_data))))
		return 0;
	*data = tmp;
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
	*data = tmp;
	*cap = tmp_cap;
	return 1;
}

ALWAYS_INLINE static void private_jarr_swap(void **RESTRICT data, size_t *RESTRICT cap, size_t *RESTRICT size, void **RESTRICT other_data, size_t *RESTRICT other_cap, size_t *RESTRICT other_size)
{
	const size_t tmp_size = *size;
	const size_t tmp_cap = *cap;
	void *RESTRICT tmp_data = *data;
	*size = *other_size;
	*cap = *other_cap;
	*data = *other_data;
	*other_size = tmp_size;
	*other_cap = tmp_cap;
	*other_data = tmp_data;
}

#endif // JARR_H_DEF__
