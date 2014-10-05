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

typedef struct SparseMatrix{
    int rows;
    int cols;
    struct Node** row;
    struct Node** col;
} SparseMatrix;

typedef struct Node{
    double data;
    int row;
    int col;
    struct Node* next_row;
    struct Node* next_col;
} Node;

SparseMatrix* new_matrix( int nrows, int ncols )
{
<<<<<<< HEAD
    /*
      Allocate space for a sparse matrix with nrows rows 
      and ncols columns
    */
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(struct SparseMatrix));
    matrix->rows = nrows;
    matrix->cols = ncols;
    matrix->row = (Node**)malloc(sizeof(struct Node*) * nrows);
    matrix->col = (Node**)malloc(sizeof(struct Node*) * ncols);
    int i;
    for(i = 0; i < nrows; i++){
        matrix->row[i] = NULL;
    }
    for(i = 0; i < ncols; i++){
        matrix->col[i] = NULL;
    }   
    return matrix;
=======
  SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));
  matrix->rows = (MatrixNode**)calloc(nrows, sizeof(MatrixNode*));
  matrix->cols = (MatrixNode**)calloc(ncols, sizeof(MatrixNode*));

  matrix->nrows = nrows;
  matrix->ncols = ncols;

  return matrix;
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

void free_matrix( SparseMatrix* a )
{
<<<<<<< HEAD
    /*
        Free all space allocated for matrix "a"
    */
    int i;
    for(i = 0; i < a->rows; i++){
        Node* current_node = a->row[i];
        while(current_node != NULL){
            Node* next_node = current_node->next_col;
            free(current_node);
            current_node = next_node;
        }
    }
    free(a->row);
    free(a->col);
    free(a);
=======
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

>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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
<<<<<<< HEAD
    /*
      Print a sparse matrix to the standard input in 
      the format given in the project description
    */
    int i;
    printf("%d %d\n", a->rows, a->cols);
    for(i = 0; i < a->rows; i++){
        Node* current_node = a->row[i];
        while(current_node != NULL){
            printf("%d %d %lf\n", current_node->row, current_node->col, current_node->data);
            current_node = current_node->next_col;
        }
    }
    return a;
}

Node* insert_node( SparseMatrix* a, int i, int j, double val )
{
    /*
      Insert a new node into the matrix
     */
    // Allocate space for new node and define it 
    Node* node = (Node*)malloc(sizeof(struct Node));
    node->row = i;
    node->col = j;
    node->data = val;
    node->next_row = NULL;
    node->next_col = NULL;

    // Find row and insert the new node
    if(a->row[i] == NULL){
        a->row[i] = node;
    }else{
        Node* current_node = a->row[i];
        while(current_node->next_col != NULL){
            current_node = current_node->next_col;
        }
        current_node->next_col = node;
    }

    // Find col and insert the new node
    if(a->col[j] == NULL){
        a->col[j] = node;
    }else{
        Node* current_node = a->col[j];
        while(current_node->next_row != NULL){
            current_node = current_node->next_row;
        }
        current_node->next_row = node;
    }
    return node;
=======
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
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

SparseMatrix* transpose_matrix( SparseMatrix* a )
{
<<<<<<< HEAD
    /*
        Allocate and return the address of a sparse matrix that contains 
        the element of "a" in transposed order (with rows and columns 
        swapped)
    */
    SparseMatrix* b = new_matrix(a->cols, a->rows);
    int i;
    for(i = 0; i < a->cols; i++){
        Node* current_node = a->col[i];
        while(current_node != NULL){
            Node* new_node = insert_node(b, current_node->col, current_node->row, current_node->data);
            current_node = current_node->next_row;
        }
    }
    return b;
=======
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
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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
<<<<<<< HEAD
        /*
           Add code to insert val in row i and column j of the matrix 
        */
        if( i < 0 || j < 0 || i >= m || j >= n){
            printf("Your dimensions fall outside the size of the array\n");
            exit;
        }
        insert_node(a, i, j, val);
=======
      insert_into(a, val, i, j);
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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
