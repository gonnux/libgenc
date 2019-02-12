#ifndef _GENC_ARRAY_LIST_H
#define _GENC_ARRAY_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define GENC_ARRAY_LIST(type) \
struct { \
    type** elems; \
    size_t capacity; \
    size_t size; \
} genc_ArrayList

#define GENC_ARRAY_LIST_ELEM_SIZE(arrayList) \
sizeof(*(GENC_ARRAY_LIST_ELEMS(arrayList)))

#define GENC_ARRAY_LIST_CAPACITY(arrayList) \
((arrayList)->genc_ArrayList.capacity)

#define GENC_ARRAY_LIST_SIZE(arrayList) \
((arrayList)->genc_ArrayList.size)

#define GENC_ARRAY_LIST_ELEMS(arrayList) \
((arrayList)->genc_ArrayList.elems)

#define GENC_ARRAY_LIST_RAW_REALLOC(arrayList, newCapacity) do { \
    GENC_ARRAY_LIST_CAPACITY(arrayList) = newCapacity; \
    GENC_ARRAY_LIST_ELEMS(arrayList) = realloc(GENC_ARRAY_LIST_ELEMS(arrayList), \
                                               GENC_ARRAY_LIST_CAPACITY(arrayList) \
                                               * GENC_ARRAY_LIST_ELEM_SIZE(arrayList)); \
} while(0)

#define GENC_ARRAY_LIST_SHRINK(arrayList) \
GENC_ARRAY_LIST_RAW_REALLOC(arrayList, GENC_ARRAY_LIST_SIZE(arrayList)); \

#define GENC_ARRAY_LIST_REALLOC(arrayList, newCapacity) do { \
    if(newCapacity >= 0) { \
        if(GENC_ARRAY_LIST_ELEMS(arrayList) != NULL) { \
            if(newCapacity != GENC_ARRAY_LIST_CAPACITY(arrayList)) { \
                if(newCapacity <= GENC_ARRAY_LIST_SIZE(arrayList)) { \
                    GENC_ARRAY_LIST_SHRINK(arrayList); \
                } else { \
                    GENC_ARRAY_LIST_RAW_REALLOC(arrayList, newCapacity); \
                } \
            } \
        } else { \
            GENC_ARRAY_LIST_ELEMS(arrayList) = calloc(newCapacity, GENC_ARRAY_LIST_ELEM_SIZE(arrayList)); \
            GENC_ARRAY_LIST_CAPACITY(arrayList) = newCapacity; \
        } \
    } \
} while(0)

#define GENC_ARRAY_LIST_REALLOC2(arrayList) do { \
    if(GENC_ARRAY_LIST_SIZE(arrayList) == GENC_ARRAY_LIST_CAPACITY(arrayList)) \
        GENC_ARRAY_LIST_RAW_REALLOC(arrayList, (GENC_ARRAY_LIST_CAPACITY(arrayList) + 1) * 2); \
} while(0)

#define GENC_ARRAY_LIST_RAW_MOVE(arrayList, beginIndex, endIndex, moveCount) do { \
    memmove( \
        GENC_ARRAY_LIST_ELEMS(arrayList) + endIndex, \
        GENC_ARRAY_LIST_ELEMS(arrayList) + beginIndex, \
        (moveCount) * GENC_ARRAY_LIST_ELEM_SIZE(arrayList)); \
} while(0)

#define GENC_ARRAY_LIST_INIT(arrayList) do { \
    GENC_ARRAY_LIST_ELEMS(arrayList) = NULL; \
    GENC_ARRAY_LIST_CAPACITY(arrayList) = 0; \
    GENC_ARRAY_LIST_SIZE(arrayList) = 0; \
} while(0)

#define GENC_ARRAY_LIST_ZERO_ELEMS(arrayList, beginIndex, endIndex) do { \
    if(GENC_ARRAY_LIST_SIZE(arrayList) > 0 && endIndex - beginIndex >= 0) \
        memset(GENC_ARRAY_LIST_ELEMS(arrayList) + beginIndex, 0, (endIndex - beginIndex + 1) * GENC_ARRAY_LIST_ELEM_SIZE(arrayList)); \
} while(0)

#define GENC_ARRAY_LIST_INIT2(arrayList, initialCapacity) do { \
    GENC_ARRAY_LIST_INIT(arrayList); \
    GENC_ARRAY_LIST_REALLOC(arrayList, initialCapacity); \
} while(0)

#define GENC_ARRAY_LIST_FREE(arrayList) do { \
    free(GENC_ARRAY_LIST_ELEMS(arrayList)); \
    GENC_ARRAY_LIST_INIT(arrayList); \
} while(0)

#define GENC_ARRAY_LIST_GET(arrayList, index) \
(GENC_ARRAY_LIST_ELEMS(arrayList)[index])

#define GENC_ARRAY_LIST_GET2(arrayList, index, elem) \
*elem = GENC_ARRAY_LIST_GET(arrayList, index)

#define GENC_ARRAY_LIST_RAW_SET(arrayList, index, elem) \
GENC_ARRAY_LIST_ELEMS(arrayList)[index] = elem

#define GENC_ARRAY_LIST_SET(arrayList, index, elem) do { \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList)) \
        GENC_ARRAY_LIST_RAW_SET(arrayList, index, elem); \
} while(0)

#define GENC_ARRAY_LIST_PEEK(arrayList) \
GENC_ARRAY_LIST_GET(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1)

#define GENC_ARRAY_LIST_PEEK2(arrayList, elem) \
GENC_ARRAY_LIST_GET2(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1, elem)

#define GENC_ARRAY_LIST_INSERT(arrayList, index, elem) do { \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList)) \
        break; \
    GENC_ARRAY_LIST_REALLOC2(arrayList); \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList)) \
        GENC_ARRAY_LIST_RAW_MOVE(arrayList, index, index + 1, GENC_ARRAY_LIST_SIZE(arrayList) - index); \
    GENC_ARRAY_LIST_RAW_SET(arrayList, index, elem); \
    ++GENC_ARRAY_LIST_SIZE(arrayList); \
} while(0)

#define GENC_ARRAY_LIST_PUSH(arrayList, elem) \
GENC_ARRAY_LIST_INSERT(arrayList, GENC_ARRAY_LIST_SIZE(arrayList), elem)

#define GENC_ARRAY_LIST_REMOVE(arrayList, index, elem) do { \
    if(index > GENC_ARRAY_LIST_SIZE(arrayList) - 1) \
        break; \
    *elem = GENC_ARRAY_LIST_GET(arrayList, index); \
    if(index < GENC_ARRAY_LIST_SIZE(arrayList) - 1) \
        GENC_ARRAY_LIST_RAW_MOVE(arrayList, index + 1, index, GENC_ARRAY_LIST_SIZE(arrayList) - index - 1); \
    --GENC_ARRAY_LIST_SIZE(arrayList); \
} while(0)

#define GENC_ARRAY_LIST_POP(arrayList, elem) \
GENC_ARRAY_LIST_REMOVE(arrayList, GENC_ARRAY_LIST_SIZE(arrayList) - 1, elem)

#define GENC_ARRAY_LIST_FOR_EACH(arrayList, index) \
for(size_t index = 0; index != GENC_ARRAY_LIST_SIZE(arrayList); ++index)

#define GENC_ARRAY_LIST_REVERSE_FOR_EACH(arrayList, index) \
for(size_t index = GENC_ARRAY_LIST_SIZE(arrayList) - 1; index != -1; --index)

#define GENC_ARRAY_LIST_SUBSET_FOR_EACH(arrayList, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_LIST_REVERSE_SUBSET_FOR_EACH(arrayList, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
