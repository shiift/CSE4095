#include <stdio.h>

int main() 
{
    int n, i;
    int sum;
    
    printf( "Enter the value of n: " );
    scanf( "%d", &n );

    /* 
        Compute sum of integers from n to 2n if n is nonnegative, or
        from 2n to n if n is negative, using only "while" loops
    */
    sum = 0;    
    i=2*n; 

    if( n >= 0 )
    {
       while( i >= n )
       {
           sum += i;
           i--;
       }
    }
    else    
    {
       while( i <= n )
       {
           sum += i;
           i++;
       }
    }

    printf( "Sum is %d\n", sum );

    return 0;
}
