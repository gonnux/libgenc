#ifndef _GENC_ARRAY_LIST_H
#define _GENC_ARRAY_LIST_H

#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define GENC_ARRAY_LIST(type) \
struct {                      \
    type* elements;           \
    size_t capacity;          \
    size_t size;              \
} genc_ArrayList

#define GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList) \
sizeof(*((arrayList)->genc_ArrayList.elements))

#define GENC_ARRAY_LIST_INIT(arrayList, _capacity)                                                      \
do {                                                                                                    \
    if(_capacity <= 0)                                                                                  \
        errx(EXIT_FAILURE, "%s: %u: capacity should be larger than 0", __FILE__, __LINE__);             \
    (arrayList)->genc_ArrayList.elements = malloc(_capacity * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
    GENC_ARRAY_LIST_CAPACITY(arrayList) = _capacity;                                                    \
    GENC_ARRAY_LIST_SIZE(arrayList) = 0;                                                                \
} while(0)

#define GENC_ARRAY_LIST_CAPACITY(arrayList) \
((arrayList)->genc_ArrayList.capacity)

#define GENC_ARRAY_LIST_SIZE(arrayList) \
((arrayList)->genc_ArrayList.size)

#define GENC_ARRAY_LIST_GET(arrayList, index) \
((arrayList)->genc_ArrayList.elements[index])

#define GENC_ARRAY_LIST_GET2(arrayList, index, element) \
*element = GENC_ARRAY_LIST_GET(arrayList, index)

#define GENC_ARRAY_LIST_SET(arrayList, index, element) \
(arrayList)->genc_ArrayList.elements[index] = element

#define GENC_ARRAY_LIST_PEEK(arrayList, element) \
GENC_ARRAY_LIST_GET2(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1, element)

#define GENC_ARRAY_LIST_REALLOC(arrayList, capacity)                                                \
do {                                                                                                \
    if(capacity >= GENC_ARRAY_LIST_SIZE(arrayList)) {                                               \
        GENC_ARRAY_LIST_CAPACITY(arrayList) = capacity;                                             \
        (arrayList)->genc_ArrayList.elements = realloc((arrayList)->genc_ArrayList.elements,        \
                                                        GENC_ARRAY_LIST_CAPACITY(arrayList)         \
                                                        * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
    }                                                                                               \
} while(0)

#define GENC_ARRAY_LIST_INSERT(arrayList, index, element)                                           \
do {                                                                                                \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList))                                                     \
        break;                                                                                      \
    if(GENC_ARRAY_LIST_SIZE(arrayList) == GENC_ARRAY_LIST_CAPACITY(arrayList)) {                    \
        GENC_ARRAY_LIST_CAPACITY(arrayList) *= 2;                                                   \
        (arrayList)->genc_ArrayList.elements = realloc((arrayList)->genc_ArrayList.elements,        \
                                                        GENC_ARRAY_LIST_CAPACITY(arrayList)         \
                                                        * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
    }                                                                                               \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList)) {                                                   \
        memmove((arrayList)->genc_ArrayList.elements + index + 1,                                   \
             (arrayList)->genc_ArrayList.elements + index,                                          \
             (GENC_ARRAY_LIST_SIZE(arrayList) - index) * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList));  \
    }                                                                                               \
    GENC_ARRAY_LIST_SET(arrayList, index, element);                                                 \
    ++GENC_ARRAY_LIST_SIZE(arrayList);                                                              \
} while(0)

#define GENC_ARRAY_LIST_PUSH(arrayList, element) \
GENC_ARRAY_LIST_INSERT(arrayList, GENC_ARRAY_LIST_SIZE(arrayList), element)

#define GENC_ARRAY_LIST_REMOVE(arrayList, index, element)                                          \
do {                                                                                               \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList) - 1)                                                \
        break;                                                                                     \
    *element = GENC_ARRAY_LIST_GET(arrayList, index);                                              \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList) - 1) {                                              \
        memmove((arrayList)->genc_ArrayList.elements + index,                                      \
             (arrayList)->genc_ArrayList.elements + index + 1,                                     \
             (GENC_ARRAY_LIST_SIZE(arrayList) - index) * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
    }                                                                                              \
    --GENC_ARRAY_LIST_SIZE(arrayList);                                                             \
} while(0)

#define GENC_ARRAY_LIST_POP(arrayList, element) \
GENC_ARRAY_LIST_REMOVE(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1, element)

#define GENC_ARRAY_LIST_FOR_EACH(arrayList, index) \
for(size_t index = 0; index != GENC_ARRAY_LIST_SIZE(arrayList); ++index)

#define GENC_ARRAY_LIST_REVERSE_FOR_EACH(arrayList, index) \
for(size_t index = GENC_ARRAY_LIST_SIZE(arrayList) - 1; index != -1; --index)

#define GENC_ARRAY_LIST_SUBSET_FOR_EACH(arrayList, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_LIST_REVERSE_SUBSET_FOR_EACH(arrayList, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
