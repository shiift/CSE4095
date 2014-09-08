#include <stdio.h>

int collatz(int n, int d){
    if(n == 1){
        printf("It takes %d steps.\n", d);
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
    while ( 1 ){
        printf( "Enter a value for n (negative to quit): " );
        scanf( "%d", &n );
        if(n < 0){
            break;
        }
        collatz(n, 0);
    }
}
