#include "gonc_array.h"
#include <stdio.h>

GONC_ARRAY(integer_array, int);

int main()
{
    struct integer_array ia;
    GONC_ARRAY_INIT(&ia, int, 10);
    for(int i = 0; i < (&ia)->capacity; ++i)
    {
        GONC_ARRAY_SET(&ia, i, i * 100);
        printf("element: %d size: %u capacity: %u\n", (&ia)->elements[i], (&ia)->size, (&ia)->capacity);
    }
}
