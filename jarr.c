#include "jarr.h"
#include <stdio.h>

/* #define JARR_TEMPLATES */

#ifdef JARR_TEMPLATES

#define JARR_INIT(T)                          \
ALWAYS_INLINE void jarr_init_##T(T *jarr_ptr) \
{                                             \
	jarr_init(jarr_ptr);                  \
}

JARR_TEMPLATE_T(JARR_INIT)

#define f_jarr_init(jarr_ptr) JARR_GENERIC(jarr_init, jarr_ptr, )

#define JARR_DELETE_NOCHECK(T)                          \
ALWAYS_INLINE void jarr_delete_nocheck_##T(T *jarr_ptr) \
{                                                       \
	jarr_delete_nocheck(jarr_ptr);                  \
}

JARR_TEMPLATE_T(JARR_DELETE_NOCHECK)

#define f_jarr_delete_nocheck(jarr_ptr) JARR_GENERIC(jarr_delete_nocheck, jarr_ptr, )

#define JARR_DELETE(T)                          \
ALWAYS_INLINE void jarr_delete_##T(T *jarr_ptr) \
{                                               \
	jarr_delete(jarr_ptr);                  \
}

JARR_TEMPLATE_T(JARR_DELETE)

#define f_jarr_delete(jarr_ptr) JARR_GENERIC(jarr_delete, jarr_ptr, )

#define JARR_NEW_ALLOC(T)                                     \
ALWAYS_INLINE int jarr_new_alloc_##T(T *jarr_ptr, size_t cap) \
{                                                             \
	return jarr_new_alloc(jarr_ptr, cap);                 \
}

JARR_TEMPLATE_T(JARR_NEW_ALLOC)

#define f_jarr_new_alloc(jarr_ptr) JARR_GENERIC(jarr_new_alloc, jarr_ptr, cap)

#define JARR_RESERVE_NOCHECK(T)\
ALWAYS_INLINE int jarr_reserve_nocheck_##T(T *jarr_ptr, size_t cap) \
{                                                                   \
	return jarr_reserve_nocheck(jarr_ptr, cap);                 \
}

JARR_TEMPLATE_T(JARR_RESERVE_NOCHECK)

#define f_jarr_reserve_nocheck(jarr_ptr, cap) JARR_GENERIC(jarr_reserve_nocheck, jarr_ptr, cap)

#endif // end of templates

#ifdef JARR_DEBUG

#include <assert.h>
static ALWAYS_INLINE int debug()
{
	int ret;
	char a[100];
	jarray_int_t arr;
	jarr_init(&arr);
	assert( jarr_new(&arr, 1, 2, 3) );
	assert( jarr_append(&arr, a, 10) );
	assert( jarr_cat(&arr, 1, 3, 4) );
	assert( jarr_push_back(&arr, 3) );
	assert( jarr_reserve(&arr, 100) );
	assert( jarr_shrink(&arr) );
	jarr_delete(&arr);
	return 1;
}

int main()
{
	assert(debug());
	return 0;
}

#endif
