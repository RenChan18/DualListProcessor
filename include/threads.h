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

enum {rand_range = 100};
enum {array_size = 23};
enum {sleet_time = 1};

typedef struct {
    List *list;
    int threadIndex;
} ThreadArg;


void random_fill(int *arr, size_t size);
List* initAndFillList(); 
void* processBitCount(void *arg);
//void* processBitCount2(void *arg);
void elementProcessing();

#endif

