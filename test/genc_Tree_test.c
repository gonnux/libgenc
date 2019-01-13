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


void genc_Tree_test(void** state) {
    struct node node;
    node.value = 100;
    GENC_TREE_NODE_INIT2(&node, 2);
    struct node node2;
    GENC_TREE_NODE_INIT2(&node2, 2);
    node2.value = 200;
    GENC_TREE_NODE_ADD_CHILD(&node, &node2);
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(&node), 1);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Tree_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
