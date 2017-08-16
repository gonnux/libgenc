#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_Array.h"

struct integer_array {
    GENC_ARRAY(int);
};

static void genc_Array_test(void** state) {
    struct integer_array ia;
    GENC_ARRAY_INIT(&ia, 10);
    for(int i = 0; i < GENC_ARRAY_SIZE(&ia); ++i)
        GENC_ARRAY_SET(&ia, i, i * 100);
    GENC_ARRAY_FOR_EACH(&ia, i)
        assert_int_equal(GENC_ARRAY_GET(&ia, i), i * 100);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_Array_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
