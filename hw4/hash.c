#define DEBUG 0
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
}

void removeFromHTable(Hashtable* t,char* key)
{
	/* Removes the pair identified by key from the hashtable t
		*/
    int hash = getHash(t, key);
    HTNode* cNode = t->_tab[hash];
    HTNode* pNode = t->_tab[hash];
    if(strcmp(cNode->_key, key) == 0){
        t->_tab[hash] = cNode->_next;
        free(cNode->_key);
        free(cNode->_value);
        free(cNode);
        return;
    }
    while( cNode != NULL ){
        if(strcmp(cNode->_key, key) == 0){
            HTNode* fNode = cNode->_next;
            free(cNode->_key);
            free(cNode->_value);
            free(cNode);
            pNode->_next = fNode;
        }
        pNode = cNode;
        cNode = cNode->_next;
    }
}

BOOL isInHTable(Hashtable* t,char* key)
{
	/* Returns true if and only if key is defined in t. */
    int hash = getHash(t, key);
    HTNode* cNode = t->_tab[hash];
    while( cNode != NULL ){
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
                free(cNode->_key);
                free(cNode->_value);
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
            a = 7;
        else
            a *= 7;
        i++;
    }
    int rv = sum % size; 
    assert(rv >= 0 && rv < size);
    return rv;
}
