#ifndef _GONC_ARRAY_H
#define _GONC_ARRAY_H

#include <stdlib.h>

#define GONC_ARRAY(name, type) \
struct name                    \
{                              \
    type* elements;            \
    size_t capacity;           \
    size_t size;               \
}

#define GONC_ARRAY_INIT(array, type, _capacity)           \
do                                                        \
{                                                         \
    (array)->elements = malloc(_capacity * sizeof(type)); \
    (array)->capacity = _capacity;                        \
    (array)->size = 0;                                    \
}                                                         \
while(0)

#define GONC_ARRAY_GET(array, index) \
(array)->elements[index]

#define GONC_ARRAY_SET(array, index, element) \
do                                            \
{                                             \
    if(index < (array)->capacity)             \
    {                                         \
        (array)->elements[index] = element;   \
        ++((array)->size);                    \
    }                                         \
}                                             \
while(0)

#endif
