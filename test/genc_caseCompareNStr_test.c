#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_caseCompareNStr.h"
int main() {
    printf("%d\n", genc_caseCompareNStr("APPLE", sizeof("APPLE") - 1, "apple", sizeof("apple") - 1));
    return 0;
}
