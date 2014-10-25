#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "matrix.h"

#define TRUE  1
#define FALSE 0

#define DEFAULT_DIM 2

typedef struct
{
    int         dim;
    double**   data;
    double** square;
    double      sum;
} matrix_struct;

typedef struct
{
    int nextrow;
    pthread_mutex_t lock;
} row_tracker;

typedef struct
{
    int nextrow;
    int nextcol;
    pthread_mutex_t lock;
} mat_tracker;

typedef struct
{
    double* row_sum;
    matrix_struct* mstruct;
    row_tracker* rtracker;
    mat_tracker* mtracker;
} track_struct;

/**************************************************/
void sum_matrix(matrix_struct*  mat)
{
    int i, j, dim;
    double    sum;
    double**  data;

    dim  = mat->dim;
    data = mat->data;

    sum = 0;
    for( i=0; i<dim; i++)
    {
        for( j=0; j<dim; j++)
        {
            sum += data[i][j];
        }
    }

    mat->sum = sum;
    return;
}

void * sum_rows(void* args)
{
    int col, row, dim;
    track_struct* tracker = (track_struct*) args;
    
    dim = tracker->mstruct->dim;

    pthread_mutex_lock(&tracker->rtracker->lock);
    row = tracker->rtracker->nextrow;
    tracker->rtracker->nextrow++;
    pthread_mutex_unlock(&tracker->rtracker->lock);
    
    while(row < dim){
        double sum = 0; 
        for(col = 0; col < dim; col++){
            sum += tracker->mstruct->data[row][col];
        }
        tracker->row_sum[row] = sum;
        pthread_mutex_lock(&tracker->rtracker->lock);
        row = tracker->rtracker->nextrow;
        tracker->rtracker->nextrow++;
        pthread_mutex_unlock(&tracker->rtracker->lock);
    }
}

/**************************************************/
void square_matrix(matrix_struct*  mat)
{
    int i, j, k, dim;
    double**  data;
    double**  square;

    dim  = mat->dim;
    data = mat->data;
    square = mat->square;

    for( i=0; i<dim; i++)
    {
        for( j=0; j<dim; j++)
        {
            square[i][j] = 0;
            for( k=0; k<dim; k++)
            {
                square[i][j] += data[i][k]*data[k][j];
            }
        }
    }
    return;
}

void * prod_cells(void* args)
{
    int col, row, dim;
    track_struct* tracker = (track_struct*) args;
    
    dim = tracker->mstruct->dim;

    pthread_mutex_lock(&tracker->mtracker->lock);
    row = tracker->mtracker->nextrow;
    col = tracker->mtracker->nextcol;
    if(row < dim - 1){
        tracker->mtracker->nextrow++;
    }else{
        tracker->mtracker->nextrow = 0;
        tracker->mtracker->nextcol++;
    }
    pthread_mutex_unlock(&tracker->mtracker->lock);
    
    while(col < dim){
        double prod = 0;
        int i;
        for(i = 0; i < dim; i++){
            prod += tracker->mstruct->data[row][i] * tracker->mstruct->data[i][col];
        }
        tracker->mstruct->square[row][col] = prod;
        
        pthread_mutex_lock(&tracker->mtracker->lock);
        row = tracker->mtracker->nextrow;
        col = tracker->mtracker->nextcol;
        if(row < dim - 1){
            tracker->mtracker->nextrow++;
        }else{
            tracker->mtracker->nextrow = 0;
            tracker->mtracker->nextcol++;
        }
        pthread_mutex_unlock(&tracker->mtracker->lock);
    }
}

/**************************************************/

void * run_threads(void* args)
{
	sum_rows(args);
	prod_cells(args);
}

void init_threads(matrix_struct* mat, int threads)
{
    int i;
    pthread_t tid[threads];

    track_struct* tracker = (track_struct*)malloc(sizeof(track_struct));
    tracker->row_sum = (double*)calloc(mat->dim, sizeof(double));
    tracker->mstruct = mat;
    tracker->rtracker = (row_tracker*)malloc(sizeof(row_tracker));
    tracker->rtracker->nextrow = 0;
    tracker->mtracker = (mat_tracker*)malloc(sizeof(mat_tracker));
    tracker->mtracker->nextrow = 0;
    tracker->mtracker->nextcol = 0;
    pthread_mutex_init(&tracker->rtracker->lock, NULL);
    pthread_mutex_init(&tracker->mtracker->lock, NULL);

    for(i = 0; i < threads; i++){
        pthread_create(&tid[i], NULL, run_threads, tracker);
    }
    for(i = 0; i < threads; i++){
        pthread_join(tid[i], NULL);
    }
    for(i = 0; i < mat->dim; i++){
        mat->sum += tracker->row_sum[i];
    }

    pthread_mutex_destroy(&tracker->rtracker->lock);
    pthread_mutex_destroy(&tracker->mtracker->lock);
    free(tracker->rtracker);
    free(tracker);
}

/**************************************************/
int main (int argc, char *argv[])
{
    int i;
    int dim = DEFAULT_DIM; 
    int interactive = FALSE;
    int threads = 1;
    double** tmp;
    matrix_struct mat;

    for( i = 1; i < argc; i++)
    {
        if( strncmp(argv[i], "-d", strlen("-d")) == 0 )
        {
            dim = atoi(argv[++i]);
        }
        else if( strncmp(argv[i], "-i", strlen("-i")) == 0 )
        {
            interactive = TRUE;
        }
        else if( strncmp(argv[i], "-t", strlen("-t")) == 0)
        {
            threads = atoi(argv[++i]);
        }
        else  /* unrecognized command line argument */
        {
            fprintf( stderr, "Usage: %s ", argv[0] );
            fprintf( stderr, "[-d N|-dimension N] " );
            fprintf( stderr, "[-i|-interactive] " );
            fprintf( stderr, "[-t N|-threads N] " );
            fprintf( stderr, "\n" );
            exit(-1);
        }
    }

    /* Allocate storage and initialize values */
    mat.dim = dim;
    mat.data   = allocate_matrix( dim, dim);
    mat.square = allocate_matrix( dim, dim);
    if( (mat.data == NULL) || (mat.square == NULL) )
    {
        printf("Error allocating memory\n");
        exit(-1);
    }
    if( interactive )
    {
        read_matrix(mat.data, dim, dim);
    }
    else
    {
        fill_matrix(mat.data, dim, dim);
    }

    if( threads == 1 )
        sum_matrix( &mat );
    else
        init_threads( &mat, threads );
    printf ("Matrix sum =  %f\n", mat.sum);

    if( threads == 1 )
        square_matrix( &mat );
    if( interactive )
    {
        print_matrix(mat.square, dim, dim);
    }

    free_matrix(mat.data);
    free_matrix(mat.square);

    exit(0);
}
