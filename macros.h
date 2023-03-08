#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
# define RESTRICT restrict
#elif defined(__GNUC__) || defined(__clang__)
# define RESTRICT __restrict__
#elif defined(_MSC_VER)
# define RESTRICT __restrict
#else
#define RESTRICT
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
    #define ALWAYS_INLINE __forceinline inline
#else
    #define ALWAYS_INLINE inline
#endif

#if defined(__PRETTY_FUNCTION__)
	#define CURR_FUNC __PRETTY_FUNCTION__
#elif defined(__FUNCTION__)
	#define CURR_FUNC __FUNCTION__
#elif defined(__func__)
	#define CURR_FUNC __func__
#else
	#define CURR_FUNC ""
#endif

#if (defined(__GNUC__) && (__GNUC__ >= 3)) || (defined(__clang__) && __has_builtin(__builtin_expect))
  #define likely(x) __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else
  #define likely(x) (x)
  #define unlikely(x) (x)
#endif


#if defined(__GNUC__) || defined(__clang__)
    #if __has_attribute(pure)
        #define PURE __attribute__((pure))
    #else
        #define PURE
    #endif

    #if __has_attribute(const)
        #define CONST __attribute__((const))
    #else
        #define CONST
    #endif

    #if __has_attribute(flatten)
        #define FLATTEN __attribute__((flatten))
    #else
        #define FLATTEN
    #endif
#elif defined(_MSC_VER)
    #define PURE __declspec(noalias)
    #define CONST __declspec(restrict)
    #define FLATTEN
#else
    #define PURE
    #define CONST
    #define FLATTEN
#endif

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_STATIC_ASSERT__) && defined(_Static_assert)
	#define JARR_ASSERT(expr, msg) _Static_assert(expr, msg)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_STATIC_ASSERT__)
	#define JARR_ASSERT(expr, msg) static_assert(expr, msg)
#else
	#define JARR_ASSERT(expr, msg)
#endif

#define JARR_SIZEOF_T(var) (sizeof(*((var)->data)))
#define JARR_SIZEOF_ARR(arr) (sizeof(arr)/sizeof(*(arr)))

#define MAX(a,b) ((a)>(b)?(a):(b))
