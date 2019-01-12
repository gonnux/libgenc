#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#include "genc_ArrayList.h"

#define GENC_TREE_NODE(type, parentType) \
struct { \
    parentType parent; \
    struct { \
        GENC_ARRAY_LIST(type); \
    } children; \
} genc_Tree_node

#define GENC_TREE_NODE_PARENT(node) \
(node)->genc_Tree_node.parent

#define GENC_TREE_NODE_GET_PARENT(node) \
(node)->genc_Tree_node.parent

#define GENC_TREE_NODE_SET_PARENT(node, parentNode) \
(node)->genc_Tree_node.parent = parentNode

#define GENC_TREE_NODE_CHILDREN(node) \
(&(node)->genc_Tree_node.children)

#define GENC_TREE_NODE_INIT(node) { \
    GENC_ARRAY_LIST_INIT(GENC_TREE_NODE_CHILDREN(node)); \
}

#define GENC_TREE_NODE_INIT2(node, childCapacity) { \
    GENC_ARRAY_LIST_INIT2(GENC_TREE_NODE_CHILDREN(node), childCapacity); \
}

#define GENC_TREE_NODE_INIT3(node, childCount) { \
    GENC_ARRAY_LIST_INIT3(GENC_TREE_NODE_CHILDREN(node), childCount); \
}

#define GENC_TREE_NODE_REALLOC_CHILDREN(node, childCapacity) \
GENC_ARRAY_LIST_REALLOC(GENC_TREE_NODE_CHILDREN(node), childCapacity)

#define GENC_TREE_NODE_FREE(node) \
GENC_ARRAY_LIST_FREE(GENC_TREE_NODE_CHILDREN(node))

#define GENC_TREE_NODE_ADD_CHILD(node, child) { \
    GENC_TREE_NODE_SET_PARENT(child, node); \
    GENC_ARRAY_LIST_PUSH(GENC_TREE_NODE_CHILDREN(node), child); \
}

#define GENC_TREE_NODE_ADD_EMPTY_CHILD(node) { \
    GENC_ARRAY_LIST_PUSH_EMPTY(GENC_TREE_NODE_CHILDREN(node)); \
    GENC_TREE_NODE_SET_PARENT(&GENC_ARRAY_LIST_PEEK(GENC_TREE_NODE_CHILDREN(node)), node); \
}

#define GENC_TREE_NODE_GET_CHILD(node, index) \
GENC_ARRAY_LIST_GET(GENC_TREE_NODE_CHILDREN(node), index)

#define GENC_TREE_NODE_CHILD_COUNT(node) \
GENC_ARRAY_LIST_SIZE(GENC_TREE_NODE_CHILDREN(node))

#define GENC_TREE_NODE_FOR_EACH_CHILD(node, index) \
GENC_ARRAY_LIST_FOR_EACH(GENC_TREE_NODE_CHILDREN(node), index)

#endif
