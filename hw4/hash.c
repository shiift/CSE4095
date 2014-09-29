#define DEBUG 0
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Hashtable* makeHTable(int mxs)
{
	/* Implement a constructor that builds a hashtable relying 
		on auxiliary chaining (lists) and capable to hold up to 
		mxs lists in its primary structure. Write a hash function
		that is suitable for strings. */
    Hashtable* t = (Hashtable*)malloc(sizeof(Hashtable));
    t->_sz = mxs;
    t->_tab = (HTNode**)malloc(mxs * sizeof(HTNode*));
    int i;
    for(i = 0; i < mxs; i++){
        t->_tab[i] = NULL;
    }
    return t;
}

void addHTable(Hashtable* t,char* key,char* value)
{
    printf("addHTable: \"%s\"\t\"%s\"\n", key, value);
	/* Add the pair key/value to the hashtable t. */
    int hash = getHash(t, key);
    HTNode* newNode = (HTNode*)malloc(sizeof(HTNode));
    newNode->_key = strdup(key);
    newNode->_value = strdup(value);
    newNode->_next = NULL;
    if(t->_tab[hash] == NULL){
        t->_tab[hash] = newNode;
    }else{
        HTNode* cNode = t->_tab[hash];
        while(cNode->_next != NULL){
            cNode = cNode->_next;
        }
        cNode->_next = newNode;
    }
    printf("addHTable: added %d\t\"%s\"\t\"%s\"\n", hash, t->_tab[hash]->_key, t->_tab[hash]->_value);
    printf("addHTable: in 104 %s\n", t->_tab[104]->_key);
}

void removeFromHTable(Hashtable* t,char* key)
{
	/* Removes the pair identified by key from the hashtable t
		*/
    int hash = getHash(t, key);
    HTNode* cNode = t->_tab[hash];
    if(strcmp(cNode->_key, key) == 0){
        t->_tab[hash] = cNode->_next;
        free(cNode);
        return;
    }
    while( cNode->_next != NULL ){
        if(DEBUG)
            printf("removeFromHTable: %s\t%s\n", cNode->_next->_key, cNode->_next->_value);
        if(strcmp(cNode->_next->_key, key) == 0){
            HTNode* tempNode = cNode->_next->_next;
            free(cNode->_next);
            cNode->_next = tempNode;
            return;
        }
        cNode = cNode->_next;
    }
    printf("Key not in table.\n");
}

BOOL isInHTable(Hashtable* t,char* key)
{
	/* Returns true if and only if key is defined in t. */
    int hash = getHash(t, key);
    HTNode* cNode = t->_tab[hash];
    while( cNode != NULL ){
        printf("isInHTable: %s\t%s\n", cNode->_key, cNode->_value);
        if(strcmp(cNode->_key, key) == 0){
            return TRUE;
        }
        cNode = cNode->_next;
    }
    return FALSE;
}
char* getValueInHTable(Hashtable* t,char* key)
{
	/* Returns the value associated to key in t. If there is no
		such value (key does not appear in t) simply return NULL */
    int hash = getHash(t, key);
    HTNode* cNode = t->_tab[hash];
    while( cNode != NULL ){
        if(strcmp(cNode->_key, key) == 0){
            return cNode->_value;
        }
        cNode = cNode->_next;
    }
    return NULL;
}
void destroyHTable(Hashtable* t)
{
	/* Deallocate all the memory needed for t and its 
		auxiliary structures */
    if( t == NULL )
        return;
    int i;
    for(i = 0; i < t->_sz; i++){
        if(t->_tab[i] != NULL){
            HTNode* cNode = t->_tab[i];
            while(cNode != NULL){
                HTNode* nNode = cNode->_next;
                free(cNode);
                cNode = nNode;
            }
        }
    }
    free(t->_tab);
    free(t);
}

int getHash(Hashtable* t, char* key){
    if(DEBUG)
        printf("getHash: %s\n", key);
    int i, a, sum;
    int size = t->_sz;
    i = a = sum = 0;
    while( key[i] != '\0' ){
        sum += key[i] * a;
        if(a == 0)
            a = 2;
        else
            a *= 2;
        i++;
    }
    printf("getHash: hash = %d\n", sum % size);
    return sum % size; 
}
