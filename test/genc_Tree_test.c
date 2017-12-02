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

    
    GENC_TREE_NODE_ADD_CHILD(&node, newNode);
    GENC_TREE_NODE_ADD_CHILD(&node1, node3);

    printf("%d\n", GENC_TREE_NODE_GET_CHILD(&node1, 0).value);
    printf("%d\n", GENC_TREE_NODE_GET_CHILD(&node1, 1).value);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Tree_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
