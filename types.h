#define JARR_T_JARRAY_INT_T 1
#define JARR_T_JARRAY_UNSIGNED_INT_T 2
#define JARR_T_JARRAY_LONG_T 3
#define JARR_T_JARRAY_LONG_LONG_T 4
#define JARR_T_JARRAY_UNSIGNED_LONG_T 5
#define JARR_T_JARRAY_UNSIGNED_LONG_LONG_T 6
#define JARR_T_JARRAY_SIZE_T_T 7
#define JARR_T_JARRAY_DOUBLE_T 8
#define JARR_T_JARRAY_LONG_DOUBLE_T 9
#define JARR_T_JARRAY_FLOAT_T 10
#define JARR_T_JARRAY_SHORT_T 11
#define JARR_T_JARRAY_USHORT_T 12
#define JARR_T_INT_PTR 13
#define JARR_T_UNSIGNED_INT_PTR 14
#define JARR_T_JARRAY_INT_T_PTR 15
#define JARR_T_JARRAY_UNSIGNED_INT_T_PTR 16
#define JARR_T_JARRAY_LONG_T_PTR 17
#define JARR_T_JARRAY_LONG_LONG_T_PTR 18
#define JARR_T_JARRAY_UNSIGNED_LONG_T_PTR 19
#define JARR_T_JARRAY_UNSIGNED_LONG_LONG_T_PTR 20
#define JARR_T_JARRAY_SIZE_T_T_PTR 21
#define JARR_T_JARRAY_DOUBLE_T_PTR 22
#define JARR_T_JARRAY_LONG_DOUBLE_T_PTR 23
#define JARR_T_JARRAY_FLOAT_T_PTR 24
#define JARR_T_JARRAY_SHORT_T_PTR 25
#define JARR_T_JARRAY_USHORT_T_PTR 26
#define JARR_T_LONG_PTR 27
#define JARR_T_LONG_LONG_PTR 28
#define JARR_T_UNSIGNED_LONG_PTR 29
#define JARR_T_UNSIGNED_LONG_LONG_PTR 30
#define JARR_T_DOUBLE_PTR 31
#define JARR_T_LONG_DOUBLE_PTR 32
#define JARR_T_FLOAT_PTR 33
#define JARR_T_SHORT_PTR 34
#define JARR_T_UNSIGNED_SHORT_PTR 35
#define JARR_T_SIZE_T_PTR 36
#define JARR_T_INT 37
#define JARR_T_UNSIGNED_INT 38
#define JARR_T_LONG 39
#define JARR_T_LONG_LONG 40
#define JARR_T_UNSIGNED_LONG 41
#define JARR_T_UNSIGNED_LONG_LONG 42
#define JARR_T_DOUBLE 43
#define JARR_T_LONG_DOUBLE 44
#define JARR_T_FLOAT 45
#define JARR_T_SHORT 46
#define JARR_T_UNSIGNED_SHORT 47
#define JARR_T_SIZE_T 48
#define JARR_T_CHAR 49
#define JARR_T_UNSIGNED_CHAR 50

