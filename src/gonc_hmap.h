#ifndef _GONC_HMAP_H
#define _GONC_HMAP_H

#include <stdlib.h>

#define GONC_HMAP_ELEMENT(type) \
struct                          \
{                               \
    unsigned char* key;         \
    size_t key_length;          \
    type* previous;             \
    type* next;                 \
} gonc_hmap_element

#define GONC_HMAP_ELEMENT_INIT(hmap) \
(hmap)->gonc_hmap_element.previous = (hmap)->gonc_hmap_element.next = NULL;

#define GONC_HMAP_ELEMENT_KEY(element) \
(element)->gonc_hmap_element.key

#define GONC_HMAP_ELEMENT_KEY_LENGTH(element) \
(element)->gonc_hmap_element.key_length

#define GONC_HMAP_ELEMENT_PREVIOUS(element) \
(element)->gonc_hmap_element.previous

#define GONC_HMAP_ELEMENT_NEXT(element) \
(element)->gonc_hmap_element.next

#define GONC_HMAP(type) \
struct                  \
{                       \
    type** elements;    \
    size_t capacity;    \
    size_t size;        \
} gonc_hmap

#define GONC_HMAP_INIT(hmap, _capacity)                                                     \
do                                                                                          \
{                                                                                           \
    (hmap)->gonc_hmap.elements = calloc(_capacity, sizeof(*((hmap)->gonc_hmap.elements)));  \
    (hmap)->gonc_hmap.capacity = _capacity;                                                 \
    (hmap)->gonc_hmap.size = 0;                                                             \
}                                                                                           \
while(0)

#define GONC_HMAP_INDEX(hmap, index) \
(hmap)->gonc_hmap.elements[index]

#define GONC_HMAP_CAPACITY(hmap) \
(hmap)->gonc_hmap.capacity

#define GONC_HMAP_SIZE(hmap) \
(hmap)->gonc_hmap.size

#define GONC_HMAP_GET(hmap, _key, _key_length, element)                                         \
do                                                                                              \
{                                                                                               \
    size_t hash = 0;                                                                            \
    for(size_t i = 0; i < _key_length; ++i)                                                     \
    {                                                                                           \
        hash += _key[i];                                                                        \
        hash << 8;                                                                              \
    }                                                                                           \
    hash %= (hmap)->gonc_hmap.capacity;                                                         \
    element = (hmap)->gonc_hmap.elements[hash];                                                 \
    while(element != NULL && strncmp(_key, (element)->gonc_hmap_element.key, _key_length) != 0) \
        element = (element)->gonc_hmap_element.next;                                            \
}                                                                                               \
while(0)

#define GONC_HMAP_REMOVE(hmap, _key, _key_length, element)                                                         \
do                                                                                                                 \
{                                                                                                                  \
    size_t hash = 0;                                                                                               \
    for(size_t i = 0; i < _key_length; ++i)                                                                        \
    {                                                                                                              \
        hash += _key[i];                                                                                           \
        hash << 8;                                                                                                 \
    }                                                                                                              \
    hash %= (hmap)->gonc_hmap.capacity;                                                                            \
    element = (hmap)->gonc_hmap.elements[hash];                                                                    \
    while(element != NULL && strncmp(_key, (element)->gonc_hmap_element.key, _key_length) != 0)                    \
        element = (element)->gonc_hmap_element.next;                                                               \
    if(element != NULL)                                                                                            \
    {                                                                                                              \
        if(element == (hmap)->gonc_hmap.elements[hash] && (element)->gonc_hmap_element.next == NULL)               \
            (hmap)->gonc_hmap.elements[hash] = NULL;                                                               \
        if((element)->gonc_hmap_element.previous != NULL)                                                          \
        {                                                                                                          \
            (element)->gonc_hmap_element.previous->gonc_hmap_element.next = (element)->gonc_hmap_element.next;     \
            (element)->gonc_hmap_element.previous = NULL;                                                          \
        }                                                                                                          \
        if((element)->gonc_hmap_element.next != NULL)                                                              \
            (element)->gonc_hmap_element.next->gonc_hmap_element.previous = (element)->gonc_hmap_element.previous; \
            (element)->gonc_hmap_element.next = NULL;                                                              \
        }                                                                                                          \
        --((hmap)->gonc_hmap.size);                                                                                \
    }                                                                                                              \
}                                                                                                                  \
while(0)

