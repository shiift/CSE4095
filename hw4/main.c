#include "wlist.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

void playGame(Hashtable* t)
{
	/* This is the main game logic. Simply prompt the user to enter a
		word. If the word is not in the hashtable t, prompt again.
		
		If the user enters the empty word, the game ends.
		
		If the user enters a challenge that appears in the dictionary
		prompt him again for the associated word and check that 
		the word associated to the challenge is the same as the word he
		paired. If so, increase his score.
		
		If a pair was successfully played, remove it from the hashtable
		to avoid a repeat.

		When the game ends, reports the player score as the ratio
		#of valid pairs tried / #of correct matches.
		*/
}

int main(int argc,char* argv[])
{
	Hashtable* theTable = readWordList("pairs2.txt");
	playGame(theTable);
    isInHTable(theTable, "Adam");
    printf("%s\n", theTable->_tab[70]->_key);
	destroyHTable(theTable);
	return 0;
}
