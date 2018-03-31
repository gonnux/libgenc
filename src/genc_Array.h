#ifndef _GENC_ARRAY_H
#define _GENC_ARRAY_H

#include <stdlib.h>

#define GENC_ARRAY(type) \
struct { \
    type* elements; \
    size_t size; \
} genc_Array

#define GENC_ARRAY_INIT(array, newSize) { \
    (array)->genc_Array.elements = malloc(newSize * sizeof(*((array)->genc_Array.elements))); \
    (array)->genc_Array.size = newSize; \
}

#define GENC_ARRAY_SIZE(array) \
(array)->genc_Array.size

#define GENC_ARRAY_ELEMENT_SIZE(array) \
sizeof(*(array)->genc_Array.elements)

#define GENC_ARRAY_AT(array, index) \
(array)->genc_Array.elements[index]

#define GENC_ARRAY_GET(array, index, element) \
*(element) = (array)->genc_Array.elements[index]

#define GENC_ARRAY_SET(array, index, element) { \
    if(index < (array)->genc_Array.size) \
        (array)->genc_Array.elements[index] = element; \
}

#define GENC_ARRAY_FOR_EACH(array, index) \
for(size_t index = 0; index != (array)->genc_Array.size; ++index)

#define GENC_ARRAY_REVERSE_FOR_EACH(array, index) \
for(size_t index = (array)->genc_Array.size - 1; index != -1; --index)

#define GENC_ARRAY_SUBSET_FOR_EACH(array, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_REVERSE_SUBSET_FOR_EACH(array, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
