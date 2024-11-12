// list.c
#include "list.h"
#include <stdio.h>

List* create_list() {
    List *list = (List*) malloc(sizeof(List));
    if (list == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}

void delete_list(List *list) {
    if (list == NULL) return;
    Node *current = list->head;
    Node *next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int pop_front (List *list) {
    if (list == NULL || list->head == NULL) {
        return -1;
    }

    Node *prev = list->head;
    int value = prev->value;
    list->head = prev->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    free(prev);
    list->size--;
    return value;
}

int pop_back (List *list) {
    if (list == NULL || list->tail == NULL) {
        return -1;
    }

    Node *next =  list->tail;
    int value = next->value;
    list->tail = next->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    free(next);
    list->size--; 
    return value;
}

void push_back (List *list, int value)
{
    if (list == NULL) return;
    Node *tmp = (Node*) malloc(sizeof(Node));
     if (tmp == NULL) {
        perror("Memory allocation failed");
        return;
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;

    if (list->tail) {
        list->tail->next = tmp;
    }
    else {
        list->head = tmp;
    }
    list->tail = tmp;
    list->size++;
}

void print_list(const List *list)
{
    if (list == NULL) return;
    Node *p;
    p = list->head;
    while(p) {
        printf("%d ", p->value);
        p = p->next;
    }  
    printf("\n");
}

void random_fill(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % rand_range;
    }
}

List* init_and_fill_list() {
int *arr = malloc(array_size * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    srand(time(NULL));
    random_fill(arr, array_size);
    
    List *list = create_list();
    if (list == NULL) {
        perror( "Failed to create list");
        return NULL;
    }

    for (int i = 0; i < array_size; i++) {
        push_back(list, arr[i]);
        
    }
    return list;
}
