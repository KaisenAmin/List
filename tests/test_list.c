#include "../List.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int checks = 0;
static int failures = 0;

#define CHECK(condition) check((condition), #condition, __LINE__)

static void check(bool ok, const char *expression, int line)
{
    checks++;
    if (!ok)
    {
        failures++;
        printf("FAIL line %d: %s\n", line, expression);
    }
}

typedef struct
{
    int key;
    int order;
} Pair;

static int compareStrings(const void *first, const void *second)
{
    return strcmp(first, second);
}

static int comparePairs(const void *first, const void *second)
{
    const Pair *a = first;
    const Pair *b = second;
    return (a->key > b->key) - (a->key < b->key);
}

static bool hasInts(List *list, const int *expected, int count)
{
    if (list->count(list) != count)
    {
        return false;
    }
    for (int i = 0; i < count; i++)
    {
        if (*(int *)list->get(list, i) != expected[i])
        {
            return false;
        }
    }
    return true;
}

static void testAddGetCount(void)
{
    int values[100];
    List *list = createList();
    CHECK(list != NULL && list->count(list) == 0);
    for (int i = 0; i < 100; i++)
    {
        values[i] = i * 3;
        list->add(list, &values[i]);
    }
    CHECK(countItems(list) == 100 && list->capacity >= 100);
    CHECK(*(int *)getItem(list, 0) == 0 && *(int *)list->get(list, 99) == 297);
    CHECK(list->get(list, 100) == NULL && list->get(list, -1) == NULL);
    destroyList(list);
}

static void testInsertPopRemoveIndex(void)
{
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    List *list = createList();
    list->add(list, &b);
    list->add(list, &d);
    list->insert(list, 0, &a);
    list->insert(list, 2, &c);
    list->insert(list, 4, &e);
    list->insert(list, 9, &e);
    list->insert(list, -1, &e);
    CHECK(hasInts(list, (int[]){1, 2, 3, 4, 5}, 5));

    CHECK(list->index(list, &c) == 2 && list->index(list, &(int){3}) == -1);
    CHECK(*(int *)list->pop(list, 0) == 1 && *(int *)list->pop(list, 3) == 5);
    CHECK(list->pop(list, 3) == NULL && list->pop(list, -1) == NULL);
    CHECK(hasInts(list, (int[]){2, 3, 4}, 3));

    list->remove(list, &c);
    list->remove(list, &a);
    CHECK(hasInts(list, (int[]){2, 4}, 2));

    list->add(list, &b);
    list->remove(list, &b);
    CHECK(hasInts(list, (int[]){4, 2}, 2));
    destroyList(list);
}

static void testClearCopyExtend(void)
{
    int values[] = {5, 10, 15};
    List *list = createList();
    for (int i = 0; i < 3; i++)
    {
        list->add(list, &values[i]);
    }

    List *copy = list->copy(list);
    CHECK(copy != NULL && copy != list && hasInts(copy, values, 3));
    list->clear(list);
    CHECK(list->count(list) == 0 && list->get(list, 0) == NULL);
    CHECK(hasInts(copy, values, 3));

    list->add(list, &values[2]);
    CHECK(hasInts(list, (int[]){15}, 1));

    list->extend(list, copy);
    CHECK(hasInts(list, (int[]){15, 5, 10, 15}, 4));
    list->extend(list, list);
    CHECK(hasInts(list, (int[]){15, 5, 10, 15, 15, 5, 10, 15}, 8));

    List *empty = createList();
    List *emptyCopy = empty->copy(empty);
    CHECK(emptyCopy && emptyCopy->count(emptyCopy) == 0);
    list->extend(list, empty);
    CHECK(list->count(list) == 8);

    destroyList(emptyCopy);
    destroyList(empty);
    copy->destroy(copy);
    destroyList(list);
}

static void testReverseAndSort(void)
{
    int values[] = {42, 23, 35, -7, 23, 0};
    List *list = createList();
    for (int i = 0; i < 6; i++)
    {
        list->add(list, &values[i]);
    }
    list->sort(list);
    CHECK(hasInts(list, (int[]){-7, 0, 23, 23, 35, 42}, 6));
    CHECK(list->get(list, 2) == &values[1] && list->get(list, 3) == &values[4]);
    list->reverse(list);
    CHECK(hasInts(list, (int[]){42, 35, 23, 23, 0, -7}, 6));
    destroyList(list);

    List *words = createList();
    char *items[] = {"pear", "apple", "fig", "banana"};
    for (int i = 0; i < 4; i++)
    {
        words->add(words, items[i]);
    }
    words->sortBy(words, compareStrings);
    CHECK(strcmp(words->get(words, 0), "apple") == 0 && strcmp(words->get(words, 3), "pear") == 0);
    destroyList(words);

    Pair pairs[] = {{2, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 4}, {2, 5}};
    List *stable = createList();
    for (int i = 0; i < 6; i++)
    {
        stable->add(stable, &pairs[i]);
    }
    sortListBy(stable, comparePairs);
    int expectedOrder[] = {4, 1, 3, 0, 2, 5};
    bool isStable = true;
    for (int i = 0; i < 6; i++)
    {
        isStable = isStable && ((Pair *)stable->get(stable, i))->order == expectedOrder[i];
    }
    CHECK(isStable);
    destroyList(stable);

    List *single = createList();
    single->sort(single);
    single->reverse(single);
    single->add(single, &values[0]);
    single->sort(single);
    CHECK(hasInts(single, (int[]){42}, 1));
    destroyList(single);
}

static void testNullSafety(void)
{
    addItem(NULL, NULL);
    clearList(NULL);
    reverseList(NULL);
    sortList(NULL);
    extendList(NULL, NULL);
    insertItem(NULL, 0, NULL);
    removeItem(NULL, NULL);
    destroyList(NULL);
    CHECK(getItem(NULL, 0) == NULL && popItem(NULL, 0) == NULL && copyList(NULL) == NULL);
    CHECK(countItems(NULL) == 0 && indexItem(NULL, NULL) == -1);
}

int main(void)
{
    testAddGetCount();
    testInsertPopRemoveIndex();
    testClearCopyExtend();
    testReverseAndSort();
    testNullSafety();
    printf("%d checks, %d failures\n", checks, failures);
    return failures == 0 ? 0 : 1;
}
