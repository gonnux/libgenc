#ifndef _GONC_ARRAY_H
#define _GONC_ARRAY_H

#include <stdlib.h>

#define GONC_ARRAY(type) \
struct                   \
{                        \
    type* elements;      \
    size_t capacity;     \
    size_t size;         \
} gonc_array

#define GONC_ARRAY_INIT(array, _capacity)                                                       \
do                                                                                              \
{                                                                                               \
    (array)->gonc_array.elements = malloc(_capacity * sizeof(*((array)->gonc_array.elements))); \
    (array)->gonc_array.capacity = _capacity;                                                   \
    (array)->gonc_array.size = 0;                                                               \
}                                                                                               \
while(0)

#define GONC_ARRAY_CAPACITY(array) \
(array)->gonc_array.capacity

#define GONC_ARRAY_SIZE(array) \
(array)->gonc_array.size

#define GONC_ARRAY_GET(array, index) \
(array)->gonc_array.elements[index]

#define GONC_ARRAY_SET(array, index, element)          \
do                                                     \
{                                                      \
    if(index < (array)->gonc_array.capacity)           \
    {                                                  \
        (array)->gonc_array.elements[index] = element; \
        ++((array)->gonc_array.size);                  \
    }                                                  \
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
