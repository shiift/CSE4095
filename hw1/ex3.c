#include <stdio.h>

/*
  Write the  body of the following function for computing the n-th 
  power using recursion
*/
double power( double x, int n )
{
    if(n == 0){ return 1; }
    if(n % 2 == 0){
        return power( x, n/2 ) * power( x, n/2 );
    }else{
        return x * power( x, n/2 ) * power( x, n/2 );
    }
}

double power2( double x, int n)
{
    double result;
    if(n == 0){ return 1; }
    result = power2( x, n/2 );
    if(n % 2 == 0){
        return result * result;
    }else{
        return x * result * result;
    }
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

        printf( "%lf^%d = %lf\n", x, n, power2(x,n) );

    }
}
