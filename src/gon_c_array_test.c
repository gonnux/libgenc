#include "gon_c_array.h"
#include <stdio.h>

struct integer_array
{
    GON_C_ARRAY(int);
};

int main()
{
    struct integer_array ia;
    GON_C_ARRAY_INIT(&ia, 10);
    for(int i = 0; i < GON_C_ARRAY_SIZE(&ia); ++i)
    {
        GON_C_ARRAY_SET(&ia, i, i * 100);
        printf("element: %d size: %u\n", GON_C_ARRAY_GET(&ia, i), GON_C_ARRAY_SIZE(&ia));
    }
    GON_C_ARRAY_FOR_EACH(&ia, i)
    {
        printf("%d\n", GON_C_ARRAY_GET(&ia, i));
    }
}
