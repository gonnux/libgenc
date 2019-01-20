#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "../src/genc_Map.h"

void GENC_MAP_test(void** state) {
    struct MyMapElement {
        int value;
        GENC_MAP_ELEMENT(struct MyMapElement);
    };
    struct MyMap {
        GENC_MAP(struct MyMapElement);
    };
    struct MyMap map;
    GENC_MAP_INIT(&map);
    assert_int_equal(GENC_MAP_SIZE(&map), 0);

    struct MyMapElement element;
    struct MyMapElement element2;

    struct MyMapElement* oldElement;

    GENC_MAP_ELEMENT_INIT(&element);
    element.value = 100;
    GENC_MAP_ELEMENT_KEY(&element) = "HELLO";
    GENC_MAP_ELEMENT_KEY_LENGTH(&element) = 5;

    GENC_MAP_SET(&map, &element, &oldElement);

    assert_ptr_equal(oldElement, NULL);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);

    GENC_MAP_ELEMENT_INIT(&element2);
    element2.value = 200;
    GENC_MAP_ELEMENT_KEY(&element2) = "HELLO";
    GENC_MAP_ELEMENT_KEY_LENGTH(&element2) = 5;

    GENC_MAP_SET(&map, &element2, &oldElement);
    assert_ptr_equal(oldElement, &element);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);

    struct MyMapElement* elementOut;
    GENC_MAP_GET(&map, "HELLO", 5, &elementOut);
    assert_ptr_equal(elementOut, &element2);

    for(size_t index = 0; index != GENC_MAP_CAPACITY(&map); ++index) {
        if(GENC_MAP_HEAD(&map, index) != NULL) {
            assert_ptr_equal(GENC_MAP_HEAD(&map, index), &element2);
            break;
        }
    }
    assert_int_equal(GENC_MAP_CAPACITY(&map), 10007);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);

    GENC_MAP_REALLOC(&map, 20007);
    for(size_t index = 0; index != GENC_MAP_CAPACITY(&map); ++index) {
        if(GENC_MAP_HEAD(&map, index) != NULL) {
            assert_ptr_equal(GENC_MAP_HEAD(&map, index), &element2);
            break;
        }
    }
    assert_int_equal(GENC_MAP_CAPACITY(&map), 20007);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);


    GENC_MAP_REALLOC(&map, 2000);
    for(size_t index = 0; index != GENC_MAP_CAPACITY(&map); ++index) {
        if(GENC_MAP_HEAD(&map, index) != NULL) {
            assert_ptr_equal(GENC_MAP_HEAD(&map, index), &element2);
            break;
        }
    }
    assert_int_equal(GENC_MAP_CAPACITY(&map), 2000);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(GENC_MAP_test),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
