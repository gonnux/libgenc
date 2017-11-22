#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/genc_List.h"

struct Integer {
    int value;
    GENC_LIST_ELEMENT(struct Integer);
};

struct Integer_List {
    GENC_LIST(struct Integer);
};

void genc_List_test(void** state) {
    struct Integer_List list;
    GENC_LIST_INIT(&list);
    struct Integer element1;
    GENC_LIST_ELEMENT_INIT(&element1);
    element1.value = 100;
    struct Integer element2;
    GENC_LIST_ELEMENT_INIT(&element2);
    element2.value = 200;

    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element1);
    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element2);

    GENC_LIST_FOR_EACH(&list, struct Integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GENC_LIST_REVERSE_FOR_EACH(&list, struct Integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GENC_LIST_REMOVE(&list, GENC_LIST_HEAD(&list));
    GENC_LIST_FOR_EACH(&list, struct Integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GENC_LIST_REMOVE(&list, GENC_LIST_HEAD(&list));
    GENC_LIST_FOR_EACH(&list, struct Integer, item)
    {
        printf("%d\n", item->value);
    }

    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element1);
    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element2);

    struct Integer* element = GENC_LIST_HEAD(&list);

    GENC_LIST_AFTER(&list, element, 1);
    
    printf("%d\n", element->value);

    while(GENC_LIST_SIZE(&list) > 0)
    {
        GENC_LIST_REMOVE(&list, GENC_LIST_HEAD(&list));
    }

    printf("After destroy:\n");

    GENC_LIST_FOR_EACH(&list, struct Integer, item)
    {
        printf("%d\n", item->value);
    }
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(genc_List_test)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
