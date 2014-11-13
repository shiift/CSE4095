#ifndef __SPELL_H
#define __SPELL_H

#include "tree.h"

// void spellCheckDocument(char* filename,Tree* dico);
void spellCheckDocument(Documents* docs, int fNum);
int incrementList(Documents* docs);
void spellCheckDocuments(Documents* docs);

#endif
