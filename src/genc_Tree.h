#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#include "genc_Alist.h"

#define GENC_TREE_NODE(type, parentType) \
struct { \
    parentType parent; \
    struct { \
        GENC_ALIST(type); \
    } children; \
} genc_Tree_node

#define GENC_TREE_NODE_PARENT(self) \
(self)->genc_Tree_node.parent

#define GENC_TREE_NODE_GET_PARENT(self) \
(self)->genc_Tree_node.parent

#define GENC_TREE_NODE_SET_PARENT(self, parentNode) \
(self)->genc_Tree_node.parent = parentNode

#define GENC_TREE_NODE_CHILDREN(self) \
(&(self)->genc_Tree_node.children)

#define GENC_TREE_NODE_INIT(self) { \
    GENC_ALIST_INIT(GENC_TREE_NODE_CHILDREN(self)); \
}

#define GENC_TREE_NODE_INIT2(self, childCapacity) { \
    GENC_ALIST_INIT2(GENC_TREE_NODE_CHILDREN(self), childCapacity); \
}

#define GENC_TREE_NODE_REALLOC_CHILDREN(self, childCapacity) \
GENC_ALIST_REALLOC(GENC_TREE_NODE_CHILDREN(self), childCapacity)

#define GENC_TREE_NODE_FREE(self) \
GENC_ALIST_FREE(GENC_TREE_NODE_CHILDREN(self))

#define GENC_TREE_NODE_ADD(self, child) { \
    GENC_TREE_NODE_SET_PARENT(child, self); \
    GENC_ALIST_PUSH(GENC_TREE_NODE_CHILDREN(self), child); \
}

#define GENC_TREE_NODE_RAW_GET(self, idx) \
GENC_ALIST_RAW_GET(GENC_TREE_NODE_CHILDREN(self), idx)

#define GENC_TREE_NODE_GET(self, idx, child) \
GENC_ALIST_GET(GENC_TREE_NODE_CHILDREN(self), idx, child)

#define GENC_TREE_NODE_SIZE(self) \
GENC_ALIST_SIZE(GENC_TREE_NODE_CHILDREN(self))

#define GENC_TREE_NODE_FOREACH(self, idx) \
GENC_ALIST_FOREACH(GENC_TREE_NODE_CHILDREN(self), idx)

#endif
