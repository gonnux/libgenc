#ifndef _GON_C_HMAP_H
#define _GON_C_HMAP_H

#include <stdlib.h>

#define GON_C_HMAP_ELEMENT(type) \
struct                          \
{                               \
    unsigned char* key;         \
    size_t key_length;          \
    type* previous;             \
    type* next;                 \
} gon_c_hmap_element

#define GON_C_HMAP_ELEMENT_INIT(hmap) \
(hmap)->gon_c_hmap_element.previous = (hmap)->gon_c_hmap_element.next = NULL;

#define GON_C_HMAP_ELEMENT_KEY(element) \
(element)->gon_c_hmap_element.key

#define GON_C_HMAP_ELEMENT_KEY_LENGTH(element) \
(element)->gon_c_hmap_element.key_length

#define GON_C_HMAP_ELEMENT_PREVIOUS(element) \
(element)->gon_c_hmap_element.previous

#define GON_C_HMAP_ELEMENT_NEXT(element) \
(element)->gon_c_hmap_element.next

#define GON_C_HMAP(type) \
struct                  \
{                       \
    type** elements;    \
    size_t capacity;    \
    size_t size;        \
} gon_c_hmap

#define GON_C_HMAP_INIT(hmap, _capacity)                                                     \
do                                                                                          \
{                                                                                           \
    (hmap)->gon_c_hmap.elements = calloc(_capacity, sizeof(*((hmap)->gon_c_hmap.elements)));  \
    (hmap)->gon_c_hmap.capacity = _capacity;                                                 \
    (hmap)->gon_c_hmap.size = 0;                                                             \
}                                                                                           \
while(0)

#define GON_C_HMAP_INDEX(hmap, index) \
(hmap)->gon_c_hmap.elements[index]

#define GON_C_HMAP_CAPACITY(hmap) \
(hmap)->gon_c_hmap.capacity

#define GON_C_HMAP_SIZE(hmap) \
(hmap)->gon_c_hmap.size

#define GON_C_HMAP_GET(hmap, _key, _key_length, element)                                         \
do                                                                                              \
{                                                                                               \
    size_t hash = 0;                                                                            \
    for(size_t i = 0; i < _key_length; ++i)                                                     \
    {                                                                                           \
        hash += _key[i];                                                                        \
        hash << 8;                                                                              \
    }                                                                                           \
    hash %= (hmap)->gon_c_hmap.capacity;                                                         \
    element = (hmap)->gon_c_hmap.elements[hash];                                                 \
    while(element != NULL && strncmp(_key, (element)->gon_c_hmap_element.key, _key_length) != 0) \
        element = (element)->gon_c_hmap_element.next;                                            \
}                                                                                               \
while(0)

#define GON_C_HMAP_REMOVE(hmap, _key, _key_length, element)                                                         \
do                                                                                                                 \
{                                                                                                                  \
    size_t hash = 0;                                                                                               \
    for(size_t i = 0; i < _key_length; ++i)                                                                        \
    {                                                                                                              \
        hash += _key[i];                                                                                           \
        hash << 8;                                                                                                 \
    }                                                                                                              \
    hash %= (hmap)->gon_c_hmap.capacity;                                                                            \
    element = (hmap)->gon_c_hmap.elements[hash];                                                                    \
    while(element != NULL && strncmp(_key, (element)->gon_c_hmap_element.key, _key_length) != 0)                    \
        element = (element)->gon_c_hmap_element.next;                                                               \
    if(element != NULL)                                                                                            \
    {                                                                                                              \
        if(element == (hmap)->gon_c_hmap.elements[hash] && (element)->gon_c_hmap_element.next == NULL)               \
            (hmap)->gon_c_hmap.elements[hash] = NULL;                                                               \
        if((element)->gon_c_hmap_element.previous != NULL)                                                          \
        {                                                                                                          \
            (element)->gon_c_hmap_element.previous->gon_c_hmap_element.next = (element)->gon_c_hmap_element.next;     \
            (element)->gon_c_hmap_element.previous = NULL;                                                          \
        }                                                                                                          \
        if((element)->gon_c_hmap_element.next != NULL)                                                              \
            (element)->gon_c_hmap_element.next->gon_c_hmap_element.previous = (element)->gon_c_hmap_element.previous; \
            (element)->gon_c_hmap_element.next = NULL;                                                              \
        }                                                                                                          \
        --((hmap)->gon_c_hmap.size);                                                                                \
    }                                                                                                              \
}                                                                                                                  \
while(0)

