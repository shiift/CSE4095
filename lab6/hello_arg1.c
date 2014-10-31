/*****************************************************************************
* FILE: hello_arg1.c
* DESCRIPTION:
*   This "hello world" Pthreads program demonstrates an unsafe (incorrect)
*   way to pass thread arguments at thread creation.  In this case, the
*   argument variable is changed by the main thread as it creates new threads.
* AUTHOR: Blaise Barney
* LAST REVISED: 10/20/14 Ion Mandoiu
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS     8

void *PrintHello(void *threadid)
{
   int rc;
   long taskid;
   sleep(1);
   taskid = *(long *)threadid;

   rc = pthread_detach( pthread_self() );
   if( rc ){
     printf("ERROR; return code from pthread_detach() is %d\n", rc);
     exit(-1);
   }

   printf("Hello from thread %ld\n", taskid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;

   for(t=0;t<NUM_THREADS;t++) {
     printf("Creating thread %ld\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);
     if( rc ){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
     }
   }

   pthread_exit(NULL);
}