#define JARR_TYPE_CHECK(src_arr) _Generic((src_arr), \
	jarray_int_t*: JARR_IS_JARRAY_PTR,           \
	jarray_uint_t*: JARR_IS_JARRAY_PTR,          \
	jarray_long_t*: JARR_IS_JARRAY_PTR,          \
	jarray_long_long_t*: JARR_IS_JARRAY_PTR,     \
	jarray_ulong_t*: JARR_IS_JARRAY_PTR,         \
	jarray_ulong_long_t*: JARR_IS_JARRAY_PTR,    \
	jarray_size_t_t*: JARR_IS_JARRAY_PTR,        \
	jarray_double_t*: JARR_IS_JARRAY_PTR,        \
	jarray_long_double_t*: JARR_IS_JARRAY_PTR,   \
	jarray_float_t*: JARR_IS_JARRAY_PTR,         \
	jarray_short_t*: JARR_IS_JARRAY_PTR,         \
	jarray_ushort_t*: JARR_IS_JARRAY_PTR,        \
	jarray_char_t*: JARR_IS_JARRAY_PTR,          \
	jarray_uchar_t*: JARR_IS_JARRAY_PTR,         \
	jarray_int_t: JARR_IS_JARRAY,                \
	jarray_uint_t: JARR_IS_JARRAY,               \
	jarray_long_t: JARR_IS_JARRAY,               \
	jarray_long_long_t: JARR_IS_JARRAY,          \
	jarray_ulong_t: JARR_IS_JARRAY,              \
	jarray_ulong_long_t: JARR_IS_JARRAY,         \
	jarray_size_t_t: JARR_IS_JARRAY,             \
	jarray_double_t: JARR_IS_JARRAY,             \
	jarray_long_double_t: JARR_IS_JARRAY,        \
	jarray_float_t: JARR_IS_JARRAY,              \
	jarray_short_t: JARR_IS_JARRAY,              \
	jarray_ushort_t: JARR_IS_JARRAY,             \
	jarray_char_t: JARR_IS_JARRAY,               \
	jarray_uchar_t: JARR_IS_JARRAY,              \
	int*: JARR_IS_ARRAY,                         \
	unsigned int*: JARR_IS_ARRAY,                \
	long*: JARR_IS_ARRAY,                        \
	long long*: JARR_IS_ARRAY,                   \
	unsigned long*: JARR_IS_ARRAY,               \
	unsigned long long*: JARR_IS_ARRAY,          \
	double*: JARR_IS_ARRAY,                      \
	long double*: JARR_IS_ARRAY,                 \
	float*: JARR_IS_ARRAY,                       \
	short*: JARR_IS_ARRAY,                       \
	unsigned short*: JARR_IS_ARRAY,              \
	int: JARR_IS_ARRAY,                          \
	unsigned int: JARR_IS_ARRAY,                 \
	long: JARR_IS_ARRAY,                         \
	long long: JARR_IS_ARRAY,                    \
	unsigned long: JARR_IS_ARRAY,                \
	unsigned long long: JARR_IS_ARRAY,           \
	double: JARR_IS_ARRAY,                       \
	long double: JARR_IS_ARRAY,                  \
	float: JARR_IS_ARRAY,                        \
	short: JARR_IS_ARRAY,                        \
	unsigned short: JARR_IS_ARRAY,               \
	unsigned char: JARR_IS_ARRAY,                \
	char: JARR_IS_ARRAY                          \
	)

#define JARR_GET_T(var) _Generic(((var)),                     \
	jarray_int_t*: JARR_JARRAY_INT_T_PTR,                 \
	jarray_uint_t*: JARR_JARRAY_UINT_T_PTR,               \
	jarray_long_t*: JARR_JARRAY_LONG_T_PTR,               \
	jarray_long_long_t*: JARR_JARRAY_LONG_LONG_T_PTR,     \
	jarray_ulong_t*: JARR_JARRAY_ULONG_T_PTR,             \
	jarray_ulong_long_t*: JARR_JARRAY_ULONG_LONG_T_PTR,   \
	jarray_size_t_t*: JARR_JARRAY_SIZE_T_T_PTR,           \
	jarray_double_t*: JARR_JARRAY_DOUBLE_T_PTR,           \
	jarray_long_double_t*: JARR_JARRAY_LONG_DOUBLE_T_PTR, \
	jarray_float_t*: JARR_JARRAY_FLOAT_T_PTR,             \
	jarray_short_t*: JARR_JARRAY_SHORT_T_PTR,             \
	jarray_ushort_t*: JARR_JARRAY_USHORT_T_PTR,           \
	jarray_int_t: JARR_JARRAY_INT_T,                      \
	jarray_uint_t: JARR_JARRAY_UINT_T,                    \
	jarray_long_t: JARR_JARRAY_LONG_T,                    \
	jarray_long_long_t: JARR_JARRAY_LONG_LONG_T,          \
	jarray_ulong_t: JARR_JARRAY_ULONG_T,                  \
	jarray_ulong_long_t: JARR_JARRAY_ULONG_LONG_T,        \
	jarray_size_t_t: JARR_JARRAY_SIZE_T_T,                \
	jarray_double_t: JARR_JARRAY_DOUBLE_T,                \
	jarray_long_double_t: JARR_JARRAY_LONG_DOUBLE_T,      \
	jarray_float_t: JARR_JARRAY_FLOAT_T,                  \
	jarray_short_t: JARR_JARRAY_SHORT_T,                  \
	jarray_ushort_t: JARR_JARRAY_USHORT_T,                \
	int*: JARR_INT_PTR,                                   \
	unsigned int*: JARR_UNSIGNED_INT_PTR,                 \
	long*: JARR_LONG_PTR,                                 \
	long long*: JARR_LONG LONG_PTR,                       \
	unsigned long*: JARR_UNSIGNED LONG_PTR,               \
	unsigned long long*: JARR_UNSIGNED LONG LONG_PTR,     \
	double*: JARR_DOUBLE_PTR,                             \
	long double*: JARR_LONG DOUBLE_PTR,                   \
	float*: JARR_FLOAT_PTR,                               \
	short*: JARR_SHORT_PTR,                               \
	unsigned short*: JARR_UNSIGNED SHORT_PTR,             \
	size_t*: JARR_SIZE_T_PTR,                             \
	int: JARR_INT,                                        \
	unsigned int: JARR_UNSIGNED_INT,                      \
	long: JARR_LONG,                                      \
	long long: JARR_LONG LONG,                            \
	unsigned long: JARR_UNSIGNED_LONG,                    \
	unsigned long long: JARR_UNSIGNED_LONG_LONG,          \
	double: JARR_DOUBLE,                                  \
	long double: JARR_LONG_DOUBLE,                        \
	float: JARR_FLOAT,                                    \
	short: JARR_SHORT,                                    \
	unsigned short: JARR_UNSIGNED_SHORT,                  \
	size_t: JARR_SIZE_T,                                  \
	char: JARR_CHAR,                                      \
	unsigned char: JARR_UCHAR                             \
	)

