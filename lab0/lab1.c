#include <stdio.h>

int collatz(int n, int d){
    printf("%d ", n);
    if(n == 1){
        printf("\nIt takes %d steps.\n", d);
        return 0;
    }
    if(n % 2 == 0){
        return collatz(n / 2, d + 1);
    }else{
        return collatz(3 * n + 1, d + 1);
    }
}

int main(){
    int n;
    
    printf( "Enter a value for n: " );
    scanf( "%d", &n );
    
    collatz(n, 0);
}
