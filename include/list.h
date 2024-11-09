// list.h
#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    size_t size;
    Node *head;
    Node *tail;
} List;

List* createList();
void deleteList(List **list);
void pushBack(List *list, int value);
void popFront(List *list);
void popBack(List *list);
void printList(const List *list);

#endif // LIST_H

