#ifndef _GONC_HMAP_H
#define _GONC_HMAP_H

#include <stdlib.h>

#define GONC_HMAP(type) \
struct                  \
{                       \
    type* elements;     \
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

#define GONC_HMAP_CAPACITY(hmap) \
(hmap)->gonc_hmap.capacity

#define GONC_HMAP_SIZE(hmap) \
(hmap)->gonc_hmap.size

#define GONC_HMAP_GET(hmap, key_string, value)       \
do                                                   \
{                                                    \
    size_t hash = 0;                                 \
    for(size_t i = 0; i < (key_string)->length; ++i) \
    {                                                \
        hash += (key_string)->chars[i];              \
        hash << 8;                                   \
    }                                                \
    hash %= (hmap)->gonc_hmap.capacity;              \
    value = (hmap)->gonc_hmap.elements[hash];        \
}                                                    \
while(0)

#define GONC_HMAP_SET(hmap, key_string, value)       \
do                                                   \
{                                                    \
    size_t hash = 0;                                 \
    for(size_t i = 0; i < (key_string)->length; ++i) \
    {                                                \
        hash += (key_string)->chars[i];              \
        hash << 8;                                   \
    }                                                \
    hash %= (hmap)->gonc_hmap.capacity;              \
    (hmap)->gonc_hmap.elements[hash] = value;        \
}                                                    \
while(0)

#endif
