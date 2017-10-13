#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#include <libgenc/genc_ArrayList.h>

#define GENC_TREE_NODE(type)   \
struct {                       \
    struct {                   \
        GENC_ARRAY_LIST(type); \
    } children;                \
} genc_Tree_node

/*
#define GENC_LIST_ELEMENT_INIT(element) \
(element)->genc_List_element.previous = (element)->genc_List_element.next = NULL

#define GENC_LIST_ELEMENT_PREVIOUS(element) \
(element)->genc_List_element.previous

#define GENC_LIST_ELEMENT_NEXT(element) \
(element)->genc_List_element.next


#define GENC_LIST(type) \
struct {                \
    type* head;         \
    type* tail;         \
    size_t size;        \
} genc_List

#define GENC_LIST_INIT(list)                                \
do {                                                        \
    (list)->genc_List.head = (list)->genc_List.tail = NULL; \
    (list)->genc_List.size = 0;                             \
} while(0)

#define GENC_TREE_HEAD(list) \
(list)->genc_List.head

#define GENC_LIST_TAIL(list) \
(list)->genc_List.tail

#define GENC_LIST_SIZE(list) \
(list)->genc_List.size

#define GENC_LIST_ELEMENT_PREPEND(element, newElement)                                \
do {                                                                                  \
    (newElement)->genc_List_element.next = element;                                   \
    (newElement)->genc_List_element.previous = (element)->genc_List_element.previous; \
    if((element)->genc_List_element.previous != NULL) {                               \
        (element)->genc_List_element.previous->genc_List_element.next = newElement;   \
        (element)->genc_List_element.previous = newElement;                           \
    } else                                                                            \
        (element)->genc_List_element.previous = newElement;                           \
} while(0)

#define GENC_LIST_INSERT_BEFORE(list, element, newElement)                                \
do {                                                                                      \
    if(element != NULL) {                                                                 \
        GENC_LIST_ELEMENT_PREPEND(element, newElement);                                   \
        if((element)->genc_List_element.previous == NULL)                                 \
            (list)->genc_List.head = newElement;                                          \
    } else {                                                                              \
        (newElement)->genc_List_element.next = NULL;                                      \
        (newElement)->genc_List_element.previous = NULL;                                  \
        (list)->genc_List.head = (list)->genc_List.tail = newElement;                     \
    }                                                                                     \
    ++((list)->genc_List.size);                                                           \
} while(0)

#define GENC_LIST_PREPEND(list, element) \
GENC_LIST_INSERT_BEFORE(list, (list)->genc_List.head, element)

#define GENC_LIST_ELEMENT_APPEND(element, newElement)                               \
do {                                                                                \
    (newElement)->genc_List_element.previous = element;                             \
    (newElement)->genc_List_element.next = (element)->genc_List_element.next;       \
    if((element)->genc_List_element.next != NULL) {                                 \
        (element)->genc_List_element.next->genc_List_element.previous = newElement; \
        (element)->genc_List_element.next = newElement;                             \
    } else                                                                          \
        (element)->genc_List_element.next = newElement;                             \
} while(0)

#define GENC_LIST_INSERT_AFTER(list, element, newElement)             \
do {                                                                  \
    if(element != NULL) {                                             \
        GENC_LIST_ELEMENT_APPEND(element, newElement);                \
        if((element)->genc_List_element.next == NULL)                 \
            (list)->genc_List.tail = newElement;                      \
    } else {                                                          \
        (newElement)->genc_List_element.previous = NULL;              \
        (newElement)->genc_List_element.next = NULL;                  \
        (list)->genc_List.head = (list)->genc_List.tail = newElement; \
    }                                                                 \
    ++((list)->genc_List.size);                                       \
} while(0)

#define GENC_LIST_APPEND(list, element) \
GENC_LIST_INSERT_AFTER(list, (list)->genc_List.tail, element)

#define GENC_LIST_REMOVE(list, element)                                                                        \
do {                                                                                                           \
    if((element)->genc_List_element.previous != NULL && (element)->genc_List_element.next != NULL) {           \
        (element)->genc_List_element.previous->genc_List_element.next = (element)->genc_List_element.next;     \
        (element)->genc_List_element.next->genc_List_element.previous = (element)->genc_List_element.previous; \
        (element)->genc_List_element.previous = (element)->genc_List_element.next = NULL;                      \
    } else if((element)->genc_List_element.previous != NULL && (element)->genc_List_element.next == NULL) {    \
        (element)->genc_List_element.previous->genc_List_element.next = (element)->genc_List_element.next;     \
        (list)->genc_List.tail = (element)->genc_List_element.previous;                                        \
        (element)->genc_List_element.previous = NULL;                                                          \
    } else if((element)->genc_List_element.previous == NULL && (element)->genc_List_element.next != NULL) {    \
        (element)->genc_List_element.next->genc_List_element.previous = (element)->genc_List_element.previous; \
        (list)->genc_List.head = (element)->genc_List_element.next;                                            \
        (element)->genc_List_element.next = NULL;                                                              \
    } else if((element)->genc_List_element.previous == NULL && (element)->genc_List_element.next == NULL) {    \
        (list)->genc_List.head = (list)->genc_List.tail = NULL;                                                \
    }                                                                                                          \
    --((list)->genc_List.size);                                                                                \
} while(0)

#define GENC_LIST_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.head; element != NULL; element = element->genc_List_element.next)

#define GENC_LIST_FOR_EACH2(list, element) \
for(element = (list)->genc_List.head; element != NULL; element = element->genc_List_element.next)

#define GENC_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.tail; element != NULL; element = element->genc_List_element.previous)

#define GENC_LIST_REVERSE_FOR_EACH2(list, element) \
for(element = (list)->genc_List.tail; element != NULL; element = element->genc_List_element.previous)

#define GENC_LIST_SUBSET_FOR_EACH(list, type, element, start, end) \
for(type* element = start; element != end; element = element->genc_List_element.next)

#define GENC_LIST_SUBSET_FOR_EACH2(list, element, start, end) \
for(element = start; element != end; element = element->genc_List_element.next)

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH(list, type, element, end, start) \
for(type* element = end; element != start; element = element->genc_List_element.previous)

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH2(list, element, end, start) \
for(element = end; element != start; element = element->genc_List_element.previous)

#define GENC_LIST_REMOVE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.head; (list)->genc_List.size != 0; element = (list)->genc_List.head)

#define GENC_LIST_BEFORE(list, element, _offset)                      \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->genc_List_element.previous;

#define GENC_LIST_AFTER(list, element, _offset)                       \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->genc_List_element.next;
*/
#endif
