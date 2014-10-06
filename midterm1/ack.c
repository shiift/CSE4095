#include <stdio.h>
#include <string.h>

int ackermann(m, n){
    if(m == 0){
        return n + 1;
    }else if(n == 0){
        return ackermann(m-1, 1);
    }else if(n > 0){
        return ackermann(m-1, ackermann(m, n-1));
    }
    printf("ERROR\n");
}

int strtoint(char* c){
    int i, val;
    val = 0;
    for(i = 0; i < strlen(c); i++){
        val = val * 10 + c[i] - '0'; 
    }
    return val;
}

int main(int argc, char* argv[])
{
    int m, n;
    m = strtoint(argv[1]);
    n = strtoint(argv[2]);
    printf("Ack(%d,%d) = %d\n", m, n, ackermann(m, n));
}
