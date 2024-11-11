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

List *create_list();
void  delete_list(List **list);
void  push_back(List *list, int value);
void  pop_front(List *list);
void  pop_back(List *list);
void  print_list(const List *list);
void  random_fill(int *arr, size_t size);
List *init_and_fill_list();

#endif // LIST_H
