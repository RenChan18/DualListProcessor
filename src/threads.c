// threads.c
#include "threads.h"
#include "list.h"

void random_fill(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % rand_range;
    }
}

List* initAndFillList() {
int *arr = malloc(array_size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    srand(time(NULL));
    random_fill(arr, array_size);
    
    List *list = createList();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return NULL;
    }

    for (int i = 0; i < array_size; i++) {
        pushBack(list, arr[i]);
        
    }
    printf("List after adding elements: ");
    printList(list);
    return list;
}

void* processBitCount(void *arg) {
    List *list = ((ThreadArg*) arg)->list;
    int threadIndex = ((ThreadArg*) arg)->threadIndex;
    int count = 0;
    while (1) {
        pthread_mutex_lock(&list->mutex);

        if ((threadIndex == 1 && list->head == NULL) ||
            (threadIndex == 2 && list->tail == NULL)) {
            pthread_mutex_unlock(&list->mutex);
            break;
        }

        if (threadIndex == 1) {
            popFront(list);
            printf("List after popFront: ");
        } else {
            popBack(list);
            printf("List after popBack: ");
        }
        printList(list);
        pthread_mutex_unlock(&list->mutex);

        count++;
        usleep(sleet_time);  // Задержка 0.1 секунды
    }
    printf("Thread %d count: %d\n", threadIndex, count);
    return NULL;
}



void elementProcessing() {
    pthread_t thread1, thread2;
    int  iret1, iret2;
    List *list = initAndFillList();

    ThreadArg arg1 = { list, 1 }; 
    ThreadArg arg2 = { list, 2 };


    iret1 = pthread_create( &thread1, NULL, processBitCount, (void*) &arg1);

    if(iret1) {
       fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
       exit(EXIT_FAILURE);
   }

    iret2 = pthread_create( &thread2, NULL, processBitCount, (void*) &arg2);
    if(iret2) {
       fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
       exit(EXIT_FAILURE);
	 }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("List after pops: ");
    printList(list);

    printf("End...\n");
}
