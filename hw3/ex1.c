#include <stdio.h>
#include <string.h>

#define READLEN 1024

int is_vowel(char c)
{
  return c=='a' || c=='e' || c=='i' || c=='o' || c=='u'
    || c=='A' || c=='E' || c=='I' || c=='O' || c=='U';
}

int main()
{
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
}
