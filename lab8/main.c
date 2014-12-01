#include "dico.h"
#include "tree.h"
#include "spell.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char** getDir()
{
    char** name = (char**)malloc(sizeof(char*) * 256);
    int i;
    for(i = 0; i < 256; i++){
        name[i] = (char*)malloc(sizeof(char) * 256);
    }
    DIR *d;
    struct dirent *dir;
    int index = 0;
    int count = 0;
    d = opendir("TWAIN");
    if(d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            strcpy(name[count],"TWAIN/");
            strcat(name[count],dir->d_name);
            count++;
        }
        closedir(d);
    }
    return name;
}

int main(int argc,char* argv[])
{
    Tree* t = readDictionary("words.txt");
    char** names = getDir();
    
    int k = atoi(argv[2]);
    pthread_t threads[k];
    
    Documents* docs = (Documents*)malloc(sizeof(Documents));
    docs->files = names;
    docs->dico = t;
    docs->j = atoi(argv[1]);
    docs->location = 2;
    pthread_rwlock_init(&docs->rwlock,NULL);
    pthread_mutex_init(&docs->listloc,NULL);

    int i;
    for(i = 0; i < k; i++){
        pthread_create(&threads[i], NULL, (void* (*)(void*)) &spellCheckDocuments, (void*)docs);
    }
    for(i = 0; i < k; i++){
        pthread_join(threads[i],NULL);
    }
    
    pthread_mutex_destroy(&docs->listloc);
    pthread_rwlock_destroy(&docs->rwlock);
    int inc;
    for(inc = 0; inc < 256; inc++){
        free(names[inc]);
    }
    free(names);
    destroyTree(t);
    free(docs);
    return 0;
}
