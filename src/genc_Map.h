
#ifndef _GENC_MAP_H
#define _GENC_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "genc_List.h"

#define GENC_MAP_ELEMENT(type) \
struct { \
    GENC_LIST_ELEMENT(type); \
    struct { \
        unsigned char* key; \
        size_t keyLength; \
    } genc_Map_element; \
}

#define GENC_MAP_ELEMENT_INIT(element) do { \
    GENC_LIST_ELEMENT_INIT(element); \
    (element)->genc_Map_element.key = NULL; \
    (element)->genc_Map_element.keyLength = 0; \
} while(0)

#define GENC_MAP_ELEMENT_KEY(element) \
(element)->genc_Map_element.key

#define GENC_MAP_ELEMENT_KEY_LENGTH(element) \
(element)->genc_Map_element.keyLength

#define GENC_MAP(type) \
struct { \
    type** elements; \
    size_t capacity; \
    size_t size; \
} genc_Map

#define GENC_MAP_ELEMENTS(map) \
(map)->genc_Map.elements

#define GENC_MAP_CAPACITY(map) \
(map)->genc_Map.capacity

#define GENC_MAP_SIZE(map) \
(map)->genc_Map.size

#define GENC_MAP_INDEX(map, index) \
(map)->genc_Map.elements[index]

#define GENC_MAP_REALLOC(map, capacity) { \
    if(GENC_MAP_ELEMENTS(map) == NULL) \
        GENC_MAP_ELEMENTS(map) = calloc(capacity, sizeof(*GENC_MAP_ELEMENTS(map))); \
    else \
        GENC_MAP_ELEMENTS(map) = realloc(GENC_MAP_ELEMENTS(map), GENC_MAP_CAPACITY(map) * sizeof(*(GENC_MAP_ELEMENTS(map)))); \
    GENC_MAP_CAPACITY(map) = capacity; \
}

#define GENC_MAP_REALLOC2(map)                                                    \
do {                                                                                           \
    if(GENC_MAP_SIZE(map) == GENC_MAP_CAPACITY(map))                 \
        GENC_MAP_REALLOC(map, (GENC_MAP_CAPACITY(map) + 1) * 2); \
} while(0)

#define GENC_MAP_INIT(map) { \
    GENC_MAP_REALLOC(map, 10007); \
    GENC_MAP_SIZE(map) = 0; \
}

#define GENC_MAP_INIT2(map, capacity) { \
    GENC_MAP_REALLOC(map, capacity); \
    GENC_MAP_SIZE(map) = 0; \
}

#define GENC_MAP_GET_HASH(map, key, keyLength, hash) { \
    *(hash) = 0; \
    for(size_t i = 0; i != keyLength; ++i) { \
        *(hash) += key[i]; \
        *(hash) << 8; \
    } \
    *(hash) %= GENC_MAP_CAPACITY(map); \
}

#define GENC_MAP_GET_RAW(map, hash, key, keyLength, element) { \
    *(element) = GENC_MAP_INDEX(map, hash); \
    while(*(element) != NULL && strncmp(key, GENC_MAP_ELEMENT_KEY(*(element)), keyLength) != 0) \
        *(element) = GENC_LIST_ELEMENT_NEXT(*(element)); \
}

#define GENC_MAP_GET(map, key, keyLength, element) { \
    size_t hash; \
    GENC_MAP_GET_HASH(map, key, keyLength, &hash); \
    GENC_MAP_GET_RAW(map, hash, key, keyLength, element); \
}

#define GENC_MAP_REMOVE_RAW(map, hash, key, keyLength, element) { \
    element = GENC_MAP_INDEX(map, hash); \
    while(element != NULL && strncmp(key, GENC_MAP_ELEMENT_KEY(element), keyLength) != 0) \
        element = GENC_LIST_ELEMENT_NEXT(element); \
    if(element != NULL) { \
        if(element == GENC_MAP_INDEX(map, hash) && GENC_LIST_ELEMENT_NEXT(element) == NULL) \
            GENC_MAP_INDEX(map, hash) = NULL; \
        GENC_LIST_ELMEENT_REMOVE(element); \
        --(GENC_MAP_SIZE(map)); \
    } \
}

#define GENC_MAP_REMOVE(map, key, keyLength, element) { \
    size_t hash; \
    GENC_MAP_GET_HASH(map, key, keyLength, &hash); \
    GENC_MAP_REMOVE_RAW(map, hash, key, keyLength, element); \
}

// test is needed for oldElement
#define GENC_MAP_SET_RAW(map, hash, element, oldElement) { \
    *(oldElement) = GENC_MAP_INDEX(map, hash); \
    if(*(oldElement) == NULL) { \
        GENC_MAP_INDEX(map, hash) = element; \
        ++GENC_MAP_SIZE(map); \
    } else { \
        bool foundOldElement = false; \
        for( ; *(oldElement) != NULL; \
            *(oldElement) = GENC_LIST_ELEMENT_NEXT(*(oldElement))) { \
            if(strncmp(GENC_MAP_ELEMENT_KEY(element), \
               GENC_MAP_ELEMENT_KEY(*(oldElement)), \
               GENC_MAP_ELEMENT_KEY_LENGTH(element)) == 0) { \
                foundOldElement = true; \
                break; \
            } \
        } \
        if(foundOldElement) { \
            GENC_LIST_ELEMENT_REMOVE(*(oldElement)); \
            if(*(oldElement) != GENC_MAP_INDEX(map, hash)) \
                GENC_LIST_ELEMENT_PREPEND_TO_HEAD(GENC_MAP_INDEX(map, hash), element); \
        } else { \
            ++GENC_MAP_SIZE(map); \
            GENC_LIST_ELEMENT_PREPEND_TO_HEAD(GENC_MAP_INDEX(map, hash), element); \
	} \
        GENC_MAP_INDEX(map, hash) = element; \
    } \
}

#define GENC_MAP_SET(map, element, oldElement) { \
    size_t hash; \
    GENC_MAP_GET_HASH(map, GENC_MAP_ELEMENT_KEY(element), GENC_MAP_ELEMENT_KEY_LENGTH(element), &hash); \
    GENC_MAP_SET_RAW(map, hash, element, oldElement); \
}

#define GENC_MAP_FOR_EACH_BEGIN(map, element) { \
    for(size_t index = 0; index != GENC_MAP_CAPACITY(map); ++index) { \
	for(element = GENC_MAP_INDEX(map, index); \
            element != NULL; \
	    element = GENC_LIST_ELEMENT_NEXT(element)) {

#define GENC_MAP_FOR_EACH_END \
	} \
    } \
}

#define GENC_MAP_FREE_ELEMENTS(map) \
free(GENC_MAP_ELEMENTS(map))

#define GENC_MAP_DESTROY(map)

#endif
