#ifndef _GENC_MTREE_H
#define _GENC_MTREE_H

#include "genc_Map.h"

#define GENC_MTREE_NODE(type, parentType) \
struct { \
    GENC_MAP_ELEM(type); \
    struct { \
        parentType parent; \
        struct { \
            GENC_MAP(type); \
        } children; \
    } genc_Mtree_node; \
}

#define GENC_MTREE_NODE_PARENT(self) \
(self)->genc_Mtree_node.parent

#define GENC_MTREE_NODE_GET_PARENT(self) \
(self)->genc_Mtree_node.parent

#define GENC_MTREE_NODE_SET_PARENT(self, parentNode) \
(self)->genc_Mtree_node.parent = parentNode

#define GENC_MTREE_NODE_CHILDREN(self) \
(&(self)->genc_Mtree_node.children)

#define GENC_MTREE_NODE_KEY(self) \
GENC_MAP_ELEM_KEY(self)

#define GENC_MTREE_NODE_KEY_LENGTH(self) \
GENC_MAP_ELEM_KEY_LENGTH(self)

#define GENC_MTREE_NODE_INIT(self, ret) { \
    GENC_MAP_INIT(GENC_MTREE_NODE_CHILDREN(self), ret); \
}

#define GENC_MTREE_NODE_INIT2(self, childCapacity) { \
    GENC_MAP_INIT2(GENC_MTREE_NODE_CHILDREN(self), childCapacity); \
}

#define GENC_MTREE_NODE_REALLOC_CHILDREN(self, childCapacity) \
GENC_MAP_REALLOC(GENC_MTREE_NODE_CHILDREN(self), childCapacity)

#define GENC_MTREE_NODE_FREE(self) \
GENC_MAP_FREE(GENC_MTREE_NODE_CHILDREN(self))

#define GENC_MTREE_NODE_SET(self, child, oldChild) { \
    GENC_MTREE_NODE_SET_PARENT(child, self); \
    GENC_MAP_SET(GENC_MTREE_NODE_CHILDREN(self), child, oldChild); \
}

#define GENC_MTREE_NODE_GET(self, key, keyLength, elem) \
GENC_MAP_GET(GENC_MTREE_NODE_CHILDREN(self), key, keyLength, elem)

#define GENC_MTREE_NODE_SIZE(self) \
GENC_MAP_SIZE(GENC_MTREE_NODE_CHILDREN(self))

#define GENC_MTREE_NODE_FOREACH_BEGIN(self, childNode) \
GENC_MAP_FOREACH_BEGIN(GENC_MTREE_NODE_CHILDREN(self), childNode)

#define GENC_MTREE_NODE_FOREACH_END \
GENC_MAP_FOREACH_END

#define GENC_MTREE_NODE_FREE(self) \
GENC_MAP_FREE(GENC_MTREE_NODE_CHILDREN(self))

#endif
