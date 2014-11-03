#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void * run_thread(void* args)
{
    int* result = (int*)args;
    int m = *result;
    int count = 0;

    unsigned short shorts[3];
    shorts[0] = 18287;
    shorts[1] = pthread_self();
    shorts[2] = 53899;
    unsigned short* ushort = seed48(shorts);
    
    int i;
    for(i = 0; i < m; i++){
        double rand1 = erand48(shorts);
        double rand2 = erand48(shorts);
        if(rand1 * rand1 + rand2 * rand2 <= 1){
            count++;
        }
    }
    *result = count;
}

int main(int argc,char* argv[])
{
    int m, k;
    m = atoi(argv[1]);
    k = atoi(argv[2]);

    pthread_t tid[k];
    int results[k];

    int i, p;
    p = 0;
    for(i = 0; i < k; i++){
        results[i] = m;
        pthread_create(&tid[i], NULL, run_thread, &(results[i]));
    } 
    for(i = 0; i < k; i++){
        pthread_join(tid[i], NULL);
        p += results[i];
    }
    printf("%lf\n", 4.0 * (double)p/(double)(m*k));
}
