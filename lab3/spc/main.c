#include "dico.h"
#include "tree.h"
#include "spell.h"

int main(int argc,char* argv[])
{
   Tree* t = readDictionary("words.txt");
   spellCheckDocument("document.txt",t);
   destroyTree(t);
   return 0;
}
