#include "dico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* cleanupWord(char* word)
{
   char* rv = word;
   char* at = word;
   while(*word != 0) {
      *at = tolower(*word);
      if (isalnum(*at))
         at++;
      word++;
   }
   *at = 0;
   return rv;
}

void fillTreeWith(Tree* t,char** words,int low,int up)
{
   if (low <= up) {
      int mid = low + (up - low)/2;
      addStringToTree(t,words[mid]);
      fillTreeWith(t,words,low,mid-1);
      fillTreeWith(t,words,mid+1,up);
   }
}
int stringCompare(const void* s1,const void* s2)
{
   return strcmp(*(char**)s1,*(char**)s2);
}

Tree* readDictionary(char* fname)
{
   FILE* f = fopen(fname,"r");
   if (f==NULL) {
      printf("Coulnd't find file: %s. Exiting.\n",fname);
      exit(2);
   }
   int nbWords = 0;
   char line[1024];    // we are assuming that the line can fit.
   while (!feof(f)) {
      fscanf(f,"%s\n",line);
      nbWords++;
   }
   rewind(f);
   char** words = (char**)malloc(sizeof(char*)*nbWords);
   int at = 0;
   while(!feof(f)) {
      fscanf(f,"%s\n",line);
      words[at++] = strdup(cleanupWord(line)); // words[at] has no punctuation and is all lowercase.
   }
   qsort(words,nbWords,sizeof(char*),stringCompare);	
   // remove duplicates that could appear as result of 'cleanup' above. So this is a packing
   at = 1;
   int i;
   for(i=1;i<nbWords;i++) {
      // If the 'cleaned-up' word at offset at-1 is the same as at offset i, drop the i^th one!
      // Also drop if the word is empty
      if (strcmp(words[at-1],words[i]) != 0 && strlen(words[i]) > 0)
         words[at++] = words[i];
      else free(words[i]); // it is a duplicate of a previous entry.
   }
   nbWords = at;  // adjust the number of words after the de-duplication.
   Tree* t = makeEmptyTree();
   fillTreeWith(t,words,0,nbWords-1);
   fclose(f);
   return t;
}
