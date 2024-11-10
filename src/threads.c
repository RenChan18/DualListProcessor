// threads.c
#include "threads.h"
#include "list.h"

void random_fill(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % RAND_RANGE;
    }
}

List* initAndFillList() {
int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    srand(time(NULL));
    random_fill(arr, ARRAY_SIZE);
    
    List *list = createList();
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return NULL;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        pushBack(list, arr[i]);
        
    }
    printf("List after adding elements: ");
    printList(list);
    return list;
}

void* processBitCount1(void *arg) {
    List *list = (List*) arg;
    int count = 0;
    while (1) {
        pthread_mutex_lock(&list->mutex);
        if (list->head == NULL) {
            pthread_mutex_unlock(&list->mutex);
            break;
        }
        popFront(list);
        printf("List after popFront: ");
        printList(list);
        pthread_mutex_unlock(&list->mutex);
        count++;
        usleep(1);      
    }
    printf("TH1 count: %d\n", count);
    return NULL;
}

void* processBitCount2(void *arg) {
    List *list = (List*) arg;
    int count = 0;
    while (1) {
        pthread_mutex_lock(&list->mutex); 
        if (list->tail == NULL) {
            pthread_mutex_unlock(&list->mutex);
            break;
        }
        popBack(list);
        printf("List after popBack: ");
        printList(list);
        pthread_mutex_unlock(&list->mutex);
        count++;
        usleep(1);
    }
    printf("TH2 count: %d\n", count);
    return NULL;
}


void elementProcessing() {
    pthread_t thread1, thread2;
    int  iret1, iret2;
    List *a = initAndFillList();

    ThreadArg arg1 = { a, 1 }; 
    ThreadArg arg2 = { a, 2 };


    iret1 = pthread_create( &thread1, NULL, processBitCount1, (void*) a);

    if(iret1) {
       fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
       exit(EXIT_FAILURE);
   }

    iret2 = pthread_create( &thread2, NULL, processBitCount2, (void*) a);
    if(iret2) {
       fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
       exit(EXIT_FAILURE);
	 }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("List after pops: ");
    printList(a);

    printf("End...\n");
}
