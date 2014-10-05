#include <stdio.h>

int fib(int n)
{

  /* First two numbers are 1 (for base case) */
  if(n == 0)
    return 1;
  if(n == 1)
    return 1;

  /* Recurse to get the next number */
  return fib(n-1) + fib(n-2);
}

int isprime(int n)
{
  int i, prime = 0;
  for(i = 2; i < n; i++)
    {
      if(n % i == 0)
	prime = 1;
    }

  return prime;
}

/*
  Write the  body of the following function; return 1 if n-th Fibonacci 
  number is prime and 0 otherwise. Hint: use previous two functions!
*/
int check( int n)
{
  return isprime(fib(n));
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
