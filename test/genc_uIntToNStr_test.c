#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_uIntToNStr.h"
int main() {
    char* str;
    genc_uIntToNStr(200, 10, &str);
    printf("%s\n", str);
    free(str);
    genc_uIntToNStr(10, 16, &str);
    printf("%s\n", str);
    free(str);

    return 0;
}
