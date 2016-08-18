#include "gonc_ltostr.h"
#include <stdio.h>
int main()
{
    char* str;
    gonc_ltostr(200, 10, &str);
    printf("%s\n", str);
    free(str);
    gonc_ltostr(10, 16, &str);
    printf("%s\n", str);
    free(str);

    return 0;
}
