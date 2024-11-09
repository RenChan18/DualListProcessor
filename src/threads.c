// threads.c
#include "threads.h"

void* processBitCount(void (*func)(List *list, int value),void* arg) {

}

void elementProcessing() {
    pthread_t thread1, thread2;
    int  iret1, iret2;
    void* a;
   iret1 = pthread_create( &thread1, NULL, processBitCount, (void*) a);

   if(iret1)

   {

       fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);

       exit(EXIT_FAILURE);

   }

   iret2 = pthread_create( &thread2, NULL, processBitCount, (void*) a);

   if(iret2)

   {

       fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);

       exit(EXIT_FAILURE);

	 }
}
