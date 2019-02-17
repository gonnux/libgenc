#ifndef _GENC_MAP_H
#define _GENC_MAP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "genc_List.h"
#include "genc_SipHash.h"

#define GENC_MAP_ELEM(type) \
struct { \
    GENC_LIST_ELEM(type); \
    struct { \
        const char* key; \
        size_t keyLength; \
    } genc_Map_elem; \
}

#define GENC_MAP_ELEM_TYPE(elem) \
__typeof__(*elem)

#define GENC_MAP_ELEM_INIT(elem) do { \
    GENC_LIST_ELEM_INIT(elem); \
    (elem)->genc_Map_elem.key = NULL; \
    (elem)->genc_Map_elem.keyLength = 0; \
} while(0)

#define GENC_MAP_ELEM_KEY(elem) \
(elem)->genc_Map_elem.key

#define GENC_MAP_ELEM_KEY_LENGTH(elem) \
(elem)->genc_Map_elem.keyLength

#define GENC_MAP(type) \
struct { \
    type** heads; \
    type** tails; \
    size_t capacity; \
    size_t size; \
    uint8_t nonce[16]; \
} genc_Map

#define GENC_MAP_HEADS(self) \
(self)->genc_Map.heads

#define GENC_MAP_HEADS_TYPE(self) \
__typeof__(**GENC_MAP_HEADS(self))

#define GENC_MAP_TAILS(self) \
(self)->genc_Map.tails

#define GENC_MAP_TAILS_TYPE(self) \
__typeof__(**GENC_MAP_TAILS(self))

#define GENC_MAP_CAPACITY(self) \
(self)->genc_Map.capacity

#define GENC_MAP_SIZE(self) \
(self)->genc_Map.size

#define GENC_MAP_HEAD(self, index) \
(self)->genc_Map.heads[index]

#define GENC_MAP_TAIL(self, index) \
(self)->genc_Map.tails[index]

#define GENC_MAP_NONCE(self) \
(self)->genc_Map.nonce

#define GENC_MAP_REALLOC(self, capacity) do { \
    GENC_MAP_HEADS_TYPE(self)* head = NULL; \
    for(size_t index = 0; index != GENC_MAP_CAPACITY(self); ++index) { \
        if(GENC_MAP_HEAD(self, index) != NULL) { \
            if(head != NULL) { \
                GENC_LIST_ELEM_PREPEND(head, GENC_MAP_TAIL(self, index)); \
            } \
            head = GENC_MAP_HEAD(self, index); \
            GENC_MAP_HEAD(self, index) = NULL; \
            GENC_MAP_TAIL(self, index) = NULL; \
        } \
    } \
    GENC_MAP_SIZE(self) = 0; \
    const size_t capacityDiff = capacity - GENC_MAP_CAPACITY(self); \
    if(GENC_MAP_HEADS(self) == NULL) \
        GENC_MAP_HEADS(self) = calloc(capacity, sizeof(*GENC_MAP_HEADS(self))); \
    else { \
        GENC_MAP_HEADS(self) = realloc(GENC_MAP_HEADS(self), capacity * sizeof(*(GENC_MAP_HEADS(self)))); \
        if(capacity > GENC_MAP_CAPACITY(self)) \
            memset(GENC_MAP_HEADS(self) + GENC_MAP_CAPACITY(self), 0, capacityDiff); \
    } \
    if(GENC_MAP_TAILS(self) == NULL) \
        GENC_MAP_TAILS(self) = calloc(capacity, sizeof(*GENC_MAP_TAILS(self))); \
    else { \
        GENC_MAP_TAILS(self) = realloc(GENC_MAP_TAILS(self), capacity * sizeof(*(GENC_MAP_TAILS(self)))); \
        if(capacity > GENC_MAP_CAPACITY(self)) \
            memset(GENC_MAP_TAILS(self) + GENC_MAP_CAPACITY(self), 0, capacityDiff); \
    } \
    GENC_MAP_CAPACITY(self) = capacity; \
    if(head == NULL) \
        break; \
    GENC_MAP_HEADS_TYPE(self)* elem = head; \
    GENC_MAP_HEADS_TYPE(self)* nextElem = GENC_LIST_ELEM_NEXT(elem); \
    GENC_MAP_HEADS_TYPE(self)* oldElem = NULL; \
    for(; elem != NULL; elem = nextElem) { \
        GENC_LIST_ELEM_REMOVE(elem); \
        GENC_MAP_SET(self, elem, &oldElem); \
        nextElem = GENC_LIST_ELEM_NEXT(elem); \
    } \
} while(0)

