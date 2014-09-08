#include <stdio.h>

struct FibNum {
    int n_1;
    int n_2;
};

/*
  Write the  body of the following function for computing the n-th 
  Fibonacci number using recursion
*/
struct FibNum fib(int n)
{
    int temp;
    struct FibNum fibs;

    if(n == 0){
        fibs.n_1 = 0;
        fibs.n_2 = 0;
        return fibs;
    }
    if(n == 1){
        fibs.n_1 = 1;
        fibs.n_2 = 0;
        return fibs;
    }
    fibs = fib(n-1);
    temp = fibs.n_1;
    fibs.n_1 += fibs.n_2;
    fibs.n_2 = temp;
    return fibs; 
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
    for(i = 5; i*i < n; i += 6){                // check multiples from 5 -> n/2 (close enough to sqrt(n)) 
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
    return isprime(fib(n).n_1);
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
