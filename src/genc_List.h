#ifndef _GENC_LIST_H
#define _GENC_LIST_H

#define GENC_LIST_ELEMENT(type) \
struct { \
    type* previous; \
    type* next; \
} genc_List_element

#define GENC_LIST_ELEMENT_INIT(element) \
(element)->genc_List_element.previous = (element)->genc_List_element.next = NULL

#define GENC_LIST_ELEMENT_PREVIOUS(element) \
(element)->genc_List_element.previous

#define GENC_LIST_ELEMENT_NEXT(element) \
(element)->genc_List_element.next

#define GENC_LIST_ELEMENT_SIZE(list) \
sizeof(*(list)->genc_List.head)

#define GENC_LIST_ELEMENT_TYPE(element) \
typeof(*(element))

#define GENC_LIST_ELEMENT_TYPE2(list) \
typeof(*(list)->genc_List.head)

#define GENC_LIST(type) \
struct { \
    type* head; \
    type* tail; \
    size_t size; \
} genc_List

#define GENC_LIST_INIT(list) { \
    (list)->genc_List.head = (list)->genc_List.tail = NULL; \
    (list)->genc_List.size = 0; \
}

#define GENC_LIST_HEAD(list) \
(list)->genc_List.head

#define GENC_LIST_TAIL(list) \
(list)->genc_List.tail

#define GENC_LIST_SIZE(list) \
(list)->genc_List.size

#define GENC_LIST_ELEMENT_REPLACE(element, newElement) { \
    GENC_LIST_ELEMENT_PREVIOUS(newElement) = GENC_LIST_ELEMENT_PREVIOUS(element); \
    GENC_LIST_ELEMENT_NEXT(newElement) = GENC_LIST_ELEMENT_NEXT(element); \
    GENC_LIST_ELEMENT_PREVIOUS(GENC_LIST_ELEMENT_NEXT(element)) = newElement; \
    GENC_LIST_ELEMENT_NEXT(GENC_LIST_ELEMENT_PREVIOUS(element)) = newElement; \
}

#define GENC_LIST_ELEMENT_PREPEND(element, newElement) { \
    GENC_LIST_ELEMENT_NEXT(newElement) = element; \
    GENC_LIST_ELEMENT_PREVIOUS(newElement) = GENC_LIST_ELEMENT_PREVIOUS(element); \
    if(GENC_LIST_ELEMENT_PREVIOUS(element) != NULL) { \
        GENC_LIST_ELEMENT_NEXT(GENC_LIST_ELEMENT_PREVIOUS(element)) = newElement; \
        GENC_LIST_ELEMENT_PREVIOUS(element) = newElement; \
    } else \
        GENC_LIST_ELEMENT_PREVIOUS(element) = newElement; \
}

#define GENC_LIST_ELEMENT_PREPEND_TO_HEAD(element, newElement) { \
    GENC_LIST_ELEMENT_NEXT(newElement) = element; \
    GENC_LIST_ELEMENT_PREVIOUS(newElement) = NULL; \
    GENC_LIST_ELEMENT_PREVIOUS(element) = newElement; \
}

#define GENC_LIST_INSERT_BEFORE(list, element, newElement) { \
    if(element != NULL) { \
        if((element)->genc_List_element.previous == NULL) { \
            GENC_LIST_ELEMENT_PREPEND(element, newElement); \
            (list)->genc_List.head = newElement; \
        } else \
            GENC_LIST_ELEMENT_PREPEND(element, newElement); \
    } else { \
        GENC_LIST_ELEMENT_NEXT(newElement) = NULL; \
        GENC_LIST_ELEMENT_PREVIOUS(newElement) = NULL; \
        (list)->genc_List.head = (list)->genc_List.tail = newElement; \
    } \
    ++((list)->genc_List.size); \
}

#define GENC_LIST_PREPEND(list, element) \
GENC_LIST_INSERT_BEFORE(list, (list)->genc_List.head, element)

#define GENC_LIST_ELEMENT_APPEND(element, newElement) { \
    GENC_LIST_ELEMENT_PREVIOUS(newElement) = element; \
    GENC_LIST_ELEMENT_NEXT(newElement) = GENC_LIST_ELEMENT_NEXT(element); \
    if(GENC_LIST_ELEMENT_NEXT(element) != NULL) { \
        GENC_LIST_ELEMENT_PREVIOUS(GENC_LIST_ELEMENT_NEXT(element)) = newElement; \
        GENC_LIST_ELEMENT_NEXT(element) = newElement; \
    } else \
        GENC_LIST_ELEMENT_NEXT(element) = newElement; \
}

#define GENC_LIST_ELEMENT_APPEND_TO_TAIL(element, newElement) { \
    GENC_LIST_ELEMENT_PREVIOUS(newElement) = element; \
    GENC_LIST_ELEMENT_NEXT(newElement) = GENC_LIST_ELEMENT_NEXT(element); \
    GENC_LIST_ELEMENT_NEXT(element) = newElement; \
}

