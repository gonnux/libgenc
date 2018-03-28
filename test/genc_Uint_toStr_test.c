#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_Uint_toStr.h"
int main() {
    char* str;
    genc_Uint_toStr(200, 10, &str);
    printf("%s\n", str);
    free(str);
    genc_Uint_toStr(10, 16, &str);
    printf("%s\n", str);
    free(str);

    return 0;
}
