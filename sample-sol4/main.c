#include "wlist.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int nbGood = 0;
	int nbTried = 0;
	do {
		printf("Enter a word:");
		char str[1024];
		*str = 0;
		int nbr = scanf("%s",str);
		if (nbr == 0 || *str == 0)
			break;
		if (isInHTable(t,str)) {
			char response[1024];
			*response = 0;
			char* expected = getValueInHTable(t,str);
			printf("Enter the associated word:");
			scanf("%s",response);
			if (*response && strcmp(expected,response) == 0) {
				printf("Good response!\n");
				nbGood += 1;
				nbTried += 1;
				removeFromHTable(t,str);
			} else nbTried += 1;
		}
	} while(TRUE);
	printf("Game over! rate: %f\n",(float)nbGood / nbTried * 100);
}

int main(int argc,char* argv[])
{
	Hashtable* theTable = readWordList("pairs.txt");
	playGame(theTable);
	destroyHTable(theTable);
	return 0;
}