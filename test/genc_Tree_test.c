#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_Tree.h"

struct node {
    int value;
    GENC_TREE_NODE(struct node, struct node*);
};

/*
struct xnode {
    int value;
    GENC_TREE_NODE(struct xnode*, struct xnode*);
};
*/

void genc_Tree_init3_test(void** state) {
    int value = 100;
    struct node node;
    node.value = value;
    GENC_TREE_NODE_INIT3(&node, 3);
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(&node), 3);
}

void genc_Tree_test(void** state) {
    struct node node;
    node.value = 100;
    GENC_TREE_NODE_INIT2(&node, 2);
    GENC_TREE_NODE_ADD_EMPTY_CHILD(&node);
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(&node), 1);
}

void genc_Tree_test2(void** state) {
    struct node node;
    node.value = 100;
    GENC_TREE_NODE_INIT2(&node, 2);
    struct node node2;
    GENC_TREE_NODE_INIT2(&node2, 2);
    node2.value = 200;
    GENC_TREE_NODE_ADD_CHILD(&node, &node2);
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(&node), 1);
}
/*
void genc_Tree_test3(void** state) {
    struct xnode* node = malloc(sizeof(struct xnode));
    node->value = 100;
    GENC_TREE_NODE_INIT2(node, 2);
    struct xnode* node2 = malloc(sizeof(struct xnode));
    GENC_TREE_NODE_INIT2(node2, 2);
    node2->value = 200;
    GENC_TREE_NODE_ADD_CHILD(node, node2);
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(node), 1);
}
*/
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Tree_init3_test),
        cmocka_unit_test(genc_Tree_test),
        cmocka_unit_test(genc_Tree_test2),
//        cmocka_unit_test(genc_Tree_test3)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
