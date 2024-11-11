// list.h
#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { rand_range = 100 };
enum { array_size = 23 };

typedef struct Node {
    int          value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    size_t          size;
    Node           *head;
    Node           *tail;
    pthread_mutex_t mutex;
} List;

List *createList();
void  deleteList(List **list);
void  pushBack(List *list, int value);
void  popFront(List *list);
void  popBack(List *list);
void  printList(const List *list);
void  random_fill(int *arr, size_t size);
List *initAndFillList();

#endif // LIST_H
