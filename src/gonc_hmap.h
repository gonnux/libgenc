#ifndef _GONC_HMAP_H
#define _GONC_HMAP_H

#define GONC_HMAP(type) \
struct                  \
{                       \
    type* elements;     \
    size_t capacity;    \
    size_t size;        \
} gonc_hmap

#define GONC_HMAP_INIT(hmap, type, _capacity)                      \
do                                                                 \
{                                                                  \
    (hmap)->gonc_hmap.elements = malloc(_capacity * sizeof(type)); \
    (hmap)->gonc_hmap.capacity = _capacity;                        \
    (hmap)->gonc_hmap.size = 0;                                    \
}                                                                  \
while(0)

#define GONC_HMAP_CAPACITY(hmap) \
(hmap)->gonc_hmap.capacity

#define GONC_HMAP_SIZE(hmap) \
(hmap)->gonc_hmap.size

#endif
