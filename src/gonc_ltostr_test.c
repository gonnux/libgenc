#include "gonc_ltostr.h"
#include <stdio.h>
int main()
{
    char* str;
    ltostr(200, 10, &str);
    printf("%s", str);
    free(str);
    return 0;
}
