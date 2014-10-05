#include <stdio.h>
#include <stdlib.h>

typedef struct MatrixNode
{
  double data;
  int row;
  int col;
  
  struct MatrixNode* nextrow;
  struct MatrixNode* nextcol;
} MatrixNode;

typedef struct SparseMatrix
{
  MatrixNode** rows;
  MatrixNode** cols;

  int nrows;
  int ncols;

} SparseMatrix;

SparseMatrix* new_matrix( int nrows, int ncols )
{
  SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
  matrix->rows = (MatrixNode**)calloc(nrows, sizeof(MatrixNode*));
  matrix->cols = (MatrixNode**)calloc(ncols, sizeof(MatrixNode*));

  matrix->nrows = nrows;
  matrix->ncols = ncols;

  return matrix;
}

void free_matrix( SparseMatrix* a )
{
  int i;
  MatrixNode* seek;

  for(i=0; i < a->nrows; i++)
    {
      seek = a->rows[i];
      while(seek)
	{
	  MatrixNode* next = seek->nextcol;
	  free(seek);
	  seek = next;
	}
    }

}

SparseMatrix* print_matrix_correct( SparseMatrix* a )
{
  int i;
  MatrixNode* seek;

  printf("\n%d %d\n", a->nrows, a->ncols);
  for(i=0; i < a->nrows; i++)
    {
      seek = a->rows[i];
      while(seek)
	{
	  printf("%d %d %.0lf\n", seek->row, seek->col, seek->data);
	  seek = seek->nextcol;
	}
    }
}

SparseMatrix* print_matrix( SparseMatrix* a )
{
  int i, j;
  MatrixNode* seek;

  print_matrix_correct(a); /* print matrix the right way */

  printf("-----------Extra print style--------");
  printf("\n%d %d\n", a->nrows, a->ncols);
  for(i=0; i < a->nrows; i++)
    {
      seek = a->rows[i];
      for(j=0; j < a->ncols; j++)
	{
	  if(!seek || seek->col > j) /* Output zeroes to pad */
	    printf("0.00 ");
	  else
	    {
	      printf("%.2lf ", seek->data);
	      seek = seek->nextcol;
	    }
	}

      printf("\n");
    }
}

SparseMatrix* transpose_matrix( SparseMatrix* a )
{
  void insert_into(SparseMatrix* m, double n, int row, int col);

  int i;
  SparseMatrix* b = new_matrix(a->ncols, a->nrows);
  MatrixNode* seek;
  
  for(i=0; i < a->nrows; i++)
    {
      seek = a->rows[i];
      while(seek)
	{
	  insert_into(b, seek->data, seek->col, seek->row);
	  seek = seek->nextcol;
	}
    }

  return b;
}

MatrixNode* new_node( double n, int row, int col)
{
  MatrixNode* node = (MatrixNode*)malloc(sizeof(MatrixNode));
  node->data = n;
  node->row = row;
  node->col = col;

  node->nextrow = NULL;
  node->nextcol = NULL;
  return node;
}

void insert_into( SparseMatrix* a, double n, int row, int col)
{
  MatrixNode* node = new_node(n, row, col);
  MatrixNode* seek;

  if(!a->rows[row])                  /* Nothing in row slot */
    a->rows[row] = node;
  else if(a->rows[row]->col > col)  /* Smallest row - insert into first */
    {
      node->nextcol = a->rows[row];
      a->rows[row] = node;
    }
  else                             /* Loop through columns in row */
    {
      seek = a->rows[row];
      while(seek)
	{
	  if(!seek->nextcol)     /* Reached last node - insert into end */
	    {
	      seek->nextcol = node;
	      break;
	    }

	  if(seek->col < col && seek->nextcol->col > col) /* Right col */
	    {
	      node->nextcol = seek->nextcol;
	      seek->nextcol = node;
	      break;
	    }

	  seek = seek->nextcol;   /* Look at next node */
	}
    }


  if(!a->cols[col])              /* no value in columns */
    a->cols[col] = node;
  else if(a->cols[col]->row > row)    /* smallest value so far */
    {
      node->nextrow = a->cols[col];
      a->cols[col] = node;
    }
  else
    {
      seek = a->cols[col];
      while(seek)
	{
	  if(!seek->nextrow)            /* reached end of list */
	    {
	      seek->nextrow = node;
	      break;
	    }

	  if(seek->row < row && seek->nextrow->row > row) /* right place */
	    {
	      node->nextrow = seek->nextrow;
	      seek->nextrow = node;
	      break;
	    }
	  seek = seek->nextrow;
	}
    }
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
      insert_into(a, val, i, j);
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
