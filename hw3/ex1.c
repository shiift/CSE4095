#include <stdio.h>
#include <string.h>

#define READLEN 1024

int is_vowel(char c)
{
<<<<<<< HEAD
    /*
     returns 1 if c is a vowels, 0 otherwise
    */
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return 1;
    return 0;
=======
  return c=='a' || c=='e' || c=='i' || c=='o' || c=='u'
    || c=='A' || c=='E' || c=='I' || c=='O' || c=='U';
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

int main()
{
<<<<<<< HEAD
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
=======
  char read[READLEN];
  char* readSeek = read;
  char output[READLEN];
  int outputPos = 0;

  memset(read, '\0', READLEN);

  /* Read the value */
  printf("Enter a sentence: ");
  scanf("%[^\n]", read);

  /* Loop through read array - ends when reaches \0 */
  while(*readSeek)
    {
      if(!is_vowel(*readSeek))
	  output[outputPos++] = *readSeek;

      readSeek++;
    }

  /* Add ending marker for string, print */
  output[outputPos++] = '\0';
  printf("\nRemoved Vowels: %s\n", output);
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}
