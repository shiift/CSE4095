#ifndef __TREE_H
#define __TREE_H

#include <stdbool.h>

typedef struct Tree {
	struct TNode* _root;	
} Tree;

typedef struct TNode {
	struct TNode* _left;
	struct TNode* _right;
	char*  _key;
} TNode;

Tree* makeEmptyTree();
void destroyTree(Tree* root);
Tree* addStringToTree(Tree* t,char* value);
bool lookupInTree(Tree* t,char* value);
#endif