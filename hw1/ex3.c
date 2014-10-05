#include <stdio.h>

int isEven(int n)
{
  return (n % 2 == 0) ? 1 : 0;
}

double power( double x, int n)
{
  /* Check base-cases */
  if(n == 0)
    return 1;
  if(n == 1)
    return x;

  /* Check which recursion algorithm to use  */
  if(isEven(n))
      return power(x, n/2) * power(x, n/2);
  else
    return x * power(x, n/2) * power(x, n/2);
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
