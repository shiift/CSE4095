#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) 
{
	const int size = 100;
	int n,sum = 0;
	int* t = (int*)malloc(sizeof(int)*size);
	for(n = size-1;n >= 0;n--)
		t[n] = n;
	for(n=0;n < size;n++)
		sum += t[n];
	printf("Sum is %d\n",sum);
    free(t);
	return 0;
}
