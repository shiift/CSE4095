#include <stdio.h>
#include <stdlib.h>

double** allocate_matrix( int rows, int cols )
{
<<<<<<< HEAD
    /*
        Allocate space for a rows X cols matrix 
    */
    int i;
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for(i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));
    return matrix;
=======
  int i;

  /* Create row of all pointers (those will be individually allocated */
  double** matrix = (double **)calloc(rows, sizeof(double *) * rows);
  
  for(i=0; i < rows; i++)
      matrix[i] = (double *)calloc(cols, sizeof(double) * cols);

  return matrix;
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

void free_matrix( double** a, int rows )
{
<<<<<<< HEAD
    /*
        Free the space for a matrix; the number of rows 
        may be needed if each row is allocated with a 
        separate malloc/calloc
    */
    int i;
    for(i = 0; i < rows; i++){
        free(a[i]);
    }
    free(a);
=======
  int i;
  for(i=0; i < rows; i++)
    free(a[i]);
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

int read_matrix( double** a, int rows, int cols )
{
<<<<<<< HEAD
    /*
        Read in from standard input the elements of a 
        rows X cols matrix, given row by row, and within 
        a row in increasing column order
    */
    int i, j;
    double temp;
    for(i = 0; i < rows; i++) {
        for(j = 0; j < cols; j++){
            scanf("%lf", &a[i][j]);
        }
    }
    return 0;
=======
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
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

void print_matrix( double** a, int rows, int cols )
{
<<<<<<< HEAD
    /*
        Print matrix elements to standard output, one line per row
    */
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%lf ", a[i][j]);
        }
        printf("\n");
=======
  int i, j;
  for(i=0; i < rows; i++)
    {
      for(j=0; j < cols; j++)
	printf("%lf ", a[i][j]);
      
      printf("\n");
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
    }
}

double** transpose( double** a, int rows, int cols )
{
<<<<<<< HEAD
    /*
        Allocate and return the address of a matrix that contains 
        the element of "a" in transposed order (with rows and columns 
        swapped)
    */
    int i, j;
    double** t = allocate_matrix(cols, rows);
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            t[j][i] = a[i][j];
        }
    }
    return t;
=======
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
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

int main()
{
    int     m, n;
    double**   a;
    double**   t;

    printf( "Enter m and n (<= 0 to exit)\n" );
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
           if( t ) // was if ( t )
           {
              printf( "Transposed matrix\n" );
              print_matrix(t, n, m);
              free_matrix(t, n);
           }
           free_matrix(a, m);
        }
        printf( "Enter m and n (<= 0 to exit)\n" );
        scanf( "%d %d", &m, &n );
    }
    return 0;
}
 
