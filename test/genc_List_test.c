#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_List.h"

struct Integer {
    int value;
    GENC_LIST_ELEMENT(struct Integer);
};

struct Integer_List {
    GENC_LIST(struct Integer);
};

static void Integer_List_toRawArray(struct Integer_List* integerList, int** rawArray, int* rawArraySize) {
    *rawArray = malloc(GENC_LIST_SIZE(integerList) * sizeof(int));
    assert_non_null(rawArray);
    int index = 0;
    GENC_LIST_FOR_EACH(integerList, element) {
        (*rawArray)[index++] = element->value;
printf("value %d\n", element->value);
    }
    *rawArraySize = GENC_LIST_SIZE(integerList); 
    assert_true(*rawArraySize >= 0);
    // assertion of arraySize greater than zero is currently omitted.
}

static void GENC_LIST_INIT_test(void** state) {
    struct Integer_List integerList; 
    GENC_LIST_INIT(&integerList);
    assert_null(GENC_LIST_HEAD(&integerList));
    assert_null(GENC_LIST_TAIL(&integerList));
    assert_int_equal(GENC_LIST_SIZE(&integerList), 0);
}

void GENC_LIST_ELEMENT_INIT_test(void** state) {
    struct Integer integer;
    GENC_LIST_ELEMENT_INIT(&integer);
    assert_null(GENC_LIST_ELEMENT_NEXT(&integer));
    assert_null(GENC_LIST_ELEMENT_PREVIOUS(&integer));
}

void GENC_LIST_ELEMENT_PREPEND_test(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEMENT_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEMENT_INIT(&integer2);
    GENC_LIST_ELEMENT_PREPEND(&integer1, &integer2);
    assert_ptr_equal(GENC_LIST_ELEMENT_PREVIOUS(&integer1), &integer2);
    assert_ptr_equal(GENC_LIST_ELEMENT_NEXT(&integer2), &integer1);
}

void GENC_LIST_ELEMENT_APPEND_test(void** state) {
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEMENT_INIT(&integer1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEMENT_INIT(&integer2);
    GENC_LIST_ELEMENT_APPEND(&integer1, &integer2);
    assert_ptr_equal(GENC_LIST_ELEMENT_NEXT(&integer1), &integer2);
    assert_ptr_equal(GENC_LIST_ELEMENT_PREVIOUS(&integer2), &integer1);
}

void GENC_LIST_INSERT_BEFORE_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEMENT_INIT(&integer1);
    GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_HEAD(&integerList), &integer1);

    assert_non_null(GENC_LIST_HEAD(&integerList));
    assert_null(GENC_LIST_ELEMENT_PREVIOUS(GENC_LIST_HEAD(&integerList)));
    assert_null(GENC_LIST_ELEMENT_NEXT(GENC_LIST_HEAD(&integerList)));
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);

    assert_non_null(GENC_LIST_TAIL(&integerList));
    assert_null(GENC_LIST_ELEMENT_PREVIOUS(GENC_LIST_TAIL(&integerList)));
    assert_null(GENC_LIST_ELEMENT_NEXT(GENC_LIST_TAIL(&integerList)));
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);

    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEMENT_INIT(&integer2);
    GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_HEAD(&integerList), &integer2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);
    struct Integer integer3 = {.value = 3};

    GENC_LIST_ELEMENT_INIT(&integer3);
    GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_TAIL(&integerList), &integer3);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);
}

void GENC_LIST_INSERT_AFTER_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);
    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEMENT_INIT(&integer1);
    GENC_LIST_INSERT_AFTER(&integerList, GENC_LIST_TAIL(&integerList), &integer1);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);
    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEMENT_INIT(&integer2);
    GENC_LIST_INSERT_AFTER(&integerList, GENC_LIST_TAIL(&integerList), &integer2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);
    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEMENT_INIT(&integer3);
    GENC_LIST_INSERT_AFTER(&integerList, GENC_LIST_HEAD(&integerList), &integer3);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);
}

void GENC_LIST_PREPEND_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);

    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEMENT_INIT(&integer1);
    GENC_LIST_PREPEND(&integerList, &integer1);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 1);

    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEMENT_INIT(&integer2);
    GENC_LIST_PREPEND(&integerList, &integer2);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 2);

    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEMENT_INIT(&integer3);
    GENC_LIST_PREPEND(&integerList, &integer3);
    assert_int_equal(GENC_LIST_HEAD(&integerList)->value, 3);
}

void GENC_LIST_APPEND_test(void** state) {
    struct Integer_List integerList;
    GENC_LIST_INIT(&integerList);

    struct Integer integer1 = {.value = 1};
    GENC_LIST_ELEMENT_INIT(&integer1);
    GENC_LIST_APPEND(&integerList, &integer1);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 1);

    struct Integer integer2 = {.value = 2};
    GENC_LIST_ELEMENT_INIT(&integer2);
    GENC_LIST_APPEND(&integerList, &integer2);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 2);

    struct Integer integer3 = {.value = 3};
    GENC_LIST_ELEMENT_INIT(&integer3);
    GENC_LIST_APPEND(&integerList, &integer3);
    assert_int_equal(GENC_LIST_TAIL(&integerList)->value, 3);
}


void genc_List_test(void** state) {
    struct Integer_List integerList;
/*
    GENC_LIST_INIT(&integerList);
    struct Integer* element = NULL;
    int rawIntegerArray[] = {1, 2, 3, 4, 5};
    int rawIntegerArraySize = sizeof(rawIntegerArray) / sizeof(int);
    for(int index = 0; index < rawIntegerArraySize; ++index) {
        element = malloc(sizeof(struct Integer));
        GENC_LIST_ELEMENT_INIT(element);
        element->value = rawIntegerArray[index];
        GENC_LIST_INSERT_BEFORE(&integerList, GENC_LIST_HEAD(&integerList), element);
    }
    int* outputRawIntegerArray;
    int outputRawIntegerArraySize;
    Integer_List_toRawArray(&integerList, &outputRawIntegerArray, &outputRawIntegerArraySize);
    assert_int_equal(rawIntegerArraySize, outputRawIntegerArraySize);
    assert_memory_equal(rawIntegerArray, outputRawIntegerArray, outputRawIntegerArraySize);
    free(outputRawIntegerArray);
*/
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(GENC_LIST_INIT_test),
        cmocka_unit_test(GENC_LIST_ELEMENT_INIT_test),
        cmocka_unit_test(GENC_LIST_ELEMENT_PREPEND_test),
        cmocka_unit_test(GENC_LIST_ELEMENT_APPEND_test),
        cmocka_unit_test(GENC_LIST_INSERT_BEFORE_test),
        cmocka_unit_test(GENC_LIST_INSERT_AFTER_test),
        cmocka_unit_test(GENC_LIST_PREPEND_test),
        cmocka_unit_test(GENC_LIST_APPEND_test),
        cmocka_unit_test(genc_List_test)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
