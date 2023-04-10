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

   _s (safe) macros will assert that jarray has been allocated.
   if not, it will crash.

   you shall check non-_u macros for non-zero value
   and decide how to error-handle malloc or realloc failures.

   realloc is done to a temporary pointer first,
   so the original pointer will not be nullified.

   at() will do bounds checking by asserting that index <= this->size.
   it will crash at runtime if assertion fails.
*/

#define JARR_ALIGN_POWER_OF_TWO
#define JARR_64_BIT

#ifdef JARR_DEBUG
#	define JARR_ASSERT(x) assert(x),
#else
#	define JARR_ASSERT(x)
#endif // JARR_DEBUG

#define JARR_ASSERT_HAS_SPACE(jarr) JARR_ASSERT(((jarr)->size) != ((jarr)->capacity)),
#define JARR_ASSERT_NOT_NULL(jarr) JARR_ASSERT(((jarr)->data)),

#include JARR_PATH_TO_PP_VA_ARGS_MACROS_H
#include "macros.h" // .gch

#define JARR_ST_ASSERT_RIGHT_TYPE(T, expr) JARR_ST_ASSERT_TYPECHECK(*((T)->data), expr);
#define JARR_ST_ASSERT_IS_SAME_JARR(this_, other_) JARR_ST_ASSERT(JARR_SAME_TYPE(((this_)->data), ((other_)->data)), "Passing two jarrays not of same type");

#ifdef __cplusplus
#	define JARR_NOEXCEPT__ noexcept
#else
#	define JARR_NOEXCEPT__
#endif // __cplusplus

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "macros.h"

#define JARR_MIN_CAP 8

#define jarray(T, name)          \
	struct {                 \
		size_t size;     \
		size_t capacity; \
		T *data;         \
	} name = {0}

#define jarr_static(T, capacity)                  \
	struct {                                  \
		size_t size;                      \
		T data[JARR_NEXT_POW2(capacity)]; \
	}

#define jarr_st_get_cap(jarr_st)           \
	(sizeof(jarr_st)/sizeof(*(jarr_st)))

#define jarr_init(this_)         \
do {                             \
	((this_)->data) = NULL;  \
	((this_)->capacity) = 0; \
	((this_)->size) = 0;     \
} while (0)

#define jarr_delete(this_)       \
do {                             \
	((this_)->capacity) = 0; \
	((this_)->size) = 0;     \
	free(((this_)->data));   \
	((this_)->data) = NULL;  \
} while (0)

#ifdef JSTR_H_DEF__
#define jarr_jstr_delete(jarr)                             \
do {                                                       \
	for (int jarr_i__ = 0, jarr_sz__ = ((jarr)->size); \
			jarr_i__ < jarr_sz__;              \
			++jarr_i__)                        \
		jstr_delete(&((this_)->data)[jarr_i__]);   \
	jarr_delete(this_);                                \
} while (0)
#endif // JSTR_H_DEF__

#define jarr_at(this_jarr, index)             \
(                                             \
	assert(index <= ((this_jarr)->size)), \
	(((this_jarr)->data) + index)         \
)

#define jarr_new(this_, cap)                                                  \
do {                                                                          \
	((this_)->size) = 0;                                                  \
	((this_)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP);     \
	((this_)->data) = malloc(((this_)->capacity) * JARR_SIZEOF_T(this_)); \
	if (unlikely(!((this_)->data)))                                       \
		((this_)->capacity) = 0;                                      \
} while (0)

