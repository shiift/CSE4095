#ifndef __HASH_H
#define __HASH_H

typedef struct HTNodeTag {
	struct HTNodeTag*  _next;
	char*           _key;
	char*         _value;
} HTNode;

typedef struct HashtableTag {
	int _sz;
	HTNode** _tab;
} Hashtable;

#define BOOL char
#define TRUE 1
#define FALSE 0

Hashtable* makeHTable(int mxs);
void addHTable(Hashtable* t,char* key,char* value);
void removeFromHTable(Hashtable* t,char* key);
BOOL isInHTable(Hashtable* t,char* key);
char* getValueInHTable(Hashtable* t,char* key);
void destroyHTable(Hashtable* t);
int getHash(Hashtable* t, char* key);

#endif
