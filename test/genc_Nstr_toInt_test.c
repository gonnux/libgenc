#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_Nstr_toInt.h"

static void genc_Nstr_toInt_test(void** state) {
    assert_int_equal(genc_Nstr_toInt("1024", sizeof("1024") - 1), 1024);
    assert_int_equal(genc_Nstr_toInt("+12345", sizeof("+12345") - 1), 12345);
    assert_int_equal(genc_Nstr_toInt("-9999", sizeof("-9999") - 1), -9999);

}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Nstr_toInt_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
