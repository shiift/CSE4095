#include <stdio.h>

int vowel[256]; 

void init_array()
{
    int i; 
    for( i=0; i<256; i++ ) vowel[i] = 0;
    vowel['a'] = vowel['A'] = vowel['e'] = vowel['E'] = vowel['i'] = vowel['I'] = 
    vowel['o'] = vowel['O'] = vowel['u'] = vowel['U'] = 1;
    return;
}

int is_vowel(int c)
{
  return vowel[c]; 
}

int main()
{
    int c; 

    init_array();

    while( EOF != (c=getchar()) )
    {
        if( !is_vowel(c) )
        {
            (void)putchar(c); 
        }
    }
    return 0;
}
