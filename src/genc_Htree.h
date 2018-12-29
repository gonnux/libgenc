#ifndef _GENC_HTREE_H
#define _GENC_HTREE_H

#include "genc_HashMap.h"

#define GENC_HTREE_NODE(type, parentType) \
struct { \
    parentType parent; \
    struct { \
        GENC_HASH_MAP(type); \
    } children; \
} genc_Htree_node

#define GENC_HTREE_NODE_PARENT(node) \
(node)->genc_Htree_node.parent

#define GENC_HTREE_NODE_GET_PARENT(node) \
(node)->genc_Htree_node.parent

#define GENC_HTREE_NODE_SET_PARENT(node, parentNode) \
(node)->genc_Htree_node.parent = parentNode

#define GENC_HTREE_NODE_CHILDREN(node) \
(&(node)->genc_Htree_node.children)

#define GENC_HTREE_NODE_INIT(node) { \
    GENC_HASH_MAP_INIT(GENC_HTREE_NODE_CHILDREN);
}

#define GENC_HTREE_NODE_INIT2(node, childCapacity) { \
    GENC_HASH_MAP_INIT2(GENC_HTREE_NODE_CHILDREN(node), childCapacity); \
}

#define GENC_HTREE_NODE_INIT3(node, childCount) { \
    GENC_HASH_MAP_INIT3(GENC_HTREE_NODE_CHILDREN(node), childCount); \
}

#define GENC_HTREE_NODE_REALLOC_CHILDREN(node, childCapacity) \
GENC_HASH_MAP_REALLOC(GENC_HTREE_NODE_CHILDREN(node), childCapacity)

#define GENC_HTREE_NODE_FREE(node) \
GENC_HASH_MAP_FREE(GENC_HTREE_NODE_CHILDREN(node))

#define GENC_HTREE_NODE_ADD_CHILD(node, child) { \
    GENC_HTREE_NODE_SET_PARENT(child, node); \
    GENC_HASH_MAP_PUSH(&((node)->genc_Htree_node.children), child); \
}

#define GENC_HTREE_NODE_ADD_EMPTY_CHILD(node) { \
    GENC_HASH_MAP_PUSH_EMPTY(&((node)->genc_Htree_node.children)); \
    GENC_HTREE_NODE_SET_PARENT(&GENC_HASH_MAP_PEEK(&((node)->genc_Htree_node.children)), (node)); \
}

#define GENC_HTREE_NODE_GET_CHILD(node, index) \
GENC_HASH_MAP_GET(&((node)->genc_Htree_node.children), index)

#define GENC_HTREE_NODE_GET_CHILD_COUNT(node) \
GENC_HASH_MAP_SIZE(&((node)->genc_Htree_node.children))

#define GENC_HTREE_NODE_FOR_EACH_CHILD(node, index) \
GENC_HASH_MAP_FOR_EACH((&(node)->genc_Htree_node.children), index)

#endif
