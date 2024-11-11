// threads.c
#include "threads.h"

int countOnesAndZeroes(int num, int threadIndex)
{
    int count0 = 0, count1 = 0;
    while (num > 0) {
        if (num & 1) {
            count1++;
        } else {
            count0++;
        }
        num = num >> 1;
    }
    if (threadIndex == 1)
        return count0;
    else if (threadIndex == 2)
        return count1;
    return 0;
}

void *processBitCount(void *arg)
{
    List *list          = ((ThreadArg *)arg)->list;
    int   threadIndex   = ((ThreadArg *)arg)->threadIndex;
    int   countOnes     = 0;
    int   countBits     = 0;
    int   countZeroes   = 0;
    int   count_element = 0;
    while (1) {
        pthread_mutex_lock(&list->mutex);

        if ((threadIndex == 1 && list->head == NULL) ||
            (threadIndex == 2 && list->tail == NULL)) {
            pthread_mutex_unlock(&list->mutex);
            break;
        }

        if (threadIndex == 1) {
            countOnes += countOnesAndZeroes(list->head->value, threadIndex);
            countBits = countOnes;
            popFront(list);
            printf("List after popFront: ");
        } else {
            countZeroes += countOnesAndZeroes(list->tail->value, threadIndex);
            countBits = countZeroes;
            popBack(list);
            printf("List after popBack: ");
        }
        printList(list);
        pthread_mutex_unlock(&list->mutex);
        count_element++;
        usleep(sleep_time); // Задержка 0.1 секунды
    }
    printf("Thread %d count1: %d, count0: %d, count_el %d, CountBits:= %d\n",
           threadIndex, countOnes, countZeroes, count_element, countBits);
    return NULL;
}

void elementProcessing()
{
    pthread_t thread1, thread2;
    int       iret1, iret2;
    List     *list = initAndFillList();

    ThreadArg arg1 = {list, 1};
    ThreadArg arg2 = {list, 2};

    iret1 = pthread_create(&thread1, NULL, processBitCount, (void *)&arg1);

    if (iret1) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create(&thread2, NULL, processBitCount, (void *)&arg2);
    if (iret2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", iret2);
        exit(EXIT_FAILURE);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("List after pops: ");
    printList(list);

    printf("End...\n");
}
