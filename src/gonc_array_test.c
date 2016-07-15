#include "gonc_array.h"
#include <stdio.h>

struct integer_array
{
    GONC_ARRAY(int);
};

int main()
{
    struct integer_array ia;
    GONC_ARRAY_INIT(&ia, int, 10);
    for(int i = 0; i < GONC_ARRAY_CAPACITY(&ia); ++i)
    {
        GONC_ARRAY_SET(&ia, i, i * 100);
        printf("element: %d size: %u capacity: %u\n", GONC_ARRAY_GET(&ia, i), GONC_ARRAY_SIZE(&ia), GONC_ARRAY_CAPACITY(&ia));
    }
    GONC_ARRAY_FOR_EACH(&ia, i)
    {
        printf("%d\n", GONC_ARRAY_GET(&ia, i));
    }
}
