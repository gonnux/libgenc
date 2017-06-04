#include <stdio.h>
#include "gon_c_list.h"

struct integer
{
    int value;
    GON_C_LIST_ELEMENT(struct integer);
};

struct integer_list
{
    GON_C_LIST(struct integer);
};

int main()
{
    struct integer_list list;
    GON_C_LIST_INIT(&list);
    struct integer element1;
    GON_C_LIST_ELEMENT_INIT(&element1);
    element1.value = 100;
    struct integer element2;
    GON_C_LIST_ELEMENT_INIT(&element2);
    element2.value = 200;

    GON_C_LIST_INSERT_AFTER(&list, GON_C_LIST_HEAD(&list), &element1);
    GON_C_LIST_INSERT_AFTER(&list, GON_C_LIST_HEAD(&list), &element2);

    GON_C_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GON_C_LIST_REVERSE_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GON_C_LIST_REMOVE(&list, GON_C_LIST_HEAD(&list));
    GON_C_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }
    printf("\n");
    GON_C_LIST_REMOVE(&list, GON_C_LIST_HEAD(&list));
    GON_C_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    GON_C_LIST_INSERT_AFTER(&list, GON_C_LIST_HEAD(&list), &element1);
    GON_C_LIST_INSERT_AFTER(&list, GON_C_LIST_HEAD(&list), &element2);

    struct integer* element = GON_C_LIST_HEAD(&list);

    GON_C_LIST_AFTER(&list, element, 1);
    
    printf("%d\n", element->value);

    while(GON_C_LIST_SIZE(&list) > 0)
    {
        GON_C_LIST_REMOVE(&list, GON_C_LIST_HEAD(&list));
    }

    printf("After destroy:\n");

    GON_C_LIST_FOR_EACH(&list, struct integer, item)
    {
        printf("%d\n", item->value);
    }

    return 0;
}