#define JARR_CAST_TO(var) _Generic(((var)),                \
	jarray_int_t*: (jarray_int_t*)var,                 \
	jarray_uint_t*: (jarray_uint_t*)var,               \
	jarray_long_t*: (jarray_long_t*)var,               \
	jarray_long_long_t*: (jarray_long_long_t*)var,     \
	jarray_ulong_t*: (jarray_ulong_t*)var,             \
	jarray_ulong_long_t*: (jarray_ulong_long_t*)var,   \
	jarray_size_t_t*: (jarray_size_t_t*)var,           \
	jarray_double_t*: (jarray_double_t*)var,           \
	jarray_long_double_t*: (jarray_long_double_t*)var, \
	jarray_float_t*: (jarray_float_t*)var,             \
	jarray_short_t*: (jarray_short_t*)var,             \
	jarray_ushort_t*: (jarray_ushort_t*)var,           \
	jarray_int_t: (jarray_int_t)var,                   \
	jarray_uint_t: (jarray_uint_t)var,                 \
	jarray_long_t: (jarray_long_t)var,                 \
	jarray_long_long_t: (jarray_long_long_t)var,       \
	jarray_ulong_t: (jarray_ulong_t)var,               \
	jarray_ulong_long_t: (jarray_ulong_long_t)var,     \
	jarray_size_t_t: (jarray_size_t_t)var,             \
	jarray_double_t: (jarray_double_t)var,             \
	jarray_long_double_t: (jarray_long_double_t)var,   \
	jarray_float_t: (jarray_float_t)var,               \
	jarray_short_t: (jarray_short_t)var,               \
	jarray_ushort_t: (jarray_ushort_t)var,             \
	jarray_char_t: (jarray_char_t)var,                 \
	jarray_uchar_t: (jarray_uchar_t)var,               \
	int*: (int*)var,                                   \
	unsigned int*: (unsigned int*)var,                 \
	long*: (long*)var,                                 \
	long long*: (long long*)var,                       \
	unsigned long*: (unsigned long*)var,               \
	unsigned long long*: (unsigned long long*)var,     \
	double*: (double*)var,                             \
	long double*: (long double*)var,                   \
	float*: (float*)var,                               \
	short*: (short*)var,                               \
	unsigned short*: (unsigned short*)var,             \
	size_t*: (size_t*)var,                             \
	int: (int)var,                                     \
	unsigned int: (unsigned int)var,                   \
	long: (long)var,                                   \
	long long: (long long)var,                         \
	unsigned long: (unsigned long)var,                 \
	unsigned long long: (unsigned long long)var,       \
	double: (double)var,                               \
	long double: (long double)var,                     \
	float: (float)var,                                 \
	short: (short)var,                                 \
	unsigned short: (unsigned short)var,               \
	size_t: (size_t)var,                               \
	char: (char)var,                                   \
	unsigned char: (unsigned char)var                  \
	)

