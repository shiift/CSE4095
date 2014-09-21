#include <stdio.h>
#include <stdlib.h>

double** allocate_matrix( int rows, int cols )
{
    /*
        Allocate space for a rows X cols matrix 
    */
    int i;
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for(i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));
    return matrix;
}

void free_matrix( double** a, int rows )
{
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
}

int read_matrix( double** a, int rows, int cols )
{
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
}

void print_matrix( double** a, int rows, int cols )
{
    /*
        Print matrix elements to standard output, one line per row
    */
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }
}

double** transpose( double** a, int rows, int cols )
{
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
           if( t ) // was if ( t )
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
 
