#include <stdio.h>
#include "gonc_hmap.h"
#include "gonc_string.h"

int main()
{
    struct my_hmap_element
    {
        int value;
        GONC_HMAP_ELEMENT(struct my_hmap_element);
    };
    struct my_hmap
    {
        GONC_HMAP(struct my_hmap_element);
    };
    struct my_hmap hmap;
    GONC_HMAP_INIT(&hmap, 10007);
    struct my_hmap_element element;
    GONC_HMAP_ELEMENT_INIT(&element);
    struct my_hmap_element* old_element;

    (&element)->value = 100;
    (&element)->gonc_hmap_element.key = "HELLO";
    (&element)->gonc_hmap_element.key_length = 5;
    GONC_HMAP_SET(&hmap, &element, old_element);
    struct my_hmap_element* element_out;
    GONC_HMAP_GET(&hmap, "HELLO", 5, element_out);
    printf("%d\n", element_out->value);
    return 0;

}
