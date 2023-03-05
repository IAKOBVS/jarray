#define JARR_TEMPLATE_T(F)      \
	F(jarray_int_t)         \
	F(jarray_uint_t)        \
	F(jarray_long_t)        \
	F(jarray_long_long_t)   \
	F(jarray_ulong_t)       \
	F(jarray_ulong_long_t)  \
	F(jarray_size_t_t)      \
	F(jarray_double_t)      \
	F(jarray_long_double_t) \
	F(jarray_float_t)       \
	F(jarray_short_t)       \
	F(jarray_ushort_t)      \
	F(jarray_char_t)        \
	F(jarray_uchar_t)       \

#define JARR_TEMPLATE_T_t(F)                       \
	F(jarray_int_t, int)                       \
	F(jarray_uint_t, unsigned int)             \
	F(jarray_long_t, long)                     \
	F(jarray_long_long_t, long long)           \
	F(jarray_ulong_t, unsigned long)           \
	F(jarray_ulong_long_t, unsigned long long) \
	F(jarray_size_t_t, size_t)                 \
	F(jarray_double_t, double)                 \
	F(jarray_long_double_t, long double)       \
	F(jarray_float_t, float)                   \
	F(jarray_short_t, short)                   \
	F(jarray_ushort_t, unsigned short)         \
	F(jarray_char_t, char)                     \
	F(jarray_uchar_t, unsigned char)           \

#define JARR_GENERIC(F, T, ...) _Generic((T),                                   \
	*jarray_int_t: F##_jarray_int_t(jarr_ptr, __VA_ARGS__),                 \
	*jarray_uint_t: F##_jarray_uint_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_long_t F##_jarray_long_t(jarr_ptr, __VA_ARGS__),                \
	*jarray_long_long_t: F##_jarray_long_long_t(jarr_ptr, __VA_ARGS__),     \
	*jarray_ulong_t: F##_jarray_ulong_t(jarr_ptr, __VA_ARGS__),             \
	*jarray_ulong_long_t F##_jarray_ulong_long_t(jarr_ptr, __VA_ARGS__),    \
	*jarray_size_t_t: F##_jarray_size_t_t(jarr_ptr, __VA_ARGS__),           \
	*jarray_double_t: F##_jarray_double_t(jarr_ptr, __VA_ARGS__),           \
	*jarray_long_double_t: F##_jarray_long_double_t(jarr_ptr, __VA_ARGS__), \
	*jarray_float_t: F##_jarray_float_t(jarr_ptr, __VA_ARGS__),             \
	*jarray_short: F##_jarray_short_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_ushort_t F##_jarray_ushort_t(jarr_ptr, __VA_ARGS__),            \
	*jarray_char_t: F##_jarray_char_t(jarr_ptr, __VA_ARGS__),               \
	*jarray_unsigned_char_t: F##_jarray_uchar_t(jarr_ptr, __VA_ARGS__)      \
		)

/* jarray_type type */

/*
jarray_int_t, int
jarray_uint_t, unsigned int
jarray_long_t, long
jarray_long_long_t, long long
jarray_ulong_t, unsigned long
jarray_ulong_long_t, unsigned long long
jarray_size_t_t, size_t
jarray_double_t, double
jarray_long_double_t, long double
jarray_float_t, float
jarray_short_t, short
jarray_ushort_t, unsigned short
jarray_char_t, char
jarray_uchar_t, unsigned char
*/

/* jarray_type */

/*
jarray_int_t
jarray_uint_t
jarray_long_t
jarray_long_long_t
jarray_ulong_t
jarray_ulong_long_t
jarray_size_t_t
jarray_double_t
jarray_long_double_t
jarray_float_t
jarray_short_t
jarray_ushort_t
jarray_char_t
jarray_uchar_t
*/

/* type */

/*
int
unsigned int
long
long long
unsigned long
unsigned long long
size_t
double
long double
float
short
unsigned short
char
unsigned char
*/

/* type: jarray */

/*
int: jarray_int_t,
unsigned int: jarray_uint_t,
long: jarray_long_t,
long long: jarray_long_long_t,
unsigned long: jarray_ulong_t,
unsigned long long: jarray_ulong_long_t,
size: jarray_size_t_t_t,
double: jarray_double_t,
long double: jarray_long_double_t,
*jarray_float_t: jarray_float_t,
short: jarray_short_t,
unsigned short: jarray_ushort_t,
char: jarray_char_t,
*jarray_unsigned_char_t: jarray_uchar_t,
*/
