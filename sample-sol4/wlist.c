#include "wlist.h"
#include <stdio.h>

Hashtable* readWordList(char* filename)
{
	/* Read a list of pairs from filename and construct a 
		brand new Hashtable that contains all the pairs in the file. 
		Namely, if the file contains a pair (a,b), then the hash table
		should contain both a->b and b->a. 

		Make sure that the hashtable is large enough to accomodate 
		your list of pairs. Use a prime number for the size. 		
		*/
	FILE* theFile = fopen(filename,"r");
	Hashtable*  t = makeHTable(51);
	char key[1024],value[1024];
	while(!feof(theFile)) {
		fscanf(theFile,"%s %s",key,value);
		printf("Got [%s] -> [%s]\n",key,value);
		addHTable(t,key,value);
		addHTable(t,value,key);
	}
	fclose(theFile);
	return t;
}