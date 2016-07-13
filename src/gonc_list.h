#ifndef _GONC_LIST_H
#define _GONC_LIST_H

#define GONC_LIST(name, type) \
struct name                   \
{                             \
    type* head;              \
    type* tail;               \
    size_t size;              \
}

#define GONC_LIST_INIT(list)             \
do                                       \
{                                        \
    (list)->head = (list)->tail = NULL; \
    (list)->size = 0;                    \
}                                        \
while(0)

#define GONC_LIST_ELEMENT(type) \
struct                          \
{                               \
    type* previous;             \
    type* next;                 \
}                               

#define GONC_LIST_ELEMENT_INIT(element) \
(element)->previous = (element)->next = NULL

#define GONC_LIST_PREVIOUS(list, element) \
    (element)->previous

#define GONC_LIST_NEXT(list, element) \
    (element)->next

#define GONC_LIST_INSERT_BEFORE(list, element, new_element) \
do                                                          \
{                                                           \
    (new_element)->next = element;                          \
    if(element != NULL)                                     \
    {                                                       \
        (new_element)->previous = (element)->previous;      \
        if((element)->previous != NULL)                     \
        {                                                   \
            (element)->previous->next = new_element;        \
            (element)->previous = new_element;              \
        }                                                   \
        else                                                \
        {                                                   \
            (element)->previous = new_element;              \
            (list)->head = new_element;                    \
        }                                                   \
    }                                                       \
    else                                                    \
        (list)->head = (list)->tail = new_element;         \
    ++((list)->size);                                       \
}                                                           \
while(0)

#define GONC_LIST_INSERT_AFTER(list, element, new_element) \
do                                                         \
{                                                          \
    (new_element)->previous = element;                     \
    if(element != NULL)                                    \
    {                                                      \
        (new_element)->next = (element)->next;             \
        if((element)->next != NULL)                        \
        {                                                  \
            (element)->next->previous = new_element;       \
            (element)->next = new_element;                 \
        }                                                  \
        else                                               \
        {                                                  \
            (element)->next = new_element;                 \
            (list)->tail = new_element;                    \
        }                                                  \
    }                                                      \
    else                                                   \
        (list)->head = (list)->tail = new_element;        \
    ++((list)->size);                                      \
}                                                          \
while(0)

#define GONC_LIST_REMOVE(list, element)                             \
do                                                                  \
{                                                                   \
    if((element)->previous != NULL && (element)->next != NULL)      \
    {                                                               \
        (element)->previous->next = (element)->next;                \
        (element)->next->previous = (element)->previous;            \
        (element)->previous = (element)->next = NULL;               \
    }                                                               \
    else if((element)->previous != NULL && (element)->next == NULL) \
    {                                                               \
        (element)->previous->next = (element)->next;                \
        (list)->tail = (element)->previous;                         \
        (element)->previous = NULL;                                 \
    }                                                               \
    else if((element)->previous == NULL && (element)->next != NULL) \
    {                                                               \
        (element)->next->previous = (element)->previous;            \
        (list)->head = (element)->next;                            \
        (element)->next = NULL;                                     \
    }                                                               \
    else if((element)->previous == NULL && (element)->next == NULL) \
    {                                                               \
        (list)->head = (list)->tail = NULL;                        \
    }                                                               \
    --((list)->size);                                               \
}                                                                   \
while(0)

#define GONC_LIST_FOR_EACH(list, type, element) \
for(type* element = (list)->head;              \
     element != NULL;                           \
     element = element->next)

#define GONC_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->tail;                       \
     element != NULL;                                   \
     element = element->previous)

#define GONC_LIST_AFTER(list, type, element, _index)                  \
    for(size_t index = 0; index < _index && element != NULL; ++index) \
        element = element->next;                                      \

#endif
