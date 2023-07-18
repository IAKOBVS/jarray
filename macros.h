#ifndef JARR_MACROS_H_DEF
#define JARR_MACROS_H_DEF

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) || defined(__GNUC__) && (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#	define JARR_WARN_UNUSED __attribute__((warn_unused_result))
#elif defined(__attribute_warn_unused_result__)
#	define JARR_WARN_UNUSED __attribute_warn_unused_result__
#else
#	define JARR_WARN_UNUSED
#endif // __attribute__unused

#if (defined(__GNUC__) && (__GNUC__ >= 4)) || (defined(__clang__) && (__clang_major__ >= 3))
#	define JARR_HAS_TYPEOF
#endif // JARR_HAS_TYPEOF

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#	define JARR_HAS_GENERIC
#endif // JARR_HAS_GENERIC

#if defined(static_assert)
#	define JARR_ST_ASSERT(expr, msg) static_assert(expr, msg)
#	define JARR_HAS_STATIC_ASSERT
#elif __STDC_VERSION__ >= 201112L
#	define JARR_ST_ASSERT(expr, msg) _Static_assert(expr, msg)
#	define JARR_HAS_STATIC_ASSERT
#else
#	define JARR_ST_ASSERT(expr, msg)
#endif // static_assert

#ifdef JARR_ALIGN_POWER_OF_TWO
#	ifdef JARR_64_BIT
#		define JARR_NEXT_POW2(x) private_jarr_next_pow2_64(x)
#	elif JARR_32_BIT
#		define JARR_NEXT_POW2(x) private_jarr_next_pow2_32(x)
#	else
#		define JARR_NEXT_POW2(x) (x)
#	endif // JARR_64_BIT
#endif // JARR_ALIGN_POWER_OF_TWO

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	define JARR_RESTRICT restrict
#elif defined(__GNUC__) || defined(__clang__)
#	define JARR_RESTRICT __restrict__
#elif defined(_MSC_VER)
#	define JARR_RESTRICT __restrict
#else
#	define JARR_RESTRICT
#endif // restrict

#if defined(__PRETTY_FUNCTION__)
#	define CURR_FUNC __PRETTY_FUNCTION__
#elif defined(__FUNCTION__)
#	define CURR_FUNC __FUNCTION__
#elif defined(__func__)
#	define CURR_FUNC __func__
#else
#	define CURR_FUNC ""
#endif // __func__

#if (defined(__GNUC__) && (__GNUC__ >= 3)) || (defined(__clang__) && __has_builtin(__builtin_expect))
#	define likely(x) __builtin_expect(!!(x), 1)
#	define unlikely(x) __builtin_expect(!!(x), 0)
#else
#	define likely(x) (x)
#	define unlikely(x) (x)
#endif // __has_builtin(__builtin_expect)

#if defined(__GNUC__) || defined(__clang__)
#	define JARR_INLINE __attribute__((always_inline)) inline
#	if __has_attribute(pure)
#		define JARR_PURE __attribute__((pure))
#	else
#		define JARR_PURE
#	endif // JARR_PURE
#	if __has_attribute(const)
#		define JARR_CONST __attribute__((const))
#	else
#		define JARR_CONST
#	endif // JARR_CONST
#	if __has_attribute(flatten)
#		define JARR_FLATTEN __attribute__((flatten))
#	else
#		define JARR_FLATTEN
#	endif // JARR_FLATTEN
#elif defined(_MSC_VER)
#	define JARR_INLINE __forceinline inline
#	define JARR_PURE __declspec(noalias)
#	define JARR_CONST __declspec(restrict)
#	define JARR_FLATTEN
#else
#	define JARR_INLINE inline
#	define JARR_PURE
#	define JARR_CONST
#	define JARR_FLATTEN
#endif // __GNUC__ || __clang__ || _MSC_VER

#if defined(__GNUC__) || defined(__clang__)
#	include <stdint.h>
#	if __has_builtin(__builtin_clzll) && defined(JARR_64_BIT)

		JARR_CONST
		JARR_INLINE
		uint64_t private_jarr_next_pow2_64(uint64_t x)
		{
			return 1ull << (64 - __builtin_clzll(x - 1));
		}

#	endif // __has_builtin(__builtin_clzll)
#	if __has_builtin(__builtin_clz) && defined(JARR_32_BIT)

		JARR_CONST
		JARR_INLINE
		uint32_t private_jarr_next_pow2_32(uint32_t x)
		{
			return 1u << (32 - __builtin_clz(x - 1));
		}

#	endif // __has_builtin(__builtin_clz)
#elif defined(_MSC_VER)
#	include <stdint.h>
#	include <intrin.h>
#	pragma intrinsic(_BitScanReverse64)

#ifdef JARR_32_BIT
	JARR_CONST JARR_INLINE uint32_t private_jarr_next_pow2_32(uint32_t x)
	{
		unsigned long index;
		_BitScanReverse(&index, x - 1);
		return 1 << (index + 1);
	}
#endif // JARR_32_BIT

#ifdef JARR_64_BIT
	JARR_CONST JARR_INLINE uint64_t private_jarr_next_pow2_64(uint64_t x)
	{
		unsigned long index;
		_BitScanReverse64(&index, x - 1);
		return 1ull << (index + 1);
	}
#endif // JARR_64_BIT

#else
#	include <stddef.h>

#ifdef JARR_32_BIT
	JARR_CONST JARR_INLINE size_t private_jarr_next_pow2_32(size_t x)
	{
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}
#endif // JARR_32_BIT

#ifdef JARR_64_BIT
	JARR_CONST JARR_INLINE size_t private_jarr_next_pow2_64(size_t x)
	{
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		x |= x >> 32;
		return x + 1;
	}
#endif // JARR_64_BIT

#endif // __GNUC__ || __clang__

#if defined(JARR_HAS_TYPEOF) && defined(JARR_HAS_GENERIC)
#	define JARR_SAME_TYPE(x, y) _Generic((x), \
		typeof(y): 1,                     \
		default: 0                        \
	)
