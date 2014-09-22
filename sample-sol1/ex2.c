#include <stdio.h>

/*
  Computes n-th Fibonacci number using recursion
*/
int fib(int n)
{
    if( n == 0 ) { return 0; }
    if( n == 1 ) { return 1; }

    return fib(n-1) + fib(n-2);
}

/*
  Returns 1 if n is prime and 0 otherwise
*/
int isprime(int n)
{
    int i; 

    if( n < 2 ) { return( 0 ); }

    for( i = 2; i*i < n;  i++ ) 
    {
        if( n % i == 0 ) { return 0; }
    }

    return 1;
}

/*
  Returns 1 if n-th Fibonacci number is prime and 0 otherwise
*/
int check( int n)
{
  return isprime( fib(n) );
}

int main() 
{
    int n;
    
    while( 1 )
    {
        printf( "Enter the value of n (negative to exit): " );
        scanf( "%d", &n );
        if( n < 0 ) return 0;
        if( check(n) )
        {
            printf( "%dth Fibonacci number is prime\n",  n );
        }
        else
        {
            printf( "%dth Fibonacci number is not prime\n", n );
        }

    }
}
