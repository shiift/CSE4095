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

void spellCheckDocument(Documents* docs, char* filename)
{
    printf("%s\n", filename);
    Tree* dico = docs->dico;
    FILE* doc = fopen(filename,"r");
    char word[1024];
    /*char** badwords = (char**)malloc(sizeof(char*) * 1024);
    int i;
    for(i = 0; i < 1024; i++){
        badwords[i] = (char*)malloc(sizeof(char) * 1024);
    }*/
    int count = 0;
    while (!feof(doc)) {
        fscanf(doc,"%s ",word);
        cleanupWord(word);
        if (*word==0 || isANumber(word)) continue;
        pthread_rwlock_rdlock(&docs->rwlock);
        bool found = lookupInTree(dico,word);
        pthread_rwlock_unlock(&docs->rwlock);
        if (!found) {
            pthread_rwlock_wrlock(&docs->rwlock);
            printf("Word [%s] spelled incorrectly.\n",word);
            pthread_rwlock_unlock(&docs->rwlock);
            //badwords[count] = strdup(word);
            count++;
        }
    }
    fclose(doc);
}

int incrementList(Documents* docs)
{
    int returnvar;
    pthread_mutex_lock(&docs->listloc);
    returnvar = docs->location++;
    pthread_mutex_unlock(&docs->listloc);
    return returnvar;
}

void spellCheckDocuments(Documents* docs)
{
    while(docs->location < 38){
        int fileloc = incrementList(docs);
        spellCheckDocument(docs, docs->files[fileloc]);
    }
    return;
}
