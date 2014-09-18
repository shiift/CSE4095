#include <stdio.h>
#include <stdlib.h>

double** allocate_matrix( int rows, int cols )
{
    /*
        Allocate space for a rows X cols matrix 
    */
}

void free_matrix( double** a, int rows )
{
    /*
        Free the space for a matrix; the number of rows 
        may be needed if each row is allocated with a 
        separate malloc/calloc
    */
}

int read_matrix( double** a, int rows, int cols )
{
    /*
        Read in from standard input the elements of a 
        rows X cols matrix, given row by row, and within 
        a row in increasing column order
    */
}

void print_matrix( double** a, int rows, int cols )
{
    /*
        Print matrix elements to standard output, one line per row
    */
}

double** transpose( double** a, int rows, int cols )
{
    /*
        Allocate and return the address of a matrix that contains 
        the element of "a" in transposed order (with rows and columns 
        swapped)
    */
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
 
