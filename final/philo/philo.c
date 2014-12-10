#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define MICROSEC 5.0
#define THINK  0
#define HUNGRY 1
#define EAT    2

typedef struct PhiloTag {
   int            pid;
   int          state;
   // add whatever you want
} Philosopher;

void doActivity(int activity,Philosopher* p,unsigned* seed)
{
   p->state = activity;
   double v = ((double)rand_r(seed)) / RAND_MAX * MICROSEC;
   usleep(v);   
}

int main(int argc,char* argv[])
{
   int n = atoi(argv[1]);  // number of philosophers
   int c = atoi(argv[2]);  // number of cycles

   return 0;
}
