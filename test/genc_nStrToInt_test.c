#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_nStrToInt.h"

static void genc_nStrToInt_test(void** state) {
    assert_int_equal(genc_nStrToInt("1024", sizeof("1024") - 1), 1024);
    assert_int_equal(genc_nStrToInt("+12345", sizeof("+12345") - 1), 12345);
    assert_int_equal(genc_nStrToInt("-9999", sizeof("-9999") - 1), -9999);

}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_nStrToInt_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
