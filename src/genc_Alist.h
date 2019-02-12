#ifndef _GENC_ALIST_H
#define _GENC_ALIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define GENC_ALIST(type) \
struct { \
    type** elems; \
    size_t capacity; \
    size_t size; \
} genc_Alist

#define GENC_ALIST_ELEM_SIZE(arrayList) \
sizeof(*(GENC_ALIST_ELEMS(arrayList)))

#define GENC_ALIST_CAPACITY(arrayList) \
((arrayList)->genc_Alist.capacity)

#define GENC_ALIST_SIZE(arrayList) \
((arrayList)->genc_Alist.size)

#define GENC_ALIST_ELEMS(arrayList) \
((arrayList)->genc_Alist.elems)

#define GENC_ALIST_RAW_REALLOC(arrayList, newCapacity) do { \
    GENC_ALIST_CAPACITY(arrayList) = newCapacity; \
    GENC_ALIST_ELEMS(arrayList) = realloc(GENC_ALIST_ELEMS(arrayList), \
                                               GENC_ALIST_CAPACITY(arrayList) \
                                               * GENC_ALIST_ELEM_SIZE(arrayList)); \
} while(0)

#define GENC_ALIST_SHRINK(arrayList) \
GENC_ALIST_RAW_REALLOC(arrayList, GENC_ALIST_SIZE(arrayList)); \

#define GENC_ALIST_REALLOC(arrayList, newCapacity) do { \
    if(newCapacity >= 0) { \
        if(GENC_ALIST_ELEMS(arrayList) != NULL) { \
            if(newCapacity != GENC_ALIST_CAPACITY(arrayList)) { \
                if(newCapacity <= GENC_ALIST_SIZE(arrayList)) { \
                    GENC_ALIST_SHRINK(arrayList); \
                } else { \
                    GENC_ALIST_RAW_REALLOC(arrayList, newCapacity); \
                } \
            } \
        } else { \
            GENC_ALIST_ELEMS(arrayList) = calloc(newCapacity, GENC_ALIST_ELEM_SIZE(arrayList)); \
            GENC_ALIST_CAPACITY(arrayList) = newCapacity; \
        } \
    } \
} while(0)

#define GENC_ALIST_REALLOC2(arrayList) do { \
    if(GENC_ALIST_SIZE(arrayList) == GENC_ALIST_CAPACITY(arrayList)) \
        GENC_ALIST_RAW_REALLOC(arrayList, (GENC_ALIST_CAPACITY(arrayList) + 1) * 2); \
} while(0)

#define GENC_ALIST_RAW_MOVE(arrayList, beginIndex, endIndex, moveCount) do { \
    memmove( \
        GENC_ALIST_ELEMS(arrayList) + endIndex, \
        GENC_ALIST_ELEMS(arrayList) + beginIndex, \
        (moveCount) * GENC_ALIST_ELEM_SIZE(arrayList)); \
} while(0)

#define GENC_ALIST_INIT(arrayList) do { \
    GENC_ALIST_ELEMS(arrayList) = NULL; \
    GENC_ALIST_CAPACITY(arrayList) = 0; \
    GENC_ALIST_SIZE(arrayList) = 0; \
} while(0)

#define GENC_ALIST_ZERO_ELEMS(arrayList, beginIndex, endIndex) do { \
    if(GENC_ALIST_SIZE(arrayList) > 0 && endIndex - beginIndex >= 0) \
        memset(GENC_ALIST_ELEMS(arrayList) + beginIndex, 0, (endIndex - beginIndex + 1) * GENC_ALIST_ELEM_SIZE(arrayList)); \
} while(0)

#define GENC_ALIST_INIT2(arrayList, initialCapacity) do { \
    GENC_ALIST_INIT(arrayList); \
    GENC_ALIST_REALLOC(arrayList, initialCapacity); \
} while(0)

#define GENC_ALIST_FREE(arrayList) do { \
    free(GENC_ALIST_ELEMS(arrayList)); \
    GENC_ALIST_INIT(arrayList); \
} while(0)

#define GENC_ALIST_RAW_GET(arrayList, index) \
(GENC_ALIST_ELEMS(arrayList)[index])

#define GENC_ALIST_GET(arrayList, index, elem) do{ \
    if(index < GENC_ALIST_SIZE(arrayList)) \
        *(elem) = GENC_ALIST_RAW_GET(arrayList, index); \
    else \
        *(elem) = NULL; \
} while(0)

#define GENC_ALIST_RAW_SET(arrayList, index, elem) \
GENC_ALIST_ELEMS(arrayList)[index] = elem

#define GENC_ALIST_SET(arrayList, index, elem) do { \
    if(index < GENC_ALIST_SIZE(arrayList)) \
        GENC_ALIST_RAW_SET(arrayList, index, elem); \
} while(0)

#define GENC_ALIST_RAW_PEEK(arrayList) \
GENC_ALIST_GET(arrayList, GENC_ALIST_SIZE(arrayList) - 1)

#define GENC_ALIST_PEEK(arrayList, elem)  \
GENC_ALIST_GET(arrayList, GENC_ALIST_SIZE(arrayList) - 1, elem)

#define GENC_ALIST_INSERT(arrayList, index, elem) do { \
    if(index > GENC_ALIST_SIZE(arrayList)) \
        break; \
    GENC_ALIST_REALLOC2(arrayList); \
    if(index < GENC_ALIST_SIZE(arrayList)) \
        GENC_ALIST_RAW_MOVE(arrayList, index, index + 1, GENC_ALIST_SIZE(arrayList) - index); \
    GENC_ALIST_RAW_SET(arrayList, index, elem); \
    ++GENC_ALIST_SIZE(arrayList); \
} while(0)

#define GENC_ALIST_PUSH(arrayList, elem) \
GENC_ALIST_INSERT(arrayList, GENC_ALIST_SIZE(arrayList), elem)

#define GENC_ALIST_REMOVE(arrayList, index, elem) do { \
    if(index > GENC_ALIST_SIZE(arrayList) - 1) \
        break; \
    *elem = GENC_ALIST_RAW_GET(arrayList, index); \
    if(index < GENC_ALIST_SIZE(arrayList) - 1) \
        GENC_ALIST_RAW_MOVE(arrayList, index + 1, index, GENC_ALIST_SIZE(arrayList) - index - 1); \
    --GENC_ALIST_SIZE(arrayList); \
} while(0)

#define GENC_ALIST_POP(arrayList, elem) \
GENC_ALIST_REMOVE(arrayList, GENC_ALIST_SIZE(arrayList) - 1, elem)

#define GENC_ALIST_FOR_EACH(arrayList, index) \
for(size_t index = 0; index != GENC_ALIST_SIZE(arrayList); ++index)

#define GENC_ALIST_REVERSE_FOR_EACH(arrayList, index) \
for(size_t index = GENC_ALIST_SIZE(arrayList) - 1; index != -1; --index)

#define GENC_ALIST_SUBSET_FOR_EACH(arrayList, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ALIST_REVERSE_SUBSET_FOR_EACH(arrayList, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
