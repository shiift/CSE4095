#include "hash.h"

Hashtable* makeHTable(int mxs)
{
	/* Implement a constructor that builds a hashtable relying 
		on auxiliary chaining (lists) and capable to hold up to 
		mxs lists in its primary structure. Write a hash function
		that is suitable for strings. */
}

void addHTable(Hashtable* t,char* key,char* value)
{
	/* Add the pair key/value to the hashtable t. */
}

void removeFromHTable(Hashtable* t,char* key)
{
	/* Removes the pair identified by key from the hashtable t
		*/
}

BOOL isInHTable(Hashtable* t,char* key)
{
	/* Returns true if and only if key is defined in t. */
}
char* getValueInHTable(Hashtable* t,char* key)
{
	/* Returns the value associated to key in t. If there is no
		such value (key does not appear in t) simply return NULL */
}
void destroyHTable(Hashtable* t)
{
	/* Deallocate all the memory needed for t and its 
		auxiliary structures */
}