#ifndef _GENC_LIST_H
#define _GENC_LIST_H

#define GENC_LIST_ELEM(type) \
struct { \
    type* prev; \
    type* next; \
} genc_List_elem


#define GENC_LIST_ELEM_PREV(self) \
(self)->genc_List_elem.prev

#define GENC_LIST_ELEM_NEXT(self) \
(self)->genc_List_elem.next

#define GENC_LIST_ELEM_INIT(self) \
GENC_LIST_ELEM_PREV(self) = GENC_LIST_ELEM_NEXT(self) = NULL

#define GENC_LIST_ELEM_SIZE(self) \
sizeof(*(self)->genc_List.head)

#define GENC_LIST_ELEM_TYPE(self) \
__typeof__(*(self))

#define GENC_LIST_TYPEOF_ELEM(self) \
__typeof__(*(self)->genc_List.head)

#define GENC_LIST(type) \
struct { \
    type* head; \
    type* tail; \
    size_t size; \
} genc_List

#define GENC_LIST_HEAD(self) \
(self)->genc_List.head

#define GENC_LIST_TAIL(self) \
(self)->genc_List.tail

#define GENC_LIST_SIZE(self) \
(self)->genc_List.size

#define GENC_LIST_INIT(self) { \
    GENC_LIST_HEAD(self) = GENC_LIST_TAIL(self) = NULL; \
    GENC_LIST_SIZE(self) = 0; \
}

#define GENC_LIST_ELEM_REPLACE(self, newElem) { \
    GENC_LIST_ELEM_PREV(newElem) = GENC_LIST_ELEM_PREV(self); \
    GENC_LIST_ELEM_NEXT(newElem) = GENC_LIST_ELEM_NEXT(self); \
    GENC_LIST_ELEM_PREV(GENC_LIST_ELEM_NEXT(self)) = newElem; \
    GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREV(self)) = newElem; \
}

#define GENC_LIST_ELEM_PREPEND(self, newElem) { \
    GENC_LIST_ELEM_NEXT(newElem) = self; \
    GENC_LIST_ELEM_PREV(newElem) = GENC_LIST_ELEM_PREV(self); \
    if(GENC_LIST_ELEM_PREV(self) != NULL) { \
        GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREV(self)) = newElem; \
        GENC_LIST_ELEM_PREV(self) = newElem; \
    } else \
        GENC_LIST_ELEM_PREV(self) = newElem; \
}

#define GENC_LIST_ELEM_PREPEND_TO_HEAD(self, newElem) { \
    GENC_LIST_ELEM_NEXT(newElem) = self; \
    GENC_LIST_ELEM_PREV(newElem) = NULL; \
    GENC_LIST_ELEM_PREV(self) = newElem; \
}

#define GENC_LIST_INSERT_BEFORE(self, elem, newElem) { \
    if(elem != NULL) { \
        if((elem)->genc_List_elem.prev == NULL) { \
            GENC_LIST_ELEM_PREPEND(elem, newElem); \
            GENC_LIST_HEAD(self) = newElem; \
        } else \
            GENC_LIST_ELEM_PREPEND(elem, newElem); \
    } else { \
        GENC_LIST_ELEM_NEXT(newElem) = NULL; \
        GENC_LIST_ELEM_PREV(newElem) = NULL; \
        GENC_LIST_HEAD(self) = GENC_LIST_TAIL(self) = newElem; \
    } \
    ++GENC_LIST_SIZE(self); \
}

#define GENC_LIST_PREPEND(self, elem) \
GENC_LIST_INSERT_BEFORE(self, GENC_LIST_HEAD(self), elem)

#define GENC_LIST_ELEM_APPEND(self, newElem) { \
    GENC_LIST_ELEM_PREV(newElem) = self; \
    GENC_LIST_ELEM_NEXT(newElem) = GENC_LIST_ELEM_NEXT(self); \
    if(GENC_LIST_ELEM_NEXT(self) != NULL) { \
        GENC_LIST_ELEM_PREV(GENC_LIST_ELEM_NEXT(self)) = newElem; \
        GENC_LIST_ELEM_NEXT(self) = newElem; \
    } else \
        GENC_LIST_ELEM_NEXT(self) = newElem; \
}

#define GENC_LIST_ELEM_APPEND_TO_TAIL(self, newElem) { \
    GENC_LIST_ELEM_PREV(newElem) = self; \
    GENC_LIST_ELEM_NEXT(newElem) = GENC_LIST_ELEM_NEXT(self); \
    GENC_LIST_ELEM_NEXT(self) = newElem; \
}

