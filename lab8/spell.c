#include "spell.h"
#include <stdio.h>
#include <stdlib.h>
#include "dico.h"
#include <ctype.h>

bool isANumber(char* word)
{
   bool ad = true;
   while (*word && ad) 
      ad &= isdigit(*word++);	
   return ad;
}

void spellCheckDocument(char* filename,Tree* dico)
{
   FILE* doc = fopen(filename,"r");
   char word[1024];
   while (!feof(doc)) {
      fscanf(doc,"%s ",word);
      cleanupWord(word);
      if (*word==0 || isANumber(word)) continue;
      bool found = lookupInTree(dico,word);
      if (!found) {
         printf("Word [%s] spelled incorrectly.\n",word);
      }
   }
   fclose(doc);
}
