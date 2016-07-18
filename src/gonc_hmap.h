#ifndef _GONC_HMAP_H
#define _GONC_HMAP_H

#include <stdlib.h>

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
    (hmap)->gonc_hmap.elements = malloc(_capacity * sizeof(*((hmap)->gonc_hmap.elements))); \
    (hmap)->gonc_hmap.capacity = _capacity;                                                 \
    (hmap)->gonc_hmap.size = 0;                                                             \
}                                                                                           \
while(0)

#define GONC_HMAP_ELEMENT(type, value_type) \
struct                                      \
{                                           \
    unsigned char* key;                     \
    size_t key_length;                      \
    value_type* value;                      \
    type* previous;                         \
    type* next;                             \
} gonc_hmap_element

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

#define GONC_HMAP_SET(hmap, element, old_element)                                                           \
do                                                                                                          \
{                                                                                                           \
    size_t hash = 0;                                                                                        \
    for(size_t i = 0; i < key_length; ++i)                                                                  \
    {                                                                                                       \
        hash += key[i];                                                                                     \
        hash << 8;                                                                                          \
    }                                                                                                       \
    hash %= (hmap)->gonc_hmap.capacity;                                                                     \
    if((hmap)->gonc_hmap.elements[hash] == NULL)                                                            \
        (hmap)->gonc_hmap.elements[hash] = element;                                                         \
    else                                                                                                    \
    {                                                                                                       \
        old_element = (hmap)->gonc_hmap.elements[hash];                                                     \
        while(old_element != NULL && strncmp(_key, (old_element)->gonc_hmap_element.key, _key_length) != 0) \
            old_element = (old_element)->gonc_hmap_element.next;                                            \
        if(old_element != NULL)                                                                             \
        {                                                                                                   \
            if((old_element)->previous != NULL)                                                             \
                (old_element)->previous->next = (old_element)->next;                                        \
            if((old_element)->next != NULL)                                                                 \
                (old_element)->next->previous = (old_element)->previous;                                    \
            (old_element)->previous = (old_element)->next = NULL;                                           \
        }                                                                                                   \
        (element)->next = (hmap)->gonc_hmap.elements[hash];                                                 \
        (hmap)->gonc_hmap.elements[hash]->previous = element;                                               \
        (hmap)->gonc_hmap.elements[hash] = element;                                                         \
    }                                                                                                       \
}                                                                                                           \
while(0)

#endif
