#include <stdio.h>

<<<<<<< HEAD
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
=======
int fib(int n)
{

  /* First two numbers are 1 (for base case) */
  if(n == 0)
    return 1;
  if(n == 1)
    return 1;

  /* Recurse to get the next number */
  return fib(n-1) + fib(n-2);
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

int isprime(int n)
{
<<<<<<< HEAD
    int i;
    if(n < 2){ return 0; }                      // no numbers less than 2
    if(n == 2 || n == 3){ return 1; }           // 2 and 3 are prime
    if(n % 2 == 0 || n % 3 == 0){ return 0; }   // mult of 2 and 3 are not
    for(i = 5; i*i < n; i += 6){                // check multiples from 5 -> sqrt(n)
        if(n % i == 0 || n % (i+2) == 0){
            return 0;
        }
    }
    return 1;                                   // all others are prime
=======
  int i, prime = 0;
  for(i = 2; i < n; i++)
    {
      if(n % i == 0)
	prime = 1;
    }

  return prime;
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

/*
  Write the  body of the following function; return 1 if n-th Fibonacci 
  number is prime and 0 otherwise. Hint: use previous two functions!
*/
int check( int n)
{
<<<<<<< HEAD
    if(n > 46){ printf( "ERROR: Your number is too large for this program.\n" ); }
    return isprime(fib(n).n_1);
=======
  return isprime(fib(n));
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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
