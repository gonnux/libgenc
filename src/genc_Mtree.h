#ifndef _GENC_HTREE_H
#define _GENC_HTREE_H

#include "genc_Map.h"

#define GENC_HTREE_NODE(type, parentType) \
struct { \
    GENC_MAP_ELEMENT(type); \
    struct { \
        parentType parent; \
        struct { \
            GENC_MAP(type); \
        } children; \
    } genc_Htree_node; \
}

#define GENC_HTREE_NODE_PARENT(node) \
(node)->genc_Htree_node.parent

#define GENC_HTREE_NODE_GET_PARENT(node) \
(node)->genc_Htree_node.parent

#define GENC_HTREE_NODE_SET_PARENT(node, parentNode) \
(node)->genc_Htree_node.parent = parentNode

#define GENC_HTREE_NODE_CHILDREN(node) \
(&(node)->genc_Htree_node.children)

#define GENC_HTREE_NODE_INIT(node) { \
    GENC_MAP_INIT(GENC_HTREE_NODE_CHILDREN(node)); \
}

#define GENC_HTREE_NODE_INIT2(node, childCapacity) { \
    GENC_MAP_INIT2(GENC_HTREE_NODE_CHILDREN(node), childCapacity); \
}

#define GENC_HTREE_NODE_REALLOC_CHILDREN(node, childCapacity) \
GENC_MAP_REALLOC(GENC_HTREE_NODE_CHILDREN(node), childCapacity)

#define GENC_HTREE_NODE_FREE(node) \
GENC_MAP_FREE(GENC_HTREE_NODE_CHILDREN(node))

#define GENC_HTREE_NODE_ADD_CHILD(node, child, oldChild) { \
    GENC_HTREE_NODE_SET_PARENT(child, node); \
    GENC_MAP_SET(GENC_HTREE_NODE_CHILDREN(node), child, oldChild); \
}

#define GENC_HTREE_NODE_GET_CHILD(node, key, keyLength, element) \
GENC_MAP_GET(GENC_HTREE_NODE_CHILDREN(node), key, keyLength, element)

#define GENC_HTREE_NODE_GET_CHILD_COUNT(node) \
GENC_MAP_SIZE(GENC_HTREE_NODE_CHILDREN(node))

#define GENC_HTREE_NODE_FOR_EACH_CHILD(node, index) \
GENC_MAP_FOR_EACH(GENC_HTREE_NODE_CHILDREN(node), index)

#endif
