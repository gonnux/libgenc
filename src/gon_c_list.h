#ifndef _GON_C_LIST_H
#define _GON_C_LIST_H

#define GON_C_LIST_ELEMENT(type) \
struct                          \
{                               \
    type* previous;             \
    type* next;                 \
} gon_c_list_element

#define GON_C_LIST_ELEMENT_INIT(element) \
(element)->gon_c_list_element.previous = (element)->gon_c_list_element.next = NULL

#define GON_C_LIST_ELEMENT_PREVIOUS(element) \
(element)->gon_c_list_element.previous

#define GON_C_LIST_ELEMENT_NEXT(element) \
(element)->gon_c_list_element.next


#define GON_C_LIST(type) \
struct                  \
{                       \
    type* head;         \
    type* tail;         \
    size_t size;        \
} gon_c_list

#define GON_C_LIST_INIT(list)                                \
do                                                          \
{                                                           \
    (list)->gon_c_list.head = (list)->gon_c_list.tail = NULL; \
    (list)->gon_c_list.size = 0;                             \
}                                                           \
while(0)

#define GON_C_LIST_HEAD(list) \
(list)->gon_c_list.head

#define GON_C_LIST_TAIL(list) \
(list)->gon_c_list.tail

#define GON_C_LIST_SIZE(list) \
(list)->gon_c_list.size

#define GON_C_LIST_INSERT_BEFORE(list, element, new_element)                                \
do                                                                                         \
{                                                                                          \
    (new_element)->gon_c_list_element.next = element;                                       \
    if(element != NULL)                                                                    \
    {                                                                                      \
        (new_element)->gon_c_list_element.previous = (element)->gon_c_list_element.previous; \
        if((element)->gon_c_list_element.previous != NULL)                                  \
        {                                                                                  \
            (element)->gon_c_list_element.previous->gon_c_list_element.next = new_element;   \
            (element)->gon_c_list_element.previous = new_element;                           \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (element)->gon_c_list_element.previous = new_element;                           \
            (list)->gon_c_list.head = new_element;                                          \
        }                                                                                  \
    }                                                                                      \
    else                                                                                   \
        (list)->gon_c_list.head = (list)->gon_c_list.tail = new_element;                     \
    ++((list)->gon_c_list.size);                                                            \
}                                                                                          \
while(0)

#define GON_C_LIST_PREPEND(list, element) \
GON_C_LIST_INSERT_BEFORE(list, (list)->gon_c_list.head, element)

#define GON_C_LIST_INSERT_AFTER(list, element, new_element)                               \
do                                                                                       \
{                                                                                        \
    (new_element)->gon_c_list_element.previous = element;                                 \
    if(element != NULL)                                                                  \
    {                                                                                    \
        (new_element)->gon_c_list_element.next = (element)->gon_c_list_element.next;       \
        if((element)->gon_c_list_element.next != NULL)                                    \
        {                                                                                \
            (element)->gon_c_list_element.next->gon_c_list_element.previous = new_element; \
            (element)->gon_c_list_element.next = new_element;                             \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            (element)->gon_c_list_element.next = new_element;                             \
            (list)->gon_c_list.tail = new_element;                                        \
        }                                                                                \
    }                                                                                    \
    else                                                                                 \
        (list)->gon_c_list.head = (list)->gon_c_list.tail = new_element;                   \
    ++((list)->gon_c_list.size);                                                          \
}                                                                                        \
while(0)

#define GON_C_LIST_APPEND(list, element) \
GON_C_LIST_INSERT_AFTER(list, (list)->gon_c_list.tail, element)

#define GON_C_LIST_REMOVE(list, element)                                                                        \
do                                                                                                             \
{                                                                                                              \
    if((element)->gon_c_list_element.previous != NULL && (element)->gon_c_list_element.next != NULL)             \
    {                                                                                                          \
        (element)->gon_c_list_element.previous->gon_c_list_element.next = (element)->gon_c_list_element.next;     \
        (element)->gon_c_list_element.next->gon_c_list_element.previous = (element)->gon_c_list_element.previous; \
        (element)->gon_c_list_element.previous = (element)->gon_c_list_element.next = NULL;                      \
    }                                                                                                          \
    else if((element)->gon_c_list_element.previous != NULL && (element)->gon_c_list_element.next == NULL)        \
    {                                                                                                          \
        (element)->gon_c_list_element.previous->gon_c_list_element.next = (element)->gon_c_list_element.next;     \
        (list)->gon_c_list.tail = (element)->gon_c_list_element.previous;                                        \
        (element)->gon_c_list_element.previous = NULL;                                                          \
    }                                                                                                          \
    else if((element)->gon_c_list_element.previous == NULL && (element)->gon_c_list_element.next != NULL)        \
    {                                                                                                          \
        (element)->gon_c_list_element.next->gon_c_list_element.previous = (element)->gon_c_list_element.previous; \
        (list)->gon_c_list.head = (element)->gon_c_list_element.next;                                            \
        (element)->gon_c_list_element.next = NULL;                                                              \
    }                                                                                                          \
    else if((element)->gon_c_list_element.previous == NULL && (element)->gon_c_list_element.next == NULL)        \
    {                                                                                                          \
        (list)->gon_c_list.head = (list)->gon_c_list.tail = NULL;                                                \
    }                                                                                                          \
    --((list)->gon_c_list.size);                                                                                \
}                                                                                                              \
while(0)

#define GON_C_LIST_FOR_EACH(list, type, element) \
for(type* element = (list)->gon_c_list.head; element != NULL; element = element->gon_c_list_element.next)

#define GON_C_LIST_FOR_EACH2(list, element) \
for(element = (list)->gon_c_list.head; element != NULL; element = element->gon_c_list_element.next)

#define GON_C_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->gon_c_list.tail; element != NULL; element = element->gon_c_list_element.previous)

#define GON_C_LIST_REVERSE_FOR_EACH2(list, element) \
for(element = (list)->gon_c_list.tail; element != NULL; element = element->gon_c_list_element.previous)

#define GON_C_LIST_SUBSET_FOR_EACH(list, type, element, start, end) \
for(type* element = start; element != end; element = element->gon_c_list_element.next)

#define GON_C_LIST_SUBSET_FOR_EACH2(list, element, start, end) \
for(element = start; element != end; element = element->gon_c_list_element.next)

#define GON_C_LIST_REVERSE_SUBSET_FOR_EACH(list, type, element, end, start) \
for(type* element = end; element != start; element = element->gon_c_list_element.previous)

#define GON_C_LIST_REVERSE_SUBSET_FOR_EACH2(list, element, end, start) \
for(element = end; element != start; element = element->gon_c_list_element.previous)

#define GON_C_LIST_REMOVE_FOR_EACH(list, type, element) \
for(type* element = (list)->gon_c_list.head; (list)->gon_c_list.size != 0; element = (list)->gon_c_list.head)

#define GON_C_LIST_BEFORE(list, element, _offset)                      \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->gon_c_list_element.previous;

#define GON_C_LIST_AFTER(list, element, _offset)                       \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->gon_c_list_element.next;

#endif
