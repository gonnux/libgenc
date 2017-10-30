#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#include <libgenc/genc_ArrayList.h>

#define GENC_TREE_NODE(type)   \
struct {                       \
    struct {                   \
        GENC_ARRAY_LIST(type); \
    } children;                \
} genc_Tree_node

#define GENC_TREE_NODE_INIT(node, capacity) \
GENC_ARRAY_LIST_INIT((&(node)->genc_Tree_node.children), capacity)

#define GENC_TREE_NODE_ADD_CHILD(node, child) \
GENC_ARRAY_LIST_PUSH(&((node)->genc_Tree_node.children), child)

#define GENC_TREE_NODE_GET_CHILD(node, index) \
GENC_ARRAY_LIST_GET(&((node)->genc_Tree_node.children), index)

#define GENC_TREE_NODE_CHILD_COUNT(node) \
GENC_ARRAY_LIST_SIZE(&((node)->genc_Tree_node.children))

#define GENC_TREE_BFS_HISTORY(type) \
struct {                            \
    GENC_LIST(type);                \
} genc_Tree_bfsHistory

#define GENC_TREE_BFS_HISTORY_INIT(history) \
GENC_LIST_INIT(&((history)->genc_Tree_bfsHistory))

#define GENC_TREE_BFS_HISTORY_SIZE(history) \
GENC_LIST_SIZE(&((history)->genc_Tree_bfsHistory))

#define GENC_TREE_BFS_HISTORY_ELEMENT(type) \
struct {                                 \
    GENC_LIST_ELEMENT(type);             \
    type* node;                          \
} genc_Tree_bfsHistoryElement;

#define GENC_TREE_BFS_HISTORY_ELEMENT_NODE(historyElement) \
(historyElement)->genc_Tree_bfsHistoryElement.node

#define GENC_TREE_BFS_HISTORY_ELEMENT_INIT(historyElement) \
GENC_LIST_ELEMENT_INIT(&((historyElement)->genc_Tree_bfsHistoryElement))

#define GENC_TREE_NODE_BFS_BEGIN(type, node, queue) \
do { \
    struct { \
        GENC_TREE_BFS_HISTORY(type); \
    } history; \
    GENC_TREE_BFS_HISTORY_INIT(&history); \
    struct { \
        GENC_TREE_BFS_HISTORY_ELEMENT(type); \
    }* historyElement; \
    do { \
        for(int index = 0; index < GENC_TREE_NODE_CHILD_COUNT(historyElement); ++index) { \
            type* node = GENC_TREE_NODE_GET_CHILD(node, index); \
            historyElement = malloc(sizeof(struct GENC_TREE_NODE_BFS_HISTORY(type)); \
            GENC_TREE_BFS_HISTORY_ELEMENT_INIT(historyElement); \
        } \
    } while(GENC_TREE_BFS_HISTORY_SIZE(history) > 0)

#define GENC_TREE_NODE_BFS_END(type, node, queue) \
} while(0)

#define GENC_TREE_RBFS_BEGIN(node, queue)
#define GENC_TREE_RBFS_END(node, queue)

#define GENC_TREE_DFS_BEGIN(node, stack)
#define GENC_TREE_DFS_END(node, stack)

#endif
