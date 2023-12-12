/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2023 James Tirta Halim <tirtajames45 at gmail dot com>
   This file is part of the jarray library.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE. */

#ifndef JARR_H
#define JARR_H 1

#ifdef __cplusplus
#	define PJARR_BEGIN_DECLS extern "C" {
#	define PJARR_END_DECLS   }
#else
#	define PJARR_BEGIN_DECLS
#	define PJARR_END_DECLS
#endif

PJARR_BEGIN_DECLS
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
PJARR_END_DECLS

#define JARR_MIN_CAP            ((sizeof(size_t) == 8) ? 24 : 16)
#define JARR_MALLOC_ALIGNMENT   (sizeof(size_t) + sizeof(size_t))
#define JARR_ARRAY_COUNT(array) (sizeof(array) / sizeof(array[0]))
#define JARR_GROWTH             1.5

#define JARR_ALIGN_DOWN(base, size)     ((base) & -((uintptr_t)(size)))
#define JARR_ALIGN_UP(base, size)       JARR_ALIGN_DOWN((base) + (size)-1, (size))
#define JARR_ALIGN_UP_STR(base)         JARR_ALIGN_UP((uintptr_t)base, JARR_MALLOC_ALIGNMENT)
#define JARR_ALIGN_DOWN_STR(base)       JARR_ALIGN_DOWN((uintptr_t)base, JARR_MALLOC_ALIGNMENT)
#define JARR_PTR_TOPTR(p)               ((uintptr_t)p)
#define JARR_PTR_DIFF(p1, p2)           ((size_t)((uintptr_t)(p1) - (uintptr_t)(p2)))
#define JARR_PTR_IS_ALIGNED(base, size) (!(((uintptr_t)(base)) & ((size)-1)))
#define JARR_PTR_ALIGN_DOWN(base, size) JARR_ALIGN_DOWN((uintptr_t)(base), (size))
#define JARR_PTR_ALIGN_UP(base, size)   JARR_ALIGN_UP((uintptr_t)(base), (size))
#define JARR_PTR_IS_ALIGNED_STR(base)   JARR_PTR_IS_ALIGNED(base, JARR_MALLOC_ALIGNMENT)

#ifndef JARR_INLINE
#	ifdef __inline
#		define JARR_INLINE __inline
#	elif (defined __cplusplus \
	       || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L))
#		define JARR_INLINE inline
#	else
#		define JARR_INLINE
#	endif
#endif

#ifdef __glibc_has_builtin
#	define JARR_HAS_BUILTIN(name) __glibc_has_builtin(name)
#elif defined __has_builtin
#	define JARR_HAS_BUILTIN(name) __has_builtin(name)
#endif /* has_builtin */

#if defined __glibc_unlikely && defined __glibc_likely
#	define jarr_likely(x)   __glibc_likely(x)
#	define jarr_unlikely(x) __glibc_unlikely(x)
#elif (defined __GNUC__ && (__GNUC__ >= 3)) || defined __clang__
#	if JARR_HAS_BUILTIN(__builtin_expect)
#		define jarr_likely(x)   __builtin_expect((x), 1)
#		define jarr_unlikely(x) __builtin_expect((x), 0)
#	endif
#else
#	define jarr_likely(x)   (x)
#	define jarr_unlikely(x) (x)
#endif /* unlikely */

#ifdef __attribute_maybe_unused__
#	define JARR_ATTR_MAYBE_UNUSED __attribute_maybe_unused__
#elif JARR_HAS_ATTRIBUTE(__unused__)
#	define JARR_ATTR_MAYBE_UNUSED __attribute__((__unused__))
#endif

#define JARR_INIT \
	{         \
		0 \
	}

#define jarr_ty(T, name)                   \
	typedef struct pjarr_##name##_ty { \
		T *data;                   \
		size_t size;               \
		size_t capacity;           \
	} jarr_##name##_ty;                \
	jarr_##name##_ty name

