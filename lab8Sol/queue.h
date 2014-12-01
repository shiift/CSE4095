#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct Task {
   int    _update;
   char*   _fname;
} Task;

typedef struct Queue {
   int  _mxs;
   int  _head;
   int  _tail;
   int  _sz;
   Task** _t;
} Queue;

Queue* makeQueue(int mxs);
void  destroyQueue(Queue* theQueue);
void enQueue(Queue* theQueue,Task* t);
Task* deQueue(Queue* theQueue);
int isEmpty(Queue* theQueue);
#endif
