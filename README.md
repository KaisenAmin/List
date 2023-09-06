
# Project Documentation for `List` Library

## Introduction

The `List` library provides a dynamic array implementation in C. It supports common list operations such as add, get, remove, and more.

## Installation

1. Clone the repository
2. Run the `make` command:

    ```bash
    make
    ```

3. This should compile your project and create an executable named `my_program` (or whatever you named it in the `Makefile`).

4. To run your program, you can then do:

    ```bash
    ./my_program
    ```

5. If you wish to clean up the generated `.o` and executable files, you can run:

    ```bash
    make clean
    ```

Make sure your `Makefile`, `List.c`, `List.h`, and `main.c` are all in the same directory. With this `Makefile`, running the `make` command will compile the code files and link them to produce an executable.

## API Documentation

### Data Structures

#### `List`

Represents a dynamic list. 

---

### Functions

#### `List* createList()`

- **Description**: Creates a new, empty list.
- **Returns**: A pointer to a new `List` object.

##### Example

```c
List* myList = createList();
```

#### `void addItem(List* list, void* item)`

- **Description**: Adds an item to the end of the list.
- **Parameters**:
  - `list`: The list to add the item to.
  - `item`: The item to add.

##### Example

```c
int* data = malloc(sizeof(int));
*data = 5;
addItem(myList, data);
```

#### `void* getItem(List* list, int index)`

- **Description**: Gets the item at the specified index.
- **Parameters**:
  - `list`: The list to get the item from.
  - `index`: The index of the item.

##### Example

```c
void* item = getItem(myList, 0);
if(item != NULL) {
    printf("Item at index 0: %d\n", *(int*)item);
}
```

#### `int countItems(List* list)`

- **Description**: Returns the number of items in the list.
- **Parameters**:
  - `list`: The list to get the count from.

##### Example

```c
int count = countItems(myList);
printf("Number of items in the list: %d\n", count);
```

#### `void extendList(List* list, List* other)`

- **Description**: Adds all items from another list to the end of the given list.
- **Parameters**:
  - `list`: The list to extend.
  - `other`: The list to take items from.

##### Example

```c
List* anotherList = createList();
// ... populate anotherList
extendList(myList, anotherList);
```

#### `void insertItem(List* list, int index, void* item)`

- **Description**: Inserts an item at the specified index.
- **Parameters**:
  - `list`: The list to insert the item into.
  - `index`: The index at which to insert the item.
  - `item`: The item to insert.

##### Example

```c
int* newData = malloc(sizeof(int));
*newData = 10;
insertItem(myList, 1, newData);
```

#### `int indexItem(List* list, void* item)`

- **Description**: Returns the index of the first occurrence of the given item in the list.
- **Parameters**:
  - `list`: The list to search.
  - `item`: The item to find.

##### Example

```c
int index = indexItem(myList, data);
if (index != -1) {
    printf("Item found at index: %d\n", index);
}
```

#### `void* popItem(List* list, int index)`

- **Description**: Removes and returns the item at the given index.
- **Parameters**:
  - `list`: The list to remove the item from.
  - `index`: The index of the item to remove.

##### Example

```c
void* removedItem = popItem(myList, 0);
if (removedItem != NULL) {
    printf("Removed item: %d\n", *(int*)removedItem);
}
```

#### `void removeItem(List* list, void* item)`

- **Description**: Removes the first occurrence of the specified item.
- **Parameters**:
  - `list`: The list to remove the item from.
  - `item`: The item to remove.

##### Example

```c
removeItem(myList, data);
```

#### `void reverseList(List* list)`

- **Description**: Reverses the order of items in the list.
- **Parameters**:
  - `list`: The list to reverse.

##### Example

```c
reverseList(myList);
```

#### `void sortList(List* list)`

- **Description**: Sorts the items in the list.
- **Parameters**:
  - `list`: The list to sort.

##### Example

```c
sortList(myList);
```

## Examples

### Basic Operations

```c
// Create a new list
List* myList = createList();

// Add items to the list
int* num1 = malloc(sizeof(int));
*num1 = 42;
addItem(myList, num1);

int* num2 = malloc(sizeof(int));
*num2 = 23;
addItem(myList, num2);

// Display the list
for (int i = 0; i < countItems(myList); i++) 
{
    printf("%d ", *(int*)getItem(myList, i));
}
printf("\n");

// Remove the first item
popItem(myList, 0);

// Display the list again
for (int i = 0; i < countItems(myList); i++) 
{
    printf("%d ", *(int*)getItem(myList, i));
}
printf("\n");

// Clear the list
clearList(myList);
```