#define GON_C_HMAP_SET(hmap, element, old_element)                                                                                           \
do                                                                                                                                          \
{                                                                                                                                           \
    size_t hash = 0;                                                                                                                        \
    for(size_t i = 0; i < (element)->gon_c_hmap_element.key_length; ++i)                                                                     \
    {                                                                                                                                       \
        hash += (element)->gon_c_hmap_element.key[i];                                                                                        \
        hash << 8;                                                                                                                          \
    }                                                                                                                                       \
    hash %= (hmap)->gon_c_hmap.capacity;                                                                                                     \
    if((hmap)->gon_c_hmap.elements[hash] == NULL)                                                                                            \
        (hmap)->gon_c_hmap.elements[hash] = element;                                                                                         \
    else                                                                                                                                    \
    {                                                                                                                                       \
        old_element = (hmap)->gon_c_hmap.elements[hash];                                                                                     \
        while(old_element != NULL &&                                                                                                        \
             strncmp((element)->gon_c_hmap_element.key, (old_element)->gon_c_hmap_element.key, (element)->gon_c_hmap_element.key_length) != 0) \
        {                                                                                                                                   \
            old_element = (old_element)->gon_c_hmap_element.next;                                                                            \
        }                                                                                                                                   \
        if(old_element != NULL)                                                                                                             \
        {                                                                                                                                   \
            if((old_element)->gon_c_hmap_element.previous != NULL)                                                                           \
            {                                                                                                                               \
                (old_element)->gon_c_hmap_element.previous->gon_c_hmap_element.next = (old_element)->gon_c_hmap_element.next;                  \
                (old_element)->gon_c_hmap_element.previous = NULL;                                                                           \
            }                                                                                                                               \
            if((old_element)->gon_c_hmap_element.next != NULL)                                                                               \
            {                                                                                                                               \
                (old_element)->gon_c_hmap_element.next->gon_c_hmap_element.previous = (old_element)->gon_c_hmap_element.previous;              \
                (old_element)->gon_c_hmap_element.next = NULL;                                                                               \
            }                                                                                                                               \
        }                                                                                                                                   \
        else                                                                                                                                \
            ++((hmap)->gon_c_hmap.size);                                                                                                     \
        (element)->gon_c_hmap_element.next = (hmap)->gon_c_hmap.elements[hash];                                                               \
        (hmap)->gon_c_hmap.elements[hash]->gon_c_hmap_element.previous = element;                                                             \
        (hmap)->gon_c_hmap.elements[hash] = element;                                                                                         \
    }                                                                                                                                       \
}                                                                                                                                           \
while(0)

#define GON_C_HMAP_INDEX_REMOVE(hmap, index, element)                                                   \
do                                                                                                     \
{                                                                                                      \
    element = (hmap)->gon_c_hmap.elements[index];                                                       \
    if(element != NULL)                                                                                \
    {                                                                                                  \
        (hmap)->gon_c_hmap.elements[index] = element->gon_c_hmap_element.next;                           \
        (element)->gon_c_hmap_element.next->gon_c_hmap_element.previous = NULL;                          \
        (element)->gon_c_hmap_element.next->gon_c_hmap_element.next = (element)->gon_c_hmap_element.next; \
        (element)->gon_c_hmap_element.previous = NULL;                                                  \
        (element)->gon_c_hmap_element.next = NULL;                                                      \
    }                                                                                                  \
}                                                                                                      \
while(0)

#define GON_C_HMAP_FREE_ELEMENTS(hmap) \
free((hmap)->gon_c_hmap.elements)

#endif