#define GONC_HMAP_SET(hmap, element, old_element)                                                                                           \
do                                                                                                                                          \
{                                                                                                                                           \
    size_t hash = 0;                                                                                                                        \
    for(size_t i = 0; i < (element)->gonc_hmap_element.key_length; ++i)                                                                     \
    {                                                                                                                                       \
        hash += (element)->gonc_hmap_element.key[i];                                                                                        \
        hash << 8;                                                                                                                          \
    }                                                                                                                                       \
    hash %= (hmap)->gonc_hmap.capacity;                                                                                                     \
    if((hmap)->gonc_hmap.elements[hash] == NULL)                                                                                            \
        (hmap)->gonc_hmap.elements[hash] = element;                                                                                         \
    else                                                                                                                                    \
    {                                                                                                                                       \
        old_element = (hmap)->gonc_hmap.elements[hash];                                                                                     \
        while(old_element != NULL &&                                                                                                        \
             strncmp((element)->gonc_hmap_element.key, (old_element)->gonc_hmap_element.key, (element)->gonc_hmap_element.key_length) != 0) \
        {                                                                                                                                   \
            old_element = (old_element)->gonc_hmap_element.next;                                                                            \
        }                                                                                                                                   \
        if(old_element != NULL)                                                                                                             \
        {                                                                                                                                   \
            if((old_element)->gonc_hmap_element.previous != NULL)                                                                           \
            {                                                                                                                               \
                (old_element)->gonc_hmap_element.previous->gonc_hmap_element.next = (old_element)->gonc_hmap_element.next;                  \
                (old_element)->gonc_hmap_element.previous = NULL;                                                                           \
            }                                                                                                                               \
            if((old_element)->gonc_hmap_element.next != NULL)                                                                               \
            {                                                                                                                               \
                (old_element)->gonc_hmap_element.next->gonc_hmap_element.previous = (old_element)->gonc_hmap_element.previous;              \
                (old_element)->gonc_hmap_element.next = NULL;                                                                               \
            }                                                                                                                               \
        }                                                                                                                                   \
        else                                                                                                                                \
            ++((hmap)->gonc_hmap.size);                                                                                                     \
        (element)->gonc_hmap_element.next = (hmap)->gonc_hmap.elements[hash];                                                               \
        (hmap)->gonc_hmap.elements[hash]->gonc_hmap_element.previous = element;                                                             \
        (hmap)->gonc_hmap.elements[hash] = element;                                                                                         \
    }                                                                                                                                       \
}                                                                                                                                           \
while(0)

#define GONC_HMAP_INDEX_REMOVE(hmap, index, element)                                                   \
do                                                                                                     \
{                                                                                                      \
    element = (hmap)->gonc_hmap.elements[index];                                                       \
    if(element != NULL)                                                                                \
    {                                                                                                  \
        (hmap)->gonc_hmap.elements[index] = element->gonc_hmap_element.next;                           \
        (element)->gonc_hmap_element.next->gonc_hmap_element.previous = NULL;                          \
        (element)->gonc_hmap_element.next->gonc_hmap_element.next = (element)->gonc_hmap_element.next; \
        (element)->gonc_hmap_element.previous = NULL;                                                  \
        (element)->gonc_hmap_element.next = NULL;                                                      \
    }                                                                                                  \
}                                                                                                      \
while(0)

#define GONC_HMAP_FREE_ELEMENTS(hmap) \
free((hmap)->gonc_hmap.elements)

#endif
