#include <stdio.h>
#include <stdlib.h>

/********************************************************************/
double** allocate_matrix( int rows, int cols )
{
   int i;
   /*
      allocate pointers to row arrays
   */
   double** mat = (double**)calloc((size_t)rows, sizeof(double*));
   /*
      allocate space for all row arrays in one calloc call
   */
   double* storage = (double*)calloc((size_t)rows*cols, sizeof(double));

   if( (mat != NULL) && (storage != NULL) )
   {
      /*
        set row array pointers
      */

      for(i=0; i<rows; i++)
      {
         mat[i] = storage + i*cols;
      }
      return mat;
   }
   else
   {
      return NULL;
   }
}

/********************************************************************/
void free_matrix( double** a )
{
   free( a[0] );  /* free the space allocated for row arrays  */
   free( a );     /* free the array of pointers to row arrays */
}


/********************************************************************/
int read_matrix( double** a, int rows, int cols )
{
   int i, j;

   for(i=0; i<rows; i++)
   {
      for(j=0; j<cols; j++)
      {
        if( !scanf("%lf", &(a[i][j]) ) )
        {
           return 0;
        }
      }
   }
   return 1;
}

/********************************************************************/
void print_matrix( double** a, int rows, int cols )
{
   int i, j;
   for(i=0; i<rows; i++)
   {
      for(j=0; j<cols; j++)
      {
        (void)printf("%g ", a[i][j] );
      }
      (void)printf("\n");
   }
   (void)printf("\n");
}

/********************************************************************/

void fill_matrix( double** a, int rows, int cols )
{
   int i, j;

   for(i=0; i<rows; i++)
   {
      for(j=0; j<cols; j++)
      {
        a[i][j] = i + j;
      }
   }
}

/********************************************************************/
