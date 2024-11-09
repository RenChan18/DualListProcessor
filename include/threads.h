// threads.h
#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void* processBitCount(void (*func)(List *list, int value),void* arg);
void elementProcessing();

#endif

