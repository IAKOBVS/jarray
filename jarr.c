/* #include "jarr.h" */
/* #include "macros.h" */

/* ALWAYS_INLINE int private_jarr_new_alloc(const size_t new_size, void** data, size_t *size, size_t *capacity, const size_t sizeof_data) */
/* { */
/* 	*size = 0; */
/* 	*capacity = MAX(JARR_NEXT_POW2(2 * new_size), JARR_MIN_CAP); */
/* 	*data = malloc(*capacity * sizeof_data); */
/* 	if (unlikely(!*data)) { */
/* 		return 0; */
/* 		*capacity = 0; */
/* 		*data = NULL; */
/* 	} */
/* 	return 1; */
/* } */

/* int private_jarr_new_cat(const size_t new_size, void **RESTRICT data, size_t *size, size_t *capacity, const size_t sizeof_data, ...) */
/* { */
/* 	*size = new_size; */
/* 	*capacity = MAX(JARR_NEXT_POW2(2 * new_size), JARR_MIN_CAP); */
/* 	*data = malloc(*capacity * sizeof_data); */
/* 	if (unlikely(!*data)) { */
/* 		*size = 0; */
/* 		*capacity = 0; */
/* 		*data = NULL; */
/* 		return 0; */
/* 	} */
/* 	memset(*data, 0, *capacity); */
/* 	unsigned char *RESTRICT tmp = *data; */
/* 	va_list ap; */
/* 	va_start(ap, sizeof_data); */
/* 	for (const void *RESTRICT argv = va_arg(ap, const void *); argv; argv = va_arg(ap, const void *), tmp += sizeof_data) */
/* 		memcpy(tmp, argv, sizeof_data); */
/* 	va_end(ap); */
/* 	return 1; */
/* } */
