#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_List.h"

struct Integer {
    int value;
    GENC_LIST_ELEM(struct Integer);
};

struct Integer_List {
    GENC_LIST(struct Integer);
};
/*
static void Integer_List_toRawArray(struct Integer_List* integerList, int** rawArray, int* rawArraySize) {
    *rawArray = malloc(GENC_LIST_SIZE(integerList) * sizeof(int));
    assert_non_null(rawArray);
    int index = 0;
    GENC_LIST_FOREACH(integerList, elem) {
        (*rawArray)[index++] = elem->value;
        printf("value %d\n", elem->value);
    }
    *rawArraySize = GENC_LIST_SIZE(integerList); 
    assert_true(*rawArraySize >= 0);
    // assertion of arraySize greater than zero is currently omitted.
}
*/
static void GENC_LIST_INIT_test(void** state) {
    struct Integer_List integerList; 
    GENC_LIST_INIT(&integerList);
    assert_null(GENC_LIST_HEAD(&integerList));
    assert_null(GENC_LIST_TAIL(&integerList));
    assert_int_equal(GENC_LIST_SIZE(&integerList), 0);
}

void GENC_LIST_ELEM_INIT_test(void** state) {
    struct Integer integer;
    GENC_LIST_ELEM_INIT(&integer);
    assert_null(GENC_LIST_ELEM_NEXT(&integer));
    assert_null(GENC_LIST_ELEM_PREV(&integer));
}

void GENC_LIST_ELEM_PREPEND_test(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    GENC_LIST_ELEM_PREPEND(&integer1, &integer2);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), &integer2);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer2), &integer1);
}

void GENC_LIST_ELEM_APPEND_test(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    GENC_LIST_ELEM_APPEND(&integer1, &integer2);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), &integer2);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer2), &integer1);
}

void GENC_LIST_INSERT_BEFORE_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_HEAD(&integerList), &integer1);

    assert_non_null(GENC_LIST_HEAD(&integerList));
    assert_null(GENC_LIST_ELEM_PREV(GENC_LIST_HEAD(&integerList)));
    assert_null(GENC_LIST_ELEM_NEXT(GENC_LIST_HEAD(&integerList)));
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);

    assert_non_null(GENC_LIST_TAIL(&integerList));
    assert_null(GENC_LIST_ELEM_PREV(GENC_LIST_TAIL(&integerList)));
    assert_null(GENC_LIST_ELEM_NEXT(GENC_LIST_TAIL(&integerList)));
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);

    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_HEAD(&integerList), &integer2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);
    struct Integer integer3 = {.value = 3};

    GENC_LIST_ELEM_INIT(&integer3);
    GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_TAIL(&integerList), &integer3);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);
}

void GENC_LIST_INSERT_AFTER_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    GENC_LIST_INSERT_AFTER(&integerList, GENC_LIST_TAIL(&integerList), &integer1);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    GENC_LIST_INSERT_AFTER(&integerList, GENC_LIST_TAIL(&integerList), &integer2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);
    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEM_INIT(&integer3);
    GENC_LIST_INSERT_AFTER(&integerList, GENC_LIST_HEAD(&integerList), &integer3);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);
}

void GENC_LIST_PREPEND_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);

    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    GENC_LIST_PREPEND(&integerList, &integer1);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);

    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    GENC_LIST_PREPEND(&integerList, &integer2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 2);

    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEM_INIT(&integer3);
    GENC_LIST_PREPEND(&integerList, &integer3);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 3);
}

void GENC_LIST_APPEND_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);

    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    GENC_LIST_APPEND(&integerList, &integer1);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);

    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    GENC_LIST_APPEND(&integerList, &integer2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 2);

    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEM_INIT(&integer3);
    GENC_LIST_APPEND(&integerList, &integer3);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 3);
}

void GENC_LIST_REMOVE_test(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);

    GENC_LIST_ELEM_REMOVE(&integer1);

    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), NULL);
}

void GENC_LIST_REMOVE_test2(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);

    GENC_LIST_ELEM_APPEND(&integer1, &integer2)
    GENC_LIST_ELEM_REMOVE(&integer1);

    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer2), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer2), NULL);
}

void GENC_LIST_REMOVE_test3(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);

    GENC_LIST_ELEM_APPEND(&integer1, &integer2)
    GENC_LIST_ELEM_REMOVE(&integer2);

    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer2), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer2), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), NULL);
}

void GENC_LIST_REMOVE_test4(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEM_INIT(&integer2);

    GENC_LIST_ELEM_APPEND(&integer1, &integer2);
    GENC_LIST_ELEM_APPEND(&integer2, &integer3);
    GENC_LIST_ELEM_REMOVE(&integer1);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), NULL);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer2), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer2), &integer3);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer3), &integer2);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer3), NULL);
}

void GENC_LIST_REMOVE_test5(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEM_INIT(&integer2);

    GENC_LIST_ELEM_APPEND(&integer1, &integer2);
    GENC_LIST_ELEM_APPEND(&integer2, &integer3);
    GENC_LIST_ELEM_REMOVE(&integer2);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), &integer3);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer2), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer2), NULL);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer3), &integer1);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer3), NULL);
}

void GENC_LIST_REMOVE_test6(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEM_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEM_INIT(&integer2);
    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEM_INIT(&integer2);

    GENC_LIST_ELEM_APPEND(&integer1, &integer2);
    GENC_LIST_ELEM_APPEND(&integer2, &integer3);
    GENC_LIST_ELEM_REMOVE(&integer3);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer1), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer1), &integer2);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer2), &integer1);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer2), NULL);

    assert_ptr_equal(GENC_LIST_ELEM_PREV(&integer3), NULL);
    assert_ptr_equal(GENC_LIST_ELEM_NEXT(&integer3), NULL);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(GENC_LIST_INIT_test),
        cmocka_unit_test(GENC_LIST_ELEM_INIT_test),
        cmocka_unit_test(GENC_LIST_ELEM_PREPEND_test),
        cmocka_unit_test(GENC_LIST_ELEM_APPEND_test),
        cmocka_unit_test(GENC_LIST_INSERT_BEFORE_test),
        cmocka_unit_test(GENC_LIST_INSERT_AFTER_test),
        cmocka_unit_test(GENC_LIST_PREPEND_test),
        cmocka_unit_test(GENC_LIST_APPEND_test),
        cmocka_unit_test(GENC_LIST_REMOVE_test),
        cmocka_unit_test(GENC_LIST_REMOVE_test2),
        cmocka_unit_test(GENC_LIST_REMOVE_test3),
        cmocka_unit_test(GENC_LIST_REMOVE_test4),
        cmocka_unit_test(GENC_LIST_REMOVE_test5),
        cmocka_unit_test(GENC_LIST_REMOVE_test6),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