#define jarr_new_auto(this_, ...)                              \
	jarr_new_cat(this_, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define jarr_new_cat(this_, cap, ...)                                           \
do {                                                                            \
	((this_)->capacity) = MAX(JARR_NEXT_POW2(2 * cap), JARR_MIN_CAP);       \
	((this_)->data) = malloc((((this_)->capacity)) * JARR_SIZEOF_T(this_)); \
	if (likely((this_)->data)) {                                            \
		PP_ST_ASSERT_IS_T_VA_ARGS(*((this_)->data), __VA_ARGS__);       \
		(PP_LOOP_FROM(((this_)->data), 0, __VA_ARGS__));                \
		((this_)->size) = PP_NARG(__VA_ARGS__);                         \
	} else {                                                                \
		((this_)->size) = 0;                                            \
		((this_)->capacity) = 0;                                        \
	}                                                                       \
} while (0)

#define jarr_reserve_f_exact(this_, cap_)                                              \
do {                                                                                   \
	((this_)->cap) = (cap_);                                                       \
	((this_)->data) = realloc(((this_)->data), (cap_) * sizeof(*((this_)->data))); \
	if (unlikely(!((this_)->data))) {                                              \
		((this_)->size) = 0;                                                   \
		((this_)->cap) = 0;                                                    \
	}                                                                              \
} while (0)

#define jarr_reserve_f(this_, cap_)                                                    \
do {                                                                                   \
	do {                                                                           \
		((this_)->capacity) *= 2;                                              \
	} while (((this_)->capacity) < cap_);                                          \
	((this_)->data) = realloc(((this_)->data), (cap_) * sizeof(*((this_)->data))); \
	if (unlikely(!((this_)->data))) {                                              \
		((this_)->size) = 0;                                                   \
		((this_)->cap) = 0;                                                    \
	}                                                                              \
} while (0)

#define jarr_reserve(this_, cap)            \
do {                                        \
	if ((cap) > ((this_)->capacity))    \
		jarr_reserve_f(this_, cap); \
} while (0)

#define private_jarr_reserve_x(this_, multiplier)                         \
	jarr_reserve_f_exact(this_, ((multiplier) * ((this_)->capacity)))

#define jarr_reserve_2x(this_) private_jarr_reserve_x(this_, 2)
#define jarr_reserve_4x(this_) private_jarr_reserve_x(this_, 4)
#define jarr_reserve_8x(this_) private_jarr_reserve_x(this_, 8)
#define jarr_reserve_16x(this_) private_jarr_reserve_x(this_, 16)
#define jarr_reserve_32x(this_) private_jarr_reserve_x(this_, 32)
#define jarr_reserve_64x(this_) private_jarr_reserve_x(this_, 64)

#define jarr_shrink_to_fit_f(this_)                  \
	jarr_reserve_f_exact(this_, ((this_)->size)) \

#define jarr_shrink_to_fit(this_)                           \
do {                                                        \
	if (likely(((this_)->capacity) != ((this_)->size))) \
		jarr_shrink_to_fit_f(this_)                 \
} while (0)

#define jarr_shrink_to_size_f(this_, size_) \
(void)(                                     \
	((this_)->size) = size_             \
)

#define jarr_shrink_to_size(this_, size_)            \
do {                                                 \
	if (size_ < ((this_)->size))                 \
		jarr_shrink_to_size_f(this_, size_); \
} while (0)

#define jarr_shrink_to_f(this_, cap)      \
do {                                      \
	jarr_reserve_f_exact(this_, cap); \
	if (likely((this_)->data))        \
		((this_)->size) = cap;    \
} while (0)

#define jarr_shrink_to(this_, cap)           \
do {                                         \
	if (cap < ((this_)->size))           \
		jarr_shrink_to_f(this_, cap);\
} while (0)

#define jarr_push_back_u(this_, value)               \
do {                                                 \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)      \
	(((this_)->data)[((this_)->size)++] = value);\
} while (0)

#define jarr_push_back_f(this_, value)                        \
do {                                                          \
	jarr_reserve_f_exact(this_, ((this_)->capacity) * 2); \
	if (likely(((this_)->data)))                          \
		jarr_push_back_u(this_, value);               \
} while (0)

#define jarr_push_back(this_, value)               \
do {                                               \
	if (((this_)->capacity) > ((this_)->size)) \
		 jarr_push_back_u(this_, value);   \
	else                                       \
		jarr_push_back_f(this_, value);    \
} while (0)

#define jarr_st_push_back(this_, value)         \
JARR_MACRO_START                                \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value) \
	jarr_push_back_u(this_, value)          \
JARR_MACRO_END

#define jarr_append_arr(dest, src, src_size)                       \
do {                                                               \
	JARR_ST_ASSERT_IS_SAME_JARR_T(dest, src)                   \
	if (((dest)->size) + (src_size) > ((dest)->capacity)) {    \
		jarr_reserve_f(dest, ((dest)->size) + (src_size)); \
		if (likely(((this_)->data))) {                     \
			memcpy(((dest)->data), src, sizeof(src));  \
			((dest)->size) += (src_size);              \
		}                                                  \
	} else {                                                   \
		memcpy(((dest)->data), src, sizeof(src));          \
		((dest)->size) += (src_size);                      \
	}                                                          \
} while (0)

#define jarr_append_jarr(dest, src)                                                                    \
do {                                                                                                   \
	JARR_ST_ASSERT_IS_SAME_JARR_T(dest, src)                                                       \
	if (((dest)->size) + ((src)->size) > ((dest)->capacity)) {                                     \
		jarr_reserve_f(dest, ((dest)->size) + ((src)->size));                                  \
		if (likely(((dest)->data))) {                                                          \
			memcpy(((dest)->data), ((src)->data), ((src)->size) * sizeof(*((src)->data))); \
			((dest)->size) += ((src)->size);                                               \
		}                                                                                      \
	} else {                                                                                       \
		(memcpy(((dest)->data), ((src)->data), ((src)->size) * sizeof(*((src)->data))),        \
		((dest)->size) += ((src)->size), 1)                                                    \
	}                                                                                              \
} while (0)

#define private_jarr_cat_u(this_, argc, ...)                         \
do {                                                                 \
	PP_ST_ASSERT_IS_T_VA_ARGS(*((this_)->data), __VA_ARGS__);    \
	PP_LOOP_FROM(((this_)->data), ((this_)->size), __VA_ARGS__), \
	(((this_)->size) += argc)                                    \
} while (0)

