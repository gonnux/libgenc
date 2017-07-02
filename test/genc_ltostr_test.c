#include "genc_ltostr.h"
#include <stdio.h>
int main()
{
    char* str;
    genc_ltostr(200, 10, &str);
    printf("%s\n", str);
    free(str);
    genc_ltostr(10, 16, &str);
    printf("%s\n", str);
    free(str);

    return 0;
}
