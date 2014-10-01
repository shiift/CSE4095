#include "wlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hashtable* readWordList(char* filename)
{
	/* Read a list of pairs from filename and construct a 
		brand new Hashtable that contains all the pairs in the file. 
		Namely, if the file contains a pair (a,b), then the hash table
		should contain both a->b and b->a. 

		Make sure that the hashtable is large enough to accomodate 
		your list of pairs. Use a prime number for the size. 		
		*/
    Hashtable* t = makeHTable(113);
    FILE *fp;
    char s[1024];
    fp = fopen(filename, "r");

    while (fgets(s, 34, fp) != NULL){
        char *c, *k, *v;
        c = strchr(s, '\n');
        if (c != NULL)
            *c = '\0';
        k = strtok(s, " ");
        v = strtok(NULL, " ");
        if(!(isInHTable(t, k) || isInHTable(t, v))){
            addHTable(t, k, v);
            addHTable(t, v, k);
        }
    }

    fclose(fp);
    return t;
}
