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
    char key[1024];
    char value[1024];
    int score = 0;

    printf("Enter a key (return to exit): ");
    fgets(key, sizeof(key), stdin);

    while(key[0] != '\n'){
        char *pos;
        if ((pos = strchr(key, '\n')) != NULL)
            *pos = '\0';
        if(isInHTable(t, key)){
            printf("Enter a matching value: ");
            fgets(value, sizeof(value), stdin);
            if ((pos = strchr(value, '\n')) != NULL)
                *pos = '\0';
            if(strcmp(getValueInHTable(t, key),value) == 0){
                removeFromHTable(t, key);
                removeFromHTable(t, value);
                printf("You entered a corrrect match!\n");
                score++;
            }else{
                printf("Sorry, incorrect value.\n");
            }
        }else{
            printf("Key not in table.\n");
        }
        printf("Enter a key (return to exit): ");
        fgets(key, sizeof(key), stdin);
    }
    printf("Final Score: %d\n", score);
}

int main(int argc,char* argv[])
{
	Hashtable* theTable = readWordList("pairs.txt");
	playGame(theTable);
	destroyHTable(theTable);
	return 0;
}
