#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_caseCompareNStr.h"
static void genc_caseCompareNStr_test(void** state) {
    assert_int_equal(genc_caseCompareNStr("APPLE", sizeof("APPLE") - 1, "apple", sizeof("apple") - 1), 0);
    assert_int_equal(genc_caseCompareNStr("apple", sizeof("apple") - 1, "APPLE", sizeof("APPLE") - 1), 0);
    assert_true(genc_caseCompareNStr("apple", sizeof("apple") - 1, "apple!", sizeof("apple!") - 1) < 0);
    assert_true(genc_caseCompareNStr("banana", sizeof("banana") - 1, "APPLE", sizeof("APPLE") - 1) > 0);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_caseCompareNStr_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
