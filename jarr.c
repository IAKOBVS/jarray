#include "jarr.h"

/* void* private_jarr_cast_to(int T, void* var) { */
/* 	switch (T) { */
/* 	case JARR_JARRAY_INT_T_PTR: */
/* 		return (jarray_int_t*)var; */
/* 	case JARR_JARRAY_UINT_T_PTR: */
/* 		return (jarray_uint_t*)var; */
/* 	case JARR_JARRAY_LONG_T_PTR: */
/* 		return (jarray_long_t*)var; */
/* 	case JARR_JARRAY_LONG_LONG_T_PTR: */
/* 		return (jarray_long_long_t*)var; */
/* 	case JARR_JARRAY_ULONG_T_PTR: */
/* 		return (jarray_ulong_t*)var; */
/* 	case JARR_JARRAY_ULONG_LONG_T_PTR: */
/* 		return (jarray_ulong_long_t*)var; */
/* 	case JARR_JARRAY_SIZE_T_T_PTR: */
/* 		return (jarray_size_t_t*)var; */
/* 	case JARR_JARRAY_DOUBLE_T_PTR: */
/* 		return (jarray_double_t*)var; */
/* 	case JARR_JARRAY_LONG_DOUBLE_T_PTR: */
/* 		return (jarray_long_double_t*)var; */
/* 	case JARR_JARRAY_FLOAT_T_PTR: */
/* 		return (jarray_float_t*)var; */
/* 	case JARR_JARRAY_SHORT_T_PTR: */
/* 		return (jarray_short_t*)var; */
/* 	case JARR_JARRAY_USHORT_T_PTR: */
/* 		return (jarray_ushort_t*)var; */
/* 	case JARR_INT_PTR: */
/* 		return (int*)var; */
/* 	case JARR_UNSIGNED_INT_PTR: */
/* 		return (unsigned int*)var; */
/* 	case JARR_LONG_PTR: */
/* 		return (long*)var; */
/* 	case JARR_LONG_LONG_PTR: */
/* 		return (long long*)var; */
/* 	case JARR_UNSIGNED_LONG_PTR: */
/* 		return (unsigned long*)var; */
/* 	case JARR_UNSIGNED_LONG_LONG_PTR: */
/* 		return (unsigned long long*)var; */
/* 	case JARR_DOUBLE_PTR: */
/* 		return (double*)var; */
/* 	case JARR_LONG_DOUBLE_PTR: */
/* 		return (long double*)var; */
/* 	case JARR_FLOAT_PTR: */
/* 		return (float*)var; */
/* 	case JARR_SHORT_PTR: */
/* 		return (short*)var; */
/* 	case JARR_UNSIGNED_SHORT_PTR: */
/* 		return (unsigned short*)var; */
/* 	case JARR_SIZE_T_PTR: */
/* 		return (size_t*)var; */
/* 	case JARR_INT: */
/* 		return (int*)var; */
/* 	case JARR_UNSIGNED_INT: */
/* 		return (unsigned int*)var; */
/* 	case JARR_LONG: */
/* 		return (long*)var; */
/* 	case JARR_LONG_LONG: */
/* 		return (long long*)var; */
/* 	case JARR_UNSIGNED_LONG: */
/* 		return (unsigned long*)var; */
/* 	case JARR_UNSIGNED_LONG_LONG: */
/* 		return (unsigned long long*)var; */
/* 	case JARR_DOUBLE: */
/* 		return (double*)var; */
/* 	case JARR_LONG_DOUBLE: */
/* 		return (long double*)var; */
/* 	case JARR_FLOAT: */
/* 		return (float*)var; */
/* 	case JARR_SHORT: */
/* 		return (short*)var; */
/* 	case JARR_UNSIGNED_SHORT: */
/* 		return (unsigned short*)var; */
/* 	case JARR_SIZE_T: */
/* 		return (size_t*)var; */
/* 	default: */
/* 		return var; */
/* 	} */
/* } */

/* void private_jarr_assign_va_args(int T, int Tdata, void* jarr, ...) */
/* { */
/* 	va_list ap; */
/* 	va_start(ap, jarr); */
/* 	typeof(private_jarr_cast_to(T, jarr)) tmp = jarr; */
/* 	for (typeof(private_jarr_cast_to(T, jarr->data)) argv = va_arg(ap, typeof(argv)); argv; argv = va_arg(ap, typeof(argv))) */
/* 	va_end(ap); */
/* } */

#ifdef JARR_DEBUG
int main ()
{
}
#endif
