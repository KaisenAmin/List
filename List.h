#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/**
 * @struct List
 * @brief A dynamic array-like structure.
 *
 * This List struct serves as a dynamic array-like structure that holds a series of void pointers.
 */
typedef struct List 
{
    void** items;          ///< Dynamic array of items.
    int size;              ///< Number of elements in the list.
    int capacity;          ///< Capacity of the list.

    /**
     * @brief Adds an item to the list.
     */
    void (*add)(struct List*, void*);

    /**
     * @brief Retrieves an item at the specified index.
     */
    void* (*get)(struct List*, int);

    /**
     * @brief Clears all items in the list.
     */
    void (*clear)(struct List*);

    /**
     * @brief Counts the items in the list.
     */
    int (*count)(struct List*);

    /**
     * @brief Returns a copy of the list.
     */
    struct List* (*copy)(struct List*);

    /**
     * @brief Extends the list with another list.
     */
    void (*extend)(struct List*, struct List*);

    /**
     * @brief Inserts an item at a specific index.
     */
    void (*insert)(struct List*, int, void*);

    /**
     * @brief Removes and returns an item at a specific index.
     */
    void* (*pop)(struct List*, int);

    /**
     * @brief Removes the first occurrence of a specific item.
     */
    void (*remove)(struct List*, void*);

    /**
     * @brief Reverses the items in the list.
     */
    void (*reverse)(struct List*);

    /**
     * @brief Sorts the items in the list.
     */
    void (*sort)(struct List*);

    /**
     * @brief Returns the index of the first occurrence of a specific item.
     */
    int (*index)(struct List*, void*);

} List;

// Function prototypes
List* createList();
void addItem(List* list, void* item);
void* getItem(List* list, int index);
void clearList(List* list);
int countItems(List* list);
List* copyList(List* list);
void extendList(List* list, List* other);
void insertItem(List* list, int index, void* item);
void* popItem(List* list, int index);
void removeItem(List* list, void* item);
void reverseList(List* list);
void sortList(List* list);
int indexItem(List* list, void* item);

#endif // LIST_H
