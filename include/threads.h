// threads.h
#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <time.h>
#include "list.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "list.h"

#ifndef RAND_RANGE
#define RAND_RANGE 100
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 23
#endif

typedef struct {
    List *list;
    int threadIndex;
} ThreadArg;


void random_fill(int *arr, size_t size);
List* initAndFillList(); 
void* processBitCount1(void *arg);
void* processBitCount2(void *arg);
void elementProcessing();

#endif