#define jarr_chk(j)         (jarr_unlikely(PJARR_DATA(j) == NULL))
#define jarr_err(msg)       pjarr_err(msg)
#define jarr_errdie(msg)    pjarr_errdie(msg)
#define jarr_foreachi(j, i) for (size_t i = 0, _pjarr_foreachi_size_##i = (j)->size; i < _pjarr_foreachi_size_##i; ++i)
#define jarr_debug(j)       fprintf(stderr, "size:%zu\ncap:%zu\n", (j)->size, (j)->capacity);
#define jarr_start(j)       PJARR_DATA(j)
#define jarr_end(j)         (PJARR_DATA(j) + PJARR_SZ(j))
#if JARR_DEBUG
#	define jarr_at(j, idx) \
		(jarr_likely(idx < PJARR_SZ(j)) ? (PJARR_DATA(j) + (idx)) : (jarr_errdie("Index out of bounds."), PJARR_DATA(j)))
#else
#	define jarr_at(j, idx) \
		(PJARR_DATA(j) + (idx))
#endif
#define PJARR_ELEMSZ(j)               (sizeof((PJARR_DATA(j))[0]))
#define PJARR_ARRSZ(j)                (sizeof(PJARR_DATA(j)) / sizeof((PJARR_DATA(j))[0]))
#define PJARR_DATA(j)                 ((j)->data)
#define PJARR_SZ(j)                   ((j)->size)
#define PJARR_CAP(j)                  ((j)->capacity)
#define PJARR_MIN_CAP(j)              (JARR_MIN_CAP / PJARR_ELEMSZ(j))
#define PJARR_MEMMOVE(j, dst, src, n) memmove(dst, src, (n)*PJARR_ELEMSZ(j))
#define PJARR_MEMCPY(j, dst, src, n)  memcpy(dst, src, (n)*PJARR_ELEMSZ(j))
#define PJARR_ALIGN_UP(j, base)       ((PJARR_ELEMSZ(j) <= (sizeof(size_t) + sizeof(size_t))) ? JARR_ALIGN_UP_STR(base) : base)

#if JARR_PANIC
#	define PJARR_MALLOC_ERR(j, do_on_malloc_err)         \
		if (jarr_unlikely((PJARR_DATA(j)) == NULL)) { \
			PJARR_NULLIFY_MEMBERS(j);             \
			do_on_malloc_err;                     \
			jarr_errdie("");                      \
		}
#else
#	define PJARR_MALLOC_ERR(j, do_on_malloc_err)         \
		if (jarr_unlikely((PJARR_DATA(j)) == NULL)) { \
			PJARR_NULLIFY_MEMBERS(j);             \
			do_on_malloc_err;                     \
		}
#endif

#define PJARR_GROW(old_cap, new_cap)                                       \
	do {                                                               \
		JARR_STATIC_ASSERT_IS_SIZE(old_cap);                       \
		JARR_STATIC_ASSERT_IS_SIZE(new_cap);                       \
		if (jarr_unlikely(old_cap == 0))                           \
			old_cap = JARR_MIN_CAP / JARR_ALLOC_MULTIPLIER;    \
		do                                                         \
			(old_cap) = (size_t)((old_cap)*JARR_GROWTH);       \
		while ((old_cap) < (new_cap));                             \
		(old_cap) = JARR_ALIGN_UP(old_cap, JARR_MALLOC_ALIGNMENT); \
	} while (0)
#define jarr_reserve(j, new_cap)                                                                                   \
	do {                                                                                                       \
		if (jarr_unlikely(PJARR_CAP(j) == 0))                                                              \
			PJARR_CAP(j) = PJARR_MIN_CAP(j);                                                           \
		PJARR_GROW(PJARR_CAP(j), new_cap);                                                                 \
		PJARR_CAP(j) = PJARR_ALIGN_UP(j, PJARR_CAP(j) * PJARR_ELEMSZ(j));                                  \
		PJARR_DATA(j) = PJARR_CAST(PJARR_DATA(j), realloc(PJARR_DATA(j), PJARR_CAP(j) * PJARR_ELEMSZ(j))); \
		if (jarr_chk(j))                                                                                   \
			break;                                                                                     \
		PJARR_CAP(j) /= PJARR_ELEMSZ(j);                                                                   \
	} while (0)
