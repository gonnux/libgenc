#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_Nstr_ciCompare.h"
static void genc_Nstr_ciCompare_test(void** state) {
    assert_int_equal(genc_Nstr_ciCompare("APPLE", sizeof("APPLE") - 1, "apple", sizeof("apple") - 1), 0);
    assert_int_equal(genc_Nstr_ciCompare("apple", sizeof("apple") - 1, "APPLE", sizeof("APPLE") - 1), 0);
    assert_true(genc_Nstr_ciCompare("apple", sizeof("apple") - 1, "apple!", sizeof("apple!") - 1) < 0);
    assert_true(genc_Nstr_ciCompare("banana", sizeof("banana") - 1, "APPLE", sizeof("APPLE") - 1) > 0);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Nstr_ciCompare_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
