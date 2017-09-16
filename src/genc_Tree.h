#ifndef _GENC_TREE_H
#define _GENC_TREE_H

#define GENC_TREE_ELEMENT(type) \
struct                          \
{                               \
    type* parent;               \
    size_t childCapacity;       \
    size_t childCount;          \
    type** children;            \
} genc_Tree_element

#define GENC_TREE_ELEMENT_INIT(element, childCapacity)                           \
(element)->genc_Tree_element.parent = NULL;                                      \
(element)->genc_Tree_element.childCapacity = childCapacity;                      \
(element)->genc_Tree_element.children = malloc(childCapacity * sizeof(element));

#define GENC_TREE_ELEMENT_PARENT(element) \
(element)->genc_Tree_element.parent

#define GENC_TREE_ELEMENT_CHILD_COUNT(element) \
(element)->genc_Tree_element.childCount;

#define GENC_TREE_ELEMENT_CHILD(element, index) \
(element)->genc_Tree_element.children[index]

#define GENC_TREE_ELEMENT_ADD_CHILD(element, child)                                        \
if((element)->genc_Tree_element.childCount < (element)->genc_Tree_element.childCapacity) { \
    (element)->genc_Tree_element.children[childrenCount] = child;                          \
    (child)->genc_Tree_element.parent = element;                                           \
    ++((element)->genc_Tree_element.childCount)                                            \
}

#define GENC_TREE(type) \
struct {                \
    type* root;         \
} genc_Tree

#define GENC_TREE_INIT(list)                                \
do                                                          \
{                                                           \
    (list)->genc_Tree.root = NULL;                          \
    (list)->genc_Tree.size = 0;                             \
}                                                           \
while(0)

#define GENC_TREE_ROOT(list) \
(list)->genc_Tree.root

#define GENC_TREE_SIZE(list) \
(list)->genc_Tree.size

#endif
