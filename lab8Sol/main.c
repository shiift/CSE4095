#include "dico.h"
#include "tree.h"
#include "spell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "wqueue.h"

typedef struct ThreadArg {
   WorkQueue* _wq;
   Tree*      _dico;
} ThreadArg;

WorkQueue* makeQueueWithDir(char* dir,int j)
{
   WorkQueue* wq = makeWorkQueue();
   DIR* theDir = opendir(dir);
   struct dirent* entry;
   int i = 1;
   while ((entry = readdir(theDir)) != 0) {
      if (strncmp(entry->d_name,"..",2) == 0 ||
          strncmp(entry->d_name,".",1) == 0)
         continue;
      Task* t = malloc(sizeof(Task));
      t->_update = (i++  % j) == 0;
      int len = strlen(entry->d_name) + strlen(dir) + 1;
      t->_fname = malloc(sizeof(char)* (len+1));
      strcat(strcat(strcpy(t->_fname,dir),"/"),entry->d_name);
      enQueueWork(wq,t);
      printf("Got file [%s]\n",t->_fname);
   }
   closedir(theDir);
   return wq;
}

void* minionWork(void* arg)
{
   ThreadArg* ta = (ThreadArg*)arg;
   while(1) {
      Task* t = deQueueWork(ta->_wq);
      if (t == NULL) return NULL;
      if (t->_update) {
         Queue* wordQueue = makeQueue(4);
         spellCheckDocument(t->_fname,ta->_dico,wordQueue);         
         while (!isEmpty(wordQueue)) {
            Task* wt = deQueue(wordQueue);
            if (!lookupInTree(ta->_dico,wt->_fname))
               addStringToTree(ta->_dico,wt->_fname);
            free(wt->_fname);
            free(wt);
         }
         destroyQueue(wordQueue);
      } else 
         spellCheckDocument(t->_fname,ta->_dico,NULL);
   }
}

int main(int argc,char* argv[])
{
   int k = atoi(argv[1]);
   int j = atoi(argv[2]);
   Tree* t = readDictionary("words.txt");      // read dico
   WorkQueue* wq = makeQueueWithDir("TWAIN",j);// fill work queue with filenames
   ThreadArg ta = {wq,t};                      // make struct for thread arguments
   pthread_t crew[k];                          // remember worker's ids
   for(int i=0;i<k;i++) {
      enQueueWork(wq,NULL); // k of those to say "we are done"
      pthread_create(crew+i,NULL,minionWork,(void*)&ta);
   }

   void* exitStatus;
   for(int i=0;i<k;i++)
      pthread_join(crew[i],&exitStatus);
   destroyTree(t);
   return 0;
}
