#include <stdio.h>
#include <stdlib.h>

/*
  Compute the n-th power using recursion
*/
double power( double x, int n )
{
   double  power1; 

   if( n==0 ) { return(1); }
   if( n==1 ) { return(x); }
   power1 = power( x, n/2 );
   if( n % 2 == 0 ) { return(power1*power1); }
   else { return(x*power1*power1); }
}

/*********************************************
  Evaluate polynomial using the power function
*********************************************/
double eval( int* a, int n, double x )
{
   int i;
   double result = 0;

   for( i=0; i<=n; i++ )
   {
       result += a[i]*power(x, i);
   }
   return result;
}


/*********************************************
  Evaluate polynomial using recursive 
  implementation of Horner's rule
*********************************************/
double eval2( int* a, int n, double x )
{
   if(n ==0) return a[0];
   else return a[0] + x * eval2(a+1, n-1, x);
}

/********************************************/
int main()
{
    int    i, n;
    int*   a;  /* coefficient array */
    double x;

    printf( "Enter the value of x: " );
    (void)scanf( "%lf", &x );
    (void)printf( "Enter the degree n: " );
    (void)scanf( "%d", &n );

    /* allocate coefficient array */
    a = (int*)malloc( (n+1)*sizeof(int) );
    for( i = 0; i<=n; i++ )
    { 
        (void)printf( "Enter a[%d]: ", i );
        (void)scanf( "%d", a+i );
    }

    (void)printf( "Polynomial evaluates to: %f %f\n", eval(a, n, x), eval2(a, n, x) );
    free( a );
    return 0;
}
