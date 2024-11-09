// main.c
#include <stdio.h>
#include <time.h>
#include "list.h"


#ifndef RAND_RANGE
#define RAND_RANGE 100
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 10
#endif

void random_fill(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % RAND_RANGE;
    }
}

int main(int argc, char *argv[]) {

    int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    random_fill(arr, ARRAY_SIZE);
    
    List *list = createList();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    for (int i = 0; i <= ARRAY_SIZE; i++) {
        pushBack(list, arr[i]);
        
    }

    printf("List after adding elements: ");
    printList(list);

    popFront(list);
    printf("List after popFront: ");
    printList(list);

    popBack(list);
    printf("List after popBack: ");
    printList(list);

    deleteList(&list);
    return 0;
}