#define GENC_MAP_REALLOC2(self) \
do { \
    if(GENC_MAP_SIZE(self) >= GENC_MAP_CAPACITY(self) * 0.7) \
        GENC_MAP_REALLOC(self, (GENC_MAP_CAPACITY(self) + 1) * 2); \
} while(0)

#define GENC_MAP_INIT(self) { \
    FILE* urandom = fopen("/dev/urandom", "r"); \
    if(urandom != NULL) { \
        if(fread(GENC_MAP_NONCE(self), 16, sizeof(uint8_t), urandom) < 16 * sizeof(uint8_t)) { \
            unsigned int state = time(NULL); \
            for(size_t index = 0; index < sizeof(GENC_MAP_NONCE(self)); ++index) \
                GENC_MAP_NONCE(self)[index] = (uint8_t)rand_r(&state); \
        } \
        fclose(urandom); \
    } \
    GENC_MAP_SIZE(self) = 0; \
    GENC_MAP_CAPACITY(self) = 0; \
    GENC_MAP_HEADS(self) = NULL; \
    GENC_MAP_TAILS(self) = NULL; \
    GENC_MAP_REALLOC(self, 10007); \
}

#define GENC_MAP_INIT2(self, capacity) { \
    GENC_MAP_SIZE(self) = 0; \
    GENC_MAP_CAPACITY(self) = 0; \
    GENC_MAP_HEADS(self) = NULL; \
    GENC_MAP_TAILS(self) = NULL; \
    GENC_MAP_REALLOC(self, capacity); \
}

#define GENC_MAP_RAW_GET(self, hash, key, keyLength, elem) { \
    *(elem) = GENC_MAP_HEAD(self, hash); \
    while(*(elem) != NULL && strncmp(key, GENC_MAP_ELEM_KEY(*(elem)), keyLength) != 0) \
        *(elem) = GENC_LIST_ELEM_NEXT(*(elem)); \
}

#define GENC_MAP_GET(self, key, keyLength, elem) { \
    uint64_t hash; \
    GENC_SIPHASH_HASH(((const uint8_t*)key), keyLength, ((const uint8_t*)GENC_MAP_NONCE(self)), &hash); \
    GENC_MAP_RAW_GET(self, hash % GENC_MAP_CAPACITY(self), key, keyLength, elem); \
}

#define GENC_MAP_REMOVE_RAW(self, hash, key, keyLength, elem) { \
    elem = GENC_MAP_HEAD(self, hash); \
    while(elem != NULL && strncmp(key, GENC_MAP_ELEM_KEY(elem), keyLength) != 0) \
        elem = GENC_LIST_ELEM_NEXT(elem); \
    if(elem != NULL) { \
        if(elem == GENC_MAP_HEAD(self, hash)) \
            GENC_MAP_HEAD(self, hash) = GENC_LIST_ELEM_NEXT(elem); \
        if(elem == GENC_MAP_TAIL(self, hash)) \
            GENC_MAP_TAIL(self, hash) = GENC_LIST_ELEM_PREV(elem); \
        GENC_LIST_ELEM_REMOVE(elem); \
        --(GENC_MAP_SIZE(self)); \
    } \
}

