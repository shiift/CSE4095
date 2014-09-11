#include <stdio.h>

/*
  Computes the n-th power using recursion
*/
double power( double x, int n )
{
   double  power1; 

   if( n==0 ) { return(1); }
   if( n==1 ) { return(x); }
   power1 = power( x, n/2 );
   if( n % 1 == 0 ) { return power1*power1; }
   if( n % 1 == 1 ) { return x*power1*power1; }
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
