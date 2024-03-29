#ifndef JSTR_TEST_H
#define JSTR_TEST_H

#define JSTR_PANIC 1
#define JSTR_TEST  1
#define JSTR_DEBUG 1
/* Force use of slower simple functions. */
#define JSTR_USE_SIMPLE 0

#define JSTR_BUILT

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>

#include "../src/jarr.h"

#define SUCCESS()                                                   \
	do {                                                        \
		(void)argc;                                         \
		(void)argv;                                         \
		PRINT("%s ", __FILE__);                             \
		for (; *argv; ++argv)                               \
			if (!strncmp(*argv, "-D", 2))               \
				PRINT("%s ", *argv + strlen("-D")); \
		PRINT("succeeded.\n");                              \
	} while (0)

/* clang-format off */
#define EMPTY(p)          (sizeof(p) == sizeof(const char *) ? ((const char *)p) == (const char *)NULL ? "(null)" : (p) : (p))
#define PRINT(...)    printf(__VA_ARGS__)
#define PRINTERR(...) fprintf(stderr, __VA_ARGS__)
#define START() do{}while(0)

JARR_INLINE static int TOLOWER(int c)
{
	c = (char)c;
	return (unsigned char)(c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c);
}

JARR_INLINE static int TOUPPER(int c)
{
	c = (char)c;
	return (unsigned char)(c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c);
}

JARR_INLINE static char *clean_func(const char *func)
{
	for (; !isalpha(*func); ++func);
	return (char *)func;
}

#if VERBOSE
#	define TESTING(func) PRINT("Testing %s().\n", clean_func(#func))
#else
#	define TESTING(func)
#endif
/* clang-format on */

#define ASSERT_RESULT(func, expr, result, expected)                      \
	do {                                                             \
		if (jarr_unlikely(!(expr))) {                            \
			PRINTERR("Assertion failure: %s().\nResult:%s\n" \
			         "Expected:%s\n",                        \
			         #func,                                  \
			         EMPTY(result),                          \
			         EMPTY(expected));                       \
			assert(expr);                                    \
		}                                                        \
	} while (0)

#define ASSERT_ERRFUNC(func, expr)                                     \
	do {                                                           \
		if (jarr_unlikely(!(expr))) {                          \
			PRINTERR("Assertion failure: %s().\n", #func); \
			assert(expr);                                  \
		}                                                      \
	} while (0)

#endif /* JSTR_TEST_H */
