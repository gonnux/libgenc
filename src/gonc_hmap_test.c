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

    struct my_hmap_element* element;

    struct my_hmap_element* old_element;

    element = malloc(sizeof(struct my_hmap_element));
    GONC_HMAP_ELEMENT_INIT(element);
    element->value = 100;

    GONC_HMAP_ELEMENT_KEY(element) = "HELLO";
    GONC_HMAP_ELEMENT_KEY_LENGTH(element) = 5;

    GONC_HMAP_SET(&hmap, element, old_element);

    printf("%u\n", old_element);

    element = malloc(sizeof(struct my_hmap_element));
    GONC_HMAP_ELEMENT_INIT(element);
    element->value = 200;

    GONC_HMAP_ELEMENT_KEY(element) = "HELLO";
    GONC_HMAP_ELEMENT_KEY_LENGTH(element) = 5;

    GONC_HMAP_SET(&hmap, element, old_element);

    printf("%u %d\n", old_element, old_element->value);

    struct my_hmap_element* element_out;
    GONC_HMAP_GET(&hmap, "HELLO", 5, element_out);
    printf("%d\n", element_out->value);
    return 0;
}
