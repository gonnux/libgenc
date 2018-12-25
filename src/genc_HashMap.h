
#ifndef _GENC_HASH_MAP_H
#define _GENC_HASH_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "genc_List.h"

#define GENC_HASH_MAP_ELEMENT(type) \
GENC_LIST_ELEMENT(type); \
struct \
{ \
    unsigned char* key; \
    size_t keyLength; \
} genc_HashMap_element

#define GENC_HASH_MAP_ELEMENT_INIT(element) do { \
    GENC_LIST_ELEMENT_INIT(element); \
    (element)->genc_HashMap_element.key = NULL; \
    (element)->genc_HashMap_element.keyLength = 0; \
} while(0)

#define GENC_HASH_MAP_ELEMENT_KEY(element) \
(element)->genc_HashMap_element.key

#define GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) \
(element)->genc_HashMap_element.keyLength

#define GENC_HASH_MAP_CHAIN(type) \
struct \
{ \
    GENC_LIST(type); \
} genc_HashMap_chain

#define GENC_HASH_MAP(type) \
struct { \
    type** elements; \
    size_t capacity; \
    size_t size; \
} genc_HashMap

#define GENC_HASH_MAP_INIT(hmap, _capacity) \
do { \
    (hmap)->genc_HashMap.elements = calloc(_capacity, sizeof(*((hmap)->genc_HashMap.elements))); \
    (hmap)->genc_HashMap.capacity = _capacity; \
    (hmap)->genc_HashMap.size = 0; \
} while(0)

#define GENC_HASH_MAP_INDEX(hmap, index) \
(hmap)->genc_HashMap.elements[index]

#define GENC_HASH_MAP_CAPACITY(hmap) \
(hmap)->genc_HashMap.capacity

#define GENC_HASH_MAP_SIZE(hmap) \
(hmap)->genc_HashMap.size

#define GENC_HASH_MAP_GET_HASH(hmap, _key, _keyLength, hash)  do { \
    *(hash) = 0; \
    for(size_t i = 0; i != _keyLength; ++i) { \
        *(hash) += _key[i]; \
        *(hash) << 8; \
    } \
    *(hash) %= (hmap)->genc_HashMap.capacity; \
} while(0)

#define GENC_HASH_MAP_GET_RAW(hmap, hash, _key, _keyLength, element) do { \
    *(element) = (hmap)->genc_HashMap.elements[hash]; \
    while(*(element) != NULL && strncmp(_key, GENC_HASH_MAP_ELEMENT_KEY(*(element)), _keyLength) != 0) \
        *(element) = GENC_LIST_ELEMENT_NEXT(*(element)); \
} while(0)

#define GENC_HASH_MAP_GET(hmap, _key, _keyLength, element) \
do { \
    size_t hash; \
    GENC_HASH_MAP_GET_HASH(hmap, _key, _keyLength, &hash); \
    GENC_HASH_MAP_GET_RAW(hmap, hash, _key, _keyLength, element); \
} while(0)

#define GENC_HASH_MAP_REMOVE_RAW(hmap, hash, _key, _keyLength, element) do { \
    element = (hmap)->genc_HashMap.elements[hash]; \
    while(element != NULL && strncmp(_key, (element)->genc_HashMap_element.key, _keyLength) != 0) \
        element = GENC_LIST_ELEMENT_NEXT(element); \
    if(element != NULL) { \
        if(element == (hmap)->genc_HashMap.elements[hash] && GENC_LIST_ELEMENT_NEXT(element) == NULL) \
            (hmap)->genc_HashMap.elements[hash] = NULL; \
        GENC_LIST_ELMEENT_REMOVE(element); \
        --((hmap)->genc_HashMap.size); \
    } \
} while(0)

#define GENC_HASH_MAP_REMOVE(hmap, _key, _keyLength, element) do { \
    size_t hash; \
    GENC_HASH_MAP_GET_HASH(hmap, _key, _keyLength, &hash); \
    GENC_HASH_MAP_REMOVE_RAW(hmap, hash, _key, _keyLength, element); \
} while(0)

// test is needed for oldElement
#define GENC_HASH_MAP_SET_RAW(hmap, hash, element, oldElement) do { \
    if((hmap)->genc_HashMap.elements[hash] == NULL) \
        (hmap)->genc_HashMap.elements[hash] = element; \
    else { \
        bool foundOldElement = false; \
        *(oldElement) = (hmap)->genc_HashMap.elements[hash]; \
        for(*(oldElement) = (hmap)->genc_HashMap.elements[hash]; \
            *(oldElement) != NULL; \
            *(oldElement) = GENC_LIST_ELEMENT_NEXT(*(oldElement))) { \
            if(strncmp((element)->genc_HashMap_element.key, \
               (*(oldElement))->genc_HashMap_element.key, \
               (element)->genc_HashMap_element.keyLength) == 0) { \
                foundOldElement = true; \
                break; \
            } \
        } \
        if(foundOldElement) { \
            GENC_LIST_ELEMENT_REMOVE(*(oldElement)); \
	} else \
            ++((hmap)->genc_HashMap.size); \
        GENC_LIST_ELEMENT_PREPEND_TO_HEAD((hmap)->genc_HashMap.elements[hash], element); \
        (hmap)->genc_HashMap.elements[hash] = element; \
    } \
} while(0)

#define GENC_HASH_MAP_SET(hmap, element, oldElement) \
do { \
    size_t hash; \
    GENC_HASH_MAP_GET_HASH(hmap, GENC_HASH_MAP_ELEMENT_KEY(element), GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element), &hash); \
    GENC_HASH_MAP_SET_RAW(hmap, hash, element, oldElement); \
} while(0)

#define GENC_HASH_MAP_FREE_ELEMENTS(hmap) \
free((hmap)->genc_HashMap.elements)

#endif