#define JARR_VA_ARG_T(ap) _Generic(((var)),                       \
	jarray_int_t*: va_arg(ap, jarray_int_t*),                 \
	jarray_uint_t*: va_arg(ap, jarray_uint_t*),               \
	jarray_long_t*: va_arg(ap, jarray_long_t*),               \
	jarray_long_long_t*: va_arg(ap, jarray_long_long_t*),     \
	jarray_ulong_t*: va_arg(ap, jarray_ulong_t*),             \
	jarray_ulong_long_t*: va_arg(ap, jarray_ulong_long_t*),   \
	jarray_size_t_t*: va_arg(ap, jarray_size_t_t*),           \
	jarray_double_t*: va_arg(ap, jarray_double_t*),           \
	jarray_long_double_t*: va_arg(ap, jarray_long_double_t*), \
	jarray_float_t*: va_arg(ap, jarray_float_t*),             \
	jarray_short_t*: va_arg(ap, jarray_short_t*),             \
	jarray_ushort_t*: va_arg(ap, jarray_ushort_t*),           \
	jarray_int_t: va_arg(ap, jarray_int_t),                   \
	jarray_uint_t: va_arg(ap, jarray_uint_t),                 \
	jarray_long_t: va_arg(ap, jarray_long_t),                 \
	jarray_long_long_t: va_arg(ap, jarray_long_long_t),       \
	jarray_ulong_t: va_arg(ap, jarray_ulong_t),               \
	jarray_ulong_long_t: va_arg(ap, jarray_ulong_long_t),     \
	jarray_size_t_t: va_arg(ap, jarray_size_t_t),             \
	jarray_double_t: va_arg(ap, jarray_double_t),             \
	jarray_long_double_t: va_arg(ap, jarray_long_double_t),   \
	jarray_float_t: va_arg(ap, jarray_float_t),               \
	jarray_short_t: va_arg(ap, jarray_short_t),               \
	jarray_ushort_t: va_arg(ap, jarray_ushort_t),             \
	jarray_char_t: va_arg(ap, jarray_char_t),                 \
	jarray_uchar_t: va_arg(ap, jarray_uchar_t),               \
	int*: va_arg(ap, int*),                                   \
	unsigned int*: va_arg(ap, unsigned int*),                 \
	long*: va_arg(ap, long*),                                 \
	long long*: va_arg(ap, long long*),                       \
	unsigned long long*: va_arg(ap, unsigned long long*),     \
	double*: va_arg(ap, double*),                             \
	long double*: va_arg(ap, long double*),                   \
	float*: va_arg(ap, float*),                               \
	short*: va_arg(ap, short*),                               \
	unsigned short*: va_arg(ap, unsigned short*),             \
	size_t*: va_arg(ap, size_t*),                             \
	int: va_arg(ap, int),                                     \
	unsigned int: va_arg(ap, unsigned int),                   \
	long: va_arg(ap, long),                                   \
	long long: va_arg(ap, long long),                         \
	unsigned long long: va_arg(ap, unsigned long long),       \
	double: va_arg(ap, double),                               \
	long double: va_arg(ap, long double),                     \
	float: va_arg(ap, double),                                \
	short: va_arg(ap, int),                                   \
	unsigned short: va_arg(ap, int),                          \
	size_t: va_arg(ap, size_t)                                \
	)