### Advanced Operations

```c
#include <stdio.h>
#include "List.h"

int main() 
{
    List* myList = createList();

    int* num1 = malloc(sizeof(int));
    *num1 = 42;
    myList->add(myList, num1);

    int* num2 = malloc(sizeof(int));
    *num2 = 23;
    myList->add(myList, num2);

    int* num3 = malloc(sizeof(int));
    *num3 = 35;
    myList->add(myList, num3);

    printf("Original list: ");
    for (int i = 0; i < myList->count(myList); ++i) {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");

    myList->sort(myList);
    printf("Sorted list: ");
    for (int i = 0; i < myList->count(myList); ++i) {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");

    myList->reverse(myList);
    printf("Reversed list: ");
    for (int i = 0; i < myList->count(myList); ++i) {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");

    int* popped = (int*)myList->pop(myList, 0);
    printf("Popped element: %d\n", *popped);

    myList->remove(myList, num2);
    printf("List after removing 23: ");
    for (int i = 0; i < myList->count(myList); ++i) {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");

    // Clean up
    free(num1);
    free(num2);
    free(num3);
    free(popped);
    myList->clear(myList);

    return 0;
}

```

### Example 1: Basic Adding and Getting

This example simply adds three integers to a list and retrieves them.

```c
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main() {
    List* myList = createList();
    int numbers[3] = {5, 10, 15};
    
    for (int i = 0; i < 3; i++) {
        int* num = malloc(sizeof(int));
        *num = numbers[i];
        myList->add(myList, num);
    }
    
    printf("Elements in list: ");
    for (int i = 0; i < myList->count(myList); i++) {
        printf("%d ", *((int*)myList->get(myList, i)));
    }
    printf("\n");
    
    clearList(myList);
    return 0;
}
```

### Example 2: Using `clear`

This example adds items to the list and then clears the list.

```c
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
    
    myList->clear(myList);
    printf("List cleared, count: %d\n", myList->count(myList));
    
    return 0;
}
```

### Example 3: Using `count`

This example shows how to count the number of items in a list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    printf("List count: %d\n", myList->count(myList));
    return 0;
}
```

### Example 4: Using `copy`

This example demonstrates how to copy a list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    int* num = malloc(sizeof(int));
    *num = 5;
    myList->add(myList, num);

    List* copiedList = myList->copy(myList);
    printf("Copied value: %d\n", *((int*)copiedList->get(copiedList, 0)));

    clearList(myList);
    clearList(copiedList);
    return 0;
}
```

### Example 5: Using `extend`

This example shows how to extend a list with another list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* list1 = createList();
    List* list2 = createList();
    //... (Add some items to list1 and list2)
    list1->extend(list1, list2);
    //... (Print items in extended list1)
    return 0;
}
```

### Example 6: Using `insert`

This example demonstrates how to insert an item at a specific index in the list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    int* num = malloc(sizeof(int));
    *num = 5;
    myList->insert(myList, 0, num);
    //... (Print items)
    return 0;
}
```

### Example 7: Using `pop`

This example shows how to pop an item from a list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    //... (Add some items)
    int* popped = (int*) myList->pop(myList, 0);
    //... (Do something with popped)
    return 0;
}
```

### Example 8: Using `remove`

This example demonstrates how to remove a specific item from a list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    int* num = malloc(sizeof(int));
    *num = 5;

    myList->add(myList, num);
    myList->remove(myList, num);
    //... (Check if removed)
    return 0;
}
```

### Example 9: Using `reverse`

This example shows how to reverse the items in a list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    //... (Add some items)
    myList->reverse(myList);
    //... (Print reversed items)
    return 0;
}
```

### Example 10: Using `sort`

This example demonstrates how to sort the items in a list.

```c
//... (skipping standard headers for brevity)
int main() 
{
    List* myList = createList();
    //... (Add some items)
    myList->sort(myList);
    //... (Print sorted items)
    return 0;
}
```

These examples should provide a wide range of demonstrations for how to use your `List` struct and its associated methods.


## License

This project is licensed under the MIT License.

## Author

amin tahmasebi

---

That's a comprehensive documentation, including a description of each function and a variety of examples to illustrate usage. Feel free to adapt it to your needs!