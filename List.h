#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef int (*ListCompare)(const void *first, const void *second);

typedef struct List
{
    void **items;
    int size;
    int capacity;

    void (*add)(struct List *, void *);
    void *(*get)(struct List *, int);
    void (*clear)(struct List *);
    int (*count)(struct List *);
    struct List *(*copy)(struct List *);
    void (*extend)(struct List *, struct List *);
    void (*insert)(struct List *, int, void *);
    void *(*pop)(struct List *, int);
    void (*remove)(struct List *, void *);
    void (*reverse)(struct List *);
    void (*sort)(struct List *);
    void (*sortBy)(struct List *, ListCompare);
    int (*index)(struct List *, void *);
    void (*destroy)(struct List *);
} List;

List *createList(void);
void destroyList(List *list);
void addItem(List *list, void *item);
void *getItem(List *list, int index);
void clearList(List *list);
int countItems(List *list);
List *copyList(List *list);
void extendList(List *list, List *other);
void insertItem(List *list, int index, void *item);
void *popItem(List *list, int index);
void removeItem(List *list, void *item);
void reverseList(List *list);
void sortList(List *list);
void sortListBy(List *list, ListCompare compare);
int indexItem(List *list, void *item);

#endif
