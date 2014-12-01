#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Tree* makeEmptyTree()
{
   Tree* t  = (Tree*)malloc(sizeof(Tree));
   t->_root = NULL;
   pthread_rwlock_init(&t->_rwl,NULL);
   return t;
}
void destroyAux(TNode* root)
{
   if (root) {
      destroyAux(root->_left);
      destroyAux(root->_right);
      free(root->_key);
      free(root);
   }
}
void destroyTree(Tree* root)
{
   pthread_rwlock_destroy(&root->_rwl);
   destroyAux(root->_root);
   free(root);
}
TNode* addStringToTreeAux(TNode* root,char* value)
{
   if (root == NULL) {
      root = (TNode*)malloc(sizeof(TNode));
      root->_key  = strdup(value);
      root->_left = root->_right = NULL;
      return root;
   } else {
      if (strcmp(value,root->_key) < 0)
         root->_left = addStringToTreeAux(root->_left,value);
      else if (strcmp(value,root->_key) > 0)
         root->_right = addStringToTreeAux(root->_right,value);
      else {
         printf("Trying to add the same word [%s , %s] twice in the tree. exiting.",value,root->_key);
         return root;
      }
      return root;
   }
}
bool lookupInTreeAux(TNode* root,char* value) 
{
   if (root==NULL)
      return false;
   else {
      int c = strcmp(value,root->_key);
      if (c==0)
         return true;
      else if (c < 0)
         return lookupInTreeAux(root->_left,value);
      else return lookupInTreeAux(root->_right,value);
   }
}
Tree* addStringToTree(Tree* t,char* value)
{
   pthread_rwlock_wrlock(&t->_rwl);
   t->_root = addStringToTreeAux(t->_root,value);
   pthread_rwlock_unlock(&t->_rwl);
   return t;
}
bool lookupInTree(Tree* t,char* value)
{
   pthread_rwlock_rdlock(&t->_rwl);
   bool rv = lookupInTreeAux(t->_root,value);
   pthread_rwlock_unlock(&t->_rwl);
   return rv;
}

