#include <stdio.h>
#include "gonc_hmap.h"
#include "gonc_string.h"

int main()
{
    struct myhmap
    {
        GONC_HMAP(int);
    };
    struct myhmap hmap;
    GONC_HMAP_INIT(&hmap, 10007);
    GONC_HMAP_SET(&hmap, "HELLO", 100);
    int value;
    GONC_HMAP_GET(&hmap, "HELLO", value);
    printf("%d\n", value);
    return 0;
}
