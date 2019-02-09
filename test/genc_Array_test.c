#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_Array.h"

struct Integer_Array {
    GENC_ARRAY(int);
};

static void Integer_Array_toRawArray(struct Integer_Array* array, int** rawArray, int* rawArraySize) {
    *rawArray = malloc(GENC_ARRAY_ELEM_SIZE(array) * GENC_ARRAY_SIZE(array));
    assert_non_null(rawArray);
    GENC_ARRAY_FOR_EACH(array, index) {
        GENC_ARRAY_GET2(array, index, &(*rawArray)[index]);
    }
    *rawArraySize = GENC_ARRAY_SIZE(array); 
    // assertion of arraySize greater than zero is currently omitted.
}

static void genc_Array_test(void** state) {
    struct Integer_Array integerArray;
    int rawIntegerArray[] = {1, 2, 3, 4, 5};
    int rawIntegerArraySize = sizeof(rawIntegerArray) / sizeof(int);
    GENC_ARRAY_INIT(&integerArray, rawIntegerArraySize);
    for(int i = 0; i < GENC_ARRAY_SIZE(&integerArray); ++i)
        GENC_ARRAY_SET(&integerArray, i, rawIntegerArray[i]);
    int* outputRawIntegerArray;
    int outputRawIntegerArraySize;
    Integer_Array_toRawArray(&integerArray, &outputRawIntegerArray, &outputRawIntegerArraySize);
    assert_int_equal(rawIntegerArraySize, outputRawIntegerArraySize);
    assert_memory_equal(rawIntegerArray, outputRawIntegerArray, outputRawIntegerArraySize);
    free(outputRawIntegerArray);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Array_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
