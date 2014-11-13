#include "queue.h"
#include <stdlib.h>

Queue* makeQueue(int mxs)
{
   Queue* q = (Queue*)malloc(sizeof(Queue));
   q->_mxs   = mxs;
   q->_head  =  q->_tail = q->_sz = 0;
   q->_t   = (Task**)malloc(sizeof(Task*)*mxs);
   return q;
}

void  destroyQueue(Queue* q)
{
   free(q->_t);
   free(q);
}

int isEmpty(Queue* theQueue)
{
   return theQueue->_sz == 0;
}

void enQueue(Queue* q,Task* t)
{
   if (q->_sz == q->_mxs) {
      int mxs = q->_mxs * 2;
      Task** nt = malloc(sizeof(Task*)*mxs);
      int i = q->_sz;
      int j = 0;
      for(;i>0;i--) {
         nt[j++] = q->_t[q->_head];
         q->_head = q->_head < q->_mxs-1 ? q->_head+1 : 0;
      }
      q->_head = 0;
      q->_tail = j;
      free(q->_t);
      q->_t = nt;
      q->_mxs = mxs;
   }
   q->_sz++;
   q->_t[q->_tail] = t;
   q->_tail = q->_tail < q->_mxs - 1 ? q->_tail + 1 : 0;
}
Task* deQueue(Queue* q)
{
   Task* rv = q->_t[q->_head];
   q->_t[q->_head] = NULL;
   q->_head = q->_head < q->_mxs-1 ? q->_head+1 : 0;
   q->_sz--;
   return rv;
}
