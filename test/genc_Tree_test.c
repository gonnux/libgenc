#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_Tree.h"

struct node {
    int value;
    GENC_TREE_NODE(struct node);
};

void genc_Tree_test(void** state) {
    int value = 100;
    struct node node;
    node.value = value;
    GENC_TREE_NODE_INIT2(&node, 2);
    GENC_TREE_NODE_ADD_EMPTY_CHILD(&node);
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(&node), 1);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Tree_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
