#include <stdio.h>

int main() 
{
    int n;
    int sum;
    
    printf( "Enter the value of n: " );
    scanf( "%d", &n );

    /* 
        add code to compute using only "for" loops the sum of integers 
        from n to 2n if n is nonnegative, or from 2n to n if 
        n is negative
    */
    int i;
    if(n >= 0){
        for(i = n; i <= 2 * n; i++){
            sum += i;
        }
    }else{
        for(i = 2 * n; i <= n; i++){
            sum += i;
        }
    }
    
    printf( "Sum is %d\n", sum );
}
