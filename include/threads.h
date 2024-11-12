// threads.h
#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
#include "list.h"
extern pthread_mutex_t print_mutex;

enum { sleep_time = 1 };

typedef struct {
    List *list;
    int   thread_index;
} ThreadArg;

void *process_bit_count(void *arg);
void  element_processing();
void safe_print(const char *format, ...);
int   count_ones_or_zeroes(int num, int thread_index);
#endif //THREADS_H
