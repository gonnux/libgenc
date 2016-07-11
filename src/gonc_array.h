#ifndef _GONC_ARRAY_H
#define _GONC_ARRAY_H

#include <stdlib.h>

#define GONC_ARRAY(name, type) \
struct name                    \
{                              \
    type* elements;            \
    size_t size;               \
}

#define GONC_ARRAY_INIT(array, type, _size)           \
do                                                   \
{                                                    \
    (array)->elements = malloc(_size * sizeof(type)); \
    (array)->size = _size;                          \
}                                                    \
while(0)

#endif
