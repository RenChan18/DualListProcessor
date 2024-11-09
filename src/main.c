// main.c
#include <stdio.h>
#include "list.h"

int main() {
    List *list = createList();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    for (int i = 1; i <= 5; i++) {
        pushBack(list, i);
        
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

