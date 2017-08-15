#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_String.h"
static void genc_String_test(void** state) {
    struct genc_String string1;
    GENC_STRING_SET(&string1, "Hello World!", false);
    assert_int_equal(GENC_STRING_GET_LENGTH(&string1), sizeof("Hello World!") - 1);
    assert_false(GENC_STRING_IS_FREEABLE(&string1));
    assert_string_equal(GENC_STRING_GET_CHARS(&string1), "Hello World!");
    GENC_STRING_FREE(&string1);
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_String_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
