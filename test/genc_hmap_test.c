#include <stdio.h>
#include "genc_hmap.h"
#include "genc_string.h"

int main()
{
    struct my_hmap_element
    {
        int value;
        GENC_HMAP_ELEMENT(struct my_hmap_element);
    };
    struct my_hmap
    {
        GENC_HMAP(struct my_hmap_element);
    };
    struct my_hmap hmap;
    GENC_HMAP_INIT(&hmap, 10007);

    struct my_hmap_element* element;

    struct my_hmap_element* old_element;

    element = malloc(sizeof(struct my_hmap_element));
    GENC_HMAP_ELEMENT_INIT(element);
    element->value = 100;

    GENC_HMAP_ELEMENT_KEY(element) = "HELLO";
    GENC_HMAP_ELEMENT_KEY_LENGTH(element) = 5;

    GENC_HMAP_SET(&hmap, element, old_element);

    printf("%u\n", old_element);

    element = malloc(sizeof(struct my_hmap_element));
    GENC_HMAP_ELEMENT_INIT(element);
    element->value = 200;

    GENC_HMAP_ELEMENT_KEY(element) = "HELLO";
    GENC_HMAP_ELEMENT_KEY_LENGTH(element) = 5;

    GENC_HMAP_SET(&hmap, element, old_element);

    printf("%u %d\n", old_element, old_element->value);

    struct my_hmap_element* element_out;
    GENC_HMAP_GET(&hmap, "HELLO", 5, element_out);
    printf("%d\n", element_out->value);
    return 0;
}
