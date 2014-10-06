#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE  4096


char* make_copy(int i, char* string)
{
    int len;
    char *s;

    len = strlen(string);
    s = (char*)malloc(len);
    strncpy(s, string, len);
    if( !(i%1000) ) 
        printf("i=%d, %s\n", i, s);
}

main()
{
    int i;
    char *ptr, *string = "find the bugs!";

    for(i=0; i<10000; i++) {
        ptr = malloc(BLOCKSIZE);
        strcpy(ptr, string);
        make_copy(i, ptr);
        free(ptr);
    }
}


