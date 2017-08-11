#ifndef _GENC_LIST_H
#define _GENC_LIST_H

#define GENC_LIST_ELEMENT(type) \
struct                          \
{                               \
    type* previous;             \
    type* next;                 \
} genc_list_element

#define GENC_LIST_ELEMENT_INIT(element) \
(element)->genc_list_element.previous = (element)->genc_list_element.next = NULL

#define GENC_LIST_ELEMENT_PREVIOUS(element) \
(element)->genc_list_element.previous

#define GENC_LIST_ELEMENT_NEXT(element) \
(element)->genc_list_element.next


#define GENC_LIST(type) \
struct                  \
{                       \
    type* head;         \
    type* tail;         \
    size_t size;        \
} genc_list

#define GENC_LIST_INIT(list)                                \
do                                                          \
{                                                           \
    (list)->genc_list.head = (list)->genc_list.tail = NULL; \
    (list)->genc_list.size = 0;                             \
}                                                           \
while(0)

#define GENC_LIST_HEAD(list) \
(list)->genc_list.head

#define GENC_LIST_TAIL(list) \
(list)->genc_list.tail

#define GENC_LIST_SIZE(list) \
(list)->genc_list.size

#define GENC_LIST_INSERT_BEFORE(list, element, new_element)                                \
do                                                                                         \
{                                                                                          \
    (new_element)->genc_list_element.next = element;                                       \
    if(element != NULL)                                                                    \
    {                                                                                      \
        (new_element)->genc_list_element.previous = (element)->genc_list_element.previous; \
        if((element)->genc_list_element.previous != NULL)                                  \
        {                                                                                  \
            (element)->genc_list_element.previous->genc_list_element.next = new_element;   \
            (element)->genc_list_element.previous = new_element;                           \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (element)->genc_list_element.previous = new_element;                           \
            (list)->genc_list.head = new_element;                                          \
        }                                                                                  \
    }                                                                                      \
    else                                                                                   \
        (list)->genc_list.head = (list)->genc_list.tail = new_element;                     \
    ++((list)->genc_list.size);                                                            \
}                                                                                          \
while(0)

#define GENC_LIST_PREPEND(list, element) \
GENC_LIST_INSERT_BEFORE(list, (list)->genc_list.head, element)

#define GENC_LIST_INSERT_AFTER(list, element, new_element)                               \
do                                                                                       \
{                                                                                        \
    (new_element)->genc_list_element.previous = element;                                 \
    if(element != NULL)                                                                  \
    {                                                                                    \
        (new_element)->genc_list_element.next = (element)->genc_list_element.next;       \
        if((element)->genc_list_element.next != NULL)                                    \
        {                                                                                \
            (element)->genc_list_element.next->genc_list_element.previous = new_element; \
            (element)->genc_list_element.next = new_element;                             \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            (element)->genc_list_element.next = new_element;                             \
            (list)->genc_list.tail = new_element;                                        \
        }                                                                                \
    }                                                                                    \
    else                                                                                 \
        (list)->genc_list.head = (list)->genc_list.tail = new_element;                   \
    ++((list)->genc_list.size);                                                          \
}                                                                                        \
while(0)

#define GENC_LIST_APPEND(list, element) \
GENC_LIST_INSERT_AFTER(list, (list)->genc_list.tail, element)

#define GENC_LIST_REMOVE(list, element)                                                                        \
do                                                                                                             \
{                                                                                                              \
    if((element)->genc_list_element.previous != NULL && (element)->genc_list_element.next != NULL)             \
    {                                                                                                          \
        (element)->genc_list_element.previous->genc_list_element.next = (element)->genc_list_element.next;     \
        (element)->genc_list_element.next->genc_list_element.previous = (element)->genc_list_element.previous; \
        (element)->genc_list_element.previous = (element)->genc_list_element.next = NULL;                      \
    }                                                                                                          \
    else if((element)->genc_list_element.previous != NULL && (element)->genc_list_element.next == NULL)        \
    {                                                                                                          \
        (element)->genc_list_element.previous->genc_list_element.next = (element)->genc_list_element.next;     \
        (list)->genc_list.tail = (element)->genc_list_element.previous;                                        \
        (element)->genc_list_element.previous = NULL;                                                          \
    }                                                                                                          \
    else if((element)->genc_list_element.previous == NULL && (element)->genc_list_element.next != NULL)        \
    {                                                                                                          \
        (element)->genc_list_element.next->genc_list_element.previous = (element)->genc_list_element.previous; \
        (list)->genc_list.head = (element)->genc_list_element.next;                                            \
        (element)->genc_list_element.next = NULL;                                                              \
    }                                                                                                          \
    else if((element)->genc_list_element.previous == NULL && (element)->genc_list_element.next == NULL)        \
    {                                                                                                          \
        (list)->genc_list.head = (list)->genc_list.tail = NULL;                                                \
    }                                                                                                          \
    --((list)->genc_list.size);                                                                                \
}                                                                                                              \
while(0)

#define GENC_LIST_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_list.head; element != NULL; element = element->genc_list_element.next)

#define GENC_LIST_FOR_EACH2(list, element) \
for(element = (list)->genc_list.head; element != NULL; element = element->genc_list_element.next)

#define GENC_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_list.tail; element != NULL; element = element->genc_list_element.previous)

#define GENC_LIST_REVERSE_FOR_EACH2(list, element) \
for(element = (list)->genc_list.tail; element != NULL; element = element->genc_list_element.previous)

#define GENC_LIST_SUBSET_FOR_EACH(list, type, element, start, end) \
for(type* element = start; element != end; element = element->genc_list_element.next)

#define GENC_LIST_SUBSET_FOR_EACH2(list, element, start, end) \
for(element = start; element != end; element = element->genc_list_element.next)

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH(list, type, element, end, start) \
for(type* element = end; element != start; element = element->genc_list_element.previous)

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH2(list, element, end, start) \
for(element = end; element != start; element = element->genc_list_element.previous)

#define GENC_LIST_REMOVE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_list.head; (list)->genc_list.size != 0; element = (list)->genc_list.head)

#define GENC_LIST_BEFORE(list, element, _offset)                      \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->genc_list_element.previous;

#define GENC_LIST_AFTER(list, element, _offset)                       \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->genc_list_element.next;

#endif
