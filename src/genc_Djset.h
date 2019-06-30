#ifndef _GENC_DJSET_H
#define _GENC_DJSET_H

#define GENC_DJSET_ELEM(type) \
struct { \
    type* parent; \
} genc_Djset_elem

#define GENC_DJSET_ELEM_TYPE(self) \
__typeof__(*(self))

#define GENC_DJSET_ELEM_PARENT(self) \
(self)->genc_Djset_elem.parent

#define GENC_DJSET_ELEM_INIT(self) { \
    GENC_DJSET_ELEM_PARENT(self) = self; \
}

#define GENC_DJSET_ELEM_FIND(self, ret, ret2) { \
    GENC_DJSET_ELEM_TYPE(self)* elem = self; \
    size_t idx = 0; \
    for(; GENC_DJSET_ELEM_PARENT(elem) != elem; elem = GENC_DJSET_ELEM_PARENT(elem), ++idx) \
    GENC_DJSET_ELEM_PARENT(self) = elem; \
    *(ret) = elem; \
    if(ret2 != NULL) \
      *(ret2) = idx; \
}

#define GENC_DJSET_ELEM_UNION(elem1, elem2) { \
    GENC_DJSET_ELEM_TYPE(elem1)* rep1, rep2; \
    size_t rank1, rank2; \
    GENC_DJSET_ELEM_FIND(elem1, &rep1, &rank1); \
    GENC_DJSET_ELEM_FIND(elem2, &rep2, &rank2); \
    if(rank1 <= rank2) \
      GENC_DJSET_ELEM_PARENT(rep1) = rep2; \
    else \
      GENC_DJSET_ELEM_PARENT(rep2) = rep1; \
}

#endif
