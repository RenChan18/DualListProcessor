// threads.c
#include "threads.h"
#include "list.h"

pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

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
    return (thread_index == 1) ? count_zeroes : count_ones;
}


void safe_print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    pthread_mutex_lock(&print_mutex);
    vfprintf(stderr, format, args);
    pthread_mutex_unlock(&print_mutex);

    va_end(args);
}


void *process_bit_count(void *arg)
{
    List *list          = ((ThreadArg *)arg)->list;
    int   thread_index  = ((ThreadArg *)arg)->thread_index;
    int   count_bits     = 0;
    int   count_element = 0;
    static pthread_mutex_t local_mutex = PTHREAD_MUTEX_INITIALIZER;
    while (1) {
        pthread_mutex_lock(&local_mutex);

        if ((thread_index == 1 && list->head == NULL) ||
            (thread_index == 2 && list->tail == NULL)) {
            pthread_mutex_unlock(&local_mutex);
            break;
        }
        int result;
        if (thread_index == 1) {
            result = pop_front(list);
            if (result != -1) {  // Если pop_front успешен
                count_bits += count_ones_or_zeroes(result, thread_index);
                count_element++;
            }
        } else {
            result = pop_back(list);  // Вызов pop_back
            if (result != -1) {  // Если pop_back успешен
                count_bits += count_ones_or_zeroes(result, thread_index);
                count_element++;
            }
        }
        pthread_mutex_unlock(&local_mutex);
        usleep(sleep_time); 
    }
    safe_print("Thread %d count_elements:= %d, count_bits:= %d\n", 
               thread_index, count_element, count_bits);
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
}
