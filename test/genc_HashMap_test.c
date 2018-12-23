#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include "../src/genc_HashMap.h"
#include "../src/genc_String.h"

int main() {
    struct MyHashMapElement {
        int value;
        GENC_HASH_MAP_ELEMENT(struct MyHashMapElement);
    };
    struct MyHashMap {
        GENC_HASH_MAP(struct MyHashMapElement);
    };
    struct MyHashMap HashMap;
    GENC_HASH_MAP_INIT(&HashMap, 10007);

    struct MyHashMapElement* element;

    struct MyHashMapElement* oldElement;

    element = malloc(sizeof(struct MyHashMapElement));
    GENC_HASH_MAP_ELEMENT_INIT(element);
    element->value = 100;

    GENC_HASH_MAP_ELEMENT_KEY(element) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) = 5;

    GENC_HASH_MAP_SET(&HashMap, element, oldElement);

    printf("%p\n", oldElement);

    element = malloc(sizeof(struct MyHashMapElement));
    GENC_HASH_MAP_ELEMENT_INIT(element);
    element->value = 200;

    GENC_HASH_MAP_ELEMENT_KEY(element) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(element) = 5;

    GENC_HASH_MAP_SET(&HashMap, element, oldElement);

    printf("%p %d\n", oldElement, oldElement->value);

    struct MyHashMapElement* elementOut;
    GENC_HASH_MAP_GET(&HashMap, "HELLO", 5, elementOut);
    printf("%d\n", elementOut->value);
    return 0;
}
