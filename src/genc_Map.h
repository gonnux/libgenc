
#ifndef _GENC_MAP_H
#define _GENC_MAP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "genc_List.h"
#include "genc_SipHash.h"

#define GENC_MAP_ELEMENT(type) \
struct { \
    GENC_LIST_ELEMENT(type); \
    struct { \
        const char* key; \
        size_t keyLength; \
    } genc_Map_elem; \
}

#define GENC_MAP_ELEMENT_INIT(elem) do { \
    GENC_LIST_ELEMENT_INIT(elem); \
    (elem)->genc_Map_elem.key = NULL; \
    (elem)->genc_Map_elem.keyLength = 0; \
} while(0)

#define GENC_MAP_ELEMENT_KEY(elem) \
(elem)->genc_Map_elem.key

#define GENC_MAP_ELEMENT_KEY_LENGTH(elem) \
(elem)->genc_Map_elem.keyLength

#define GENC_MAP(type) \
struct { \
    type** heads; \
    type** tails; \
    size_t capacity; \
    size_t size; \
    uint8_t nonce[16]; \
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

#define GENC_MAP_NONCE(map) \
(map)->genc_Map.nonce

#define GENC_MAP_REALLOC(map, capacity) do { \
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
    GENC_MAP_SIZE(map) = 0; \
    GENC_MAP_CAPACITY(map) = 0; \
    GENC_MAP_HEADS(map) = NULL; \
    GENC_MAP_TAILS(map) = NULL; \
    GENC_MAP_REALLOC(map, 10007); \
    FILE* urandom = fopen("/dev/urandom", "r"); \
    fread(GENC_MAP_NONCE(map), 16, sizeof(uint8_t), urandom); \
    fclose(urandom); \
}

#define GENC_MAP_INIT2(map, capacity) { \
    GENC_MAP_SIZE(map) = 0; \
    GENC_MAP_CAPACITY(map) = 0; \
    GENC_MAP_REALLOC(map, capacity); \
}

#define GENC_MAP_GET_RAW(map, hash, key, keyLength, elem) { \
    *(elem) = GENC_MAP_HEAD(map, hash); \
    while(*(elem) != NULL && strncmp(key, GENC_MAP_ELEMENT_KEY(*(elem)), keyLength) != 0) \
        *(elem) = GENC_LIST_ELEMENT_NEXT(*(elem)); \
}

#define GENC_MAP_GET(map, key, keyLength, elem) { \
    uint64_t hash; \
    GENC_SIPHASH_HASH(key, keyLength, GENC_MAP_NONCE(map), &hash); \
    GENC_MAP_GET_RAW(map, hash % GENC_MAP_CAPACITY(map), key, keyLength, elem); \
}

#define GENC_MAP_REMOVE_RAW(map, hash, key, keyLength, elem) { \
    elem = GENC_MAP_HEAD(map, hash); \
    while(elem != NULL && strncmp(key, GENC_MAP_ELEMENT_KEY(elem), keyLength) != 0) \
        elem = GENC_LIST_ELEMENT_NEXT(elem); \
    if(elem != NULL) { \
        if(elem == GENC_MAP_HEAD(map, hash)) \
            GENC_MAP_HEAD(map, hash) = GENC_LIST_ELEMENT_NEXT(elem); \
        if(elem == GENC_MAP_TAIL(map, hash)) \
            GENC_MAP_TAIL(map, hash) = GENC_LIST_ELEMENT_PREVIOUS(elem); \
        GENC_LIST_ELEMENT_REMOVE(elem); \
        --(GENC_MAP_SIZE(map)); \
    } \
}

#define GENC_MAP_REMOVE(map, key, keyLength, elem) { \
    size_t hash; \
    GENC_MAP_GET_HASH(map, key, keyLength, &hash); \
    GENC_MAP_REMOVE_RAW(map, hash, key, keyLength, elem); \
}

// test is needed for oldElement
#define GENC_MAP_SET_RAW(map, hash, elem, oldElement) { \
    *(oldElement) = GENC_MAP_HEAD(map, hash); \
    if(*(oldElement) == NULL) { \
        GENC_MAP_HEAD(map, hash) = elem; \
        GENC_MAP_TAIL(map, hash) = elem; \
        ++GENC_MAP_SIZE(map); \
    } else { \
        bool foundOldElement = false; \
        for( ; *(oldElement) != NULL; \
            *(oldElement) = GENC_LIST_ELEMENT_NEXT(*(oldElement))) { \
            if(strncmp(GENC_MAP_ELEMENT_KEY(elem), \
               GENC_MAP_ELEMENT_KEY(*(oldElement)), \
               GENC_MAP_ELEMENT_KEY_LENGTH(elem)) == 0) { \
                foundOldElement = true; \
                break; \
            } \
        } \
        if(foundOldElement) { \
            GENC_LIST_ELEMENT_REMOVE(*(oldElement)); \
            if(*(oldElement) != GENC_MAP_HEAD(map, hash)) \
                GENC_LIST_ELEMENT_PREPEND_TO_HEAD(GENC_MAP_HEAD(map, hash), elem); \
        } else { \
            ++GENC_MAP_SIZE(map); \
            GENC_LIST_ELEMENT_PREPEND_TO_HEAD(GENC_MAP_HEAD(map, hash), elem); \
        } \
        GENC_MAP_HEAD(map, hash) = elem; \
    } \
}

#define GENC_MAP_SET(map, elem, oldElement) { \
    uint64_t hash; \
    GENC_SIPHASH_HASH(GENC_MAP_ELEMENT_KEY(elem), GENC_MAP_ELEMENT_KEY_LENGTH(elem), GENC_MAP_NONCE(map), &hash); \
    GENC_MAP_SET_RAW(map, hash % GENC_MAP_CAPACITY(map), elem, oldElement); \
}

#define GENC_MAP_FOR_EACH_BEGIN(map, elem) { \
    for(size_t index = 0; index != GENC_MAP_CAPACITY(map); ++index) { \
        for(*(elem) = GENC_MAP_HEAD(map, index); \
            *(elem) != NULL; \
            *(elem) = GENC_LIST_ELEMENT_NEXT(*(elem))) {

#define GENC_MAP_FOR_EACH_END \
        } \
    } \
}

#define GENC_MAP_FREE_HEADS(map) \

#define GENC_MAP_FREE_TAILS(map) \
free(GENC_MAP_TAILS(map))

#define GENC_MAP_FREE(map) { \
    if(GENC_MAP_HEADS(map) != NULL) { \
        free(GENC_MAP_HEADS(map)); \
        GENC_MAP_HEADS(map) = NULL; \
    } \
    if(GENC_MAP_HEADS(map) != NULL) { \
        free(GENC_MAP_TAILS(map)); \
        GENC_MAP_TAILS(map) = NULL; \
    } \
}

#endif
