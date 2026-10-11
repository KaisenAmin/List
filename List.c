#include "List.h"

#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 4

static bool reserve(List *list, int needed)
{
    if (needed <= list->capacity)
    {
        return true;
    }
    int capacity = list->capacity > 0 ? list->capacity : INITIAL_CAPACITY;
    while (capacity < needed)
    {
        capacity *= 2;
    }
    void **items = realloc(list->items, (size_t)capacity * sizeof *items);
    if (!items)
    {
        return false;
    }
    list->items = items;
    list->capacity = capacity;
    return true;
}

static int compareInts(const void *first, const void *second)
{
    if (!first || !second)
    {
        return (first != NULL) - (second != NULL);
    }
    int a = *(const int *)first;
    int b = *(const int *)second;
    return (a > b) - (a < b);
}

static void mergeSort(void **items, void **buffer, int count, ListCompare compare)
{
    if (count < 2)
    {
        return;
    }
    int middle = count / 2;
    mergeSort(items, buffer, middle, compare);
    mergeSort(items + middle, buffer, count - middle, compare);

    int left = 0;
    int right = middle;
    int out = 0;
    while (left < middle && right < count)
    {
        buffer[out++] = compare(items[right], items[left]) < 0 ? items[right++] : items[left++];
    }
    while (left < middle)
    {
        buffer[out++] = items[left++];
    }
    while (right < count)
    {
        buffer[out++] = items[right++];
    }
    memcpy(items, buffer, (size_t)count * sizeof *items);
}

void addItem(List *list, void *item)
{
    if (list && reserve(list, list->size + 1))
    {
        list->items[list->size++] = item;
    }
}

void *getItem(List *list, int index)
{
    if (!list || index < 0 || index >= list->size)
    {
        return NULL;
    }
    return list->items[index];
}

void clearList(List *list)
{
    if (list)
    {
        list->size = 0;
    }
}

int countItems(List *list)
{
    return list ? list->size : 0;
}

List *copyList(List *list)
{
    if (!list)
    {
        return NULL;
    }
    List *copy = createList();
    if (!copy)
    {
        return NULL;
    }
    if (!reserve(copy, list->size))
    {
        destroyList(copy);
        return NULL;
    }
    if (list->size > 0)
    {
        memcpy(copy->items, list->items, (size_t)list->size * sizeof *list->items);
    }
    copy->size = list->size;
    return copy;
}

void extendList(List *list, List *other)
{
    if (!list || !other || other->size == 0)
    {
        return;
    }
    int count = other->size;
    if (!reserve(list, list->size + count))
    {
        return;
    }
    memcpy(list->items + list->size, other->items, (size_t)count * sizeof *list->items);
    list->size += count;
}

void insertItem(List *list, int index, void *item)
{
    if (!list || index < 0 || index > list->size || !reserve(list, list->size + 1))
    {
        return;
    }
    memmove(list->items + index + 1, list->items + index, (size_t)(list->size - index) * sizeof *list->items);
    list->items[index] = item;
    list->size++;
}

void *popItem(List *list, int index)
{
    if (!list || index < 0 || index >= list->size)
    {
        return NULL;
    }
    void *item = list->items[index];
    memmove(list->items + index, list->items + index + 1, (size_t)(list->size - index - 1) * sizeof *list->items);
    list->size--;
    return item;
}

void removeItem(List *list, void *item)
{
    int index = indexItem(list, item);
    if (index >= 0)
    {
        popItem(list, index);
    }
}

void reverseList(List *list)
{
    for (int i = 0; list && i < list->size / 2; i++)
    {
        void *temp = list->items[i];
        list->items[i] = list->items[list->size - 1 - i];
        list->items[list->size - 1 - i] = temp;
    }
}

void sortListBy(List *list, ListCompare compare)
{
    if (!list || !compare || list->size < 2)
    {
        return;
    }
    void **buffer = malloc((size_t)list->size * sizeof *buffer);
    if (buffer)
    {
        mergeSort(list->items, buffer, list->size, compare);
        free(buffer);
    }
}

void sortList(List *list)
{
    sortListBy(list, compareInts);
}

int indexItem(List *list, void *item)
{
    for (int i = 0; list && i < list->size; i++)
    {
        if (list->items[i] == item)
        {
            return i;
        }
    }
    return -1;
}

void destroyList(List *list)
{
    if (list)
    {
        free(list->items);
        free(list);
    }
}

List *createList(void)
{
    List *list = calloc(1, sizeof *list);
    if (!list)
    {
        return NULL;
    }
    list->items = malloc(INITIAL_CAPACITY * sizeof *list->items);
    if (!list->items)
    {
        free(list);
        return NULL;
    }
    list->capacity = INITIAL_CAPACITY;

    list->add = addItem;
    list->get = getItem;
    list->clear = clearList;
    list->count = countItems;
    list->copy = copyList;
    list->extend = extendList;
    list->insert = insertItem;
    list->pop = popItem;
    list->remove = removeItem;
    list->reverse = reverseList;
    list->sort = sortList;
    list->sortBy = sortListBy;
    list->index = indexItem;
    list->destroy = destroyList;
    return list;
}
