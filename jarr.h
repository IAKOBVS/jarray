#ifndef JARR_H_DEF__
#define JARR_H_DEF__

/* rename to the right path */

#define JARR_PATH_TO_PP_VA_ARGS_MACROS_H "/home/james/c/pp_macros/pp_va_args_macros.h"

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

   at() will do bounds checking by asserting that index <= this->size.
   it will crash at runtime if assertion fails.
*/

#ifdef JARR_DEBUG
#	define JARR_ASSERT(x) assert(x),
#else
#	define JARR_ASSERT(x)
#endif // JARR_DEBUG

#define JARR_ASSERT_HAS_SPACE(jarr) JARR_ASSERT(((jarr)->size) != ((jarr)->capacity)),
#define JARR_ASSERT_NOT_NULL(jarr) JARR_ASSERT(((jarr)->data)),

#define JARR_INCLUDE
#define JARR_ALIGN_POWER_OF_TWO
#define JARR_64_BIT

#include JARR_PATH_TO_PP_VA_ARGS_MACROS_H
#include "macros.h" // .gch

#define JARR_ST_ASSERT_RIGHT_TYPE(T, expr) JARR_ST_ASSERT_TYPECHECK(*((T)->data), expr)

#ifdef JARR_INCLUDE
#	include <stdio.h>
#	include <string.h>
#	include <stdlib.h>
#	include <assert.h>
#endif // JARR_INCLUDE

#define JARR_MIN_CAP 8

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

#define jarr_st_get_cap(jarr_st)           \
	(sizeof(jarr_st)/sizeof(*jarr_st))

#define jarr_init(this_)         \
(void)(                          \
	((this_)->capacity) = 0, \
	((this_)->size) = 0,     \
	((this_)->data) = NULL   \
)

#define jarr_delete(this_)   \
(void)(                      \
	free((this_)->data), \
	jarr_init(this_)     \
)

#define jarr_at(this_, index)             \
(                                         \
	assert(index <= ((this_)->size)), \
	(((this_)->data) + index)         \
)

#define private_jarr_new_alloc(this_, cap)                                             \
JARR_MACRO_START                                                                       \
	JARR_ST_ASSERT_SIZE(cap)                                                       \
	((this_)->size) = 0,                                                           \
	(((this_)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP)),            \
	(likely(((this_)->data) = malloc(((this_)->capacity) * JARR_SIZEOF_T(this_)))) \
	|| (jarr_init(this_), 0)                                                       \
JARR_MACRO_END

#define jarr_reserve_f_exact(this_, cap)                      \
JARR_MACRO_START                                              \
	JARR_ST_ASSERT_SIZE(cap)                              \
	private_jarr_realloc_exact((void **)&((this_)->data), \
				&((this_)->capacity),         \
				cap,                          \
				sizeof(*((this_)->data)))     \
JARR_MACRO_END

#define jarr_reserve_f(this_, cap)                           \
JARR_MACRO_START                                             \
	JARR_ST_ASSERT_SIZE(cap)                             \
	private_jarr_realloc_grow((void **)&((this_)->data), \
			&((this_)->capacity),                \
			cap,                                 \
			sizeof(*((this_)->data)))            \
JARR_MACRO_END

#define jarr_reserve(this_, cap)               \
JARR_MACRO_START                               \
	JARR_ST_ASSERT_SIZE(cap)               \
	((cap) > ((this_)->capacity))          \
		? (jarr_reserve_f(this_, cap)) \
		: 1                            \
JARR_MACRO_END

#define private_jarr_reserve_x(this_, multiplier)                         \
JARR_MACRO_START                                                          \
	JARR_ST_ASSERT_SIZE(multiplier)                                   \
	jarr_reserve_f_exact(this_, ((multiplier) * ((this_)->capacity))) \
JARR_MACRO_END

#define jarr_reserve_2x(this_) private_jarr_reserve_x(this_, 2)
#define jarr_reserve_4x(this_) private_jarr_reserve_x(this_, 4)
#define jarr_reserve_8x(this_) private_jarr_reserve_x(this_, 8)
#define jarr_reserve_16x(this_) private_jarr_reserve_x(this_, 16)
#define jarr_reserve_32x(this_) private_jarr_reserve_x(this_, 32)
#define jarr_reserve_64x(this_) private_jarr_reserve_x(this_, 64)

