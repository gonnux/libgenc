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

#define GENC_ALIST_TYPEOF_ELEM(self) \
__typeof__(**(self)->genc_Alist.elems)

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

#define GENC_ALIST_RAW_GET(self, idx) \
(GENC_ALIST_ELEMS(self)[idx])

#define GENC_ALIST_GET(self, idx, elem) do{ \
    if(idx < GENC_ALIST_SIZE(self)) \
        *(elem) = GENC_ALIST_RAW_GET(self, idx); \
    else \
        *(elem) = NULL; \
} while(0)

#define GENC_ALIST_RAW_SET(self, idx, elem) \
GENC_ALIST_ELEMS(self)[idx] = elem

#define GENC_ALIST_SET(self, idx, elem) do { \
    if(idx < GENC_ALIST_SIZE(self)) \
        GENC_ALIST_RAW_SET(self, idx, elem); \
} while(0)

#define GENC_ALIST_RAW_PEEK(self) \
GENC_ALIST_GET(self, GENC_ALIST_SIZE(self) - 1)

#define GENC_ALIST_PEEK(self, elem)  \
GENC_ALIST_GET(self, GENC_ALIST_SIZE(self) - 1, elem)

#define GENC_ALIST_INSERT(self, idx, elem) do { \
    if(idx > GENC_ALIST_SIZE(self)) \
        break; \
    GENC_ALIST_REALLOC2(self); \
    if(idx < GENC_ALIST_SIZE(self)) \
        GENC_ALIST_RAW_MOVE(self, idx, idx + 1, GENC_ALIST_SIZE(self) - idx); \
    GENC_ALIST_RAW_SET(self, idx, elem); \
    ++GENC_ALIST_SIZE(self); \
} while(0)

#define GENC_ALIST_PUSH(self, elem) \
GENC_ALIST_INSERT(self, GENC_ALIST_SIZE(self), elem)

#define GENC_ALIST_REMOVE(self, idx, elem) do { \
    if(idx > GENC_ALIST_SIZE(self) - 1) \
        break; \
    *elem = GENC_ALIST_RAW_GET(self, idx); \
    if(idx < GENC_ALIST_SIZE(self) - 1) \
        GENC_ALIST_RAW_MOVE(self, idx + 1, idx, GENC_ALIST_SIZE(self) - idx - 1); \
    --GENC_ALIST_SIZE(self); \
} while(0)

#define GENC_ALIST_POP(self, elem) \
GENC_ALIST_REMOVE(self, GENC_ALIST_SIZE(self) - 1, elem)

#define GENC_ALIST_FOREACH(self, idx) \
for(size_t idx = 0; idx != GENC_ALIST_SIZE(self); ++idx)

#define GENC_ALIST_REV_FOREACH(self, idx) \
for(size_t idx = GENC_ALIST_SIZE(self) - 1; idx != -1; --idx)

#define GENC_ALIST_SUB_FOREACH(self, idx, start, end) \
for(size_t idx = start; idx != end; ++idx)

#define GENC_ALIST_REV_SUB_FOREACH(self, idx, end, start) \
for(size_t idx = end; idx != start; --idx)

#define GENC_ALIST_SWAP(self, idx, idx2) do { \
    GENC_ALIST_TYPEOF_ELEM(self)* elem; \
    GENC_ALIST_TYPEOF_ELEM(self)* elem2; \
    GENC_ALIST_GET(self, idx, &elem); \
    GENC_ALIST_GET(self, idx2, &elem2); \
    GENC_ALIST_RAW_SET(self, idx2, elem);\
    GENC_ALIST_RAW_SET(self, idx, elem2); \
} while(0)

#define GENC_ALIST_SORT(self, isBigger) do { \
    size_t idx; \
    size_t idx2; \
    GENC_ALIST_FOREACH(self, idx) { \
        GENC_ALIST_SUB_FOREACH(self, idx2, 0, GENC_ALIST_SIZE(self)) { \
            if(isBigger(GENC_ALIST_RAW_GET(self, idx), GENC_ALIST_RAW_GET(self, idx2))) { \
                GENC_ALIST_SWAP(self, idx, idx2); \
            } \
        } \
    } \
} while(0) \

#endif
