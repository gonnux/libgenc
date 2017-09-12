#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#define GENC_TREE_ELEMENT(type) \
struct                          \
{                               \
    type* parent;               \
    type* children;             \
} genc_List_element

#define GENC_TREE_ELEMENT_INIT(element, childCount)                                \
(element)->genc_List_element.parent = (element)->genc_List_element.children = NULL;

#define GENC_TREE_ELEMENT_PARENT(element) \
(element)->genc_List_element.parent

#define GENC_TREE_ELEMENT_CHILD(element, index) \
(element)->genc_List_element.children[index]


#define GENC_TREE(type) \
struct {                \
    type* root;         \
    size_t size;        \
} genc_List

#define GENC_TREE_INIT(list)                                \
do                                                          \
{                                                           \
    (list)->genc_List.root = NULL;                          \
    (list)->genc_List.size = 0;                             \
}                                                           \
while(0)

#define GENC_TREE_ROOT(list) \
(list)->genc_List.root

#define GENC_TREE_SIZE(list) \
(list)->genc_List.size

#define GENC_TREE_INSERT_BEFORE(list, element, new_element)                                \
do                                                                                         \
{                                                                                          \
    (new_element)->genc_List_element.next = element;                                       \
    if(element != NULL)                                                                    \
    {                                                                                      \
        (new_element)->genc_List_element.previous = (element)->genc_List_element.previous; \
        if((element)->genc_List_element.previous != NULL)                                  \
        {                                                                                  \
            (element)->genc_List_element.previous->genc_List_element.next = new_element;   \
            (element)->genc_List_element.previous = new_element;                           \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            (element)->genc_List_element.previous = new_element;                           \
            (list)->genc_List.head = new_element;                                          \
        }                                                                                  \
    }                                                                                      \
    else                                                                                   \
        (list)->genc_List.head = (list)->genc_List.tail = new_element;                     \
    ++((list)->genc_List.size);                                                            \
}                                                                                          \
while(0)

#define GENC_TREE_PREPEND(list, element) \
GENC_TREE_INSERT_BEFORE(list, (list)->genc_List.head, element)

#define GENC_TREE_INSERT_AFTER(list, element, new_element)                               \
do                                                                                       \
{                                                                                        \
    (new_element)->genc_List_element.previous = element;                                 \
    if(element != NULL)                                                                  \
    {                                                                                    \
        (new_element)->genc_List_element.next = (element)->genc_List_element.next;       \
        if((element)->genc_List_element.next != NULL)                                    \
        {                                                                                \
            (element)->genc_List_element.next->genc_List_element.previous = new_element; \
            (element)->genc_List_element.next = new_element;                             \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            (element)->genc_List_element.next = new_element;                             \
            (list)->genc_List.tail = new_element;                                        \
        }                                                                                \
    }                                                                                    \
    else                                                                                 \
        (list)->genc_List.head = (list)->genc_List.tail = new_element;                   \
    ++((list)->genc_List.size);                                                          \
}                                                                                        \
while(0)

#define GENC_TREE_APPEND(list, element) \
GENC_TREE_INSERT_AFTER(list, (list)->genc_List.tail, element)

#define GENC_TREE_REMOVE(list, element)                                                                        \
do                                                                                                             \
{                                                                                                              \
    if((element)->genc_List_element.previous != NULL && (element)->genc_List_element.next != NULL)             \
    {                                                                                                          \
        (element)->genc_List_element.previous->genc_List_element.next = (element)->genc_List_element.next;     \
        (element)->genc_List_element.next->genc_List_element.previous = (element)->genc_List_element.previous; \
        (element)->genc_List_element.previous = (element)->genc_List_element.next = NULL;                      \
    }                                                                                                          \
    else if((element)->genc_List_element.previous != NULL && (element)->genc_List_element.next == NULL)        \
    {                                                                                                          \
        (element)->genc_List_element.previous->genc_List_element.next = (element)->genc_List_element.next;     \
        (list)->genc_List.tail = (element)->genc_List_element.previous;                                        \
        (element)->genc_List_element.previous = NULL;                                                          \
    }                                                                                                          \
    else if((element)->genc_List_element.previous == NULL && (element)->genc_List_element.next != NULL)        \
    {                                                                                                          \
        (element)->genc_List_element.next->genc_List_element.previous = (element)->genc_List_element.previous; \
        (list)->genc_List.head = (element)->genc_List_element.next;                                            \
        (element)->genc_List_element.next = NULL;                                                              \
    }                                                                                                          \
    else if((element)->genc_List_element.previous == NULL && (element)->genc_List_element.next == NULL)        \
    {                                                                                                          \
        (list)->genc_List.head = (list)->genc_List.tail = NULL;                                                \
    }                                                                                                          \
    --((list)->genc_List.size);                                                                                \
}                                                                                                              \
while(0)

#define GENC_TREE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.head; element != NULL; element = element->genc_List_element.next)

#define GENC_TREE_FOR_EACH2(list, element) \
for(element = (list)->genc_List.head; element != NULL; element = element->genc_List_element.next)

#define GENC_TREE_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.tail; element != NULL; element = element->genc_List_element.previous)

#define GENC_TREE_REVERSE_FOR_EACH2(list, element) \
for(element = (list)->genc_List.tail; element != NULL; element = element->genc_List_element.previous)

#define GENC_TREE_SUBSET_FOR_EACH(list, type, element, start, end) \
for(type* element = start; element != end; element = element->genc_List_element.next)

#define GENC_TREE_SUBSET_FOR_EACH2(list, element, start, end) \
for(element = start; element != end; element = element->genc_List_element.next)

#define GENC_TREE_REVERSE_SUBSET_FOR_EACH(list, type, element, end, start) \
for(type* element = end; element != start; element = element->genc_List_element.previous)

#define GENC_TREE_REVERSE_SUBSET_FOR_EACH2(list, element, end, start) \
for(element = end; element != start; element = element->genc_List_element.previous)

#define GENC_TREE_REMOVE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.head; (list)->genc_List.size != 0; element = (list)->genc_List.head)

#define GENC_TREE_BEFORE(list, element, _offset)                      \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->genc_List_element.previous;

#define GENC_TREE_AFTER(list, element, _offset)                       \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = element->genc_List_element.next;

#endif
