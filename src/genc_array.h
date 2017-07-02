#ifndef _GENC_ARRAY_H
#define _GENC_ARRAY_H

#include <stdlib.h>

#define GENC_ARRAY(type) \
struct                   \
{                        \
    type* elements;      \
    size_t size;         \
} genc_array

#define GENC_ARRAY_INIT(array, _size)                                                       \
do                                                                                          \
{                                                                                           \
    (array)->genc_array.elements = malloc(_size * sizeof(*((array)->genc_array.elements))); \
    (array)->genc_array.size = _size;                                                       \
}                                                                                           \
while(0)

#define GENC_ARRAY_SIZE(array) \
(array)->genc_array.size

#define GENC_ARRAY_GET(array, index) \
(array)->genc_array.elements[index]

#define GENC_ARRAY_SET(array, index, element)          \
do                                                     \
{                                                      \
    if(index < (array)->genc_array.size)               \
        (array)->genc_array.elements[index] = element; \
}                                                      \
while(0)

#define GENC_ARRAY_FOR_EACH(array, index) \
for(size_t index = 0; index != (array)->genc_array.size; ++index)

#define GENC_ARRAY_REVERSE_FOR_EACH(array, index) \
for(size_t index = (array)->genc_array.size - 1; index != -1; --index)

#define GENC_ARRAY_SUBSET_FOR_EACH(array, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_REVERSE_SUBSET_FOR_EACH(array, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
