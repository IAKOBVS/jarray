#include "test.h"
#include "../src/jarr.h"

#define T_ZERO(func)                               \
	do {                                       \
		func;                              \
		ASSERT_ERRFUNC(func, j.size == 0); \
	} while (0)

#define T(func, ...)                                                               \
	do {                                                                       \
		T expected[] = { (int)__VA_ARGS__ };                               \
		func;                                                              \
		ASSERT_ERRFUNC(func, j.data);                                      \
		ASSERT_ERRFUNC(func, j.size == JARR_ARRAY_COUNT(expected));        \
		ASSERT_ERRFUNC(func, !memcmp(j.data, expected, sizeof(expected))); \
	} while (0)

int
main(int argc, char **argv)
{
	START();
	typedef int T;
	jarr_ty(T, j) = JARR_INIT;
	T_ZERO(jarr_popback(&j));
	T_ZERO(jarr_popback(&j));
	T_ZERO(jarr_popfront(&j));
	T_ZERO(jarr_popfront(&j));
	T(jarr_pushback(&j, 1), 1);
	T(jarr_pushback(&j, 2), 1, 2);
	T(jarr_popback(&j), 1);
	T(jarr_pushfront(&j, 2), 2, 1);
	T(jarr_popfront(&j), 1);
	T_ZERO(jarr_popfront(&j));
	jarr_free(&j);
	SUCCESS();
	return EXIT_SUCCESS;
}
