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
    struct MyHashMap hashMap;
    GENC_HASH_MAP_INIT(&hashMap, 10007);
    assert_int_equal(GENC_HASH_MAP_SIZE(&hashMap), 0);

    struct MyHashMapElement element;
    struct MyHashMapElement element2;

    struct MyHashMapElement* oldElement;

    GENC_HASH_MAP_ELEMENT_INIT(&element);
    element.value = 100;
    GENC_HASH_MAP_ELEMENT_KEY(&element) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(&element) = 5;

    GENC_HASH_MAP_SET(&hashMap, &element, &oldElement);

    assert_ptr_equal(oldElement, NULL);
    assert_int_equal(GENC_HASH_MAP_SIZE(&hashMap), 1);

    GENC_HASH_MAP_ELEMENT_INIT(&element2);
    element2.value = 200;
    GENC_HASH_MAP_ELEMENT_KEY(&element2) = "HELLO";
    GENC_HASH_MAP_ELEMENT_KEY_LENGTH(&element2) = 5;

    GENC_HASH_MAP_SET(&hashMap, &element2, &oldElement);
    assert_ptr_equal(oldElement, &element);
    assert_int_equal(GENC_HASH_MAP_SIZE(&hashMap), 1);

    struct MyHashMapElement* elementOut;
    GENC_HASH_MAP_GET(&hashMap, "HELLO", 5, &elementOut);
    assert_ptr_equal(elementOut, &element2);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(GENC_HASH_MAP_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
