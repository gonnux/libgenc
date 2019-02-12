#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_ArrayList.h"

struct Integer {
    int value;
};

struct Integer_ArrayList {
    GENC_ARRAY_LIST(struct Integer);
};

static void genc_ArrayList_testRealloc(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList);
    GENC_ARRAY_LIST_REALLOC(&arrayList, 10);
    assert_int_equal(GENC_ARRAY_LIST_CAPACITY(&arrayList), 10);
    GENC_ARRAY_LIST_REALLOC(&arrayList, 1);
    assert_int_equal(GENC_ARRAY_LIST_CAPACITY(&arrayList), 1);
    GENC_ARRAY_LIST_FREE(&arrayList);
}

static void genc_ArrayList_testEmptyInsertion(void** state) {
    /*
    struct Integer_ArrayList arrayList;
    int elemCount = 3;
    int capacity = 1;
    GENC_ARRAY_LIST_INIT2(&arrayList, capacity);
    assert_int_equal(GENC_ARRAY_LIST_CAPACITY(&arrayList), capacity);
    assert_int_equal(GENC_ARRAY_LIST_SIZE(&arrayList), 0);
    for(int i = 0; i < elemCount; ++i) {
        GENC_ARRAY_LIST_PUSH_EMPTY(&arrayList);
    }
    assert_int_equal(GENC_ARRAY_LIST_SIZE(&arrayList), 3);
    */
}

static void genc_ArrayList_testInsertion(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT2(&arrayList, 1);
    struct Integer* elem;

    int elemCount = 3;
    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ARRAY_LIST_INSERT(&arrayList, 0, elem);
    }
    GENC_ARRAY_LIST_FOR_EACH(&arrayList, index) {
        elem = GENC_ARRAY_LIST_GET(&arrayList, index);
        assert_int_equal(elem->value, (GENC_ARRAY_LIST_SIZE(&arrayList) - index - 1) * 100);
        free(elem);
    }
    GENC_ARRAY_LIST_FREE(&arrayList);
}

static void genc_ArrayList_testRemoval(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT2(&arrayList, 1);
    struct Integer* elem;
    int elemCount = 10;

    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ARRAY_LIST_PUSH(&arrayList, elem);
    }

    for(int i = elemCount - 1; i >= 0; --i) {
        if(GENC_ARRAY_LIST_GET(&arrayList, i)->value % 200 != 0)
            GENC_ARRAY_LIST_REMOVE(&arrayList, i, &elem);
    }

    GENC_ARRAY_LIST_FOR_EACH(&arrayList, index) {
        elem = GENC_ARRAY_LIST_GET(&arrayList, index);
        assert_int_equal(elem->value, index * 2 * 100);
        free(elem);
    }
    GENC_ARRAY_LIST_FREE(&arrayList);
}


static void genc_ArrayList_testStack(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList);
    GENC_ARRAY_LIST_REALLOC(&arrayList, 1);
    struct Integer* elem;
    int elemCount = 10;
    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ARRAY_LIST_PUSH(&arrayList, elem);
    }
    for(int i = 0; i < elemCount; ++i) {
        GENC_ARRAY_LIST_POP(&arrayList, &elem);
        assert_int_equal(GENC_ARRAY_LIST_SIZE(&arrayList), elemCount - i - 1);
        assert_int_equal(elem->value, 100 * (elemCount - i - 1));
        free(elem);
    }
    GENC_ARRAY_LIST_FREE(&arrayList);
}

static void genc_ArrayList_testQueue(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList);
    GENC_ARRAY_LIST_REALLOC(&arrayList, 1);
    
    struct Integer* elem;
    int elemCount = 10;
    for(int i = 0; i < elemCount; ++i) {
        elem = malloc(sizeof(struct Integer));
        elem->value = i * 100;
        GENC_ARRAY_LIST_PUSH(&arrayList, elem);
    }
    
    for(int i = 0; i < elemCount; ++i) {
        GENC_ARRAY_LIST_REMOVE(&arrayList, 0, &elem);
        assert_int_equal(GENC_ARRAY_LIST_SIZE(&arrayList), elemCount - i - 1);
        assert_int_equal(elem->value, i * 100);
        free(elem);
    }
    GENC_ARRAY_LIST_FREE(&arrayList);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_ArrayList_testRealloc),
        cmocka_unit_test(genc_ArrayList_testEmptyInsertion),
        cmocka_unit_test(genc_ArrayList_testInsertion),
        cmocka_unit_test(genc_ArrayList_testRemoval),
        cmocka_unit_test(genc_ArrayList_testStack),
        cmocka_unit_test(genc_ArrayList_testQueue)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
