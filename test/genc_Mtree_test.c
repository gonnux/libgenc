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

void genc_Mtree_test(void** state) {
    int ret;
    struct node node;
    struct node child;
    struct node* oldChild;

    GENC_MTREE_NODE_INIT(&child, &ret);
    child.value = 100;
    GENC_MAP_ELEM_KEY(&child) = "HELLO";
    GENC_MAP_ELEM_KEY_LENGTH(&child) = sizeof("HELLO") - 1;

    GENC_MTREE_NODE_INIT(&node, &ret);
    GENC_MTREE_NODE_SET(&node, &child, &oldChild);
    assert_ptr_equal(oldChild, NULL);
    assert_int_equal(GENC_MTREE_NODE_SIZE(&node), 1);

    GENC_MTREE_NODE_GET(&node, "HELLO", sizeof("HELLO") - 1, &oldChild);
    assert_ptr_equal(oldChild, &child);
    GENC_MTREE_NODE_FREE(&node);
    GENC_MTREE_NODE_FREE(&child);
}

void genc_Mtree_test2(void** state) {
    int ret;
    struct node* root = malloc(sizeof(struct node));
    GENC_MTREE_NODE_INIT(root, &ret);
    struct node* child;
    struct node* child2;
    struct node* oldChild;

    child = malloc(sizeof(struct node));
    GENC_MTREE_NODE_INIT(child, &ret);
    child->value = 100;
    GENC_MAP_ELEM_KEY(child) = "apple";
    GENC_MAP_ELEM_KEY_LENGTH(child) = sizeof("apple") - 1;
    GENC_MTREE_NODE_SET(root, child, &oldChild);

    child2 = malloc(sizeof(struct node));
    GENC_MTREE_NODE_INIT(child2, &ret);
    GENC_MAP_ELEM_KEY(child2) = "apple-apple";
    GENC_MAP_ELEM_KEY_LENGTH(child2) = sizeof("apple-apple") - 1;
    GENC_MTREE_NODE_SET(child, child2, &oldChild);
    assert_int_equal(GENC_MTREE_NODE_SIZE(child), 1);

    child = malloc(sizeof(struct node));
    GENC_MTREE_NODE_INIT(child, &ret);
    child->value = 200;
    GENC_MAP_ELEM_KEY(child) = "banana";
    GENC_MAP_ELEM_KEY_LENGTH(child) = sizeof("banana") - 1;
    GENC_MTREE_NODE_SET(root, child, &oldChild);
    assert_int_equal(GENC_MTREE_NODE_SIZE(child), 0);
    assert_int_equal(GENC_MTREE_NODE_SIZE(root), 2);
}

void genc_Mtree_test3(void** state) {
    int ret;
    struct node* root = malloc(sizeof(struct node));
    struct node* child = malloc(sizeof(struct node));
    struct node* oldChild;

    GENC_MTREE_NODE_INIT(child, &ret);
    child->value = 100;
    GENC_MAP_ELEM_KEY(child) = "HELLO";
    GENC_MAP_ELEM_KEY_LENGTH(child) = sizeof("HELLO") - 1;

    GENC_MTREE_NODE_INIT(root, &ret);
    GENC_MTREE_NODE_SET(root, child, &oldChild);
    assert_ptr_equal(oldChild, NULL);
    assert_int_equal(GENC_MTREE_NODE_SIZE(root), 1);

    GENC_MTREE_NODE_GET(root, "HELLO", sizeof("HELLO") - 1, &root);
    assert_ptr_equal(root, child);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Mtree_test),
        cmocka_unit_test(genc_Mtree_test2),
        cmocka_unit_test(genc_Mtree_test3),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
