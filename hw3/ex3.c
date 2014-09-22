#include <stdio.h>
#include <stdlib.h>

/*
  Define and typed a structure called SparseMatrix for storing 
  matrices using the linked list representation given in the 
  project description.  Also define any additional structures 
  (e.g., for nodes).
*/

SparseMatrix* new_matrix( int nrows, int ncols )
{
    /*
      Allocate space for a sparse matrix with nrows rows 
      and ncols columns
    */

}

void free_matrix( SparseMatrix* a )
{
    /*
        Free all space allocated for matrix "a"
    */

}

SparseMatrix* print_matrix( SparseMatrix* a )
{
    /*
      Print a sparse matrix to the standard input in 
      the format given in the project description
    */
}

SparseMatrix* transpose_matrix( SparseMatrix* a )
{
    /*
        Allocate and return the address of a sparse matrix that contains 
        the element of "a" in transposed order (with rows and columns 
        swapped)
    */
}



/***************************************************/

int main()
{
    int i, j, m, n;
    SparseMatrix* a;
    SparseMatrix* b;
    double val;

    scanf( "%d %d", &m, &n );
    if( (m <= 0) || (n <= 0) )
    {
        fprintf(stderr, "Matrix dimensions must be positive!\n");
        return 1;
    }

    if( !(a = new_matrix(m,n)) )
    {
        fprintf(stderr, "Could not allocate memory for matrix\n");
        return 1;
    }

    while( scanf("%d %d %lf", &i, &j, &val) != EOF )
    {
        /*
           Add code to insert val in row i and column j of the matrix 
        */
    }

    if( !(b = transpose_matrix(a)) )
    {
        fprintf(stderr, "Could not allocate memory for transpose\n");
        return 1;
    }

    print_matrix( b );

    free_matrix( a );
    free_matrix( b );

    return 0;
}
