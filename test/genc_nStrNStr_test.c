#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_nStrNStr.h"
static void genc_nStrNStr_test(void** state) {
    assert_int_equal(genc_nStrNStr("APPLE", sizeof("APPLE") - 1, "<<APPLE>>", sizeof("<<APPLE>>") - 1), 2);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_nStrNStr_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
