#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/genc_Nstr_cat.h"
#include <stdio.h>

static void genc_Nstr_cat_test(void** state) {
    char* buffer = malloc(12);
    size_t bufferCapacity = 12;
    size_t bufferSize = 0;

    assert_int_equal(genc_Nstr_cat(buffer, bufferCapacity, &bufferSize, "HELLO", 5), 0);
    assert_int_equal(bufferSize, 5);
    assert_int_equal(genc_Nstr_cat(buffer, bufferCapacity, &bufferSize, " ", 1), 0);
    assert_int_equal(bufferSize, 6);
    assert_int_equal(genc_Nstr_cat(buffer, bufferCapacity, &bufferSize, "WORLD", 5), 0);
    assert_int_equal(bufferSize, 11);
    assert_int_equal(genc_Nstr_cat(buffer, bufferCapacity, &bufferSize, "\0", 1), 0);
    assert_int_equal(bufferSize, 12);
    free(buffer);

    buffer = malloc(5);
    bufferCapacity = 5;
    bufferSize = 0;
    assert_int_equal(genc_Nstr_cat(buffer, bufferCapacity, &bufferSize, "HELLO", 5), 0);
    assert_int_equal(bufferSize, 5);
    assert_int_equal(genc_Nstr_cat(buffer, bufferCapacity, &bufferSize, " ", 1), -1);
    assert_int_equal(bufferSize, 5);
    free(buffer);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Nstr_cat_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
