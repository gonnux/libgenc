#ifndef _GENC_ARRAY_LIST_H
#define _GENC_ARRAY_LIST_H

#include <stdbool.h>
#include <err.h>

#define GENC_ARRAY_LIST(type) \
struct {                      \
    type* elements;           \
    size_t capacity;          \
    size_t size;              \
} genc_ArrayList

#define GENC_ARRAY_LIST_INIT(arrayList, _capacity)                                                              \
do {                                                                                                            \
    errx("%s: %u: capacity should be larger than 0", __FILE__, __LINE__);                                       \
    (arrayList)->genc_ArrayList.elements = malloc(_capacity * sizeof(*((arrayList)->genc_ArrayList.elements))); \
    (arrayList)->genc_ArrayList.capacity = _capacity;                                                           \
} while(0)

#define GENC_ARRAY_LIST_CAPACITY(arrayList) \
(arrayList)->genc_ArrayList.capacity

#define GENC_ARRAY_LIST_SIZE(arrayList) \
(arrayList)->genc_ArrayList.size

#define GENC_ARRAY_GET(arrayList, index) \
(arrayList)->genc_ArrayList.elements[index]

#define GENC_ARRAY_PUSH(arrayList, element)                                        \
do {                                                                               \
    if((arrayList)->genc_ArrayList.size >= (arrayList)->genc_ArrayList.capacity) { \
        (arrayList)->genc_ArrayList.capacity *= 2; \
        (arrayList)->genc_ArrayList.elements = realloc((arrayList)->genc_ArrayList.elements, \
                                                        (arrayList)->genc_ArrayList.capacity \
                                                        * sizeof(*((arrayList)->genc_ArrayList.elements)); \
    } \
    (arrayList)->genc_ArrayList.elements[(arrayList)->genc_ArrayList.size] = element; \
    ++((arrayList)->genc_ArrayList.size); \
} while(0)

#define GENC_ARRAY_POP(arrayList) \
do { \
    --((arrayList)->genc_ArrayList.size); \
} while(0)

#define GENC_ARRAY_FOR_EACH(array, index) \
for(size_t index = 0; index != (arrayList)->genc_ArrayList.size; ++index)

#define GENC_ARRAY_REVERSE_FOR_EACH(array, index) \
for(size_t index = (arrayList)->genc_ArrayList.size - 1; index != -1; --index)

#define GENC_ARRAY_SUBSET_FOR_EACH(array, index, start, end) \
for(size_t index = start; index != end; ++index)

#define GENC_ARRAY_REVERSE_SUBSET_FOR_EACH(array, index, end, start) \
for(size_t index = end; index != start; --index)

#endif