#define jarr_shrink_to_fit_f(this_)                  \
JARR_MACRO_START                                     \
	jarr_reserve_f_exact(this_, ((this_)->size)) \
JARR_MACRO_END

#define jarr_shrink_to_fit(this_)                        \
JARR_MACRO_START                                         \
	(likely(((this_)->capacity) != ((this_)->size))) \
		? (jarr_shrink_to_fit_f(this_))          \
		: 1                                      \
JARR_MACRO_END

#define jarr_shrink_to_size_f(this_, size__) \
(void)                                       \
JARR_MACRO_START                             \
	((this_)->size) = size__             \
JARR_MACRO_END

#define jarr_shrink_to_size(this_, size__)           \
(void)                                               \
JARR_MACRO_START                                     \
	(size__ < ((this_)->size))                   \
	&& (jarr_shrink_to_size_f(this_, size__), 0) \
JARR_MACRO_END

#define jarr_shrink_to_f(this_, cap)     \
JARR_MACRO_START                         \
	jarr_reserve_f_exact(this_, cap) \
	&& (((this_)->size) = cap, 1)    \
JARR_MACRO_END

#define jarr_shrink_to(this_, cap)               \
JARR_MACRO_START                                 \
	(cap < ((this_)->size))                  \
		? (jarr_shrink_to_f(this_, cap)) \
		: 1                              \
JARR_MACRO_END

#define jarr_push_back_u(this_, value)               \
(void)                                               \
JARR_MACRO_START                                     \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)      \
	(((this_)->data)[((this_)->size)++] = value) \
JARR_MACRO_END

#define jarr_push_back_f(this_, value)                         \
JARR_MACRO_START                                               \
	(jarr_reserve_f_exact(this_, ((this_)->capacity) * 2)) \
	&& (jarr_push_back_u(this_, value), 1)                 \
JARR_MACRO_END

#define jarr_push_back(this_, value)                     \
JARR_MACRO_START                                         \
	 (((this_)->capacity) > ((this_)->size))         \
		 ? ((jarr_push_back_u(this_, value)), 1) \
		 : (jarr_push_back_f(this_, value))      \
JARR_MACRO_END

#define jarr_st_push_back(this_, value)      \
JARR_MACRO_START                             \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value) \
	jarr_push_back_u(this_, value)       \
JARR_MACRO_END

#define jarr_append_arr(dest, src_arr, src_arr_size)                   \
JARR_MACRO_START                                                       \
	JARR_ST_ASSERT_SIZE(src_arr_size)                              \
	(((dest)->size) + (src_arr_size) > ((dest)->capacity))         \
	?                                                              \
		(jarr_reserve_f(dest, ((dest)->size) + (src_arr_size)) \
		&& (memcpy(((dest)->data), src_arr, sizeof(src_arr)),  \
		((dest)->size) += (src_arr_size), 1))                  \
	:                                                              \
		(memcpy(((dest)->data), src_arr, sizeof(src_arr)),     \
		((dest)->size) += (src_arr_size), 1)                   \
JARR_MACRO_END

#define jarr_append_jarr(dest, src)                                                                \
JARR_MACRO_START                                                                                   \
	JARR_ST_ASSERT_TYPECHECK(((dest)->data), ((dest)->src))                                    \
	(((dest)->size) + ((src)->size) > ((dest)->capacity))                                      \
	?                                                                                          \
		(jarr_reserve_f(dest, ((dest)->size) + ((src)->size))                              \
		&& (memcpy(((dest)->data), ((src)->data), ((src)->size) * sizeof(*((src)->data))), \
		((dest)->size) += ((src)->size), 1))                                               \
	:                                                                                          \
		(memcpy(((dest)->data), ((src)->data), ((src)->size) * sizeof(*((src)->data))),    \
		((dest)->size) += ((src)->size), 1)                                                \
JARR_MACRO_END

#define private_jarr_cat_u(this_, argc, ...)                         \
(void)                                                               \
JARR_MACRO_START                                                     \
	JARR_ST_ASSERT_SIZE(argc)                                    \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, PP_FIRST_ARG(__VA_ARGS__))  \
	PP_LOOP_FROM(((this_)->data), ((this_)->size), __VA_ARGS__), \
	(((this_)->size) += argc)                                    \
