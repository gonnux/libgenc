#ifndef _GENC_HASH_MAP_H
#define _GENC_HASH_MAP_H

#include <stdlib.h>

#define GENC_HASH_MAP_ELEMENT(type) \
struct                          \
{                               \
    unsigned char* key;         \
    size_t key_length;          \
    type* previous;             \
    type* next;                 \
} genc_HashMap_element

#define GENC_HASH_MAP_ELEMENT_INIT(hmap) \
(hmap)->genc_HashMap_element.previous = (hmap)->genc_HashMap_element.next = NULL;

#define GENC_HASH_MAP_ELEMENT_KEY(element) \
(element)->genc_HashMap_element.key

#define GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) \
(element)->genc_HashMap_element.key_length

#define GENC_HASH_MAP_ELEMENT_PREVIOUS(element) \
(element)->genc_HashMap_element.previous

#define GENC_HASH_MAP_ELEMENT_NEXT(element) \
(element)->genc_HashMap_element.next

#define GENC_HASH_MAP(type) \
struct                  \
{                       \
    type** elements;    \
    size_t capacity;    \
    size_t size;        \
} genc_HashMap

#define GENC_HASH_MAP_INIT(hmap, _capacity)                                                     \
do                                                                                          \
{                                                                                           \
    (hmap)->genc_HashMap.elements = calloc(_capacity, sizeof(*((hmap)->genc_HashMap.elements)));  \
    (hmap)->genc_HashMap.capacity = _capacity;                                                 \
    (hmap)->genc_HashMap.size = 0;                                                             \
}                                                                                           \
while(0)

#define GENC_HASH_MAP_INDEX(hmap, index) \
(hmap)->genc_HashMap.elements[index]

#define GENC_HASH_MAP_CAPACITY(hmap) \
(hmap)->genc_HashMap.capacity

#define GENC_HASH_MAP_SIZE(hmap) \
(hmap)->genc_HashMap.size

#define GENC_HASH_MAP_GET(hmap, _key, _key_length, element)                                         \
do                                                                                              \
{                                                                                               \
    size_t hash = 0;                                                                            \
    for(size_t i = 0; i < _key_length; ++i)                                                     \
    {                                                                                           \
        hash += _key[i];                                                                        \
        hash << 8;                                                                              \
    }                                                                                           \
    hash %= (hmap)->genc_HashMap.capacity;                                                         \
    element = (hmap)->genc_HashMap.elements[hash];                                                 \
    while(element != NULL && strncmp(_key, (element)->genc_HashMap_element.key, _key_length) != 0) \
        element = (element)->genc_HashMap_element.next;                                            \
}                                                                                               \
while(0)

#define GENC_HASH_MAP_REMOVE(hmap, _key, _key_length, element)                                                         \
do                                                                                                                 \
{                                                                                                                  \
    size_t hash = 0;                                                                                               \
    for(size_t i = 0; i < _key_length; ++i)                                                                        \
    {                                                                                                              \
        hash += _key[i];                                                                                           \
        hash << 8;                                                                                                 \
    }                                                                                                              \
    hash %= (hmap)->genc_HashMap.capacity;                                                                            \
    element = (hmap)->genc_HashMap.elements[hash];                                                                    \
    while(element != NULL && strncmp(_key, (element)->genc_HashMap_element.key, _key_length) != 0)                    \
        element = (element)->genc_HashMap_element.next;                                                               \
    if(element != NULL)                                                                                            \
    {                                                                                                              \
        if(element == (hmap)->genc_HashMap.elements[hash] && (element)->genc_HashMap_element.next == NULL)               \
            (hmap)->genc_HashMap.elements[hash] = NULL;                                                               \
        if((element)->genc_HashMap_element.previous != NULL)                                                          \
        {                                                                                                          \
            (element)->genc_HashMap_element.previous->genc_HashMap_element.next = (element)->genc_HashMap_element.next;     \
            (element)->genc_HashMap_element.previous = NULL;                                                          \
        }                                                                                                          \
        if((element)->genc_HashMap_element.next != NULL)                                                              \
            (element)->genc_HashMap_element.next->genc_HashMap_element.previous = (element)->genc_HashMap_element.previous; \
            (element)->genc_HashMap_element.next = NULL;                                                              \
        }                                                                                                          \
        --((hmap)->genc_HashMap.size);                                                                                \
    }                                                                                                              \
}                                                                                                                  \
while(0)

