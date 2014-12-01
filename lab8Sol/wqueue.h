#ifndef __WQUEUE_H
#define __WQUEUE_H

#include "queue.h"
#include <pthread.h>

typedef struct WorkQueue {
   Queue* _theQueue;
   pthread_cond_t _cond;
   pthread_mutex_t _mtx;
} WorkQueue;

WorkQueue* makeWorkQueue();
Task* deQueueWork(WorkQueue* twq);
void enQueueWork(WorkQueue* twq,Task* t);

#endif
