#include <stdio.h>
#include <stdlib.h>

double** allocate_matrix( int rows, int cols )
{
  int i;

  /* Create row of all pointers (those will be individually allocated */
  double** matrix = (double **)calloc(rows, sizeof(double *) * rows);
  
  for(i=0; i < rows; i++)
      matrix[i] = (double *)calloc(cols, sizeof(double) * cols);

  return matrix;
}

void free_matrix( double** a, int rows )
{
  int i;
  for(i=0; i < rows; i++)
    free(a[i]);
}

int read_matrix( double** a, int rows, int cols )
{
  int i, j;
  double temp;

  for(i=0; i < rows; i++)
    {
      printf("Enter Row %d: ", (i+1));
      for(j=0; j < rows; j++)
	{
	  scanf("%lf", &temp);
	  a[i][j] = temp;
	}
    }
}

void print_matrix( double** a, int rows, int cols )
{
  int i, j;
  for(i=0; i < rows; i++)
    {
      for(j=0; j < cols; j++)
	printf("%lf ", a[i][j]);
      
      printf("\n");
    }
}

double** transpose( double** a, int rows, int cols )
{
  int i, j;
  double** transpose = allocate_matrix(cols, rows);

  for(i=0; i < rows; i++)
    {
      for(j=0; j < cols; j++)
	{
	  transpose[j][i] = a[i][j];
	}
    }

  return transpose;
}

int main()
{
    int     m, n;
    double**   a;
    double**   t;

    printf( "Enter m and n (<= 0 to exit)" );
    scanf( "%d %d", &m, &n );

    while( (m > 0) && (n > 0) )
    {
        a = allocate_matrix( m, n);
        if( a )
        {
           printf( "Enter %dx%d matrix\n", m, n );
           read_matrix(a, m, n);
           printf( "Input matrix\n" );
           print_matrix(a, m, n);
           t = transpose(a, m, n);
           if( t ) 
           {
              printf( "Transposed matrix\n" );
              print_matrix(t, n, m);
              free_matrix(t, n);
           }
           free_matrix(a, m);
        }
        printf( "Enter m and n (<= 0 to exit)" );
        scanf( "%d %d", &m, &n );
    }
    return 0;
}
 
