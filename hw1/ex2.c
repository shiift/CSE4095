#include <stdio.h>

/*
  Write the  body of the following function for computing the n-th 
  Fibonacci number using recursion
*/
int fib(int n)
{
    int fib_n1 = 1;
    int fib_n2 = 0;

    int i, temp;
    if(i = 0){
        return fib_n2;
    }
    for(i = 2; i <= n; i++){
        temp = fib_n1;
        fib_n1 += fib_n2;
        fib_n2 = temp;    
    }

    return fib_n1;
}

/*
  Write the  body of the following function; return 1 if n is prime and 0 
  otherwise
*/
int isprime(int n)
{
    int i;
    if(n < 2){ return 0; }                      // no numbers less than 2
    if(n == 2 || n == 3){ return 1; }           // 2 and 3 are prime
    if(n % 2 == 0 || n % 3 == 0){ return 0; }   // mult of 2 and 3 are not
    for(i = 5; i < n/2; i += 6){                // check multiples from 5 -> n/2 (close enough to sqrt(n)) 
        if(n % i == 0 || n % (i+2) == 0){
            return 0;
        }
    }
    return 1;                                   // all others are prime
}

/*
  Write the  body of the following function; return 1 if n-th Fibonacci 
  number is prime and 0 otherwise. Hint: use previous two functions!
*/
int check( int n)
{
    if(n > 46){ printf( "ERROR: Your number is too large for this program.\n" ); }
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
