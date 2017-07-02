#ifndef _GENC_HMAP_H
#define _GENC_HMAP_H

#include <stdlib.h>

#define GENC_HMAP_ELEMENT(type) \
struct                          \
{                               \
    unsigned char* key;         \
    size_t key_length;          \
    type* previous;             \
    type* next;                 \
} genc_hmap_element

#define GENC_HMAP_ELEMENT_INIT(hmap) \
(hmap)->genc_hmap_element.previous = (hmap)->genc_hmap_element.next = NULL;

#define GENC_HMAP_ELEMENT_KEY(element) \
(element)->genc_hmap_element.key

#define GENC_HMAP_ELEMENT_KEY_LENGTH(element) \
(element)->genc_hmap_element.key_length

#define GENC_HMAP_ELEMENT_PREVIOUS(element) \
(element)->genc_hmap_element.previous

#define GENC_HMAP_ELEMENT_NEXT(element) \
(element)->genc_hmap_element.next

#define GENC_HMAP(type) \
struct                  \
{                       \
    type** elements;    \
    size_t capacity;    \
    size_t size;        \
} genc_hmap

#define GENC_HMAP_INIT(hmap, _capacity)                                                     \
do                                                                                          \
{                                                                                           \
    (hmap)->genc_hmap.elements = calloc(_capacity, sizeof(*((hmap)->genc_hmap.elements)));  \
    (hmap)->genc_hmap.capacity = _capacity;                                                 \
    (hmap)->genc_hmap.size = 0;                                                             \
}                                                                                           \
while(0)

#define GENC_HMAP_INDEX(hmap, index) \
(hmap)->genc_hmap.elements[index]

#define GENC_HMAP_CAPACITY(hmap) \
(hmap)->genc_hmap.capacity

#define GENC_HMAP_SIZE(hmap) \
(hmap)->genc_hmap.size

#define GENC_HMAP_GET(hmap, _key, _key_length, element)                                         \
do                                                                                              \
{                                                                                               \
    size_t hash = 0;                                                                            \
    for(size_t i = 0; i < _key_length; ++i)                                                     \
    {                                                                                           \
        hash += _key[i];                                                                        \
        hash << 8;                                                                              \
    }                                                                                           \
    hash %= (hmap)->genc_hmap.capacity;                                                         \
    element = (hmap)->genc_hmap.elements[hash];                                                 \
    while(element != NULL && strncmp(_key, (element)->genc_hmap_element.key, _key_length) != 0) \
        element = (element)->genc_hmap_element.next;                                            \
}                                                                                               \
while(0)

#define GENC_HMAP_REMOVE(hmap, _key, _key_length, element)                                                         \
do                                                                                                                 \
{                                                                                                                  \
    size_t hash = 0;                                                                                               \
    for(size_t i = 0; i < _key_length; ++i)                                                                        \
    {                                                                                                              \
        hash += _key[i];                                                                                           \
        hash << 8;                                                                                                 \
    }                                                                                                              \
    hash %= (hmap)->genc_hmap.capacity;                                                                            \
    element = (hmap)->genc_hmap.elements[hash];                                                                    \
    while(element != NULL && strncmp(_key, (element)->genc_hmap_element.key, _key_length) != 0)                    \
        element = (element)->genc_hmap_element.next;                                                               \
    if(element != NULL)                                                                                            \
    {                                                                                                              \
        if(element == (hmap)->genc_hmap.elements[hash] && (element)->genc_hmap_element.next == NULL)               \
            (hmap)->genc_hmap.elements[hash] = NULL;                                                               \
        if((element)->genc_hmap_element.previous != NULL)                                                          \
        {                                                                                                          \
            (element)->genc_hmap_element.previous->genc_hmap_element.next = (element)->genc_hmap_element.next;     \
            (element)->genc_hmap_element.previous = NULL;                                                          \
        }                                                                                                          \
        if((element)->genc_hmap_element.next != NULL)                                                              \
            (element)->genc_hmap_element.next->genc_hmap_element.previous = (element)->genc_hmap_element.previous; \
            (element)->genc_hmap_element.next = NULL;                                                              \
        }                                                                                                          \
        --((hmap)->genc_hmap.size);                                                                                \
    }                                                                                                              \
}                                                                                                                  \
while(0)

#define GENC_HMAP_SET(hmap, element, old_element)                                                                                           \
do                                                                                                                                          \
{                                                                                                                                           \
    size_t hash = 0;                                                                                                                        \
    for(size_t i = 0; i < (element)->genc_hmap_element.key_length; ++i)                                                                     \
    {                                                                                                                                       \
        hash += (element)->genc_hmap_element.key[i];                                                                                        \
        hash << 8;                                                                                                                          \
    }                                                                                                                                       \
    hash %= (hmap)->genc_hmap.capacity;                                                                                                     \
    if((hmap)->genc_hmap.elements[hash] == NULL)                                                                                            \
        (hmap)->genc_hmap.elements[hash] = element;                                                                                         \
    else                                                                                                                                    \
    {                                                                                                                                       \
        old_element = (hmap)->genc_hmap.elements[hash];                                                                                     \
        while(old_element != NULL &&                                                                                                        \
             strncmp((element)->genc_hmap_element.key, (old_element)->genc_hmap_element.key, (element)->genc_hmap_element.key_length) != 0) \
        {                                                                                                                                   \
            old_element = (old_element)->genc_hmap_element.next;                                                                            \
        }                                                                                                                                   \
        if(old_element != NULL)                                                                                                             \
        {                                                                                                                                   \
            if((old_element)->genc_hmap_element.previous != NULL)                                                                           \
            {                                                                                                                               \
                (old_element)->genc_hmap_element.previous->genc_hmap_element.next = (old_element)->genc_hmap_element.next;                  \
                (old_element)->genc_hmap_element.previous = NULL;                                                                           \
            }                                                                                                                               \
            if((old_element)->genc_hmap_element.next != NULL)                                                                               \
            {                                                                                                                               \
                (old_element)->genc_hmap_element.next->genc_hmap_element.previous = (old_element)->genc_hmap_element.previous;              \
                (old_element)->genc_hmap_element.next = NULL;                                                                               \
            }                                                                                                                               \
        }                                                                                                                                   \
        else                                                                                                                                \
            ++((hmap)->genc_hmap.size);                                                                                                     \
        (element)->genc_hmap_element.next = (hmap)->genc_hmap.elements[hash];                                                               \
        (hmap)->genc_hmap.elements[hash]->genc_hmap_element.previous = element;                                                             \
        (hmap)->genc_hmap.elements[hash] = element;                                                                                         \
    }                                                                                                                                       \
}                                                                                                                                           \
while(0)

#define GENC_HMAP_INDEX_REMOVE(hmap, index, element)                                                   \
do                                                                                                     \
{                                                                                                      \
    element = (hmap)->genc_hmap.elements[index];                                                       \
    if(element != NULL)                                                                                \
    {                                                                                                  \
        (hmap)->genc_hmap.elements[index] = element->genc_hmap_element.next;                           \
        (element)->genc_hmap_element.next->genc_hmap_element.previous = NULL;                          \
        (element)->genc_hmap_element.next->genc_hmap_element.next = (element)->genc_hmap_element.next; \
        (element)->genc_hmap_element.previous = NULL;                                                  \
        (element)->genc_hmap_element.next = NULL;                                                      \
    }                                                                                                  \
}                                                                                                      \
while(0)

#define GENC_HMAP_FREE_ELEMENTS(hmap) \
free((hmap)->genc_hmap.elements)

#endif
