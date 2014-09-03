#include <stdio.h>

/*
  Write the  body of the following function for computing the n-th 
  Fibonacci number using recursion
*/
int fib(int n)
{
}

/*
  Write the  body of the following function; return 1 if n is prime and 0 
  otherwise
*/
int isprime(int n)
{
}

/*
  Write the  body of the following function; return 1 if n-th Fibonacci 
  number is prime and 0 otherwise. Hint: use previous two functions!
*/
int check( int n)
{
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
