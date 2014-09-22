#include <stdio.h>

/*
  Computes the n-th power using recursion.
  Since two recursive calls are made to power1(x,n/2), 
  the overall runtime is linear in n
*/
double power1( double x, int n )
{
    if( n==0 ) { return 1; }
    if( n==1 ) { return x; }
    if( n%2==0 ) { return( power1(x,n/2)*power1(x,n/2) ); } 
    else return( x*power1(x,n/2)*power1(x,n/2) );

}

/*
  Computes the n-th power using recursion. 
  Since a single call is made to power(x,n/2), 
  the overall runtime is logarithmic in n
*/
double power( double x, int n )
{
    double p; 
    if( n==0 ) { return 1; }
    if( n==1 ) { return x; }
    p = power(x,n/2);
    if( n%2==0 ) { return( p*p ); } 
    else return( x*p*p );

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
