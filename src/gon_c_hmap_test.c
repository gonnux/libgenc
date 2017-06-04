#include <stdio.h>
#include "gon_c_hmap.h"
#include "gon_c_string.h"

int main()
{
    struct my_hmap_element
    {
        int value;
        GON_C_HMAP_ELEMENT(struct my_hmap_element);
    };
    struct my_hmap
    {
        GON_C_HMAP(struct my_hmap_element);
    };
    struct my_hmap hmap;
    GON_C_HMAP_INIT(&hmap, 10007);

    struct my_hmap_element* element;

    struct my_hmap_element* old_element;

    element = malloc(sizeof(struct my_hmap_element));
    GON_C_HMAP_ELEMENT_INIT(element);
    element->value = 100;

    GON_C_HMAP_ELEMENT_KEY(element) = "HELLO";
    GON_C_HMAP_ELEMENT_KEY_LENGTH(element) = 5;

    GON_C_HMAP_SET(&hmap, element, old_element);

    printf("%u\n", old_element);

    element = malloc(sizeof(struct my_hmap_element));
    GON_C_HMAP_ELEMENT_INIT(element);
    element->value = 200;

    GON_C_HMAP_ELEMENT_KEY(element) = "HELLO";
    GON_C_HMAP_ELEMENT_KEY_LENGTH(element) = 5;

    GON_C_HMAP_SET(&hmap, element, old_element);

    printf("%u %d\n", old_element, old_element->value);

    struct my_hmap_element* element_out;
    GON_C_HMAP_GET(&hmap, "HELLO", 5, element_out);
    printf("%d\n", element_out->value);
    return 0;
}
