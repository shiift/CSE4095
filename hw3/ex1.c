#include <stdio.h>

int is_vowel(char c)
{
    /*
     returns 1 if c is a vowels, 0 otherwise
    */
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return 1;
    return 0;
}

int main()
{
    /*
     read text from standard input and write to the standard 
     output the text with the vowels removed
    */
    char string[1001];
    printf("Enter a string (press ctrl+c to quit):\n");
    while(fgets(string, 1001, stdin) != NULL){
        int i;
        for(i = 0; string[i] != 0; i++){
            if(!is_vowel(string[i])){
                printf("%c", string[i]);
            }
        }
    }
    return 0;
}
