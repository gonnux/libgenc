#include "gon_c_ltostr.h"
#include <stdio.h>
int main()
{
    char* str;
    gon_c_ltostr(200, 10, &str);
    printf("%s\n", str);
    free(str);
    gon_c_ltostr(10, 16, &str);
    printf("%s\n", str);
    free(str);

    return 0;
}
