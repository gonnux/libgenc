#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>
#include "../src/genc_Uint_toNstr.h"

void genc_Uint_toNstr_test(void** state) {
    char* str;
    size_t strLength = genc_Uint_toNstr(2018, 10, &str);
    assert_int_equal(strLength, sizeof("2018") - 1);
    assert_int_equal(strncmp("2018", str, sizeof("2018") - 1), 0);
    free(str);

    strLength = genc_Uint_toNstr(2018, 16, &str);
    assert_int_equal(strLength, sizeof("7E2") - 1);
    assert_int_equal(strncmp("7E2", str, sizeof("7E2") - 1), 0);
    free(str);

}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Uint_toNstr_test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
