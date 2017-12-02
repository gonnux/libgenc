#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#include "genc_ArrayList.h"

#define GENC_TREE_NODE(type)   \
struct {                       \
    type* parent;              \
    struct {                   \
        GENC_ARRAY_LIST(type); \
    } children;                \
} genc_Tree_node

#define GENC_TREE_NODE_INIT(node)                           \
do {                                                        \
    (node)->genc_Tree_node.parent = NULL;                   \
    GENC_ARRAY_LIST_INIT(&(node)->genc_Tree_node.children); \
} while(0)

#define GENC_TREE_NODE_INIT_CHILDREN(node, capacity) \
GENC_ARRAY_LIST_REALLOC((&(node)->genc_Tree_node.children), capacity)

#define GENC_TREE_NODE_INIT2(node, capacity)      \
do {                                              \
    GENC_TREE_NODE_INIT(node);                    \
    GENC_TREE_NODE_INIT_CHILDREN(node, capacity); \
} while(0)

#define GENC_TREE_NODE_GET_PARENT(node) \
(node)->genc_Tree_node.parent;

#define GENC_TREE_NODE_SET_PARENT(node, parentNode) \
(node)->genc_Tree_node.parent = parentNode;

#define GENC_TREE_NODE_ADD_CHILD(node, child) \
GENC_ARRAY_LIST_PUSH(&((node)->genc_Tree_node.children), child)

#define GENC_TREE_NODE_ADD_EMPTY_CHILD(node) \
GENC_ARRAY_LIST_PUSH_EMPTY(&((node)->genc_Tree_node.children))

#define GENC_TREE_NODE_GET_CHILD(node, index) \
GENC_ARRAY_LIST_GET(&((node)->genc_Tree_node.children), index)

#define GENC_TREE_NODE_CHILD_COUNT(node) \
GENC_ARRAY_LIST_SIZE(&((node)->genc_Tree_node.children))

#define GENC_TREE_NODE_FOR_EACH_CHILD(node, index) \
GENC_ARRAY_LIST_FOR_EACH((&(node)->genc_Tree_node.children), index)

#define GENC_TREE_NODE_GET_CHILDREN(node) \
(&(node)->genc_Tree_node.children)

#endif
