#include "../src/genc_nStrToInt.h"
#include <stdio.h>
int main()
{
    printf("%d\n", genc_nStrToInt("1234", sizeof("1234") - 1));
    return 0;
}
