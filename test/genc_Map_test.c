#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "../src/genc_Map.h"

void GENC_MAP_test(void** state) {
    struct MyMapElem {
        int value;
        GENC_MAP_ELEM(struct MyMapElem);
    };
    struct MyMap {
        GENC_MAP(struct MyMapElem);
    };
    struct MyMap map;
    GENC_MAP_INIT(&map);
    assert_int_equal(GENC_MAP_SIZE(&map), 0);

    struct MyMapElem elem;
    struct MyMapElem elem2;

    struct MyMapElem* oldElem;

    GENC_MAP_ELEM_INIT(&elem);
    elem.value = 100;
    GENC_MAP_ELEM_KEY(&elem) = "HELLO";
    GENC_MAP_ELEM_KEY_LENGTH(&elem) = 5;

    GENC_MAP_SET(&map, &elem, &oldElem);

    assert_ptr_equal(oldElem, NULL);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);

    GENC_MAP_ELEM_INIT(&elem2);
    elem2.value = 200;
    GENC_MAP_ELEM_KEY(&elem2) = "HELLO";
    GENC_MAP_ELEM_KEY_LENGTH(&elem2) = 5;

    GENC_MAP_SET(&map, &elem2, &oldElem);
    assert_ptr_equal(oldElem, &elem);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);

    struct MyMapElem* elemOut;
    GENC_MAP_GET(&map, "HELLO", 5, &elemOut);
    assert_ptr_equal(elemOut, &elem2);

    for(size_t index = 0; index != GENC_MAP_CAPACITY(&map); ++index) {
        if(GENC_MAP_HEAD(&map, index) != NULL) {
            assert_ptr_equal(GENC_MAP_HEAD(&map, index), &elem2);
            break;
        }
    }
    assert_int_equal(GENC_MAP_CAPACITY(&map), 10007);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);

    GENC_MAP_REALLOC(&map, 20007);
    for(size_t index = 0; index != GENC_MAP_CAPACITY(&map); ++index) {
        if(GENC_MAP_HEAD(&map, index) != NULL) {
            assert_ptr_equal(GENC_MAP_HEAD(&map, index), &elem2);
            break;
        }
    }
    assert_int_equal(GENC_MAP_CAPACITY(&map), 20007);
    assert_int_equal(GENC_MAP_SIZE(&map), 1);


    GENC_MAP_REALLOC(&map, 2000);
    for(size_t index = 0; index != GENC_MAP_CAPACITY(&map); ++index) {
        if(GENC_MAP_HEAD(&map, index) != NULL) {
            assert_ptr_equal(GENC_MAP_HEAD(&map, index), &elem2);
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
