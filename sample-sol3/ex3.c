#include <stdio.h>
#include <stdlib.h>

/********************************************************************/
typedef struct node {
    int row, col;  /* row and column index */
    double val;    /* value */
    struct node *nextInRow;  /* next in row */
    struct node *nextInCol;  /* next in col */
} Node;

/********************************************************************/
typedef struct {
    int   nrows, ncols;   /* matrix dimensions */
    Node** row;     /* array of pointers to row heads */
    Node** col;     /* array of pointers to col heads */
} SparseMatrix;

/********************************************************************/
/* allocate and initialize a new node                               */
/********************************************************************/
Node* new_node( int row, int col, double val)
{
   Node* node = (Node*)calloc(1, sizeof(Node));
   if(node != NULL)
   {
      node->row= row; 
      node->col= col; 
      node->val= val; 
      node->nextInRow= NULL; 
      node->nextInCol= NULL; 
      return node;
   }
   else
   {
     return NULL;
   }
}

/********************************************************************/
/* allocate header arrays for a sparse matrix                       */
/********************************************************************/
SparseMatrix* new_matrix( int nrows, int ncols )
{
   SparseMatrix* mat = (SparseMatrix*)calloc(1, sizeof(SparseMatrix));
   if(mat != NULL)
   {
      mat->nrows = nrows;
      mat->ncols = ncols;
      mat->row = (Node**)calloc((size_t)nrows, sizeof(Node*));
      mat->col = (Node**)calloc((size_t)ncols, sizeof(Node*));
   }
   if(mat && mat->row && mat->col)
   {
      return mat;
   }
   else
   {
      if(mat->row) free(mat->row);
      if(mat->col) free(mat->col);
      if(mat) free(mat);
      return NULL;
   }
}

/********************************************************************/
/* recursively free all nodes in a sparse matrix row                */
/********************************************************************/
void free_row( Node* nodePtr )
{
  if(nodePtr != NULL)
  {
     free_row( nodePtr->nextInRow );
     free( nodePtr );
  }
  return;
}

/********************************************************************/
/* free all memory allocated for a sparse matrix                    */
/********************************************************************/
void free_matrix( SparseMatrix* a )
{
   int i;
   /* free nodes */
   for( i=0; i < a->nrows;  i++ )
   {
     free_row( a->row[i] );
   }
   /* free header arrays */
   free( a->row );
   free( a->col );
   /* free SparseMatrix struct */
   free( a );
   return;
}

/********************************************************************/
/* insert a new element in a sparse matrix & return 1 if successful */
/********************************************************************/
int insert( SparseMatrix* a, int row, int col, double val )
{
   Node* rowPtr = a->row[row];
   Node* colPtr = a->col[col];

   Node* new = new_node(row, col, val);
   if(new == NULL)
   {
      return 0;
   }

   /* find insert location in row */
   while(rowPtr && rowPtr->nextInRow && rowPtr->nextInRow->row < row) 
   {
      rowPtr = rowPtr->nextInRow; 
   }
   if(rowPtr == NULL)  /* first element in row */
   {
     a->row[row] = new;
   }
   else /* link new node after rowPtr */
   {
     new->nextInRow = rowPtr->nextInRow;
     rowPtr->nextInRow = new;
   }

   /* find insert location in column */
   while(colPtr && colPtr->nextInCol && colPtr->nextInCol->col < col) 
   {
      colPtr = colPtr->nextInRow; 
   }
   if(colPtr == NULL)  /* first element in column */
   {
     a->col[col] = new;
   }
   else /* link new node after colPtr */
   {
     new->nextInCol = colPtr->nextInCol;
     colPtr->nextInCol = new;
   }

   return 1;
}

/********************************************************************/
/* print the elements in a sparse matrix row by row                 */
/********************************************************************/
void print_matrix( SparseMatrix* a )
{
    int i;
    Node* node;

    printf("%d %d\n", a->nrows, a->ncols);
    for( i=0; i<a->nrows; i++)
    {
        for( node=a->row[i]; node!=NULL; node = node->nextInRow )
        {
            printf("%d %d %g\n", node->row, node->col, node->val);
        }
    }
    return;
}

/********************************************************************/
/* return the transpose of a given sparse matrix                    */
/********************************************************************/
SparseMatrix* transpose_matrix( SparseMatrix* a )
{
    int i;
    Node* node;
    SparseMatrix* mat = new_matrix(a->ncols, a->nrows);
    if(mat != NULL)
    {
       for( i=0; i<a->nrows; i++)
       {
           for( node=a->row[i]; node!=NULL; node = node->nextInRow )
           {
              insert(mat, node->col, node->row, node->val);
           }
       }
    }
    return mat;
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
        if( !insert(a, i, j, val) )
        {
            fprintf(stderr, "Could not allocate space for new matrix element!\n");
            return 1;
        }
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
