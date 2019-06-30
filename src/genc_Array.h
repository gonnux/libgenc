#ifndef _GENC_ARRAY_H
#define _GENC_ARRAY_H

#include <stdlib.h>

#define GENC_ARRAY(type) \
struct { \
    type* elems; \
    size_t size; \
} genc_Array

#define GENC_ARRAY_INIT(self, newSize) { \
    (self)->genc_Array.elems = malloc(newSize * sizeof(*((self)->genc_Array.elems))); \
    (self)->genc_Array.size = newSize; \
}

#define GENC_ARRAY_SIZE(self) \
(self)->genc_Array.size

#define GENC_ARRAY_ELEM_SIZE(self) \
sizeof(*(self)->genc_Array.elems)

#define GENC_ARRAY_GET(self, idx) \
(self)->genc_Array.elems[idx]

#define GENC_ARRAY_GET2(self, idx, elem) \
*(elem) = (self)->genc_Array.elems[idx]

#define GENC_ARRAY_SET(self, idx, elem) { \
    if(idx < (self)->genc_Array.size) \
        (self)->genc_Array.elems[idx] = elem; \
}

#define GENC_ARRAY_FOREACH(self, idx) \
for(size_t idx = 0; idx != (self)->genc_Array.size; ++idx)

#define GENC_ARRAY_REV_FOREACH(self, idx) \
for(size_t idx = (self)->genc_Array.size - 1; idx != -1; --idx)

#define GENC_ARRAY_SUB_FOREACH(self, idx, start, end) \
for(size_t idx = start; idx != end; ++idx)

#define GENC_ARRAY_REV_SUB_FOREACH(self, idx, end, start) \
for(size_t idx = end; idx != start; --idx)

#endif
