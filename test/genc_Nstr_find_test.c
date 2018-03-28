#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_Nstr_find.h"

static void genc_Nstr_find_test(void** state) {
    assert_int_equal(genc_Nstr_find("<<APPLE>>", sizeof("<<APPLE>>") - 1, "APPLE", sizeof("APPLE") - 1), 2);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Nstr_find_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