JARR_MACRO_END

#define jarr_st_cat(jarr_st, ...)                                      \
	private_jarr_cat_u(jarr_st, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define private_jarr_cat_f(this_, argc, ...)                   \
JARR_MACRO_START                                               \
	jarr_reserve_f(this_, ((this_)->size) + (argc))        \
	&& (private_jarr_cat_u(this_, (argc), __VA_ARGS__), 1) \
JARR_MACRO_END

#define private_jarr_cat(this_, argc, ...)                            \
JARR_MACRO_START                                                      \
	(((this_)->size) + argc > ((this_)->capacity))                \
		? (private_jarr_cat_f(this_, (argc), __VA_ARGS__))    \
		: (private_jarr_cat_u(this_, (argc), __VA_ARGS__), 1) \
JARR_MACRO_END

#define private_cat(F, this_, ...) F(this_, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_cat(this_, ...) private_cat(private_jarr_cat, this_, __VA_ARGS__)
#define jarr_cat_u(this_, ...) private_cat(private_jarr_cat_u, this_, __VA_ARGS__)
#define jarr_cat_f(this_, ...) private_cat(private_jarr_cat_f, this_, __VA_ARGS__)

#define jarr_new(this_, ...)                                                 \
JARR_MACRO_START                                                             \
	(PP_NARG(__VA_ARGS__) == 1)                                          \
		? private_jarr_new_alloc(this_, PP_FIRST_ARG(__VA_ARGS__))   \
		: private_jarr_new(this_, PP_NARG(__VA_ARGS__), __VA_ARGS__) \
JARR_MACRO_END

#define jarr_new_auto(this_, ...)                                  \
JARR_MACRO_START                                                   \
	private_jarr_new(this_, PP_NARG(__VA_ARGS__), __VA_ARGS__) \
JARR_MACRO_END

#define private_jarr_new(this_, cap, ...)                                                 \
JARR_MACRO_START                                                                          \
	JARR_ST_ASSERT_SIZE(cap)                                                          \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, PP_FIRST_ARG(__VA_ARGS__))                       \
	((((this_)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP)),              \
	(likely(((this_)->data) = malloc((((this_)->capacity)) * JARR_SIZEOF_T(this_))))) \
	?                                                                                 \
		((PP_LOOP_FROM(((this_)->data), 0, __VA_ARGS__)),                         \
		(((this_)->size) = PP_NARG(__VA_ARGS__)), 1)                              \
	:                                                                                 \
		(jarr_init(this_), 0)                                                     \
JARR_MACRO_END

#define jarr_swap(this_, other_)                            \
JARR_MACRO_START                                            \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, *((other_)->data)) \
	private_jarr_swap((void **)&((this_)->data),        \
			&((this_)->capacity),               \
			&((this_)->size),                   \
			(void **)&((other_)->data),         \
			&((other_)->capacity),              \
			&((other_)->size))                  \
JARR_MACRO_END

#define jarr_pop_back(this_) (--((this_)->size))

#define jarr_pop_back_s(this_) \
(                              \
	((this_)->size)        \
	&& --((this_)->size)   \
)

#define jarr_pop_front_s(this_)                                             \
JARR_MACRO_START                                                            \
	((this_)->size)                                                     \
	&& memmove(((this_)->data), ((this_)->data + 1), --((this_)->size)) \
JARR_MACRO_END

#define jarr_pop_front(this_)                                            \
JARR_MACRO_START                                                         \
	memmove(((this_)->data), ((this_)->data + 1), --((this_)->size)) \
JARR_MACRO_END

#define jarr_push_front_u(this_, value)                                   \
(void)                                                                    \
JARR_MACRO_START                                                          \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)                           \
	memmove(((this_)->data) + 1, ((this_)->data), ((this_)->size)++), \
	(*(((this_)->data)) = value)                                      \
JARR_MACRO_END

#define jarr_push_front_f(this_, value)         \
JARR_MACRO_START                                \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value) \
	(likely(jarr_reserve_2x(this_)))        \
	&& (jarr_push_front_u(this_, value), 1) \
JARR_MACRO_END

