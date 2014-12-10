#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: I decided to put the unlock at the beginning of silly because of our
// restriction that we cannot change the code. If I was allowed to make
// changes to the code I would have put the unlock before the recursive call
// to silly inside the if statement and in an else statement as well. I would
// also remove the rdlock call before executing silly in doWork.

static long long t[1024] = {0};

void silly(long n,pthread_rwlock_t* rwl)
{
   pthread_rwlock_unlock(rwl);
   if (n==0) {
      pthread_rwlock_wrlock(rwl);
      t[0] = 1;
      pthread_rwlock_unlock(rwl);
   } else {
      pthread_rwlock_rdlock(rwl);
      if (t[n-1]==0)
         silly(n-1,rwl);
      pthread_rwlock_wrlock(rwl);
      t[n] =  n + t[n-1];      
      pthread_rwlock_unlock(rwl);
   }
}

void *doWork(pthread_rwlock_t* rwl)
{
   long sv = ((long) ((long)pthread_self() >> 16))  % 32;
   pthread_rwlock_rdlock(rwl);
   silly(sv,rwl);
   pthread_rwlock_rdlock(rwl);
   printf("called by %p with %ld got: %lld\n",pthread_self(),sv,t[sv]);
   pthread_rwlock_unlock(rwl);
   return NULL;
}

int main(int argc,char* argv[])
{
   int i;
   int nb = atoi(argv[1]);
   pthread_rwlock_t rwl;
   pthread_rwlock_init(&rwl,NULL);
   pthread_t minion[nb];
   for(i=0;i < nb;i++) {
      pthread_create(minion+i,NULL,(void*(*)(void*))doWork,&rwl);
   }
   for(i=0;i < nb;i++)
      pthread_join(minion[i],NULL);   
   pthread_rwlock_destroy(&rwl);
   return 0;
}
