#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() 
{
    // Create a list and add items
    List* myList = createList();

    int* num1 = malloc(sizeof(int));
    *num1 = 42;
    myList->add(myList, num1);

    int* num2 = malloc(sizeof(int));
    *num2 = 23;
    myList->add(myList, num2);

    printf("List after adding 42 and 23:\n");
    for (int i = 0; i < myList->count(myList); i++) 
    {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");

    // Create another list and add items
    List* anotherList = createList();

    int* num3 = malloc(sizeof(int));
    *num3 = 99;
    anotherList->add(anotherList, num3);

    int* num4 = malloc(sizeof(int));
    *num4 = 100;
    anotherList->add(anotherList, num4);
    
    // Extend myList with anotherList
    myList->extend(myList, anotherList);

    printf("List after extending:\n");
    for (int i = 0; i < myList->count(myList); i++) 
    {
        printf("%d ", *((int*)myList->get(myList, i)));
    }

    printf("\n");

    // Insert a number at index 1
    int* num5 = malloc(sizeof(int));
    *num5 = 55;
    myList->insert(myList, 1, num5);

    printf("List after inserting 55 at index 1:\n");
    for (int i = 0; i < myList->count(myList); i++) 
    {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");

    // Clean up
    myList->clear(myList);
    anotherList->clear(anotherList);
    free(num1);
    free(num2);
    free(num3);
    free(num4);
    free(num5);

    return 0;
}
