#ifndef _GONC_ARRAY_H
#define _GONC_ARRAY_H

#include <stdlib.h>
#include <libgonc/config.h>

#define GONC_ARRAY(type) \
struct                   \
{                        \
    type* elements;      \
    size_t size;         \
} gonc_array

#define GONC_ARRAY_INIT(array, _size)                                                       \
do                                                                                          \
{                                                                                           \
    (array)->gonc_array.elements = malloc(_size * sizeof(*((array)->gonc_array.elements))); \
    (array)->gonc_array.size = _size;                                                       \
}                                                                                           \
while(0)

#define GONC_ARRAY_SIZE(array) \
(array)->gonc_array.size

#define GONC_ARRAY_GET(array, index) \
(array)->gonc_array.elements[index]

#define GONC_ARRAY_SET(array, index, element)          \
do                                                     \
{                                                      \
    if(index < (array)->gonc_array.size)               \
        (array)->gonc_array.elements[index] = element; \
}                                                      \
while(0)

#define GONC_ARRAY_FOR_EACH(array, index) \
for(size_t index = 0; index != (array)->gonc_array.size; ++index)

#define GONC_ARRAY_REVERSE_FOR_EACH(array, index) \
for(size_t index = (array)->gonc_array.size - 1; index != -1; --index)

#define GONC_ARRAY_SUBSET_FOR_EACH(array, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GONC_ARRAY_REVERSE_SUBSET_FOR_EACH(array, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
