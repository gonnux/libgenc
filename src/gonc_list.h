#ifndef _GONC_LIST_H
#define _GONC_LIST_H

#define GONC_LIST_ELEMENT(type) \
struct                          \
{                               \
    type* previous;             \
    type* next;                 \
} gonc_list_element

#define GONC_LIST_ELEMENT_INIT(element) \
(element)->gonc_list_element.previous = (element)->gonc_list_element.next = NULL

#define GONC_LIST(type) \
struct                  \
{                       \
    type* head;         \
    type* tail;         \
    size_t size;        \
} gonc_list

#define GONC_LIST_INIT(list)                                \
do                                                          \
{                                                           \
    (list)->gonc_list.head = (list)->gonc_list.tail = NULL; \
    (list)->gonc_list.size = 0;                             \
}                                                           \
while(0)

#define GONC_LIST_HEAD(list) \
(list)->gonc_list.head

#define GONC_LIST_TAIL(list) \
(list)->gonc_list.tail

#define GONC_LIST_SIZE(list) \
(list)->gonc_list.size

#define GONC_LIST_PREVIOUS(list, element) \
(element)->gonc_list_element.previous

#define GONC_LIST_NEXT(list, element) \
(element)->gonc_list_element.next

#define GONC_LIST_INSERT_BEFORE(list, element, new_element)                                \
do                                                                                         \
{                                                                                          \
    (new_element)->gonc_list_element.next = element;                                       \
    if(element != NULL)                                                                    \
    {                                                                                      \
        (new_element)->gonc_list_element.previous = (element)->gonc_list_element.previous; \
        if((element)->gonc_list_element.previous != NULL)                                  \
        {                                                                                  \
            (element)->gonc_list_element.previous->gonc_list_element.next = new_element;   \
            (element)->gonc_list_element.previous = new_element;                           \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (element)->gonc_list_element.previous = new_element;                           \
            (list)->gonc_list.head = new_element;                                          \
        }                                                                                  \
    }                                                                                      \
    else                                                                                   \
        (list)->gonc_list.head = (list)->gonc_list.tail = new_element;                     \
    ++((list)->gonc_list.size);                                                            \
}                                                                                          \
while(0)

#define GONC_LIST_INSERT_AFTER(list, element, new_element)                               \
do                                                                                       \
{                                                                                        \
    (new_element)->gonc_list_element.previous = element;                                 \
    if(element != NULL)                                                                  \
    {                                                                                    \
        (new_element)->gonc_list_element.next = (element)->gonc_list_element.next;       \
        if((element)->gonc_list_element.next != NULL)                                    \
        {                                                                                \
            (element)->gonc_list_element.next->gonc_list_element.previous = new_element; \
            (element)->gonc_list_element.next = new_element;                             \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            (element)->gonc_list_element.next = new_element;                             \
            (list)->gonc_list.tail = new_element;                                        \
        }                                                                                \
    }                                                                                    \
    else                                                                                 \
        (list)->gonc_list.head = (list)->gonc_list.tail = new_element;                   \
    ++((list)->gonc_list.size);                                                          \
}                                                                                        \
while(0)

#define GONC_LIST_APPEND(list, element)
GONC_LIST_INSERT_AFTER(list, (list)->tail, element)

#define GONC_LIST_REMOVE(list, element)                                                                        \
do                                                                                                             \
{                                                                                                              \
    if((element)->gonc_list_element.previous != NULL && (element)->gonc_list_element.next != NULL)             \
    {                                                                                                          \
        (element)->gonc_list_element.previous->gonc_list_element.next = (element)->gonc_list_element.next;     \
        (element)->gonc_list_element.next->gonc_list_element.previous = (element)->gonc_list_element.previous; \
        (element)->gonc_list_element.previous = (element)->gonc_list_element.next = NULL;                      \
    }                                                                                                          \
    else if((element)->gonc_list_element.previous != NULL && (element)->gonc_list_element.next == NULL)        \
    {                                                                                                          \
        (element)->gonc_list_element.previous->gonc_list_element.next = (element)->gonc_list_element.next;     \
        (list)->gonc_list.tail = (element)->gonc_list_element.previous;                                        \
        (element)->gonc_list_element.previous = NULL;                                                          \
    }                                                                                                          \
    else if((element)->gonc_list_element.previous == NULL && (element)->gonc_list_element.next != NULL)        \
    {                                                                                                          \
        (element)->gonc_list_element.next->gonc_list_element.previous = (element)->gonc_list_element.previous; \
        (list)->gonc_list.head = (element)->gonc_list_element.next;                                            \
        (element)->gonc_list_element.next = NULL;                                                              \
    }                                                                                                          \
    else if((element)->gonc_list_element.previous == NULL && (element)->gonc_list_element.next == NULL)        \
    {                                                                                                          \
        (list)->gonc_list.head = (list)->gonc_list.tail = NULL;                                                \
    }                                                                                                          \
    --((list)->gonc_list.size);                                                                                \
}                                                                                                              \
while(0)

#define GONC_LIST_FOR_EACH(list, type, element) \
for(type* element = (list)->gonc_list.head;     \
     element != NULL;                           \
     element = element->gonc_list_element.next)

#define GONC_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->gonc_list.tail;             \
     element != NULL;                                   \
     element = element->gonc_list_element.previous)

#define GONC_LIST_FOR_EACH2(list, element) \
for(element = (list)->gonc_list.head;      \
     element != NULL;                      \
     element = element->gonc_list_element.next)

#define GONC_LIST_REVERSE_FOR_EACH2(list, element) \
for(element = (list)->gonc_list.tail;              \
     element != NULL;                              \
     element = element->gonc_list_element.previous)

#define GONC_LIST_SUBSET_FOR_EACH(list, type, element, start, end) \
for(type* element = start;                                         \
     element != end;                                               \
     element = element->gonc_list_element.next)

#define GONC_LIST_REVERSE_SUBSET_FOR_EACH(list, type, element, end, start) \
for(type* element = end;                                                   \
     element != start;                                                     \
     element = element->gonc_list_element.previous)

#define GONC_LIST_SUBSET_FOR_EACH2(list, element, start, end) \
for(element = start;                                          \
     element != end;                                          \
     element = element->gonc_list_element.next)

#define GONC_LIST_REVERSE_SUBSET_FOR_EACH2(list, element, end, start) \
for(element = end;                                                    \
     element != start;                                                \
     element = element->gonc_list_element.previous)

#define GONC_LIST_BEFORE(list, element, _offset)                      \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->gonc_list_element.previous;

#define GONC_LIST_AFTER(list, element, _offset)                       \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->gonc_list_element.next;

#endif
