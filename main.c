#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() 
{
    List* myList = createList();
    int numbers[3] = {5, 10, 15};
    
    for (int i = 0; i < 3; i++) 
    {
        int* num = malloc(sizeof(int));
        *num = numbers[i];
        myList->add(myList, num);
    }
    
    printf("Elements in list: ");
    for (int i = 0; i < myList->count(myList); i++) 
    {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    
    printf("\n");
    
    clearList(myList);
    return 0;
}
