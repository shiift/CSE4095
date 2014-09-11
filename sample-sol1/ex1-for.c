#include <stdio.h>

int main() 
{
    int n, i;
    int sum;
    
    printf( "Enter the value of n: " );
    scanf( "%d", &n );

    /* 
        Compute sum of integers from n to 2n if n is nonnegative, or 
        from 2n to n if n is negative, using only "for" loops
    */
    sum = 0;

    if( n>=0 )
    {
       for( i=2*n; i>=n; i-- )
       {
          sum += i;
       }
    }
    else
    {
       for( i=2*n; i<=n; i++ )
       {
          sum += i;
       }
    }
    
    printf( "Sum is %d\n", sum );

    return 0;
}
