#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_strNStr.h"
static void genc_strNStr_test(void** state) {
    assert_int_equal(genc_strNStr("<<APPLE>>", "APPLE", sizeof("APPLE") - 1), 2);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_strNStr_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
