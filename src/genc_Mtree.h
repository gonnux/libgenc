#ifndef _GENC_MTREE_H
#define _GENC_MTREE_H

#include "genc_Map.h"

#define GENC_MTREE_NODE(type, parentType) \
struct { \
    GENC_MAP_ELEMENT(type); \
    struct { \
        parentType parent; \
        struct { \
            GENC_MAP(type); \
        } children; \
    } genc_Mtree_node; \
}

#define GENC_MTREE_NODE_PARENT(node) \
(node)->genc_Mtree_node.parent

#define GENC_MTREE_NODE_GET_PARENT(node) \
(node)->genc_Mtree_node.parent

#define GENC_MTREE_NODE_SET_PARENT(node, parentNode) \
(node)->genc_Mtree_node.parent = parentNode

#define GENC_MTREE_NODE_CHILDREN(node) \
(&(node)->genc_Mtree_node.children)

#define GENC_MTREE_NODE_INIT(node) { \
    GENC_MAP_INIT(GENC_MTREE_NODE_CHILDREN(node)); \
}

#define GENC_MTREE_NODE_INIT2(node, childCapacity) { \
    GENC_MAP_INIT2(GENC_MTREE_NODE_CHILDREN(node), childCapacity); \
}

#define GENC_MTREE_NODE_REALLOC_CHILDREN(node, childCapacity) \
GENC_MAP_REALLOC(GENC_MTREE_NODE_CHILDREN(node), childCapacity)

#define GENC_MTREE_NODE_FREE(node) \
GENC_MAP_FREE(GENC_MTREE_NODE_CHILDREN(node))

#define GENC_MTREE_NODE_ADD_CHILD(node, child, oldChild) { \
    GENC_MTREE_NODE_SET_PARENT(child, node); \
    GENC_MAP_SET(GENC_MTREE_NODE_CHILDREN(node), child, oldChild); \
}

#define GENC_MTREE_NODE_GET_CHILD(node, key, keyLength, element) \
GENC_MAP_GET(GENC_MTREE_NODE_CHILDREN(node), key, keyLength, element)

#define GENC_MTREE_NODE_GET_CHILD_COUNT(node) \
GENC_MAP_SIZE(GENC_MTREE_NODE_CHILDREN(node))

#define GENC_MTREE_NODE_FOR_EACH_CHILD(node, index) \
GENC_MAP_FOR_EACH(GENC_MTREE_NODE_CHILDREN(node), index)

#endif