#define jarr_st_cat(jarr_st, ...)                                      \
	private_jarr_cat_u(jarr_st, PP_NARG(__VA_ARGS__), __VA_ARGS__)

#define private_jarr_cat_f(this_, argc, ...)                        \
do {                                                                \
	if (jarr_reserve_f(this_, ((this_)->size) + (argc)))        \
		private_jarr_cat_u(this_, (argc), __VA_ARGS__), 1 \
} while (0)

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

#ifdef JARR_HAS_TYPEOF

#define jarr_swap(this_, other_)                                     \
do {                                                                 \
	JARR_ST_ASSERT_IS_SAME_JARR_T(this_, other_)                 \
	size_t tmp_size = ((this_)->size);                           \
	size_t tmp_cap = ((this_)->capacity);                        \
	typeof(((this_)->data)) tmp_data = ((this_)->data);          \
                                                                     \
	((this_)->size) = ((other_)->size);                          \
	((this_)->capacity) = ((other_)->capacity);                  \
	((this_)->data) = ((other_)->data);                          \
                                                                     \
	((other_)->size) = tmp_size;                                 \
	((other_)->capacity) = tmp_cap;                              \
	((other_)->data) = tmp_data;                                 \
} while (0)

#else

#define jarr_swap(this_, other_)                 \
	private_jarr_swap(&((this_)->data),      \
			  &((this_)->capacity),  \
			  &((this_)->size),      \
			  &((other_)->data),     \
			  &((other_)->capacity), \
			  &((other_)->size))

#endif // JARR_HAS_TYPEOF

#define jarr_pop_back(this_) (--((this_)->size))

#define jarr_pop_back_s(this_) \
(                              \
	((this_)->size)        \
	&& --((this_)->size)   \
)

#define jarr_pop_front_s(this_)                                             \
(                                                                           \
	((this_)->size)                                                     \
	&& memmove(((this_)->data), ((this_)->data + 1), --((this_)->size)) \
)

#define jarr_pop_front(this_)                                            \
	memmove(((this_)->data), ((this_)->data + 1), --((this_)->size))

#define jarr_push_front_u(this_, value)                                   \
do {                                                                      \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)                           \
	memmove(((this_)->data) + 1, ((this_)->data), ((this_)->size)++); \
	(*(((this_)->data)) = value);                                     \
} while (0)


#define jarr_push_front_f(this_, value)          \
do {                                             \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)  \
	if (likely(jarr_reserve_2x(this_)))      \
		jarr_push_front_u(this_, value); \
} while (0)

#define jarr_push_front(this_, value)                         \
do {                                                          \
	JARR_ST_ASSERT_RIGHT_TYPE(this_, value)               \
	if (unlikely(((this_)->capacity) == ((this_)->size))) \
		jarr_push_front_f(this_, value);              \
	else                                                  \
		jarr_push_front_u(this_, value);              \
} while (0)

#define jarr_push_front_s(this_, value)                            \
	(assert(((this_)->capacity)), jarr_push_front(this_, value))

#define jarr_cmp_f(dest, src)                                   \
JARR_MACRO_START                                                \
	JARR_ST_ASSERT_IS_SAME_JARR_T(dest, src)                \
	(memcmp(((dest)->data), ((src)->data), ((dest)->size))) \
JARR_MACRO_END

#define jarr_cmp(dest, src)                      \
JARR_MACRO_START                                 \
	JARR_ST_ASSERT_IS_SAME_JARR_T(dest, src) \
	(((dest)->size) != ((src)->size))        \
	|| cmp_f(dest, src)                      \
JARR_MACRO_END

#define jarr_foreach_index(elem, this_)                      \
	for (size_t elem = 0, jarr_size_ = ((this_)->size); \
		elem < jarr_size_; ++elem)

#define jarr_foreach(elem, this_)                              \
	for (typeof(*((this_)->data)) *elem = ((this_)->data), \
	*const jarr_end__ = ((this_)->data) + ((this_)->size); \
		elem < jarr_end__;                             \
			++elem)

#define jarr_st_foreach(elem, arr)                       \
	for (typeof(*(arr)) *elem = (arr),               \
	*const jarr_end__ = (&(JARR_SIZEOF_ARR((arr)))); \
		elem < jarr_end__;                       \
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
static
void private_jarr_swap(void **JARR_RESTRICT__ data,
			size_t *JARR_RESTRICT__ cap,
			size_t *JARR_RESTRICT__ size,
			void **JARR_RESTRICT__ other_data,
			size_t *JARR_RESTRICT__ other_cap,
			size_t *JARR_RESTRICT__ other_size) JARR_NOEXCEPT__
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
const void *private_jarr_constify(const void *data) JARR_NOEXCEPT__ { return data; }

#endif // JARR_H_DEF__
