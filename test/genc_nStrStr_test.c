#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_nStrStr.h"
static void genc_nStrStr_test(void** state) {
    assert_int_equal(genc_nStrStr("APPLE", sizeof("APPLE") - 1, "<<APPLE>>"), 2);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_nStrStr_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
