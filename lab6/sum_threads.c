#include <stdio.h>
#include <stdlib.h>

#define LEN 100000
#define NUMVEC 2

typedef struct 
{
    int     len; 
    int   *data;
    int   start;
    int     end;
    int     sum;
} vect_struct;



int sum( vect_struct* vector )
{
    /* Define and use local variables for convenience */
    int start, end, i, mysum; 
    int* data; 

    start=0;
    end = vector->len;
    data = vector->data;

    mysum = 0;
    for (i=start; i<end ; i++) 
    {
        mysum += data[i];
    }
    return mysum;
}

void sum_threads( void* args)
{
    vect_struct* vector = (vect_struct *) args;
    int i;
    for(i = vector->start; i < vector->end; i++)
    {
        vector->sum += vector->data[i];
    }
}

int main (int argc, char *argv[])
{
    vect_struct* vectors[NUMVEC];

    int j;
    for(j = 0; j < NUMVEC; j++)
    {
        int i;
        vect_struct* vector;

        /* Allocate storage and initialize values */
        vector = (vect_struct*)malloc( sizeof(vect_struct) );
        if(vector==NULL)
        {
            printf("Error allocating vector\n");
            exit(-1);
        }
        vector->len = LEN;
        vector->data = (int*) malloc (LEN*sizeof(int));
        if(vector->data==NULL)
        {
            printf("Error allocating memory\n");
            exit(-1);
        }

        for( i=0; i<vector->len; i++ ) 
            vector->data[i]=1;

        vector->start = 0;
        vector->end = vector->len;
        vector->sum = 0;
        vectors[j] = vector;
    }

    vectors[0]->end = vectors[0]->len / NUMVEC;
    vectors[1]->start = vectors[1]->len / NUMVEC;

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, sum_threads, (void*) vectors[0]);
    pthread_create(&tid2, NULL, sum_threads, (void*) vectors[1]);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    /* Print result  */ 
    printf ("Sum =  %d\n", vectors[0]->sum + vectors[1]->sum);
    
    for(j = 0; j < NUMVEC; j++)
    {
        free(vectors[j]->data);
        free(vectors[j]);
    }
}
