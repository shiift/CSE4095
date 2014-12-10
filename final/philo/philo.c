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
    int      max_state;
    int     handedness;
    // add whatever you want
} Philosopher;

typedef struct Fork {
    int      available;
    pthread_mutex_t  m;
} Fork;

void doActivity(int activity,Philosopher* p,unsigned* seed)
{
    p->state = activity;
    double v = ((double)rand_r(seed)) / RAND_MAX * MICROSEC;
    usleep(v); 
}

int dining(Philosopher* philo){
    //while(philo->state <= philo->max_state){
    //    doActivity(philo->state+1, philo, pthread_self());
    //}
    return 1;
}

int main(int argc,char* argv[])
{
    int n = atoi(argv[1]);  // number of philosophers
    int c = atoi(argv[2]);  // number of cycles
    if(argc != 3)
        return -1;
    int i;
    Philosopher** philos = malloc(sizeof(Philosopher*) * n);
    Fork** forks = malloc(sizeof(Fork*) * n);
    for(i = 0; i < n; i++){
        forks[i] = malloc(sizeof(Fork) * n);
        forks[i]->available = 1;
        pthread_mutex_init(&forks[i]->m, NULL);
    }
    for(i = 0; i < n; i++){
        philos[i] = malloc(sizeof(Philosopher) * n);
        philos[i]->state = 0;
        philos[i]->max_state = c-1;
        philos[i]->handedness = i % 2;
        pthread_create(philos[i]->pid,NULL,(void*(*)(void*))dining,(void*)philos[i]);
    }

    for(i = 0; i < n; i++){
        pthread_mutex_destroy(&forks[i]->m);
        free(forks[i]);
    }
    for(i = 0; i < n; i++){
        free(philos[i]);
    }
    free(forks);
    free(philos);
    return 0;
}
