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

static void genc_ArrayList_testInsertion(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT2(&arrayList, 1);
    struct Integer element;
    int elementCount = 3;
    for(int i = 0; i < elementCount; ++i) {
        element.value = i * 100;
        GENC_ARRAY_LIST_INSERT(&arrayList, 0, element);
    }
    GENC_ARRAY_LIST_FOR_EACH(&arrayList, index) {
        element = GENC_ARRAY_LIST_GET(&arrayList, index);
        assert_int_equal(element.value, (GENC_ARRAY_LIST_SIZE(&arrayList) - index - 1) * 100);
    }
}

static void genc_ArrayList_testStack(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList);
    GENC_ARRAY_LIST_REALLOC(&arrayList, 1);
    struct Integer element;
    int elementCount = 10;
    for(int i = 0; i < elementCount; ++i) {
        element.value = i * 100;
        GENC_ARRAY_LIST_PUSH(&arrayList, element);
    }
    for(int i = 0; i < elementCount; ++i) {
        GENC_ARRAY_LIST_POP(&arrayList, &element);
        assert_int_equal(GENC_ARRAY_LIST_SIZE(&arrayList), elementCount - i - 1);
        assert_int_equal(element.value, 100 * (elementCount - i - 1));
    }
}

static void genc_ArrayList_testQueue(void** state) {
    struct Integer_ArrayList arrayList;
    GENC_ARRAY_LIST_INIT(&arrayList);
    GENC_ARRAY_LIST_REALLOC(&arrayList, 1);
    struct Integer element;
    int elementCount = 10;
    for(int i = 0; i < elementCount; ++i) {
        element.value = i * 100;
        GENC_ARRAY_LIST_PUSH(&arrayList, element);
    }
    for(int i = 0; i < elementCount; ++i) {
        GENC_ARRAY_LIST_REMOVE(&arrayList, 0, &element);
        assert_int_equal(GENC_ARRAY_LIST_SIZE(&arrayList), elementCount - i - 1);
        assert_int_equal(element.value, i * 100);
    }
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_ArrayList_testInsertion),
        cmocka_unit_test(genc_ArrayList_testStack)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
