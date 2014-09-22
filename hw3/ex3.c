#include <stdio.h>
#include <stdlib.h>

/*
  Define and typed a structure called SparseMatrix for storing 
  matrices using the linked list representation given in the 
  project description.  Also define any additional structures 
  (e.g., for nodes).
*/

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
    /*
      Allocate space for a sparse matrix with nrows rows 
      and ncols columns
    */
    SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(struct SparseMatrix));
    matrix->rows = nrows;
    matrix->cols = ncols;
    matrix->row = (Node**)malloc(sizeof(struct Node*) * nrows);
    matrix->col = (Node**)malloc(sizeof(struct Node*) * ncols);
    return matrix;
}

void free_matrix( SparseMatrix* a )
{
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
    free(a);
}

SparseMatrix* print_matrix( SparseMatrix* a )
{
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
}

SparseMatrix* transpose_matrix( SparseMatrix* a )
{
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
        if( i < 0 || j < 0 || i >= m || j >= n){
            printf("Your dimensions fall outside the size of the array\n");
            exit;
        }
        insert_node(a, i, j, val);
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
