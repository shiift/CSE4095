#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define TRUE  1
#define FALSE 0

#define DEFAULT_DIM 2
#define DEFAULT_NUM_THREADS 1
#define MAX_NUM_THREADS 10

typedef struct
{
   int         dim;
   double**   data;
   double** square;
   double      sum;
   int    num_threads;
   int    tid;
} matrix_struct;

/**************************************************/
void sum_matrix(void* thread_arg)
{
   int i, j, dim, num_threads, tid;
   double    sum;
   double**  data;
   matrix_struct*  mat = (matrix_struct*)thread_arg;

   dim  = mat->dim;
   data = mat->data;
   num_threads = mat->num_threads;
   tid = mat->tid;

   sum = 0;
   i = tid;
   while( i < dim )
   {
      for( j=0; j<dim; j++)
      {
         sum += data[i][j];
      }
      i += num_threads;
   }

   mat->sum = sum;
   pthread_exit(NULL);
}

/**************************************************/
void square_matrix(void* thread_arg)
{
   int i, j, k, dim, tid, num_threads;
   double**  data;
   double**  square;
   matrix_struct*  mat = (matrix_struct*)thread_arg;

   dim  = mat->dim;
   data = mat->data;
   square = mat->square;
   num_threads = mat->num_threads;
   tid = mat->tid;

   i = tid;
   while( i < dim )
   {
      for( j=0; j<dim; j++)
      {
         square[i][j] = 0;
         for( k=0; k<dim; k++)
         {
            square[i][j] += data[i][k]*data[k][j];
         }
      }
      i += num_threads;
   }
   pthread_exit(NULL);
}

/**************************************************/
int main (int argc, char *argv[])
{
   int i, rc;
   int dim = DEFAULT_DIM;
   int interactive = FALSE;
   int num_threads = DEFAULT_NUM_THREADS;
   pthread_t threads[MAX_NUM_THREADS];
   matrix_struct mat[MAX_NUM_THREADS];
   double mysum;


   for( i = 1; i < argc; i++)
   {
      if( strncmp(argv[i], "-d", strlen("-d")) == 0 )
      {
         dim = atoi(argv[++i]);
      }
      else if( strncmp(argv[i], "-t", strlen("-t")) == 0 )
      {
         num_threads = atoi(argv[++i]);
         if(num_threads > MAX_NUM_THREADS)
         {
            num_threads = MAX_NUM_THREADS;
         }
      }
      else if( strncmp(argv[i], "-i", strlen("-i")) == 0 )
      {
         interactive = TRUE;
      }
      else  /* unrecognized command line argument */
      {
         fprintf( stderr, "Usage: %s ", argv[0] );
         fprintf( stderr, "[-d N|-dimension N] " );
         fprintf( stderr, "[-t N|-threads N] " );
         fprintf( stderr, "[-i|-interactive] " );
         fprintf( stderr, "\n" );
         exit(-1);
      }
   }

   /* Allocate storage and initialize values */
   mat[0].dim = dim;
   mat[0].tid = 0;
   mat[0].num_threads = num_threads;
   mat[0].data   = allocate_matrix( dim, dim);
   mat[0].square = allocate_matrix( dim, dim);
   if( (mat[0].data == NULL) || (mat[0].square == NULL) )
   {
      printf("Error allocating memory\n");
      exit(-1);
   }
   if( interactive )
   {
      read_matrix(mat[0].data, dim, dim);
   }
   else
   {
      fill_matrix(mat[0].data, dim, dim);
   }

   for(i=1; i<num_threads; i++)
   {
      mat[i].dim = dim;
      mat[i].tid = i;
      mat[i].num_threads = num_threads;
      mat[i].data   = mat[0].data;    /* all threads use the same data matrix */
      mat[i].square = mat[0].square;  /* all threads use the same results matrix */
   }

   /* compute sum */
   for(i=0; i<num_threads; i++)
   {
      rc = pthread_create(&threads[i], NULL, sum_matrix, (void *)&(mat[i]));
      if (rc)
      {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
   mysum = 0;
   for(i=0; i<num_threads; i++)
   {
     rc = pthread_join(threads[i], NULL);
     if (rc) {
       printf("ERROR; return code from pthread_join() is %d\n", rc);
       exit(-1);
     }
     mysum += mat[i].sum;
   }
   printf ("Matrix sum =  %f\n", mysum);


   /* square the matrix using threads */
   for(i=0; i<num_threads; i++)
   {
      rc = pthread_create(&threads[i], NULL, square_matrix, (void *)&(mat[i]));
      if (rc)
      {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* make sure all threads have finished */
   for(i=0; i<num_threads; i++)
   {
     rc = pthread_join(threads[i], NULL);
     if (rc) {
       printf("ERROR; return code from pthread_join() is %d\n", rc);
       exit(-1);
     }
   }

   if( interactive )
   {
      print_matrix(mat[0].square, dim, dim);
   }

   free_matrix(mat[0].data);
   free_matrix(mat[0].square);

   exit(0);
}
