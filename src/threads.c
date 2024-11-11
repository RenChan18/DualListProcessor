// threads.c
#include "threads.h"

int count_ones_or_zeroes(int num, int thread_index)
{
    int count_zeroes = 0, count_ones = 0;
    while (num > 0) {
        if (num & 1) {
            count_ones++;
        } else {
            count_zeroes++;
        }
        num = num >> 1;
    }
    if (thread_index == 1)
        return count_zeroes;
    else if (thread_index == 2)
        return count_ones;
    return 0;
}

void *process_bit_count(void *arg)
{
    List *list          = ((ThreadArg *)arg)->list;
    int   thread_index   = ((ThreadArg *)arg)->thread_index;
    int   countBits     = 0;
    int   count_element = 0;
    while (1) {
        pthread_mutex_lock(&list->mutex);

        if ((thread_index == 1 && list->head == NULL) ||
            (thread_index == 2 && list->tail == NULL)) {
            pthread_mutex_unlock(&list->mutex);
            break;
        }

        if (thread_index == 1) {
            countBits += count_ones_or_zeroes(list->head->value, thread_index);
            popFront(list);
        } else {
            countBits += count_ones_or_zeroes(list->tail->value, thread_index);
            popBack(list);
        }
        printList(list);
        pthread_mutex_unlock(&list->mutex);
        count_element++;
        usleep(sleep_time); // Задержка 0.1 секунды
    }
    printf("Thread %d count_elements:= %d, count_bits:= %d\n",
           thread_index, count_element, countBits);
    return NULL;
}

void element_processing()
{
    pthread_t thread1, thread2;
    int       iret1, iret2;
    List     *list = init_and_fill_list();

    ThreadArg arg1 = {list, 1};
    ThreadArg arg2 = {list, 2};

    iret1 = pthread_create(&thread1, NULL, process_bit_count, (void *)&arg1);

    if (iret1) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
        exit(EXIT_FAILURE);
    }

    iret2 = pthread_create(&thread2, NULL, process_bit_count, (void *)&arg2);
    if (iret2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n", iret2);
        exit(EXIT_FAILURE);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("List after pops: ");
    printList(list);

}