#define GENC_HASH_MAP_SET(hmap, element, old_element)                                                                                           \
do                                                                                                                                          \
{                                                                                                                                           \
    size_t hash = 0;                                                                                                                        \
    for(size_t i = 0; i < (element)->genc_HashMap_element.key_length; ++i)                                                                     \
    {                                                                                                                                       \
        hash += (element)->genc_HashMap_element.key[i];                                                                                        \
        hash << 8;                                                                                                                          \
    }                                                                                                                                       \
    hash %= (hmap)->genc_HashMap.capacity;                                                                                                     \
    if((hmap)->genc_HashMap.elements[hash] == NULL)                                                                                            \
        (hmap)->genc_HashMap.elements[hash] = element;                                                                                         \
    else                                                                                                                                    \
    {                                                                                                                                       \
        old_element = (hmap)->genc_HashMap.elements[hash];                                                                                     \
        while(old_element != NULL &&                                                                                                        \
             strncmp((element)->genc_HashMap_element.key, (old_element)->genc_HashMap_element.key, (element)->genc_HashMap_element.key_length) != 0) \
        {                                                                                                                                   \
            old_element = (old_element)->genc_HashMap_element.next;                                                                            \
        }                                                                                                                                   \
        if(old_element != NULL)                                                                                                             \
        {                                                                                                                                   \
            if((old_element)->genc_HashMap_element.previous != NULL)                                                                           \
            {                                                                                                                               \
                (old_element)->genc_HashMap_element.previous->genc_HashMap_element.next = (old_element)->genc_HashMap_element.next;                  \
                (old_element)->genc_HashMap_element.previous = NULL;                                                                           \
            }                                                                                                                               \
            if((old_element)->genc_HashMap_element.next != NULL)                                                                               \
            {                                                                                                                               \
                (old_element)->genc_HashMap_element.next->genc_HashMap_element.previous = (old_element)->genc_HashMap_element.previous;              \
                (old_element)->genc_HashMap_element.next = NULL;                                                                               \
            }                                                                                                                               \
        }                                                                                                                                   \
        else                                                                                                                                \
            ++((hmap)->genc_HashMap.size);                                                                                                     \
        (element)->genc_HashMap_element.next = (hmap)->genc_HashMap.elements[hash];                                                               \
        (hmap)->genc_HashMap.elements[hash]->genc_HashMap_element.previous = element;                                                             \
        (hmap)->genc_HashMap.elements[hash] = element;                                                                                         \
    }                                                                                                                                       \
}                                                                                                                                           \
while(0)

#define GENC_HASH_MAP_INDEX_REMOVE(hmap, index, element)                                                   \
do                                                                                                     \
{                                                                                                      \
    element = (hmap)->genc_HashMap.elements[index];                                                       \
    if(element != NULL)                                                                                \
    {                                                                                                  \
        (hmap)->genc_HashMap.elements[index] = element->genc_HashMap_element.next;                           \
        (element)->genc_HashMap_element.next->genc_HashMap_element.previous = NULL;                          \
        (element)->genc_HashMap_element.next->genc_HashMap_element.next = (element)->genc_HashMap_element.next; \
        (element)->genc_HashMap_element.previous = NULL;                                                  \
        (element)->genc_HashMap_element.next = NULL;                                                      \
    }                                                                                                  \
}                                                                                                      \
while(0)

#define GENC_HASH_MAP_FREE_ELEMENTS(hmap) \
free((hmap)->genc_HashMap.elements)

#endif
