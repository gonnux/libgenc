
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
    type** heads; \
    type** tails; \
    size_t capacity; \
    size_t size; \
} genc_Map

#define GENC_MAP_HEADS(map) \
(map)->genc_Map.heads

#define GENC_MAP_TAILS(map) \
(map)->genc_Map.tails

#define GENC_MAP_CAPACITY(map) \
(map)->genc_Map.capacity

#define GENC_MAP_SIZE(map) \
(map)->genc_Map.size

#define GENC_MAP_HEAD(map, index) \
(map)->genc_Map.heads[index]

#define GENC_MAP_TAIL(map, index) \
(map)->genc_Map.tails[index]

#define GENC_MAP_REALLOC(map, capacity) do { \
    if(GENC_MAP_SIZE(map) >= capacity) \
        break; \
    typeof(**GENC_MAP_HEADS(map))* head = NULL; \
    for(size_t index = 0; index != GENC_MAP_CAPACITY(map); ++index) { \
        if(GENC_MAP_HEAD(map, index) != NULL) { \
            if(head != NULL) { \
                GENC_LIST_ELEMENT_PREPEND(head, GENC_MAP_TAIL(map, index)); \
            } \
            head = GENC_MAP_HEAD(map, index); \
            GENC_MAP_HEAD(map, index) = NULL; \
            GENC_MAP_TAIL(map, index) = NULL; \
        } \
    } \
    GENC_MAP_SIZE(map) = 0; \
    const size_t capacityDiff = capacity - GENC_MAP_CAPACITY(map); \
    if(GENC_MAP_HEADS(map) == NULL) \
        GENC_MAP_HEADS(map) = calloc(capacity, sizeof(*GENC_MAP_HEADS(map))); \
    else { \
        GENC_MAP_HEADS(map) = realloc(GENC_MAP_HEADS(map), capacity * sizeof(*(GENC_MAP_HEADS(map)))); \
        if(capacity > GENC_MAP_CAPACITY(map)) \
            memset(GENC_MAP_HEADS(map) + GENC_MAP_CAPACITY(map), 0, capacityDiff); \
    } \
    if(GENC_MAP_TAILS(map) == NULL) \
        GENC_MAP_TAILS(map) = calloc(capacity, sizeof(*GENC_MAP_TAILS(map))); \
    else { \
        GENC_MAP_TAILS(map) = realloc(GENC_MAP_TAILS(map), capacity * sizeof(*(GENC_MAP_TAILS(map)))); \
        if(capacity > GENC_MAP_CAPACITY(map)) \
            memset(GENC_MAP_TAILS(map) + GENC_MAP_CAPACITY(map), 0, capacityDiff); \
    } \
    GENC_MAP_CAPACITY(map) = capacity; \
    if(head == NULL) \
        break; \
    typeof(**GENC_MAP_HEADS(map))* elem = head; \
    typeof(**GENC_MAP_HEADS(map))* nextElem = GENC_LIST_ELEMENT_NEXT(elem); \
    typeof(**GENC_MAP_HEADS(map))* oldElem = NULL; \
    for(; elem != NULL; elem = nextElem) { \
        GENC_LIST_ELEMENT_REMOVE(elem); \
        GENC_MAP_SET(map, elem, &oldElem); \
        nextElem = GENC_LIST_ELEMENT_NEXT(elem); \
    } \
} while(0)

#define GENC_MAP_REALLOC2(map) \
do { \
    if(GENC_MAP_SIZE(map) >= GENC_MAP_CAPACITY(map) * 0.7) \
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
    *(element) = GENC_MAP_HEAD(map, hash); \
    while(*(element) != NULL && strncmp(key, GENC_MAP_ELEMENT_KEY(*(element)), keyLength) != 0) \
        *(element) = GENC_LIST_ELEMENT_NEXT(*(element)); \
}

#define GENC_MAP_GET(map, key, keyLength, element) { \
    size_t hash; \
    GENC_MAP_GET_HASH(map, key, keyLength, &hash); \
    GENC_MAP_GET_RAW(map, hash, key, keyLength, element); \
}

#define GENC_MAP_REMOVE_RAW(map, hash, key, keyLength, element) { \
    element = GENC_MAP_HEAD(map, hash); \
    while(element != NULL && strncmp(key, GENC_MAP_ELEMENT_KEY(element), keyLength) != 0) \
        element = GENC_LIST_ELEMENT_NEXT(element); \
    if(element != NULL) { \
        if(element == GENC_MAP_HEAD(map, hash)) \
            GENC_MAP_HEAD(map, hash) = GENC_LIST_ELEMENT_NEXT(element); \
        if(element == GENC_MAP_TAIL(map, hash)) \
            GENC_MAP_TAIL(map, hash) = GENC_LIST_ELEMENT_PREVIOUS(element); \
        GENC_LIST_ELEMENT_REMOVE(element); \
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
    *(oldElement) = GENC_MAP_HEAD(map, hash); \
    if(*(oldElement) == NULL) { \
        GENC_MAP_HEAD(map, hash) = element; \
        GENC_MAP_TAIL(map, hash) = element; \
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
            if(*(oldElement) != GENC_MAP_HEAD(map, hash)) \
                GENC_LIST_ELEMENT_PREPEND_TO_HEAD(GENC_MAP_HEAD(map, hash), element); \
        } else { \
            ++GENC_MAP_SIZE(map); \
            GENC_LIST_ELEMENT_PREPEND_TO_HEAD(GENC_MAP_HEAD(map, hash), element); \
        } \
        GENC_MAP_HEAD(map, hash) = element; \
    } \
}

#define GENC_MAP_SET(map, element, oldElement) { \
    size_t hash; \
    GENC_MAP_GET_HASH(map, GENC_MAP_ELEMENT_KEY(element), GENC_MAP_ELEMENT_KEY_LENGTH(element), &hash); \
    GENC_MAP_SET_RAW(map, hash, element, oldElement); \
}

#define GENC_MAP_FOR_EACH_BEGIN(map, element) { \
    for(size_t index = 0; index != GENC_MAP_CAPACITY(map); ++index) { \
        for(*(element) = GENC_MAP_HEAD(map, index); \
            *(element) != NULL; \
            *(element) = GENC_LIST_ELEMENT_NEXT(*(element))) {

#define GENC_MAP_FOR_EACH_END \
        } \
    } \
}

#define GENC_MAP_FREE_HEADS(map) \
free(GENC_MAP_HEADS(map))

#define GENC_MAP_DESTROY(map)

#endif
