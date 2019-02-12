#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_Alist.h"

struct Integer {
    int value;
};

struct Integer_Alist {
    GENC_ALIST(struct Integer);
};

static void genc_Alist_testRealloc(void** state) {
    struct Integer_Alist alist;
    GENC_ALIST_INIT(&alist);
    GENC_ALIST_REALLOC(&alist, 10);
    assert_int_equal(GENC_ALIST_CAPACITY(&alist), 10);
    GENC_ALIST_REALLOC(&alist, 1);
    assert_int_equal(GENC_ALIST_CAPACITY(&alist), 1);
    GENC_ALIST_FREE(&alist);
}

static void genc_Alist_testEmptyInsertion(void** state) {
    /*
    struct Integer_Alist alist;
    int elemCount = 3;
    int capacity = 1;
    GENC_ALIST_INIT2(&alist, capacity);
    assert_int_equal(GENC_ALIST_CAPACITY(&alist), capacity);
    assert_int_equal(GENC_ALIST_SIZE(&alist), 0);
    for(int i = 0; i < elemCount; ++i) {
        GENC_ALIST_PUSH_EMPTY(&alist);
    }
    assert_int_equal(GENC_ALIST_SIZE(&alist), 3);
    */
}

static void genc_Alist_testInsertion(void** state) {
    struct Integer_Alist alist;
    GENC_ALIST_INIT2(&alist, 1);
    struct Integer* elem;

    int elemCount = 3;
    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ALIST_INSERT(&alist, 0, elem);
    }
    GENC_ALIST_FOR_EACH(&alist, index) {
        elem = GENC_ALIST_RAW_GET(&alist, index);
        assert_int_equal(elem->value, (GENC_ALIST_SIZE(&alist) - index - 1) * 100);
        free(elem);
    }
    GENC_ALIST_FREE(&alist);
}

static void genc_Alist_testRemoval(void** state) {
    struct Integer_Alist alist;
    GENC_ALIST_INIT2(&alist, 1);
    struct Integer* elem;
    int elemCount = 10;

    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ALIST_PUSH(&alist, elem);
    }

    for(int i = elemCount - 1; i >= 0; --i) {
        if(GENC_ALIST_RAW_GET(&alist, i)->value % 200 != 0)
            GENC_ALIST_REMOVE(&alist, i, &elem);
    }

    GENC_ALIST_FOR_EACH(&alist, index) {
        elem = GENC_ALIST_RAW_GET(&alist, index);
        assert_int_equal(elem->value, index * 2 * 100);
        free(elem);
    }
    GENC_ALIST_FREE(&alist);
}


static void genc_Alist_testStack(void** state) {
    struct Integer_Alist alist;
    GENC_ALIST_INIT(&alist);
    GENC_ALIST_REALLOC(&alist, 1);
    struct Integer* elem;
    int elemCount = 10;
    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ALIST_PUSH(&alist, elem);
    }
    for(int i = 0; i < elemCount; ++i) {
        GENC_ALIST_POP(&alist, &elem);
        assert_int_equal(GENC_ALIST_SIZE(&alist), elemCount - i - 1);
        assert_int_equal(elem->value, 100 * (elemCount - i - 1));
        free(elem);
    }
    GENC_ALIST_FREE(&alist);
}

static void genc_Alist_testQueue(void** state) {
    struct Integer_Alist alist;
    GENC_ALIST_INIT(&alist);
    GENC_ALIST_REALLOC(&alist, 1);
    
    struct Integer* elem;
    int elemCount = 10;
    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ALIST_PUSH(&alist, elem);
    }
    
    for(int i = 0; i < elemCount; ++i) {
        GENC_ALIST_REMOVE(&alist, 0, &elem);
        assert_int_equal(GENC_ALIST_SIZE(&alist), elemCount - i - 1);
        assert_int_equal(elem->value, i * 100);
        free(elem);
    }
    GENC_ALIST_FREE(&alist);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Alist_testRealloc),
        cmocka_unit_test(genc_Alist_testEmptyInsertion),
        cmocka_unit_test(genc_Alist_testInsertion),
        cmocka_unit_test(genc_Alist_testRemoval),
        cmocka_unit_test(genc_Alist_testStack),
        cmocka_unit_test(genc_Alist_testQueue)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
