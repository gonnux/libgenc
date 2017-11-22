#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_Tree.h"

void genc_Tree_test(void** state) {
    struct node {
        GENC_TREE_NODE(struct node);
        int value;
    };
    
    struct node node1 = {.value = 100};
    struct node node2 = {.value = 200};
    struct node node3 = {.value = 300};

    GENC_TREE_NODE_INIT(&node1);
    GENC_TREE_NODE_INIT_CHILDREN(&node1, 10);
    GENC_TREE_NODE_INIT(&node2);
    GENC_TREE_NODE_INIT_CHILDREN(&node2, 10);
    GENC_TREE_NODE_INIT(&node3);
    GENC_TREE_NODE_INIT_CHILDREN(&node3, 10);


    GENC_TREE_NODE_ADD_CHILD(&node1, node2);
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