#define private_jarr_arr_get_data(src_arr)           \
	_Generic((&(src_arr)),                       \
	jarray_int_t**: (((src_arr))->data),         \
	jarray_uint_t**: (((src_arr))->data),        \
	jarray_long_t**: (((src_arr))->data),        \
	jarray_long_long_t**: (((src_arr))->data),   \
	jarray_ulong_t**: (((src_arr))->data),       \
	jarray_ulong_long_t**: (((src_arr))->data),  \
	jarray_size_t_t**: (((src_arr))->data),      \
	jarray_double_t**: (((src_arr))->data),      \
	jarray_long_double_t**: (((src_arr))->data), \
	jarray_float_t**: (((src_arr))->data),       \
	jarray_short_t**: (((src_arr))->data),       \
	jarray_ushort_t**: (((src_arr))->data),      \
	jarray_char_t**: (((src_arr))->data),        \
	jarray_uchar_t**: (((src_arr))->data),       \
	jarray_int_t*: (((src_arr)).data),           \
	jarray_uint_t*: (((src_arr)).data),          \
	jarray_long_t*: (((src_arr)).data),          \
	jarray_long_long_t*: (((src_arr)).data),     \
	jarray_ulong_t*: (((src_arr)).data),         \
	jarray_ulong_long_t*: (((src_arr)).data),    \
	jarray_size_t_t*: (((src_arr)).data),        \
	jarray_double_t*: (((src_arr)).data),        \
	jarray_long_double_t*: (((src_arr)).data),   \
	jarray_float_t*: (((src_arr)).data),         \
	jarray_short_t*: (((src_arr)).data),         \
	jarray_ushort_t*: (((src_arr)).data),        \
	jarray_char_t*: (((src_arr)).data),          \
	jarray_uchar_t*: (((src_arr)).data),         \
	int**: ((src_arr)),                          \
	unsigned int**: ((src_arr)),                 \
	long**: ((src_arr)),                         \
	long long**: ((src_arr)),                    \
	unsigned long**: ((src_arr)),                \
	unsigned long long**: ((src_arr)),           \
	double**: ((src_arr)),                       \
	long double**: ((src_arr)),                  \
	float**: ((src_arr)),                        \
	short**: ((src_arr)),                        \
	unsigned short**: ((src_arr)),               \
	int*: ((src_arr)),                           \
	unsigned int*: ((src_arr)),                  \
	long*: ((src_arr)),                          \
	long long*: ((src_arr)),                     \
	unsigned long*: ((src_arr)),                 \
	unsigned long long*: ((src_arr)),            \
	double*: ((src_arr)),                        \
	long double*: ((src_arr)),                   \
	float*: ((src_arr)),                         \
	short*: ((src_arr)),                         \
	unsigned short*: ((src_arr)),                \
	unsigned char*: ((src_arr)),                 \
	char*: ((src_arr))                           \
	)

#define private_jarr_arr_get_size(src_arr, src_arr_size)                 \
	_Generic((&src_arr),                                             \
	jarray_int_t**: ((src_arr)->size),                               \
	jarray_uint_t**: ((src_arr)->size),                              \
	jarray_long_t**: ((src_arr)->size),                              \
	jarray_long_long_t**: ((src_arr)->size),                         \
	jarray_ulong_t**: ((src_arr)->size),                             \
	jarray_ulong_long_t**: ((src_arr)->size),                        \
	jarray_size_t_t**: ((src_arr)->size),                            \
	jarray_double_t**: ((src_arr)->size),                            \
	jarray_long_double_t**: ((src_arr)->size),                       \
	jarray_float_t**: ((src_arr)->size),                             \
	jarray_short_t**: ((src_arr)->size),                             \
	jarray_ushort_t**: ((src_arr)->size),                            \
	jarray_char_t**: ((src_arr)->size),                              \
	jarray_uchar_t**: ((src_arr)->size),                             \
	jarray_int_t*: ((src_arr).size),                                 \
	jarray_uint_t*: ((src_arr).size),                                \
	jarray_long_t*: ((src_arr).size),                                \
	jarray_long_long_t*: ((src_arr).size),                           \
	jarray_ulong_t*: ((src_arr).size),                               \
	jarray_ulong_long_t*: ((src_arr).size),                          \
	jarray_size_t_t*: ((src_arr).size),                              \
	jarray_double_t*: ((src_arr).size),                              \
	jarray_long_double_t*: ((src_arr).size),                         \
	jarray_float_t*: ((src_arr).size),                               \
	jarray_short_t*: ((src_arr).size),                               \
	jarray_ushort_t*: ((src_arr).size),                              \
	jarray_char_t*: ((src_arr).size),                                \
	jarray_uchar_t*: ((src_arr).size),                               \
	int**: src_arr_size,                                             \
	unsigned int**: src_arr_size,                                    \
	long**: src_arr_size,                                            \
	long long**: src_arr_size,                                       \
	unsigned long**: src_arr_size,                                   \
	unsigned long long**: src_arr_size,                              \
	double**: src_arr_size,                                          \
	long double**: src_arr_size,                                     \
	float**: src_arr_size,                                           \
	short**: src_arr_size,                                           \
	unsigned short**: src_arr_size,                                  \
	int(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                \
	unsigned int(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),       \
	long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),               \
	long long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),          \
	unsigned long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),      \
	unsigned long long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])), \
	double(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),             \
	long double(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),        \
	float(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),              \
	short(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),              \
	unsigned short(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),     \
	unsigned char(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),      \
	char(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0]))                \
	)

