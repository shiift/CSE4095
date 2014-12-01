#ifndef __TREE_H
#define __TREE_H

#include <stdbool.h>
#include <pthread.h>

typedef struct Tree {
	struct TNode* _root;	
} Tree;

typedef struct TNode {
	struct TNode* _left;
	struct TNode* _right;
	char*  _key;
} TNode;

typedef struct Documents {
    char** files;
    Tree* dico;
    int j;
    int location;
    pthread_mutex_t listloc;
    pthread_rwlock_t rwlock;
} Documents;

Tree* makeEmptyTree();
void destroyTree(Tree* root);
Tree* addStringToTree(Tree* t,char* value);
bool lookupInTree(Tree* t,char* value);
#endif
