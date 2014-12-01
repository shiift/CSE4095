#ifndef __SPELL_H
#define __SPELL_H

#include "tree.h"
#include "queue.h"

void spellCheckDocument(char* filename,Tree* dico,Queue* words);

#endif
