#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int hash(char* str)
{
	int ttl = 0;
	while (str && *str)
		ttl = ttl * 67 + *str++;
	return ttl;
}

Hashtable* makeHTable(int mxs)
{
	/* Implement a constructor that builds a hashtable relying 
		on auxiliary chaining (lists) and capable to hold up to 
		mxs lists in its primary structure. Write a hash function
		that is suitable for strings. */
	Hashtable* t = (Hashtable*)malloc(sizeof(Hashtable));
	t->_sz = mxs;
	t->_tab = (HTNode**)malloc(sizeof(HTNode*)*t->_sz);
	int i;
	for(i=0;i<t->_sz;i++)
		t->_tab[i] = NULL;
	return t;
}

HTNode* findInList(Hashtable* t,int k,char* key)
{
	assert(k>=0 && k < t->_sz);
	HTNode* cur = t->_tab[k];
	while (cur) {
		if (strcmp(cur->_key,key) == 0)
			return cur;
		cur = cur->_next;
	}	
	return NULL;
}

void addHTable(Hashtable* t,char* key,char* value)
{
	/* Add the pair key/value to the hashtable t. */
	int k = abs(hash(key)) % t->_sz;
	if (findInList(t,k,key) == NULL) {
		HTNode* new = (HTNode*)malloc(sizeof(HTNode));
		new->_key = strdup(key);
		new->_value = strdup(value);
		new->_next = t->_tab[k];
		t->_tab[k] = new;
	} 
}

void removeFromHTable(Hashtable* t,char* key)
{
	/* Removes the pair identified by key from the hashtable t
		*/
	int k = abs(hash(key)) % t->_sz;
	assert(k>=0 && k < t->_sz);
	HTNode* last = NULL;
	HTNode* cur = t->_tab[k];
	while (cur) {
		if (strcmp(cur->_key,key) == 0) {
			if (last)
				last->_next = cur->_next;
			else t->_tab[k] = cur->_next;
			free(cur->_key);
			free(cur->_value);
			free(cur);
			return;
		}
		last = cur;
		cur = cur->_next;
	}	
}

BOOL isInHTable(Hashtable* t,char* key)
{
	/* Returns true if and only if key is defined in t. */
	int k = abs(hash(key)) % t->_sz;
	return findInList(t,k,key) != NULL;
}

char* getValueInHTable(Hashtable* t,char* key)
{
	/* Returns the value associated to key in t. If there is no
		such value (key does not appear in t) simply return NULL */
	int k = abs(hash(key)) % t->_sz;
	HTNode* found = findInList(t,k,key);
	if (found)
		return found->_value;
	else return NULL;
}

void destroyHTable(Hashtable* t)
{
	/* Deallocate all the memory needed for t and its 
		auxiliary structures */
	int i;
	for(i=0;i < t->_sz;i++) {
		HTNode* cur = t->_tab[i];
		while(cur) {
			HTNode* nxt = cur->_next;
			free(cur->_value);
			free(cur->_key);
			free(cur);
			cur = nxt;
		}
	}
	free(t->_tab);
	free(t);
}