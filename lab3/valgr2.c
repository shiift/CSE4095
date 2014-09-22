#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]) 
{
	char* str1 = strdup("test");
	char* str2 = strdup("Hello");
	str1 = str2;
	printf("STRING1: %s\n",str1);
	free(str1);
	printf("STRING2: %s\n",str2);
	free(str2);
	return 0;
}