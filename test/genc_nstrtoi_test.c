#include "genc_nstrtoi.h"
#include <stdio.h>
int main()
{
    printf("%d\n", genc_nstrtoi("1234", sizeof("1234") - 1));
    return 0;
}
