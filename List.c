#include "List.h"
#include <string.h>

/**
 * @brief Adds an item to the list.
 *
 * @param list The list to which the item will be added.
 * @param item The item to be added.
 */
void addItem(List* list, void* item) 
{
    if (list->size == list->capacity) 
    {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(void*) * list->capacity);
    }
    list->items[list->size++] = item;
}

/**
 * @brief Retrieves an item from the list at a given index.
 *
 * @param list The list from which the item will be retrieved.
 * @param index The index of the item to retrieve.
 * @return A pointer to the item, or NULL if index is out of range.
 */
void* getItem(List* list, int index) 
{
    if (index < 0 || index >= list->size) 
    {
        return NULL;
    }
    return list->items[index];
}

/**
 * @brief Clears and frees all elements from the list.
 *
 * @param list The list to be cleared.
 */
void clearList(List* list) 
{
    free(list->items);
    free(list);
}

/**
 * @brief Counts the number of items in the list.
 *
 * @param list The list whose items will be counted.
 * @return The number of items in the list.
 */
int countItems(List* list)
{
    return list->size;
}

/**
 * @brief Creates a copy of the given list.
 *
 * @param original The list to be copied.
 * @return A new list containing all the elements of the original list.
 */
List* copyList(List* original)
{
    List* copy = createList();
    for (int i = 0; i < original->size; i++) 
    {
        copy->add(copy, original->get(original, i));
    }
    return copy;
}

/**
 * @brief Extends a list by appending all the items from another list.
 *
 * @param list The list to be extended.
 * @param other The list whose elements will be added to the first list.
 */
void extendList(List* list, List* other)
{
    for (int i = 0; i < other->size; i++) 
    {
        list->add(list, other->get(other, i));
    }
}

/**
 * @brief Inserts an item at a specific index in the list.
 *
 * @param list The list in which the item will be inserted.
 * @param index The index at which to insert the item.
 * @param item The item to be inserted.
 */
void insertItem(List* list, int index, void* item)
{
    if (index < 0 || index > list->size) 
    {
        return;
    }
    
    if (list->size == list->capacity) 
    {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(void*) * list->capacity);
    }
    
    // Shift elements down to make room for the new item
    for (int i = list->size; i > index; i--) 
    {
        list->items[i] = list->items[i - 1];
    }
    
    // Insert new item
    list->items[index] = item;
    list->size++;
}

/**
 * @brief Removes and returns an item at a specific index from the list.
 *
 * @param list The list from which the item will be popped.
 * @param index The index of the item to be popped.
 * @return A pointer to the popped item, or NULL if index is out of range.
 */
void* popItem(List* list, int index) 
{
    if (index < 0 || index >= list->size) 
    {
        return NULL;
    }

    void* item = list->items[index];
    memmove(&list->items[index], &list->items[index + 1], (list->size - index - 1) * sizeof(void*));
    list->size--;

    return item;
}

/**
 * @brief Removes the first occurrence of a specific item from the list.
 *
 * @param list The list from which the item will be removed.
 * @param item The item to be removed.
 */
void removeItem(List* list, void* item) 
{
    for (int i = 0; i < list->size; i++) 
    {
        if (list->items[i] == item) 
        {
            popItem(list, i);
            return;
        }
    }
}

/**
 * @brief Reverses the order of items in the list.
 *
 * @param list The list to be reversed.
 */
void reverseList(List* list) 
{
    for (int i = 0; i < list->size / 2; i++) 
    {
        void* temp = list->items[i];
        list->items[i] = list->items[list->size - i - 1];
        list->items[list->size - i - 1] = temp;
    }
}

/**
 * @brief Comparison function for sorting.
 *
 * @param a Pointer to the first item to compare.
 * @param b Pointer to the second item to compare.
 * @return Negative, zero, or positive value, depending on the comparison.
 */
int compare(const void* a, const void* b) 
{
    // Dereference the pointers from void* to int*, then dereference the int* to get int
    int int_a = *((int*) *((void**)a));
    int int_b = *((int*) *((void**)b));

    // Return comparison result
    return (int_a > int_b) - (int_a < int_b);
}

/**
 * @brief Sorts the items in the list.
 *
 * @param list The list to be sorted.
 */
void sortList(List* list) 
{
    qsort(list->items, list->size, sizeof(void*), compare);
}

/**
 * @brief Returns the index of the first occurrence of a specific item in the list.
 *
 * This function iterates through the list to find the first occurrence of the given item. 
 * It returns the index of that item if found.
 *
 * @param list The pointer to the List structure.
 * @param item The pointer to the item to search for.
 * @return The index of the first occurrence of the item, or -1 if the item is not found.
 */
int indexItem(List* list, void* item) 
{
    for (int i = 0; i < list->size; i++) 
    {
        if (list->items[i] == item) 
        {
            return i;
        }
    }
    return -1; // Return -1 if the item is not found
}

/**
 * @brief Creates a new list.
 *
 * @return A pointer to the newly created list.
 */
List* createList() 
{
    List* list = malloc(sizeof(List));
    list->items = malloc(sizeof(void*) * 2);
    list->size = 0;
    list->capacity = 2;
    list->add = addItem;
    list->get = getItem;
    list->clear = clearList;
    list->count = countItems;
    list->copy = copyList;
    list->pop = popItem;
    list->remove = removeItem;
    list->reverse = reverseList;
    list->sort = sortList;
    list->index = indexItem;
    return list;
}