#include <stdio.h>
#include <stdlib.h>

/*
  Write the  body of the following function for computing the n-th 
  power using recursion
*/

// assignment 1 power function
double power( double x, int n)
{
    double result;
    if(n == 0){ return 1; }
    if(n % 2 == 0){
        return power( x * x, n/2);
    }else{
        return x * power( x * x, n/2);
    }
}

// evaluation of polynomial using power function
double eval( int* a, int n, double x )
{
    int i;
    double total = 0;
    for(i=0; i<=n; i++){
        total += a[i] * power(x,i);
    }
    return total;
}


// recursive evaluation of polynomial
double eval_rec( int* a, int n, double x, int d)
{
    if(d == n){
        return a[n];
    }
    return a[d] + x * eval_rec(a, n, x, d + 1);
}

// adpater to make eval_rec compatible with the function
// call for eval
double eval2( int* a, int n, double x )
{
    return eval_rec(a, n, x, 0);
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

    printf( "Polynomial evaluates to: %lf\n", eval2(a, n, x) );
}
