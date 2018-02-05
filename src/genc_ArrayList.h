#ifndef _GENC_ARRAY_LIST_H
#define _GENC_ARRAY_LIST_H

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

#define GENC_ARRAY_LIST_CAPACITY(arrayList) \
((arrayList)->genc_ArrayList.capacity)

#define GENC_ARRAY_LIST_SIZE(arrayList) \
((arrayList)->genc_ArrayList.size)

#define GENC_ARRAY_LIST_RAW_REALLOC(arrayList, newCapacity)                                         \
do {                                                                                                \
    GENC_ARRAY_LIST_CAPACITY(arrayList) = newCapacity;                                              \
    (arrayList)->genc_ArrayList.elements = realloc((arrayList)->genc_ArrayList.elements,            \
                                                        GENC_ARRAY_LIST_CAPACITY(arrayList)         \
                                                        * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
} while(0)

#define GENC_ARRAY_LIST_SHRINK(arrayList)                                \
GENC_ARRAY_LIST_RAW_REALLOC(arrayList, GENC_ARRAY_LIST_SIZE(arrayList)); \

#define GENC_ARRAY_LIST_REALLOC(arrayList, newCapacity)                                                           \
do {                                                                                                              \
    if(newCapacity >= 0) {                                                                                        \
        if((arrayList)->genc_ArrayList.elements != NULL) {                                                        \
            if(newCapacity != GENC_ARRAY_LIST_CAPACITY(arrayList)) {                                              \
                if(newCapacity <= GENC_ARRAY_LIST_SIZE(arrayList)) {                                              \
                    GENC_ARRAY_LIST_SHRINK(arrayList);                                                            \
                } else {                                                                                          \
                    GENC_ARRAY_LIST_RAW_REALLOC(arrayList, newCapacity);                                          \
                }                                                                                                 \
            }                                                                                                     \
        } else {                                                                                                  \
            (arrayList)->genc_ArrayList.elements = malloc(newCapacity * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
            GENC_ARRAY_LIST_CAPACITY(arrayList) = newCapacity;                                                    \
        }                                                                                                         \
    }                                                                                                             \
} while(0)

#define GENC_ARRAY_LIST_REALLOC2(arrayList)                                                    \
do {                                                                                           \
    if(GENC_ARRAY_LIST_SIZE(arrayList) == GENC_ARRAY_LIST_CAPACITY(arrayList))                 \
        GENC_ARRAY_LIST_RAW_REALLOC(arrayList, (GENC_ARRAY_LIST_CAPACITY(arrayList) + 1) * 2); \
} while(0)

#define GENC_ARRAY_LIST_RAW_MOVE(arrayList, beginIndex, endIndex, moveCount) \
do {                                                                         \
    memmove(                                                                 \
        (arrayList)->genc_ArrayList.elements + endIndex,                     \
        (arrayList)->genc_ArrayList.elements + beginIndex,                   \
        (moveCount) * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList));              \
} while(0)

#define GENC_ARRAY_LIST_INIT(arrayList)          \
do {                                             \
    (arrayList)->genc_ArrayList.elements = NULL; \
    GENC_ARRAY_LIST_CAPACITY(arrayList) = 0;     \
    GENC_ARRAY_LIST_SIZE(arrayList) = 0;         \
} while(0)

#define GENC_ARRAY_LIST_ZERO(arrayList, beginIndex, endIndex)                                                                                \
do {                                                                                                                                         \
    if(GENC_ARRAY_LIST_SIZE(arrayList) > 0 && endIndex - beginIndex >= 0)                                                                    \
        memset((arrayList)->genc_ArrayList.elements + beginIndex, 0, (endIndex - beginIndex + 1) * GENC_ARRAY_LIST_ELEMENT_SIZE(arrayList)); \
} while(0)

#define GENC_ARRAY_LIST_INIT2(arrayList, initialCapacity) \
do {                                                      \
    GENC_ARRAY_LIST_INIT(arrayList);                      \
    GENC_ARRAY_LIST_REALLOC(arrayList, initialCapacity);  \
} while(0)

#define GENC_ARRAY_LIST_INIT3(arrayList, initialSize)      \
do {                                                       \
    GENC_ARRAY_LIST_INIT2(arrayList, (initialSize) * 2);   \
    GENC_ARRAY_LIST_SIZE(arrayList) = initialSize;         \
    GENC_ARRAY_LIST_ZERO(arrayList, 0, (initialSize) - 1); \
} while(0)


#define GENC_ARRAY_LIST_FREE(arrayList)          \
do {                                             \
    free((arrayList)->genc_ArrayList.elements);  \
    GENC_ARRAY_LIST_INIT(arrayList);             \
} while(0)

#define GENC_ARRAY_LIST_GET(arrayList, index) \
((arrayList)->genc_ArrayList.elements[index])

#define GENC_ARRAY_LIST_GET2(arrayList, index, element) \
*element = GENC_ARRAY_LIST_GET(arrayList, index)

#define GENC_ARRAY_LIST_RAW_SET(arrayList, index, element) \
(arrayList)->genc_ArrayList.elements[index] = element

#define GENC_ARRAY_LIST_SET(arrayList, index, element)      \
do {                                                        \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList))             \
        GENC_ARRAY_LIST_RAW_SET(arrayList, index, element); \
} while(0)

#define GENC_ARRAY_LIST_PEEK(arrayList, element) \
GENC_ARRAY_LIST_GET2(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1, element)

#define GENC_ARRAY_LIST_INSERT(arrayList, index, element)                                               \
do {                                                                                                    \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList))                                                         \
        break;                                                                                          \
    GENC_ARRAY_LIST_REALLOC2(arrayList);                                                                \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList))                                                         \
        GENC_ARRAY_LIST_RAW_MOVE(arrayList, index, index + 1, GENC_ARRAY_LIST_SIZE(arrayList) - index); \
    GENC_ARRAY_LIST_RAW_SET(arrayList, index, element);                                                 \
    ++GENC_ARRAY_LIST_SIZE(arrayList);                                                                  \
} while(0)

#define GENC_ARRAY_LIST_INSERT_EMPTY(arrayList, index)                                                   \
do {                                                                                                     \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList))                                                          \
        break;                                                                                           \
    GENC_ARRAY_LIST_REALLOC2(arrayList);                                                                 \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList))                                                          \
        GENC_ARRAY_LIST_RAW_MOVE(arrayList, index, index + 1, GENC_ARRAY_LIST_SIZE(arrayList) - index);  \
    ++GENC_ARRAY_LIST_SIZE(arrayList);                                                                   \
    GENC_ARRAY_LIST_ZERO(arrayList, index, index);                                                       \
} while(0)

#define GENC_ARRAY_LIST_PUSH(arrayList, element) \
GENC_ARRAY_LIST_INSERT(arrayList, GENC_ARRAY_LIST_SIZE(arrayList), element)

#define GENC_ARRAY_LIST_PUSH_EMPTY(arrayList) \
GENC_ARRAY_LIST_INSERT_EMPTY(arrayList, GENC_ARRAY_LIST_SIZE(arrayList))

#define GENC_ARRAY_LIST_REMOVE(arrayList, index, element)                                               \
do {                                                                                                    \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList) - 1)                                                     \
        break;                                                                                          \
    *element = GENC_ARRAY_LIST_GET(arrayList, index);                                                   \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList) - 1)                                                     \
        GENC_ARRAY_LIST_RAW_MOVE(arrayList, index + 1, index, GENC_ARRAY_LIST_SIZE(arrayList) - index); \
    --GENC_ARRAY_LIST_SIZE(arrayList);                                                                  \
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
