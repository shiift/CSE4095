#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  Write the  body of the following function for computing the n-th 
  power using recursion
*/

double eval( int* a, int n, double x )
{
  int i;
  double sum;

  for(i = 0; i < n+1; i++)
    {
      sum += (a[i] * pow(x, i));
    }

  return sum;
}

int main()
{
    int    i, n;
    int*   a;  /* coefficient array */
    double x;

    printf( "Enter the value of x: " );
    scanf( "%lf", &x );
    printf( "Enter the degree n: " );
    scanf( "%d", &n );

    /* allocate coefficient array */
    a = (int*)malloc( (n+1)*sizeof(int) );
    for( i = 0; i<=n; i++ )
    { 
        printf( "Enter a[%d]: ", i );
        scanf( "%d", a+i );
    }

    printf( "Polynomial evaluates to: %lf\n", eval(a, n, x) );
}
