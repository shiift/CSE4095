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
double** transpose( double** a, int rows, int cols )
{
   double** mat = allocate_matrix(cols, rows);
   int i, j;
   for(i=0; i<rows; i++)
   {
      for(j=0; j<cols; j++)
      {
        mat[j][i] = a[i][j];
      }
   }
   return mat;
}

/********************************************************************/
int main()
{
    int     m, n;
    double**   a;
    double**   t;

    (void)printf( "Enter m and n (<= 0 to exit)" );
    if(2 != scanf( "%d %d", &m, &n ) )
    {
        return 1;
    }

    while( (m > 0) && (n > 0) )
    {
        (void)printf( "Enter %dx%d matrix\n", m, n );
        a = allocate_matrix( m, n);
        if( (a != NULL) && read_matrix(a, m, n) )
        {
           print_matrix(a, m, n);
           t = transpose(a, m, n);
           if(t != NULL) 
           {
              print_matrix(t, n, m);
              free_matrix(t);
           }
           free_matrix(a);
        }
        (void)printf( "Enter m and n (<= 0 to exit)" );
        if(2 != scanf( "%d %d", &m, &n ) )
        {
            return 1;
        }
    }

    return 0;
}

