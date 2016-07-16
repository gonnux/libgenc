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
    struct gonc_string key;
    GONC_STRING_SET(&key, "HELLO");
    int value = 100;
    GONC_HMAP_SET(&hmap, &key, value);
    int value_out;
    GONC_HMAP_GET(&hmap, &key, value_out);
    printf("%d\n", value_out);
    return 0;
}
