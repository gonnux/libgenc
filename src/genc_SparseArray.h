#ifndef _GENC_SPARSE_ARRAY_H
#define _GENC_SPARSE_ARRAY_H

#define GENC_SPARSE_ARRAY(type) \
struct { \
    type** elements; \
    size_t size; \
    size_t capacity; \
} genc_SparseArray

#define GENC_SPARSE_ARRAY_INIT(sparseArray, size, capacity) do { \
    (sparseArray)->size = size; \
    (sparseArray)->capacity = capacity; \
    (sparseArray)->elements = calloc(capacity, sizeof(*((sparseArray)->elements))); \
} while(0)

#define GENC_SPARSE_ARRAY_SET()
#define GENC_SPARSE_ARRAY_REPLACE()
#define GENC_SPARSE_ARRAY_GET()

#endif
