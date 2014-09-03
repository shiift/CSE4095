#include <stdio.h>

/*
  Write the  body of the following function for computing the n-th 
  power using recursion
*/
double power( double x, int n )
{
}


int main() 
{
    double x;
    int n;
    
    while( 1 )
    {
        printf( "Enter the value of x and n (negative n to exit): " );
        scanf( "%lf %d", &x, &n );

        if( n < 0 ) return 0;

        printf( "%lf^%d = %lf\n", x, n, power(x,n) );

    }
}
