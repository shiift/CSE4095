#include <stdio.h>

int main() 
{
    int n;
    int sum;
    
    printf( "Enter the value of n: " );
    scanf( "%d", &n );

    /* 
        add code to compute using only "while" loops the sum of integers
        from n to 2n if n is nonnegative, or from 2n to n if 
        n is negative  
    */
    int i;
    if(n >= 0){
        i = n;
        while(i <= 2 * n){
            sum += i++;
        }
    }else{
        i = 2 * n;
        while(i <= n){
            sum += i++;
        }
    }

    printf( "Sum is %d\n", sum );
}
