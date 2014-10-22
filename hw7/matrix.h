#ifndef __matrix_h
#define __matrix_h

double** allocate_matrix( int rows, int cols );
void free_matrix( double** a );
int  read_matrix( double** a, int rows, int cols );
void print_matrix( double** a, int rows, int cols );
void fill_matrix( double** a, int rows, int cols );

#endif
