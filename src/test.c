#include <stdio.h>
#include "gonc_list.h"

struct integer
{
    int value;
    GONC_LIST_ELEMENT(struct integer);
};

GONC_LIST(integer_list, struct integer);

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

    GONC_LIST_INSERT_AFTER(&list, (&list)->first, &element1);
    GONC_LIST_INSERT_AFTER(&list, (&list)->first, &element2);

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
    GONC_LIST_REMOVE(&list, (&list)->first);
    GONC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GONC_LIST_REMOVE(&list, (&list)->first);
    GONC_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    return 0;
}
