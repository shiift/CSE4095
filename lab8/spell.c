#include "spell.h"
#include <stdio.h>
#include <stdlib.h>
#include "dico.h"
#include <ctype.h>
#include <string.h>

bool isANumber(char* word)
{
    bool ad = true;
    while (*word && ad) 
        ad &= isdigit(*word++);	
    return ad;
}

void spellCheckDocument(Documents* docs, int fNum)
{
    char* filename = docs->files[fNum];
    Tree* dico = docs->dico;
    FILE* doc = fopen(filename,"r");
    char word[1024];
    char** words = NULL;
    int count = 0;
    while (!feof(doc)) {
        fscanf(doc,"%s ",word);
        cleanupWord(word);
        if (*word==0 || isANumber(word)) continue;
        pthread_rwlock_rdlock(&docs->rwlock);
        bool found = lookupInTree(dico,word);
        pthread_rwlock_unlock(&docs->rwlock);
        if (!found && !(fNum % docs->j)) {
            words = realloc(words, sizeof(char*) * (count+1));
            words[count++] = strdup(word);
        }
    }
    int i;
    pthread_rwlock_wrlock(&docs->rwlock);
    for(i = 0; i < count; i++){
        bool found = lookupInTree(docs->dico, words[i]);
        if(!found){
            addStringToTree(docs->dico, words[i]);
            printf("%s is misspelled in %s\n", words[i], filename);
        }
        free(words[i]);
    }
    pthread_rwlock_unlock(&docs->rwlock);
    free(words);
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
        spellCheckDocument(docs, fileloc);
    }
    return;
}
