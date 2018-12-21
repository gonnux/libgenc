#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_HashMap.h"
#include "../src/genc_String.h"

int main() {
    struct my_HashMap_element {
        int value;
        GENC_HASH_MAP_ELEMENT(struct my_HashMap_element);
    };
    struct my_HashMap {
        GENC_HASH_MAP(struct my_HashMap_element);
    };
    struct my_HashMap HashMap;
    GENC_HASH_MAP_INIT(&HashMap, 10007);

    struct my_HashMap_element* element;

    struct my_HashMap_element* old_element;

    element = malloc(sizeof(struct my_HashMap_element));
    GENC_HASH_MAP_ELEMENT_INIT(element);
    element->value = 100;

    GENC_HASH_MAP_ELEMENT_KEY(element) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) = 5;

    GENC_HASH_MAP_SET(&HashMap, element, old_element);

    printf("%p\n", old_element);

    element = malloc(sizeof(struct my_HashMap_element));
    GENC_HASH_MAP_ELEMENT_INIT(element);
    element->value = 200;

    GENC_HASH_MAP_ELEMENT_KEY(element) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) = 5;

    GENC_HASH_MAP_SET(&HashMap, element, old_element);

    printf("%p %d\n", old_element, old_element->value);

    struct my_HashMap_element* element_out;
    GENC_HASH_MAP_GET(&HashMap, "HELLO", 5, element_out);
    printf("%d\n", element_out->value);
    return 0;
}
