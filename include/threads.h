// threads.h
#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <unistd.h>

#include "list.h"

enum { sleep_time = 1 };

typedef struct {
    List *list;
    int   threadIndex;
} ThreadArg;

void *processBitCount(void *arg);
void  elementProcessing();
int   countOnesAndZeroes(int num, int threadIndex);
#endif //THREADS_H
