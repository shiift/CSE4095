#include "wqueue.h"
#include <pthread.h>
#include <stdlib.h>

WorkQueue* makeWorkQueue()
{
   WorkQueue* wq = malloc(sizeof(WorkQueue));
   wq->_theQueue = makeQueue(4);
   pthread_mutex_init(&wq->_mtx,NULL);
   pthread_cond_init(&wq->_cond,NULL);
   return wq;
}

Task* deQueueWork(WorkQueue* twq)
{
   pthread_mutex_lock(&twq->_mtx);
   Task* t = NULL;
   while (isEmpty(twq->_theQueue)) {
      pthread_cond_wait(&twq->_cond,&twq->_mtx);
   }
   t = deQueue(twq->_theQueue);
   pthread_mutex_unlock(&twq->_mtx);
   return t;
}

void enQueueWork(WorkQueue* twq,Task* t)
{
   pthread_mutex_lock(&twq->_mtx);
   enQueue(twq->_theQueue,t);
   pthread_cond_signal(&twq->_cond);
   pthread_mutex_unlock(&twq->_mtx);
}
