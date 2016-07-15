#include <stdio.h>
#include "gonc_list.h"

struct integer
{
    int value;
    GONC_LIST_ELEMENT(struct integer);
};

struct integer_list
{
    GONC_LIST(struct integer);
};

int main()
{
    struct integer_list list;
    GONC_LIST_INIT(&list);
    struct integer element1;
    GONC_LIST_ELEMENT_INIT(&element1);
    element1.value = 100;
    struct integer element2;
    GONC_LIST_ELEMENT_INIT(&element2);
    element2.value = 200;

    GONC_LIST_INSERT_AFTER(&list, GONC_LIST_HEAD(&list), &element1);
    GONC_LIST_INSERT_AFTER(&list, GONC_LIST_HEAD(&list), &element2);

    GONC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GONC_LIST_REVERSE_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GONC_LIST_REMOVE(&list, GONC_LIST_HEAD(&list));
    GONC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GONC_LIST_REMOVE(&list, GONC_LIST_HEAD(&list));
    GONC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    GONC_LIST_INSERT_AFTER(&list, GONC_LIST_HEAD(&list), &element1);
    GONC_LIST_INSERT_AFTER(&list, GONC_LIST_HEAD(&list), &element2);

    struct integer* element = GONC_LIST_HEAD(&list);

    GONC_LIST_AFTER(&list, element, 1);
    
    printf("%d\n", element->value);

    while(GONC_LIST_SIZE(&list) > 0)
    {
        GONC_LIST_REMOVE(&list, GONC_LIST_HEAD(&list));
    }

    printf("After destroy:\n");

    GONC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    return 0;
}
