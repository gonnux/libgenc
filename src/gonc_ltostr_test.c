#include "gonc_ltostr.h"
#include <stdio.h>
int main()
{
    char* str;
    GONC_LTOSTR(200, 10, str);
    printf("%s", str);
    return 0;
}
