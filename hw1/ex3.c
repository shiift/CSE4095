#include <stdio.h>

int isEven(int n)
{
<<<<<<< HEAD
    if(n == 0){ return 1; }
    if(n % 2 == 0){
        return power( x, n/2 ) * power( x, n/2 );
    }else{
        return x * power( x, n/2 ) * power( x, n/2 );
    }
=======
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
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

double power2( double x, int n)
{
    double result;
    if(n == 0){ return 1; }
    if(n % 2 == 0){
        return power2( x * x, n/2);
    }else{
        return x * power2( x * x, n/2);
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