#define GENC_LIST_INSERT_AFTER(self, elem, newElem) { \
    if(elem != NULL) { \
        if(GENC_LIST_ELEM_NEXT(elem) == NULL) { \
            GENC_LIST_ELEM_APPEND(elem, newElem); \
            GENC_LIST_TAIL(self) = newElem; \
        } else \
            GENC_LIST_ELEM_APPEND(elem, newElem); \
    } else { \
        GENC_LIST_ELEM_PREV(newElem) = NULL; \
        GENC_LIST_ELEM_NEXT(newElem) = NULL; \
        GENC_LIST_HEAD(self) = GENC_LIST_TAIL(self) = newElem; \
    } \
    ++(GENC_LIST_SIZE(self)); \
}

#define GENC_LIST_APPEND(self, elem) \
GENC_LIST_INSERT_AFTER(self, GENC_LIST_TAIL(self), elem)

#define GENC_LIST_ELEM_REMOVE(self) { \
    if(GENC_LIST_ELEM_PREV(self) != NULL) \
        GENC_LIST_ELEM_NEXT(GENC_LIST_ELEM_PREV(self)) = GENC_LIST_ELEM_NEXT(self); \
    if(GENC_LIST_ELEM_NEXT(self) != NULL) \
        GENC_LIST_ELEM_PREV(GENC_LIST_ELEM_NEXT(self)) = GENC_LIST_ELEM_PREV(self); \
    GENC_LIST_ELEM_PREV(self) = NULL; \
    GENC_LIST_ELEM_NEXT(self) = NULL; \
}

#define GENC_LIST_REMOVE(self, elem) { \
    if(GENC_LIST_ELEM_PREV(elem) != NULL && GENC_LIST_LEMENT_NEXT(elem) == NULL) \
        GENC_LIST_TAIL(self) = GENC_LIST_ELEM_PREV(elem); \
    else if(GENC_LIST_ELEM_PREV(elem) == NULL && GENC_LIST_ELEM_NEXT(elem) != NULL) \
        GENC_LIST_HEAD(self) = GENC_LIST_ELEM_NEXT(elem); \
    else if(GENC_LIST_ELEM_PREV(elem) == NULL && GENC_LIST_ELEM_NEXT(elem) == NULL) \
        GENC_LIST_HEAD(self) = GENC_LIST_TAIL(self) = NULL; \
    GENC_LIST_ELEM_REMOVE(elem); \
    --GENC_LIST_SIZE(self); \
}

#define GENC_LIST_ELEM_FOREACH(self, elem) \
for(GENC_LIST_ELEM_TYPE(self)* elem = self; elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_ELEM_REV_FOREACH(self, elem) \
for(GENC_LIST_ELEM_TYPE(self)* elem = tail; elem != NULL; elem = GENC_LIST_ELEM_PREV(elem))

#define GENC_LIST_FOREACH(self, elem) \
for(GENC_LIST_TYPEOF_ELEM(self)* elem = GENC_LIST_HEAD(self); elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_FOREACH2(self, elem) \
for(elem = GENC_LIST_HEAD(self); elem != NULL; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_REV_FOREACH(self, type, elem) \
for(type* elem = GENC_LIST_TAIL(self); elem != NULL; elem = GENC_LIST_ELEM_PREV(elem))

#define GENC_LIST_REV_FOREACH2(self, elem) \
for(elem = GENC_LIST_TAIL(self); elem != NULL; elem = GENC_LIST_ELEM_PREV(elem))

#define GENC_LIST_SUBSET_FOREACH(self, type, elem, start, end) \
for(type* elem = start; elem != end; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_SUBSET_FOREACH2(self, elem, start, end) \
for(elem = start; elem != end; elem = GENC_LIST_ELEM_NEXT(elem))

#define GENC_LIST_REV_SUBSET_FOREACH(self, type, elem, end, start) \
for(type* elem = end; elem != start; elem = GENC_LIST_ELEM_PREV(elem))

#define GENC_LIST_REV_SUBSET_FOREACH2(self, elem, end, start) \
for(elem = end; elem != start; elem = GENC_LIST_ELEM_PREV(elem))

#define GENC_LIST_REMOVE_FOREACH(self, type, elem) \
for(type* elem = GENC_LIST_HEAD(self); GENC_LIST_SIZE(self) != 0; elem = GENC_LIST_HEAD(self))

#define GENC_LIST_BEFORE(self, elem, _offset) \
for(size_t offset = 0; offset < _offset && elem != NULL; ++offset) \
    elem = GENC_LIST_ELEM_PREV(elem);

#define GENC_LIST_AFTER(self, elem, _offset) \
for(size_t offset = 0; offset < _offset && elem != NULL; ++offset) \
    elem = GENC_LIST_ELEM_NEXT(elem);

#endif
