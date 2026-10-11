#include <stdio.h>
#include <stdlib.h>
#include "List.h"

static void printList(const char *title, List *list)
{
    printf("%s: ", title);
    for (int i = 0; i < list->count(list); i++)
    {
        printf("%d ", *(int *)list->get(list, i));
    }
    printf("\n");
}

int main(void)
{
    int numbers[] = {42, 23, 35, 5};
    List *list = createList();

    for (int i = 0; i < 4; i++)
    {
        list->add(list, &numbers[i]);
    }
    printList("Original list", list);

    list->sort(list);
    printList("Sorted list", list);

    list->reverse(list);
    printList("Reversed list", list);

    int *popped = list->pop(list, 0);
    printf("Popped element: %d\n", *popped);

    list->remove(list, &numbers[1]);
    printList("List after removing 23", list);

    list->clear(list);
    printf("List cleared, count: %d\n", list->count(list));

    list->destroy(list);
    return 0;
}
