/******************************************************************************
* FILE: hello.c
* DESCRIPTION:
*   A "hello world" Pthreads program.  Demonstrates thread creation and
*   termination.
* AUTHOR: Blaise Barney
* LAST REVISED: 10/20/14 Ion Mandoiu
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
   int rc;
   long tid;

   rc = pthread_detach( pthread_self() );
   if( rc ){
     printf("ERROR; return code from pthread_detach() is %d\n", rc);
     exit(-1);
   }

   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);

   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for( t=0; t<NUM_THREADS; t++){
     printf("In main: creating thread %ld\n", t);
     rc = pthread_create( &threads[t], NULL, PrintHello, (void *)t );
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
     }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
