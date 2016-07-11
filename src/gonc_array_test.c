#include "gonc_array.h"
#include <stdio.h>

GONC_ARRAY(integer_array, int);

int main()
{
    struct integer_array ia;
    GONC_ARRAY_INIT(&ia, int, 10);
    for(int i = 0; i < (&ia)->size; ++i)
    {
        (&ia)->elements[i] = i * 100;
        printf("%d\n", (&ia)->elements[i]);
    }
}
