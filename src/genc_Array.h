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

#define GENC_ARRAY_GET(self, index) \
(self)->genc_Array.elems[index]

#define GENC_ARRAY_GET2(self, index, elem) \
*(elem) = (self)->genc_Array.elems[index]

#define GENC_ARRAY_SET(self, index, elem) { \
    if(index < (self)->genc_Array.size) \
        (self)->genc_Array.elems[index] = elem; \
}

#define GENC_ARRAY_FOREACH(self, index) \
for(size_t index = 0; index != (self)->genc_Array.size; ++index)

#define GENC_ARRAY_REV_FOREACH(self, index) \
for(size_t index = (self)->genc_Array.size - 1; index != -1; --index)

#define GENC_ARRAY_SUB_FOREACH(self, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_REV_SUB_FOREACH(self, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
