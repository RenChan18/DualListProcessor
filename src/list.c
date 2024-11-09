// list.c
#include "list.h"

List* createList() {
    List *tmp = (List*) malloc(sizeof(List));
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
 
    return tmp;
}

void deleteList(List **list) {
    if (list == NULL || *list == NULL) return;
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void popFront (List *list) {
    
    if (list == NULL || list->head == NULL) {
        fprintf(stderr, "List is empty or NULL\n");
        return;
    }

    Node *prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    free(prev);
 
    list->size--;
    
}

void popBack (List *list) {

    if (list == NULL || list->tail == NULL) {
        fprintf(stderr, "List is empty or NULL\n");
        return;
    }
    Node *next =  list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    free(next);

    list->size--;
}

void pushBack (List *list, int value)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
     if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
    if(list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

void printList(const List *list)
{
    Node *p;
    p = list->head;
    while(p) {
        printf("%d ", p->value);
        p = p->next;
    }  
    printf("\n");
}