#define GENC_MAP_REMOVE(self, key, keyLength, elem) { \
    size_t hash; \
    GENC_MAP_GET_HASH(self, key, keyLength, &hash); \
    GENC_MAP_REMOVE_RAW(self, hash, key, keyLength, elem); \
}

// test is needed for oldElem
#define GENC_MAP_RAW_SET(self, hash, elem, oldElem) { \
    *(oldElem) = GENC_MAP_HEAD(self, hash); \
    if(*(oldElem) == NULL) { \
        GENC_MAP_HEAD(self, hash) = elem; \
        GENC_MAP_TAIL(self, hash) = elem; \
        ++GENC_MAP_SIZE(self); \
    } else { \
        bool foundOldElem = false; \
        for( ; *(oldElem) != NULL; \
            *(oldElem) = GENC_LIST_ELEM_NEXT(*(oldElem))) { \
            if(strncmp(GENC_MAP_ELEM_KEY(elem), \
               GENC_MAP_ELEM_KEY(*(oldElem)), \
               GENC_MAP_ELEM_KEY_LENGTH(elem)) == 0) { \
                foundOldElem = true; \
                break; \
            } \
        } \
        if(foundOldElem) { \
            GENC_LIST_ELEM_REMOVE(*(oldElem)); \
            if(*(oldElem) != GENC_MAP_HEAD(self, hash)) \
                GENC_LIST_ELEM_PREPEND_TO_HEAD(GENC_MAP_HEAD(self, hash), elem); \
        } else { \
            ++GENC_MAP_SIZE(self); \
            GENC_LIST_ELEM_PREPEND_TO_HEAD(GENC_MAP_HEAD(self, hash), elem); \
        } \
        GENC_MAP_HEAD(self, hash) = elem; \
    } \
}

#define GENC_MAP_SET(self, elem, oldElem) { \
    uint64_t hash; \
    GENC_SIPHASH_HASH(((const uint8_t*)GENC_MAP_ELEM_KEY(elem)), GENC_MAP_ELEM_KEY_LENGTH(elem), ((const uint8_t*)GENC_MAP_NONCE(self)), &hash); \
    GENC_MAP_RAW_SET(self, hash % GENC_MAP_CAPACITY(self), elem, oldElem); \
}

#define GENC_MAP_FOREACH_BEGIN(self, elem) { \
    GENC_MAP_HEADS_TYPE(self)* elem; \
    GENC_MAP_HEADS_TYPE(self)* genc_Map_nextElem = NULL; \
    for(size_t genc_Map_index = 0; genc_Map_index != GENC_MAP_CAPACITY(self); ++genc_Map_index) { \
        elem = GENC_MAP_HEAD(self, genc_Map_index); \
        if(elem != NULL) \
            genc_Map_nextElem = GENC_LIST_ELEM_NEXT(elem); \
        do { \
            if(elem == NULL) break; \

#define GENC_MAP_FOREACH_END(self, elem) \
            elem = genc_Map_nextElem; \
            if(genc_Map_nextElem != NULL) \
                genc_Map_nextElem = GENC_LIST_ELEM_NEXT(genc_Map_nextElem); \
        } while(elem != NULL); \
    } \
}

#define GENC_MAP_FREE_HEADS(self) \
free(GENC_MAP_HEADS(self))

#define GENC_MAP_FREE_TAILS(self) \
free(GENC_MAP_TAILS(self))

#define GENC_MAP_FREE(self) { \
    if(GENC_MAP_HEADS(self) != NULL) { \
        free(GENC_MAP_HEADS(self)); \
        GENC_MAP_HEADS(self) = NULL; \
    } \
    if(GENC_MAP_TAILS(self) != NULL) { \
        free(GENC_MAP_TAILS(self)); \
        GENC_MAP_TAILS(self) = NULL; \
    } \
    GENC_MAP_SIZE(self) = 0; \
    GENC_MAP_CAPACITY(self) = 0; \
}

#endif
