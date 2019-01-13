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
    GENC_TREE_NODE_INIT2(&node, 10);
    struct node* node2;
    for(size_t index = 0; index != 10; ++index) {
        node2 = malloc(sizeof(struct node));
        GENC_TREE_NODE_INIT(node2);
        node2->value = index * 100;
        GENC_TREE_NODE_ADD_CHILD(&node, node2);
    }
    assert_int_equal(GENC_TREE_NODE_CHILD_COUNT(&node), 10);
    for(size_t index = 0; index != 10; ++index) {
        assert_ptr_equal(GENC_TREE_NODE_GET_CHILD(&node, index)->value, index * 100);
        GENC_TREE_NODE_FREE(GENC_TREE_NODE_GET_CHILD(&node, index));
        free(GENC_TREE_NODE_GET_CHILD(&node, index));
    }
    GENC_TREE_NODE_FREE(&node);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Tree_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