#	define JARR_IS_TYPE(T, x) _Generic((x), \
		T: 1,                           \
		default: 0                      \
	)
#endif // JARR_HAS_TYPEOF && JARR_HAS_GENERIC

#if defined(__GNUC__) || defined(__clang__)
#	ifdef JARR_HAS_GENERIC
#		define JARR_GENERIC_CASE_SIZE(expr) \
			int: expr,                  \
			unsigned int: expr,         \
			size_t: expr,               \
			long: expr,                 \
			long long: expr,            \
			unsigned long long: expr    \

#		define JARR_GENERIC_CASE_STR(expr) \
			char *: expr,              \
			const char *: expr         \

#		define JARR_GENERIC_CASE_CHAR(expr) \
			char: expr,                 \
			const char: expr            \

#		define JARR_IS_SIZE(expr) _Generic((expr), \
			JARR_GENERIC_CASE_SIZE(1),         \
			default: 0)

#		define JARR_IS_STR(expr) _Generic((expr), \
			JARR_GENERIC_CASE_STR(1),         \
					default: 0)

#		define JARR_IS_CHAR(expr) _Generic((expr), \
			JARR_GENERIC_CASE_CHAR(1),         \
					default: 0)

#		define JARR_ST_ASSERT_SIZE(expr)                                                              \
			JARR_ST_ASSERT(JARR_IS_SIZE(expr), "Not using a number where a number is required!");
#		define JARR_ST_ASSERT_STR(expr)                                                              \
			JARR_ST_ASSERT(JARR_IS_STR(expr), "Not using a char * where a char * is required!");
#		define JARR_ST_ASSERT_CHAR(expr)                                                          \
			JARR_ST_ASSERT(JARR_IS_CHAR(expr), "Not using a char where a char is required!");
#		define JARR_ST_ASSERT_TYPECHECK(Texpr, expr) JARR_ST_ASSERT(JARR_SAME_TYPE(Texpr, expr), "Passing the wrong data type!");
#	endif // JARR_HAS_GENERIC
#else
#	define JARR_IS_SIZE(val)
#	define JARR_IS_STR(val)
#	define JARR_IS_CHAR(val)
#	define JARR_ST_ASSERT_SIZE(expr)
#	define JARR_ST_ASSERT_STR(expr)
#	define JARR_ST_ASSERT_CHAR(expr)
#	define JARR_ST_ASSERT_TYPECHECK(Texpr, expr)
#endif // __GNUC__ || __clang__

#ifndef MAX
#	define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif // MAX

#ifndef MIN
#	define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif // MIN

#define JARR_SIZEOF_T(var) (sizeof(*((var)->data)))
#define JARR_SIZEOF_ARR(arr) (sizeof(arr)/sizeof(*(arr)))

 #ifdef __cplusplus
#	define JARR_NOEXCEPT noexcept
#else
#	define JARR_NOEXCEPT
#endif // __cplusplus

#endif // JARR_MACROS_H_DEF
