// list.c
#include "list.h"
#include <stdio.h>

List* create_list() {
    List *list = (List*) malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    list->size = 0;
    list->head = list->tail = NULL;
    pthread_mutex_init(&list->mutex, NULL);
    return list;
}

void delete_list(List **list) {
    if (list == NULL || *list == NULL) return;
    Node *current = (*list)->head;
    Node *next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    pthread_mutex_destroy(&(*list)->mutex);
    free(*list);
    (*list) = NULL;
}

void pop_front (List *list) {
    if (list == NULL || list->head == NULL) {
        fprintf(stderr, "List is empty or NULL\n");
        return;
    }

    Node *prev = list->head;
    list->head = prev->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    free(prev);
 
    list->size--; 
    pthread_mutex_unlock(&list->mutex);
}

void pop_back (List *list) {
    if (list == NULL || list->tail == NULL) {
        fprintf(stderr, "List is empty or NULL\n");
        return;
    }
    Node *next =  list->tail;
    list->tail = next->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    free(next);

    list->size--; 
    pthread_mutex_unlock(&list->mutex);
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

    pthread_mutex_lock(&list->mutex);
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
    if(list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
    pthread_mutex_unlock(&list->mutex);
}

void print_list(const List *list)
{
    if (list == NULL) return;
    Node *p;
    p = list->head;
    pthread_mutex_lock((pthread_mutex_t *)&list->mutex);
    while(p) {
        printf("%d ", p->value);
        p = p->next;
    }  
    printf("\n");
    pthread_mutex_unlock((pthread_mutex_t *)&list->mutex);
}

void random_fill(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % rand_range;
    }
}

List* init_and_fill_list() {
int *arr = malloc(array_size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    srand(time(NULL));
    random_fill(arr, array_size);
    
    List *list = create_list();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return NULL;
    }

    for (int i = 0; i < array_size; i++) {
        push_back(list, arr[i]);
        
    }
    printf("List after adding elements: ");
    print_list(list);
    return list;
}
