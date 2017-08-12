#include <stdio.h>
#include "../src/genc_List.h"

struct integer {
    int value;
    GENC_LIST_ELEMENT(struct integer);
};

struct integer_list {
    GENC_LIST(struct integer);
};

int main() {
    struct integer_list list;
    GENC_LIST_INIT(&list);
    struct integer element1;
    GENC_LIST_ELEMENT_INIT(&element1);
    element1.value = 100;
    struct integer element2;
    GENC_LIST_ELEMENT_INIT(&element2);
    element2.value = 200;

    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element1);
    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element2);

    GENC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GENC_LIST_REVERSE_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GENC_LIST_REMOVE(&list, GENC_LIST_HEAD(&list));
    GENC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GENC_LIST_REMOVE(&list, GENC_LIST_HEAD(&list));
    GENC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element1);
    GENC_LIST_INSERT_AFTER(&list, GENC_LIST_HEAD(&list), &element2);

    struct integer* element = GENC_LIST_HEAD(&list);

    GENC_LIST_AFTER(&list, element, 1);
    
    printf("%d\n", element->value);

    while(GENC_LIST_SIZE(&list) > 0)
    {
        GENC_LIST_REMOVE(&list, GENC_LIST_HEAD(&list));
    }

    printf("After destroy:\n");

    GENC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    return 0;
}
