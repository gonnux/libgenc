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

#define GENC_ALIST_ELEM_SIZE(self) \
sizeof(*(GENC_ALIST_ELEMS(self)))

#define GENC_ALIST_CAPACITY(self) \
((self)->genc_Alist.capacity)

#define GENC_ALIST_SIZE(self) \
((self)->genc_Alist.size)

#define GENC_ALIST_ELEMS(self) \
((self)->genc_Alist.elems)

#define GENC_ALIST_RAW_REALLOC(self, newCapacity) do { \
    GENC_ALIST_CAPACITY(self) = newCapacity; \
    GENC_ALIST_ELEMS(self) = realloc(GENC_ALIST_ELEMS(self), \
                                               GENC_ALIST_CAPACITY(self) \
                                               * GENC_ALIST_ELEM_SIZE(self)); \
} while(0)

#define GENC_ALIST_SHRINK(self) \
GENC_ALIST_RAW_REALLOC(self, GENC_ALIST_SIZE(self)); \

#define GENC_ALIST_REALLOC(self, newCapacity) do { \
    if(newCapacity >= 0) { \
        if(GENC_ALIST_ELEMS(self) != NULL) { \
            if(newCapacity != GENC_ALIST_CAPACITY(self)) { \
                if(newCapacity <= GENC_ALIST_SIZE(self)) { \
                    GENC_ALIST_SHRINK(self); \
                } else { \
                    GENC_ALIST_RAW_REALLOC(self, newCapacity); \
                } \
            } \
        } else { \
            GENC_ALIST_ELEMS(self) = calloc(newCapacity, GENC_ALIST_ELEM_SIZE(self)); \
            GENC_ALIST_CAPACITY(self) = newCapacity; \
        } \
    } \
} while(0)

#define GENC_ALIST_REALLOC2(self) do { \
    if(GENC_ALIST_SIZE(self) == GENC_ALIST_CAPACITY(self)) \
        GENC_ALIST_RAW_REALLOC(self, (GENC_ALIST_CAPACITY(self) + 1) * 2); \
} while(0)

#define GENC_ALIST_RAW_MOVE(self, beginIndex, endIndex, moveCount) do { \
    memmove( \
        GENC_ALIST_ELEMS(self) + endIndex, \
        GENC_ALIST_ELEMS(self) + beginIndex, \
        (moveCount) * GENC_ALIST_ELEM_SIZE(self)); \
} while(0)

#define GENC_ALIST_INIT(self) do { \
    GENC_ALIST_ELEMS(self) = NULL; \
    GENC_ALIST_CAPACITY(self) = 0; \
    GENC_ALIST_SIZE(self) = 0; \
} while(0)

#define GENC_ALIST_ZERO_ELEMS(self, beginIndex, endIndex) do { \
    if(GENC_ALIST_SIZE(self) > 0 && endIndex - beginIndex >= 0) \
        memset(GENC_ALIST_ELEMS(self) + beginIndex, 0, (endIndex - beginIndex + 1) * GENC_ALIST_ELEM_SIZE(self)); \
} while(0)

#define GENC_ALIST_INIT2(self, initialCapacity) do { \
    GENC_ALIST_INIT(self); \
    GENC_ALIST_REALLOC(self, initialCapacity); \
} while(0)

#define GENC_ALIST_FREE(self) do { \
    free(GENC_ALIST_ELEMS(self)); \
    GENC_ALIST_INIT(self); \
} while(0)

#define GENC_ALIST_RAW_GET(self, index) \
(GENC_ALIST_ELEMS(self)[index])

#define GENC_ALIST_GET(self, index, elem) do{ \
    if(index < GENC_ALIST_SIZE(self)) \
        *(elem) = GENC_ALIST_RAW_GET(self, index); \
    else \
        *(elem) = NULL; \
} while(0)

#define GENC_ALIST_RAW_SET(self, index, elem) \
GENC_ALIST_ELEMS(self)[index] = elem

#define GENC_ALIST_SET(self, index, elem) do { \
    if(index < GENC_ALIST_SIZE(self)) \
        GENC_ALIST_RAW_SET(self, index, elem); \
} while(0)

#define GENC_ALIST_RAW_PEEK(self) \
GENC_ALIST_GET(self, GENC_ALIST_SIZE(self) - 1)

#define GENC_ALIST_PEEK(self, elem)  \
GENC_ALIST_GET(self, GENC_ALIST_SIZE(self) - 1, elem)

#define GENC_ALIST_INSERT(self, index, elem) do { \
    if(index > GENC_ALIST_SIZE(self)) \
        break; \
    GENC_ALIST_REALLOC2(self); \
    if(index < GENC_ALIST_SIZE(self)) \
        GENC_ALIST_RAW_MOVE(self, index, index + 1, GENC_ALIST_SIZE(self) - index); \
    GENC_ALIST_RAW_SET(self, index, elem); \
    ++GENC_ALIST_SIZE(self); \
} while(0)

#define GENC_ALIST_PUSH(self, elem) \
GENC_ALIST_INSERT(self, GENC_ALIST_SIZE(self), elem)

#define GENC_ALIST_REMOVE(self, index, elem) do { \
    if(index > GENC_ALIST_SIZE(self) - 1) \
        break; \
    *elem = GENC_ALIST_RAW_GET(self, index); \
    if(index < GENC_ALIST_SIZE(self) - 1) \
        GENC_ALIST_RAW_MOVE(self, index + 1, index, GENC_ALIST_SIZE(self) - index - 1); \
    --GENC_ALIST_SIZE(self); \
} while(0)

#define GENC_ALIST_POP(self, elem) \
GENC_ALIST_REMOVE(self, GENC_ALIST_SIZE(self) - 1, elem)

#define GENC_ALIST_FOREACH(self, index) \
for(size_t index = 0; index != GENC_ALIST_SIZE(self); ++index)

#define GENC_ALIST_REV_FOREACH(self, index) \
for(size_t index = GENC_ALIST_SIZE(self) - 1; index != -1; --index)

#define GENC_ALIST_SUB_FOREACH(self, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ALIST_REV_SUB_FOREACH(self, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
