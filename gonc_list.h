#ifndef _GONC_LIST_H
#define _GONC_LIST_H

#define GONC_LIST(type) \
struct                  \
{                       \
    type* first;        \
    type* last;         \
    size_t size;        \
}                       

#define GONC_LIST_INIT(list)             \
do                                       \
{                                        \
    (list)->first = (list)->last = NULL; \
    (list)->size = 0;                    \
}                                        \
while(0)

#define GONC_LIST_ELEMENT(type) \
struct                          \
{                               \
    type* previous;             \
    type* next;                 \
}                               

#define GONC_LIST_ELEMENT_INIT(element)      \
(element)->previous = (element)->next = NULL

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
            (list)->first = new_element;                    \
        }                                                   \
    }                                                       \
    else                                                    \
        (list)->first = (list)->last = new_element;         \
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
            (list)->last = new_element;                    \
        }                                                  \
    }                                                      \
    else                                                   \
        (list)->first = (list)->last = new_element;        \
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
        (list)->last = (element)->previous;                         \
        (element)->previous = NULL;                                 \
    }                                                               \
    else if((element)->previous == NULL && (element)->next != NULL) \
    {                                                               \
        (element)->next->previous = (element)->previous;            \
        (list)->first = (element)->next;                            \
        (element)->next = NULL;                                     \
    }                                                               \
    else if((element)->previous == NULL && (element)->next == NULL) \
    {                                                               \
        (list)->first = (list)->last = NULL;                        \
    }                                                               \
    --((list)->size);                                               \
}                                                                   \
while(0)

#define GONC_LIST_FOR_EACH(list, type, element) \
for(type* element = (list)->first;              \
     element != NULL;                           \
     element = element->next)                         

#define GONC_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->last;                       \
     element != NULL;                                   \
     element = element->previous)                             

#endif
