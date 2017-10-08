#ifndef _GENC_ARRAY_LIST_H
#define _GENC_ARRAY_LIST_H

#include <err.h>
#include <stdbool.h>
#include <stdlib.h>

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
    if(GENC_ARRAY_LIST_CAPACITY(arrayList) <= 0)                                                        \
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

#define GENC_ARRAY_LIST_PEEK(arrayList, element) \
*element = GENC_ARRAY_LIST_GET(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1)

#define GENC_ARRAY_LIST_PUSH(arrayList, element)                                                    \
do {                                                                                                \
    if(GENC_ARRAY_LIST_SIZE(arrayList) >= GENC_ARRAY_LIST_CAPACITY(arrayList)) {                    \
        GENC_ARRAY_LIST_CAPACITY(arrayList) *= 2;                                                   \
        (arrayList)->genc_ArrayList.elements = realloc((arrayList)->genc_ArrayList.elements,        \
                                                        GENC_ARRAY_LIST_CAPACITY(arrayList)         \
                                                        * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
    }                                                                                               \
    (arrayList)->genc_ArrayList.elements[GENC_ARRAY_LIST_SIZE(arrayList)] = element;                \
    ++GENC_ARRAY_LIST_SIZE(arrayList);                                                              \
} while(0)

#define GENC_ARRAY_LIST_POP(arrayList, element) \
do {                                            \
    GENC_ARRAY_LIST_PEEK(arrayList, element);   \
    --GENC_ARRAY_LIST_SIZE(arrayList);          \
} while(0)

#define GENC_ARRAY_LIST_FOR_EACH(arrayList, index) \
for(size_t index = 0; index != GENC_ARRAY_LIST_SIZE(arrayList); ++index)

#define GENC_ARRAY_LIST_REVERSE_FOR_EACH(arrayList, index) \
for(size_t index = GENC_ARRAY_LIST_SIZE(arrayList) - 1; index != -1; --index)

#define GENC_ARRAY_LIST_SUBSET_FOR_EACH(arrayList, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_LIST_REVERSE_SUBSET_FOR_EACH(arrayList, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
