#ifndef _GENC_LIST_H
#define _GENC_LIST_H

#define GENC_LIST_ELEM(type) \
struct { \
    type* previous; \
    type* next; \
} genc_List_elem

#define GENC_LIST_ELEM_INIT(elem) \
(elem)->genc_List_elem.previous = (elem)->genc_List_elem.next = NULL

#define GENC_LIST_ELEM_PREVIOUS(elem) \
(elem)->genc_List_elem.previous

#define GENC_LIST_ELEM_NEXT(elem) \
(elem)->genc_List_elem.next

#define GENC_LIST_ELEM_SIZE(list) \
sizeof(*(list)->genc_List.head)

#define GENC_LIST_ELEM_TYPE(elem) \
typeof(*(elem))

#define GENC_LIST_ELEM_TYPE2(list) \
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

#define GENC_LIST_ELEM_REPLACE(elem, newElem) { \
    GENC_LIST_ELEM_PREVIOUS(newElem) = GENC_LIST_ELEM_PREVIOUS(elem); \
    GENC_LIST_ELEM_NEXT(newElem) = GENC_LIST_ELEM_NEXT(elem); \
    GENC_LIST_ELEM_PREVIOUS(GENC_LIST_ELEM_NEXT(elem)) = newElem; \
    GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREVIOUS(elem)) = newElem; \
}

#define GENC_LIST_ELEM_PREPEND(elem, newElem) { \
    GENC_LIST_ELEM_NEXT(newElem) = elem; \
    GENC_LIST_ELEM_PREVIOUS(newElem) = GENC_LIST_ELEM_PREVIOUS(elem); \
    if(GENC_LIST_ELEM_PREVIOUS(elem) != NULL) { \
        GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREVIOUS(elem)) = newElem; \
        GENC_LIST_ELEM_PREVIOUS(elem) = newElem; \
    } else \
        GENC_LIST_ELEM_PREVIOUS(elem) = newElem; \
}

#define GENC_LIST_ELEM_PREPEND_TO_HEAD(elem, newElem) { \
    GENC_LIST_ELEM_NEXT(newElem) = elem; \
    GENC_LIST_ELEM_PREVIOUS(newElem) = NULL; \
    GENC_LIST_ELEM_PREVIOUS(elem) = newElem; \
}

#define GENC_LIST_INSERT_BEFORE(list, elem, newElem) { \
    if(elem != NULL) { \
        if((elem)->genc_List_elem.previous == NULL) { \
            GENC_LIST_ELEM_PREPEND(elem, newElem); \
            (list)->genc_List.head = newElem; \
        } else \
            GENC_LIST_ELEM_PREPEND(elem, newElem); \
    } else { \
        GENC_LIST_ELEM_NEXT(newElem) = NULL; \
        GENC_LIST_ELEM_PREVIOUS(newElem) = NULL; \
        (list)->genc_List.head = (list)->genc_List.tail = newElem; \
    } \
    ++((list)->genc_List.size); \
}

#define GENC_LIST_PREPEND(list, elem) \
GENC_LIST_INSERT_BEFORE(list, (list)->genc_List.head, elem)

#define GENC_LIST_ELEM_APPEND(elem, newElem) { \
    GENC_LIST_ELEM_PREVIOUS(newElem) = elem; \
    GENC_LIST_ELEM_NEXT(newElem) = GENC_LIST_ELEM_NEXT(elem); \
    if(GENC_LIST_ELEM_NEXT(elem) != NULL) { \
        GENC_LIST_ELEM_PREVIOUS(GENC_LIST_ELEM_NEXT(elem)) = newElem; \
        GENC_LIST_ELEM_NEXT(elem) = newElem; \
    } else \
        GENC_LIST_ELEM_NEXT(elem) = newElem; \
}

#define GENC_LIST_ELEM_APPEND_TO_TAIL(elem, newElem) { \
    GENC_LIST_ELEM_PREVIOUS(newElem) = elem; \
    GENC_LIST_ELEM_NEXT(newElem) = GENC_LIST_ELEM_NEXT(elem); \
    GENC_LIST_ELEM_NEXT(elem) = newElem; \
}