#define jarr_reserveexact(j, new_cap)                                                                              \
	do {                                                                                                       \
		PJARR_CAP(j) = PJARR_ALIGN_UP(j, PJARR_CAP(j) * PJARR_ELEMSZ(j));                                  \
		PJARR_DATA(j) = PJARR_CAST(PJARR_DATA(j), realloc(PJARR_DATA(j), PJARR_CAP(j) * PJARR_ELEMSZ(j))); \
		if (jarr_chk(j))                                                                                   \
			break;                                                                                     \
		PJARR_CAP(j) /= PJARR_ELEMSZ(j);                                                                   \
	} while (0)

#define PJARR_NULLIFY_MEMBERS(j)  \
	do {                      \
		PJARR_SZ(j) = 0;  \
		PJARR_CAP(j) = 0; \
	} while (0)
#define PJARR_NULLIFY(j)                  \
	do {                              \
		PJARR_DATA(j) = NULL;     \
		PJARR_NULLIFY_MEMBERS(j); \
	} while (0)

#define jarr_free(j)                 \
	do {                         \
		free(PJARR_DATA(j)); \
		PJARR_NULLIFY(j);    \
	} while (0)

/* Pop PTR[0]. */
#define jarr_popfront(j)                                                           \
	do {                                                                       \
		if (jarr_unlikely(PJARR_SZ(j) == 0))                               \
			break;                                                     \
		PJARR_MEMMOVE(j, PJARR_DATA(j), PJARR_DATA(j) + 1, --PJARR_SZ(j)); \
	} while (0)
/* Pop end of PTR. */
#define jarr_popback(j)                                  \
	do {                                             \
		if (jarr_unlikely(PJARR_SZ(j) == 0))     \
			break;                           \
		*(PJARR_DATA(j) + --PJARR_SZ(j)) = '\0'; \
	} while (0)
/* Push VAL to back of PTR. */
#define jarr_pushback(j, value)                                           \
	do {                                                              \
		if (jarr_unlikely(PJARR_CAP(j) < PJARR_SZ(j) + 1)) {      \
			if (jarr_unlikely(PJARR_CAP(j) == 0))             \
				PJARR_CAP(j) = PJARR_MIN_CAP(j);          \
			jarr_reserveexact(j, PJARR_CAP(j) * JARR_GROWTH); \
			PJARR_MALLOC_ERR(j, break)                        \
		}                                                         \
		*(PJARR_DATA(j) + PJARR_SZ(j)++) = (value);               \
	} while (0)
/* Push VAL to front of P. */
#define jarr_pushfront(j, value)                                                   \
	do {                                                                       \
		if (jarr_unlikely(PJARR_CAP(j) < PJARR_SZ(j) + 1)) {               \
			PJARR_CAP(j) = PJARR_MIN_CAP(j);                           \
			jarr_reserveexact(j, PJARR_CAP(j) * JARR_GROWTH);          \
			PJARR_MALLOC_ERR(j, break)                                 \
		}                                                                  \
		PJARR_MEMMOVE(j, PJARR_DATA(j) + 1, PJARR_DATA(j), PJARR_SZ(j)++); \
		*PJARR_DATA(j) = (value);                                          \
	} while (0)

#undef R

PJARR_BEGIN_DECLS

JARR_ATTR_MAYBE_UNUSED
static void
pjarr_errdie(const char *filename,
             const unsigned int line,
             const char *func,
             const char *msg)
{
	fprintf(stderr, "%s:%u:%s:%s:%s\n", filename, line, func, strerror(errno), msg);
	exit(EXIT_FAILURE);
}

JARR_ATTR_MAYBE_UNUSED
static void
pjarr_err(const char *filename,
          const unsigned int line,
          const char *func,
          const char *msg)
{
	fprintf(stderr, "%s:%u:%s:%s:%s\n", filename, line, func, strerror(errno), msg);
}

PJARR_END_DECLS

#ifdef __cplusplus
template <typename T, typename Other>
static T
PJARR_CAST(T, Other other)
{
	return (T)other;
}
#else
#	define PJARR_CAST(T, other) (other)
#endif /* cast */

#endif /* JARR_H */
