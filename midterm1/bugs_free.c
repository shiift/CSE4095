#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKSIZE  4096


char* make_copy(int i, char* string)
{
    int len;
    char *s;

    len = strlen(string);
    s = (char*)malloc(len + 1); // Must allocate space for the full string and the null terminator
    strncpy(s, string, len + 1); // Must copy full string and null terminator 
    if( !(i%1000) ) 
        printf("i=%d, %s\n", i, s);
    return s; // If you specify a return type then you must return something
}

main()
{
    int i;
    char *ptr;
    char *string = "find the bugs!";
    
    for(i=0; i<10000; i++) {
        ptr = (char*)malloc(BLOCKSIZE);  // It is best to cast the type of the memory allocated
        strcpy(ptr, string);
        free(make_copy(i, string));  // You must free everything you allocate
        free(ptr);
    }
}


