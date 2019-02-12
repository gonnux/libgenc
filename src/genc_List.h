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

#define GENC_LIST_ELEM_SIZE(self) \
sizeof(*(self)->genc_List.head)

#define GENC_LIST_ELEM_TYPE(elem) \
typeof(*(elem))

#define GENC_LIST_ELEM_TYPE2(self) \
typeof(*(self)->genc_List.head)

#define GENC_LIST(type) \
struct { \
    type* head; \
    type* tail; \
    size_t size; \
} genc_List

#define GENC_LIST_INIT(self) { \
    (self)->genc_List.head = (self)->genc_List.tail = NULL; \
    (self)->genc_List.size = 0; \
}

#define GENC_LIST_HEAD(self) \
(self)->genc_List.head

#define GENC_LIST_TAIL(self) \
(self)->genc_List.tail

#define GENC_LIST_SIZE(self) \
(self)->genc_List.size

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

#define GENC_LIST_INSERT_BEFORE(self, elem, newElem) { \
    if(elem != NULL) { \
        if((elem)->genc_List_elem.previous == NULL) { \
            GENC_LIST_ELEM_PREPEND(elem, newElem); \
            (self)->genc_List.head = newElem; \
        } else \
            GENC_LIST_ELEM_PREPEND(elem, newElem); \
    } else { \
        GENC_LIST_ELEM_NEXT(newElem) = NULL; \
        GENC_LIST_ELEM_PREVIOUS(newElem) = NULL; \
        (self)->genc_List.head = (self)->genc_List.tail = newElem; \
    } \
    ++((self)->genc_List.size); \
}

#define GENC_LIST_PREPEND(self, elem) \
GENC_LIST_INSERT_BEFORE(self, (self)->genc_List.head, elem)

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

#define GENC_LIST_INSERT_AFTER(self, elem, newElem) { \
    if(elem != NULL) { \
        if(GENC_LIST_ELEM_NEXT(elem) == NULL) { \
            GENC_LIST_ELEM_APPEND(elem, newElem); \
            (self)->genc_List.tail = newElem; \
        } else \
            GENC_LIST_ELEM_APPEND(elem, newElem); \
    } else { \
        GENC_LIST_ELEM_PREVIOUS(newElem) = NULL; \
        GENC_LIST_ELEM_NEXT(newElem) = NULL; \
        (self)->genc_List.head = (self)->genc_List.tail = newElem; \
    } \
    ++((self)->genc_List.size); \
}

#define GENC_LIST_APPEND(self, elem) \
GENC_LIST_INSERT_AFTER(self, (self)->genc_List.tail, elem)

#define GENC_LIST_ELEM_REMOVE(elem) { \
    if(GENC_LIST_ELEM_PREVIOUS(elem) != NULL) \
        GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREVIOUS(elem)) = GENC_LIST_ELEM_NEXT(elem); \
    if(GENC_LIST_ELEM_NEXT(elem) != NULL) \
        GENC_LIST_ELEM_PREVIOUS(GENC_LIST_ELEM_NEXT(elem)) = GENC_LIST_ELEM_PREVIOUS(elem); \
    GENC_LIST_ELEM_PREVIOUS(elem) = NULL; \
    GENC_LIST_ELEM_NEXT(elem) = NULL; \
}

#define GENC_LIST_REMOVE(self, elem) { \
    if(GENC_LIST_ELEM_PREVIOUS(elem) != NULL && GENC_LIST_LEMENT_NEXT(elem) == NULL) \
        (self)->genc_List.tail = GENC_LIST_ELEM_PREVIOUS(elem); \
    else if(GENC_LIST_ELEM_PREVIOUS(elem) == NULL && GENC_LIST_ELEM_NEXT(elem) != NULL) \
        (self)->genc_List.head = GENC_LIST_ELEM_NEXT(elem); \
    else if(GENC_LIST_ELEM_PREVIOUS(elem) == NULL && GENC_LIST_ELEM_NEXT(elem) == NULL) \
        (self)->genc_List.head = (self)->genc_List.tail = NULL; \
    GENC_LIST_ELEM_REMOVE(elem); \
    --((self)->genc_List.size); \
}

#define GENC_LIST_ELEM_FOR_EACH(head, elem) \
for(GENC_LIST_ELEM_TYPE(head)* elem = head; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_ELEM_REVERSE_FOR_EACH(tail, elem) \
for(GENC_LIST_ELEM_TYPE(tail)* elem = tail; elem != NULL; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_FOR_EACH(self, elem) \
for(GENC_LIST_ELEM_TYPE2(self)* elem = (self)->genc_List.head; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_FOR_EACH2(self, elem) \
for(elem = (self)->genc_List.head; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_REVERSE_FOR_EACH(self, type, elem) \
for(type* elem = (self)->genc_List.tail; elem != NULL; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_REVERSE_FOR_EACH2(self, elem) \
for(elem = (self)->genc_List.tail; elem != NULL; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_SUBSET_FOR_EACH(self, type, elem, start, end) \
for(type* elem = start; elem != end; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_SUBSET_FOR_EACH2(self, elem, start, end) \
for(elem = start; elem != end; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH(self, type, elem, end, start) \
for(type* elem = end; elem != start; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_REVERSE_SUBSET_FOR_EACH2(self, elem, end, start) \
for(elem = end; elem != start; elem = GENC_LIST_ELEM_PREVIOUS(elem))

#define GENC_LIST_REMOVE_FOR_EACH(self, type, elem) \
for(type* elem = (self)->genc_List.head; (self)->genc_List.size != 0; elem = (self)->genc_List.head)

#define GENC_LIST_BEFORE(self, elem, _offset) \
for(size_t offset = 0; offset < _offset && elem != NULL; ++offset) \
    elem = GENC_LIST_ELEM_PREVIOUS(elem);

#define GENC_LIST_AFTER(self, elem, _offset) \
for(size_t offset = 0; offset < _offset && elem != NULL; ++offset) \
    elem = GENC_LIST_ELEM_NEXT(elem);

#endif