#define GENC_LIST_INSERT_AFTER(list, elem, newElem) { \
    if(elem != NULL) { \
        if(GENC_LIST_ELEM_NEXT(elem) == NULL) { \
            GENC_LIST_ELEM_APPEND(elem, newElem); \
            (list)->genc_List.tail = newElem; \
        } else \
            GENC_LIST_ELEM_APPEND(elem, newElem); \
    } else { \
        GENC_LIST_ELEM_PREVIOUS(newElem) = NULL; \
        GENC_LIST_ELEM_NEXT(newElem) = NULL; \
        (list)->genc_List.head = (list)->genc_List.tail = newElem; \
    } \
    ++((list)->genc_List.size); \
}

#define GENC_LIST_APPEND(list, elem) \
GENC_LIST_INSERT_AFTER(list, (list)->genc_List.tail, elem)

#define GENC_LIST_ELEM_REMOVE(elem) { \
    if(GENC_LIST_ELEM_PREVIOUS(elem) != NULL) \
        GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREVIOUS(elem)) = GENC_LIST_ELEM_NEXT(elem); \
    if(GENC_LIST_ELEM_NEXT(elem) != NULL) \
        GENC_LIST_ELEM_PREVIOUS(GENC_LIST_ELEM_NEXT(elem)) = GENC_LIST_ELEM_PREVIOUS(elem); \
    GENC_LIST_ELEM_PREVIOUS(elem) = NULL; \
    GENC_LIST_ELEM_NEXT(elem) = NULL; \
}

#define GENC_LIST_REMOVE(list, elem) { \
    if(GENC_LIST_ELEM_PREVIOUS(elem) != NULL && GENC_LIST_LEMENT_NEXT(elem) == NULL) \
        (list)->genc_List.tail = GENC_LIST_ELEM_PREVIOUS(elem); \
    else if(GENC_LIST_ELEM_PREVIOUS(elem) == NULL && GENC_LIST_ELEM_NEXT(elem) != NULL) \
        (list)->genc_List.head = GENC_LIST_ELEM_NEXT(elem); \
    else if(GENC_LIST_ELEM_PREVIOUS(elem) == NULL && GENC_LIST_ELEM_NEXT(elem) == NULL) \
        (list)->genc_List.head = (list)->genc_List.tail = NULL; \
    GENC_LIST_ELEM_REMOVE(elem); \
    --((list)->genc_List.size); \
}

#define GENC_LIST_ELEM_FOR_EACH(head, elem) \
for(GENC_LIST_ELEM_TYPE(head)* elem = head; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_ELEM_REVERSE_FOR_EACH(tail, elem) \
for(GENC_LIST_ELEM_TYPE(tail)* elem = tail; elem != NULL; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_FOR_EACH(list, elem) \
for(GENC_LIST_ELEM_TYPE2(list)* elem = (list)->genc_List.head; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_FOR_EACH2(list, elem) \
for(elem = (list)->genc_List.head; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_REVERSE_FOR_EACH(list, type, elem) \
for(type* elem = (list)->genc_List.tail; elem != NULL; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_REVERSE_FOR_EACH2(list, elem) \
for(elem = (list)->genc_List.tail; elem != NULL; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_SUBSET_FOR_EACH(list, type, elem, start, end) \
for(type* elem = start; elem != end; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_SUBSET_FOR_EACH2(list, elem, start, end) \
for(elem = start; elem != end; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH(list, type, elem, end, start) \
for(type* elem = end; elem != start; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH2(list, elem, end, start) \
for(elem = end; elem != start; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_REMOVE_FOR_EACH(list, type, elem) \
for(type* elem = (list)->genc_List.head; (list)->genc_List.size != 0; elem = (list)->genc_List.head)

#define GENC_LIST_BEFORE(list, elem, _offset) \
for(size_t offset = 0; offset < _offset && elem != NULL; ++offset) \
    elem = GENC_LIST_ELEM_PREVIOUS(elem);

#define GENC_LIST_AFTER(list, elem, _offset) \
for(size_t offset = 0; offset < _offset && elem != NULL; ++offset) \
    elem = GENC_LIST_ELEM_NEXT(elem);

#endif