#define jarr_push_front(this_, value)                      \
JARR_MACRO_START                                           \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)            \
	(unlikely(((this_)->capacity) == ((this_)->size))) \
	? jarr_push_front_f(this_, value)                  \
	: (jarr_push_front_u(this_, value), 1)             \
JARR_MACRO_END

#define jarr_push_front_s(this_, value)                            \
	(likely(this_)->capacity) && jarr_push_front(this_, value)

#define jarr_cmp_f(jarr_dest, jarr_src)                                        \
	(memcmp(((jarr_dest)->data), ((jarr_src)->data), ((jarr_dest)->size)))

#define jarr_cmp(jarr_dest, jarr_src)                \
	((((jarr_dest)->size) != ((jarr_src)->size)) \
	|| jarr_cmp_f(jarr_dest, jarr_src))

#define jarr_foreach_index(elem, this_)                      \
	for (size_t elem = 0, jarr_size__ = ((this_)->size); \
		elem < jarr_size__; ++elem)

#define jarr_foreach(elem, this_)                                              \
	for (typeof(*((this_)->data)) *elem = ((this_)->data),                 \
	*const JARR_RESTRICT__ jarr_end__ = ((this_)->data) + ((this_)->size); \
		elem < jarr_end__;                                             \
			++elem)

#define jarr_st_foreach(elem, arr)                                       \
	for (typeof(*(arr)) *elem = (arr),                               \
	*const JARR_RESTRICT__ jarr_end__ = (&(JARR_SIZEOF_ARR((arr)))); \
		elem < jarr_end__;                                       \
		++elem)

#define jarr_foreach_cout(elem, this_)             \
	jarr_foreach(elem, this_) pp_cout(*(elem))

#define jarr_begin(this_) ((this_)->data)
#define jarr_end(this_) (((this_)->data) + ((this_)->size))
#define jarr_cbegin(this_) private_jarr_constify(((this_)->data))
#define jarr_cend(this_) private_jarr_constify(((this_)->data) + ((this_)->size))

#ifdef JARR_HAS_TYPEOF
#	define jarr_typeof_data(this_) typeof(((this_)->data))
#	define jarr_typeof(this_) typeof(((this_)))
#endif // JARR_HAS_TYPEOF

JARR_INLINE__
JARR_WARN_UNUSED
static
int private_jarr_realloc_exact(void **JARR_RESTRICT__ data,
				size_t *JARR_RESTRICT__ cap,
				const size_t target_cap,
				const size_t sizeof_data)
{
	void *JARR_RESTRICT__ tmp;
	if (unlikely(!(tmp = realloc(*data, target_cap * sizeof_data))))
		return 0;
	*data = tmp;
	*cap = target_cap;
	return 1;
}

JARR_INLINE__
JARR_WARN_UNUSED
static
int private_jarr_realloc_grow(void **JARR_RESTRICT__ data,
				size_t *JARR_RESTRICT__ cap,
				const size_t target_cap,
				const size_t sizeof_data)
{
	size_t tmp_cap = *cap * 2;
	while (tmp_cap < target_cap)
		tmp_cap *= 2;
	void *JARR_RESTRICT__ const tmp = realloc(*data, tmp_cap * sizeof_data);
	if (unlikely(!tmp))
		return 0;
	*data = tmp;
	*cap = tmp_cap;
	return 1;
}

JARR_INLINE__
static
void private_jarr_swap(void **JARR_RESTRICT__ data,
			size_t *JARR_RESTRICT__ cap,
			size_t *JARR_RESTRICT__ size,
			void **JARR_RESTRICT__ other_data,
			size_t *JARR_RESTRICT__ other_cap,
				size_t *JARR_RESTRICT__ other_size)
{
	const size_t tmp_size = *size;
	const size_t tmp_cap = *cap;
	void *JARR_RESTRICT__ const tmp_data = *data;
	*size = *other_size;
	*cap = *other_cap;
	*data = *other_data;
	*other_size = tmp_size;
	*other_cap = tmp_cap;
	*other_data = tmp_data;
}

JARR_INLINE__
JARR_WARN_UNUSED
JARR_CONST__
static
const void *private_jarr_constify(const void *data) { return data; }

#endif // JARR_H_DEF__
