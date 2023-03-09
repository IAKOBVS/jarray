#ifndef JARR_GENERIC_DEF_H

#define JARR_TEMPLATE_T(F)             \
	F(jarray_int_t)                \
	F(jarray_unsigned_int_t)       \
	F(jarray_long_t)               \
	F(jarray_long_long_t)          \
	F(jarray_unsigned_long_long_t) \
	F(jarray_size_t_t)             \
	F(jarray_double_t)             \
	F(jarray_long_double_t)        \
	F(jarray_float_t)              \
	F(jarray_short_t)              \
	F(jarray_unsigned_short_t)     \
	F(jarray_char_t)               \
	F(jarray_unsigned_char_t)      \

#define JARR_TEMPLATE_TYPENAME_t(F)               \
	F(int, int)                               \
	F(unsigned_int, unsigned int)             \
	F(long, long)                             \
	F(long_long, long long)                   \
	F(unsigned_long_long, unsigned long long) \
	F(size_t, size_t)                         \
	F(double, double)                         \
	F(long_double, long double)               \
	F(float, float)                           \
	F(short, short)                           \
	F(unsigned_short, unsigned short)         \
	F(char, char)                             \
	F(unsigned_char, unsigned char)           \

#define JARR_TEMPLATE_T_t(F)                               \
	F(jarray_int_t, int)                               \
	F(jarray_unsigned_int_t, unsigned int)             \
	F(jarray_long_t, long)                             \
	F(jarray_long_long_t, long long)                   \
	F(jarray_unsigned_long_long_t, unsigned long long) \
	F(jarray_size_t_t, size_t)                         \
	F(jarray_double_t, double)                         \
	F(jarray_long_double_t, long double)               \
	F(jarray_float_t, float)                           \
	F(jarray_short_t, short)                           \
	F(jarray_unsigned_short_t, unsigned short)         \
	F(jarray_char_t, char)                             \
	F(jarray_unsigned_char_t, unsigned char)           \

#define JARR_GENERIC_T(F, T, ...) _Generic((T),                                        \
	jarray_int_t*: F##_jarray_int_t(T, __VA_ARGS__),                               \
	jarray_unsigned_int_t*: F##_jarray_unsigned_int_t(T, __VA_ARGS__),             \
	jarray_long_t F##_jarray_long_t(T, __VA_ARGS__),                               \
	jarray_long_long_t*: F##_jarray_long_long_t(T, __VA_ARGS__),                   \
	jarray_unsigned_long_long_t*: F##_jarray_unsigned_long_long_t(T, __VA_ARGS__), \
	jarray_size_t_t*: F##_jarray_size_t_t(T, __VA_ARGS__),                         \
	jarray_double_t*: F##_jarray_double_t(T, __VA_ARGS__),                         \
	jarray_long_double_t*: F##_jarray_long_double_t(T, __VA_ARGS__),               \
	jarray_float_t*: F##_jarray_float_t(T, __VA_ARGS__),                           \
	jarray_short*: F##_jarray_short_t(T, __VA_ARGS__),                             \
	jarray_unsigned_short_t F##_jarray_unsigned_short_t(T, __VA_ARGS__),           \
	jarray_char_t*: F##_jarray_char_t(T, __VA_ARGS__),                             \
	jarray_unsigned_char_t*: F##_jarray_unsigned_char_t(T, __VA_ARGS__)            \
		)

#define JARR_GENERIC_t(F, t, ...) _Generic((t),                                    \
	int*: F##_int((void *)t, __VA_ARGS__),                                     \
	unsigned int*: F##_unsigned_int((void *)t, __VA_ARGS__),                   \
	long*: F##_long((void *)t, __VA_ARGS__),                                   \
	long long*: F##_long_long((void *)t, __VA_ARGS__),                         \
	unsigned long long*: F##_unsigned_long_long((void *)t, __VA_ARGS__),       \
	size_t*: F##_size_t((void *)t, __VA_ARGS__),                               \
	double*: F##_double((void *)t, __VA_ARGS__),                               \
	long double*: F##_long_double((void *)t, __VA_ARGS__),                     \
	float*: F##_float((void *)t, __VA_ARGS__),                                 \
	short*: F##_short((void *)t, __VA_ARGS__),                                 \
	unsigned short*: F##_unsigned_short((void *)t, __VA_ARGS__),               \
	char*: F##_char((void *)t, __VA_ARGS__),                                   \
	unsigned char*: F##_unsigned_char((void *)t, __VA_ARGS__),                 \
                                                                                   \
	int**: F##_int((void **)t, __VA_ARGS__),                                   \
	unsigned int**: F##_unsigned_int((void **)t, __VA_ARGS__),                 \
	long: F##_long((void **)t, __VA_ARGS__),                                   \
	long long**: F##_long_long((void **)t, __VA_ARGS__),                       \
	unsigned long long**: F##_unsigned_long_long((void **)t, __VA_ARGS__),     \
	size_t**: F##_size_t((void **)t, __VA_ARGS__),                             \
	double**: F##_double((void **)t, __VA_ARGS__),                             \
	long double**: F##_long_double((void **)t, __VA_ARGS__),                   \
	float**: F##_float((void **)t, __VA_ARGS__),                               \
	short**: F##_short((void **)t, __VA_ARGS__),                               \
	unsigned short**: F##_unsigned_short((void **)t, __VA_ARGS__),             \
	char**: F##_char((void **)t, __VA_ARGS__),                                 \
	unsigned char**: F##_unsigned_char((void **)t, __VA_ARGS__)                \
		)

/* jarray_type type */

/*
jarray_int_t, int
jarray_unsigned_int_t, unsigned int
jarray_long_t, long
jarray_long_long_t, long long
jarray_unsigned_long_t, unsigned long
jarray_unsigned_long_long_t, unsigned long long
jarray_size_t_t, size_t
jarray_double_t, double
jarray_long_double_t, long double
jarray_float_t, float
jarray_short_t, short
jarray_unsigned_short_t, unsigned short
jarray_char_t, char
jarray_unsigned_char_t, unsigned char
*/

/* jarray_type */

/*
jarray_int_t
jarray_unsigned_int_t
jarray_long_t
jarray_long_long_t
jarray_unsigned_long_t
jarray_unsigned_long_long_t
jarray_size_t_t
jarray_double_t
jarray_long_double_t
jarray_float_t
jarray_short_t
jarray_unsigned_short_t
jarray_char_t
jarray_unsigned_char_t
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
unsigned int: jarray_unsigned_int_t,
long: jarray_long_t,
long long: jarray_long_long_t,
unsigned long: jarray_unsigned_long_t,
unsigned long long: jarray_unsigned_long_long_t,
size: jarray_size_t_t_t,
double: jarray_double_t,
long double: jarray_long_double_t,
*jarray_float_t: jarray_float_t,
short: jarray_short_t,
unsigned short: jarray_unsigned_short_t,
char: jarray_char_t,
*jarray_unsigned_char_t: jarray_unsigned_char_t,
*/

#endif
