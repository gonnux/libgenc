#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_compareNStr.h"
static void genc_compareNStr_test(void** state) {
    assert_int_equal(genc_compareNStr("apple", sizeof("apple") - 1, "apple", sizeof("apple") - 1), 0);
    assert_int_not_equal(genc_compareNStr("APPLE", sizeof("APPLE") - 1, "apple", sizeof("apple") - 1), 0);
    assert_int_not_equal(genc_compareNStr("apple", sizeof("apple") - 1, "APPLE", sizeof("APPLE") - 1), 0);
    assert_true(genc_compareNStr("apple", sizeof("apple") - 1, "apple!", sizeof("apple!") - 1) < 0);
    assert_true(genc_compareNStr("banana", sizeof("banana") - 1, "apple", sizeof("apple") - 1) > 0);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_compareNStr_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
