#include "gon_c_nstrtoi.h"
#include <stdio.h>
int main()
{
    printf("%d\n", gon_c_nstrtoi("1234", sizeof("1234") - 1));
    return 0;
}
