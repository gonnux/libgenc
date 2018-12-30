#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_Mtree.h"

struct node {
    int value;
    GENC_MTREE_NODE(struct node, struct node*);
};

void genc_Tree_test(void** state) {
    struct node node;
    struct node child;

    struct node* oldChild;
    child.value = 100;
    GENC_MAP_ELEMENT_KEY(&child) = "HELLO";
    GENC_MAP_ELEMENT_KEY_LENGTH(&child) = sizeof("HELLO") - 1;

    GENC_MTREE_NODE_INIT(&node);
    GENC_MTREE_NODE_ADD_CHILD(&node, &child, &oldChild);
    assert_int_equal(GENC_MTREE_NODE_GET_CHILD_COUNT(&node), 1);
    GENC_MTREE_NODE_GET_CHILD(&node, "HELLO", sizeof("HELLO") - 1, &oldChild);
    assert_ptr_equal(oldChild, &child);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Tree_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