#define GENC_LIST_INSERT_AFTER(list, element, newElement) { \
    if(element != NULL) { \
        if(GENC_LIST_ELEMENT_NEXT(element) == NULL) { \
            GENC_LIST_ELEMENT_APPEND(element, newElement); \
            (list)->genc_List.tail = newElement; \
        } else \
            GENC_LIST_ELEMENT_APPEND(element, newElement); \
    } else { \
        GENC_LIST_ELEMENT_PREVIOUS(newElement) = NULL; \
        GENC_LIST_ELEMENT_NEXT(newElement) = NULL; \
        (list)->genc_List.head = (list)->genc_List.tail = newElement; \
    } \
    ++((list)->genc_List.size); \
}

#define GENC_LIST_APPEND(list, element) \
GENC_LIST_INSERT_AFTER(list, (list)->genc_List.tail, element)

#define GENC_LIST_REMOVE(list, element) { \
    if(GENC_LIST_ELEMENT_PREVIOUS(element) != NULL && GENC_LIST_ELEMENT_NEXT(element) != NULL) { \
        GENC_LIST_ELEMENT_NEXT(GENC_LIST_ELEMENT_PREVIOUS((element)) = GENC_LIST_ELEMENT_NEXT(element); \
        GENC_LIST_ELEMENT_PREVIOUS(GENC_LIST_ELEMENT_NEXT(element)) = GENC_LIST_ELEMENT_PREVIOUS(element); \
        GENC_LIST_ELEMENT_PREVIOUS(element) = GENC_LIST_ELEMENT_NEXT(element) = NULL; \
    } else if(GENC_LIST_ELEMENT_PREVIOUS(element) != NULL && GENC_LIST_LEMENT_NEXT(element) == NULL) { \
        GENC_LIST_ELEMENT_NEXT(GENC_LIST_ELEMENT_PREVIOUS(element)) = GENC_LIST_ELEMENT_NEXT(element); \
        (list)->genc_List.tail = GENC_LIST_ELEMENT_PREVIOUS(element); \
        GENC_LIST_ELEMENT_PREVIOUS(element) = NULL; \
    } else if(GENC_LIST_ELEMENT_PREVIOUS(element) == NULL && GENC_LIST_ELEMENT_NEXT(element) != NULL) { \
        GENC_LIST_ELEMENT_PREVIOUS(GENC_LIST_ELEMENT_NEXT(element)) = GENC_LIST_ELEMENT_PREVIOUS(element); \
        (list)->genc_List.head = GENC_LIST_ELEMENT_NEXT(element); \
        GENC_LIST_ELEMENT_NEXT(element) = NULL; \
    } else if(GENC_LIST_ELEMENT_PREVIOUS(element) == NULL && GENC_LIST_ELEMENT_NEXT(element) == NULL) { \
        (list)->genc_List.head = (list)->genc_List.tail = NULL; \
    } \
    --((list)->genc_List.size); \
}

#define GENC_LIST_ELEMENT_FOR_EACH(head, element) \
for(GENC_LIST_ELEMENT_TYPE(head)* element = head; element != NULL; element = GENC_LIST_ELEMENT_NEXT(element))

#define GENC_LIST_ELEMENT_REVERSE_FOR_EACH(tail, element) \
for(GENC_LIST_ELEMENT_TYPE(tail)* element = tail; element != NULL; element = GENC_LIST_ELEMENT_PREVIOUS(element))

#define GENC_LIST_FOR_EACH(list, element) \
for(GENC_LIST_ELEMENT_TYPE2(list)* element = (list)->genc_List.head; element != NULL; element = GENC_LIST_ELEMENT_NEXT(element))

#define GENC_LIST_FOR_EACH2(list, element) \
for(element = (list)->genc_List.head; element != NULL; element = GENC_LIST_ELEMENT_NEXT(element))

#define GENC_LIST_REVERSE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.tail; element != NULL; element = GENC_LIST_ELEMENT_PREVIOUS(element))

#define GENC_LIST_REVERSE_FOR_EACH2(list, element) \
for(element = (list)->genc_List.tail; element != NULL; element = GENC_LIST_ELEMENT_PREVIOUS(element))

#define GENC_LIST_SUBSET_FOR_EACH(list, type, element, start, end) \
for(type* element = start; element != end; element = GENC_LIST_ELEMENT_NEXT(element))

#define GENC_LIST_SUBSET_FOR_EACH2(list, element, start, end) \
for(element = start; element != end; element = GENC_LIST_ELEMENT_NEXT(element))

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH(list, type, element, end, start) \
for(type* element = end; element != start; element = GENC_LIST_ELEMENT_PREVIOUS(element))

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH2(list, element, end, start) \
for(element = end; element != start; element = GENC_LIST_ELEMENT_PREVIOUS(element))

#define GENC_LIST_REMOVE_FOR_EACH(list, type, element) \
for(type* element = (list)->genc_List.head; (list)->genc_List.size != 0; element = (list)->genc_List.head)

#define GENC_LIST_BEFORE(list, element, _offset) \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = GENC_LIST_ELEMENT_PREVIOUS(element);

#define GENC_LIST_AFTER(list, element, _offset) \
for(size_t offset = 0; offset < _offset && element != NULL; ++offset) \
    element = GENC_LIST_ELEMENT_NEXT(element);

#endif