#define private_jarr_arr_ret_size(src_arr, src_arr_size)                       \
	_Generic((&src_arr),                                                   \
			                                                       \
	jarray_int**: private_jarray_get_size_int(&src_arr),                   \
	jarray_uint**: private_jarray_get_size_uint(&src_arr),                 \
	jarray_long**: private_jarray_get_size_long(&src_arr),                 \
	jarray_long_long**: private_jarray_get_size_long_long(&src_arr),       \
	jarray_ulong**: private_jarray_get_size_ulong(&src_arr),               \
	jarray_ulong_long**: private_jarray_get_size_ulong_long(&src_arr),     \
	jarray_size_t**: private_jarray_get_size_size_t(&src_arr),             \
	jarray_double**: private_jarray_get_size_double(&src_arr),             \
	jarray_long_double**: private_jarray_get_size_long_double(&src_arr),   \
	jarray_float**: private_jarray_get_size_float(&src_arr),               \
	jarray_short**: private_jarray_get_size_short(&src_arr),               \
	jarray_ushort**: private_jarray_get_size_ushort(&src_arr),             \
	jarray_char**: private_jarray_get_size_char(&src_arr),                 \
	jarray_uchar**: private_jarray_get_size_uchar(&src_arr),               \
                                                                               \
	jarray_int*: private_jarray_get_size_int(src_arr),                     \
	jarray_uint*: private_jarray_get_size_uint(src_arr),                   \
	jarray_long*: private_jarray_get_size_long(src_arr),                   \
	jarray_long_long*: private_jarray_get_size_long_long(src_arr),         \
	jarray_ulong*: private_jarray_get_size_ulong(src_arr),                 \
	jarray_ulong_long*: private_jarray_get_size_ulong_long(src_arr),       \
	jarray_size_t*: private_jarray_get_size_size_t(src_arr),               \
	jarray_double*: private_jarray_get_size_double(src_arr),               \
	jarray_long_double*: private_jarray_get_size_long_double(src_arr),     \
	jarray_float*: private_jarray_get_size_float(src_arr),                 \
	jarray_short*: private_jarray_get_size_short(src_arr),                 \
	jarray_ushort*: private_jarray_get_size_ushort(src_arr),               \
	jarray_char*: private_jarray_get_size_char(src_arr),                   \
	jarray_uchar*: private_jarray_get_size_uchar(src_arr),                 \
                                                                               \
	int**: src_arr_size,                                                   \
	unsigned int**: src_arr_size,                                          \
	long**: src_arr_size,                                                  \
	long long**: src_arr_size,                                             \
	unsigned long**: src_arr_size,                                         \
	unsigned long long**: src_arr_size,                                    \
	double**: src_arr_size,                                                \
	long double**: src_arr_size,                                           \
	float**: src_arr_size,                                                 \
	short**: src_arr_size,                                                 \
	unsigned short**: src_arr_size,                                        \
                                                                               \
	int(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                      \
	unsigned int(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),             \
	long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                     \
	long long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                \
	unsigned long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),            \
	unsigned long long(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),       \
	double(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                   \
	long double(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),              \
	float(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                    \
	short(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),                    \
	unsigned short(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),           \
	unsigned char(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0])),            \
	char(*)[]: (sizeof(src_arr)/sizeof((src_arr)[0]))                      \
	)

