#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/**************************************************/
int main (int argc, char *argv[])
{
   int i;
   int dim = DEFAULT_DIM; 
   int interactive = FALSE;
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
      else  /* unrecognized command line argument */
      {
         fprintf( stderr, "Usage: %s ", argv[0] );
         fprintf( stderr, "[-dimension N | -d N] " );
         fprintf( stderr, "[-i | -interactive] " );
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

   sum_matrix( &mat );
   printf ("Matrix sum =  %f\n", mat.sum);

   square_matrix( &mat );

   if( interactive )
   {
      print_matrix(mat.square, dim, dim);
   }

   free_matrix(mat.data);
   free_matrix(mat.square);

   exit(0);
}
