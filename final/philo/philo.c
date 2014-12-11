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
    int pid;
    int state;
    int rounds;
    int num_philos;
    int handedness;
    pthread_mutex_t** forks;
} Philosopher;

void doActivity(int activity,Philosopher* p,unsigned* seed)
{
    p->state = activity;
    double v = ((double)rand_r(seed)) / RAND_MAX * MICROSEC;
    usleep(v); 
}

int dining(Philosopher* philo){
    pthread_mutex_t** forks = philo->forks;
    int counter = 0;
    unsigned seed = (unsigned)pthread_self();
    while(counter < philo->rounds){
        switch(philo->state){
            case THINK:
                printf("P[%d] Thinking\n", philo->pid);
                doActivity(HUNGRY, philo, &seed);
                break;
            case HUNGRY:
                doActivity(EAT, philo, &seed);
                if(philo->pid % 2){ // lefty
                    pthread_mutex_lock(forks[philo->pid]); 
                    pthread_mutex_lock(forks[ (philo->pid+1) % philo->num_philos ]);
                }else{              // righty
                    pthread_mutex_lock(forks[ (philo->pid+1) % philo->num_philos ]);
                    pthread_mutex_lock(forks[philo->pid]); 
                }
                printf("P[%d] Hungry\n", philo->pid);
                break;
            case EAT:
                printf("P[%d] Eating\n", philo->pid);
                doActivity(THINK, philo, &seed);
                // order of unlocking probably does not matter here, but it is nice
                // to do it anyway
                if(philo->pid % 2){ // lefty
                    pthread_mutex_unlock(forks[ (philo->pid+1) % philo->num_philos ]);
                    pthread_mutex_unlock(forks[philo->pid]); 
                }else{              // righty
                    pthread_mutex_unlock(forks[philo->pid]); 
                    pthread_mutex_unlock(forks[ (philo->pid+1) % philo->num_philos ]);
                }
                counter++;
                break;
        }
    }
    return 1;
}

int main(int argc,char* argv[])
{
    int n = atoi(argv[1]);  // number of philosophers
    int c = atoi(argv[2]);  // number of cycles
    if(argc != 3){
        printf("Incorrent Parameters\n");
        return -1;
    }
    if(n < 2){
        printf("You don't have enough Philosophers\n");
        return -1;
    }
    int i;
    pthread_t tids[n];

    Philosopher** philos = malloc(sizeof(Philosopher*) * n);
    pthread_mutex_t** forks = malloc(sizeof(pthread_mutex_t*) * n);
    for(i = 0; i < n; i++){
        forks[i] = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(forks[i], NULL);
    }
    for(i = 0; i < n; i++){
        philos[i] = malloc(sizeof(Philosopher) * n);
        philos[i]->pid = i;
        philos[i]->state = 0;
        philos[i]->rounds = c;
        philos[i]->num_philos = n;
        philos[i]->forks = forks;
        pthread_create(&tids[i],NULL,(void*(*)(void*))dining,(void*)philos[i]);
    }
    for(i = 0; i < n; i++){
        pthread_join(tids[i],NULL);
    }
    for(i = 0; i < n; i++){
        pthread_mutex_destroy(forks[i]);
        free(forks[i]);
        free(philos[i]);
    }
    free(forks);
    free(philos);
    return 0;
}
