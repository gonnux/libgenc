#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "../src/genc_HashMap.h"

void GENC_HASH_MAP_test(void** state) {
    struct MyHashMapElement {
        int value;
        GENC_HASH_MAP_ELEMENT(struct MyHashMapElement);
    };
    struct MyHashMap {
        GENC_HASH_MAP(struct MyHashMapElement);
    };
    struct MyHashMap HashMap;
    GENC_HASH_MAP_INIT(&HashMap, 10007);

    struct MyHashMapElement element;
    struct MyHashMapElement element2;

    struct MyHashMapElement* oldElement;

    GENC_HASH_MAP_ELEMENT_INIT(&element);
    element.value = 100;

    GENC_HASH_MAP_ELEMENT_KEY(&element) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(&element) = 5;

    GENC_HASH_MAP_SET(&HashMap, &element, &oldElement);

    printf("%d\n", oldElement->value);

    GENC_HASH_MAP_ELEMENT_INIT(&element2);
    element2.value = 200;

    GENC_HASH_MAP_ELEMENT_KEY(&element2) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(&element2) = 5;

    GENC_HASH_MAP_SET(&HashMap, &element2, &oldElement);

    printf("%d\n", oldElement->value);

    struct MyHashMapElement* elementOut;
    GENC_HASH_MAP_GET(&HashMap, "HELLO", 5, &elementOut);
    printf("%d\n", elementOut->value);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(GENC_HASH_MAP_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
