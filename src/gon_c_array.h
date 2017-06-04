#ifndef _GON_C_ARRAY_H
#define _GON_C_ARRAY_H

#include <stdlib.h>

#define GON_C_ARRAY(type) \
struct                   \
{                        \
    type* elements;      \
    size_t size;         \
} gon_c_array

#define GON_C_ARRAY_INIT(array, _size)                                                       \
do                                                                                          \
{                                                                                           \
    (array)->gon_c_array.elements = malloc(_size * sizeof(*((array)->gon_c_array.elements))); \
    (array)->gon_c_array.size = _size;                                                       \
}                                                                                           \
while(0)

#define GON_C_ARRAY_SIZE(array) \
(array)->gon_c_array.size

#define GON_C_ARRAY_GET(array, index) \
(array)->gon_c_array.elements[index]

#define GON_C_ARRAY_SET(array, index, element)          \
do                                                     \
{                                                      \
    if(index < (array)->gon_c_array.size)               \
        (array)->gon_c_array.elements[index] = element; \
}                                                      \
while(0)

#define GON_C_ARRAY_FOR_EACH(array, index) \
for(size_t index = 0; index != (array)->gon_c_array.size; ++index)

#define GON_C_ARRAY_REVERSE_FOR_EACH(array, index) \
for(size_t index = (array)->gon_c_array.size - 1; index != -1; --index)

#define GON_C_ARRAY_SUBSET_FOR_EACH(array, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GON_C_ARRAY_REVERSE_SUBSET_FOR_EACH(array, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
