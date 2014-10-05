#include <stdio.h>

/*
  Write the  body of the following function for testing if
  p[1],...,p[n] is a super-permutation
*/

int super( int n, int* p )
{
    int i;
    for( i = 1; i <= n; i++ )
        if(p[p[i]] != i) return 0;
    return 1;
}

int main()
{
    int i, n;
    int p[100001];  /* p[0] is not used */

    for(;;)
    {
        scanf( "%d", &n);

        if( n==0 ) return 0;

        for( i = 1; i <= n; i++ )
        {
           scanf( "%d", p+i );
        }

        if( super(n, p) )
        {
            printf( "super\n" );
        }
        else
        {
            printf( "not super\n" );
        }
    }
}
