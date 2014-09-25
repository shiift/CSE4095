#include <stdio.h>

int super( int n, int* p )
{
    /* return 1 if p[1],...,p[n] is a super-permutation, 0 otherwise */
    /* Based on the observation that p[1],...,p[n] is a super-permutation
       if and only if p[p[i]] = i for every i=1,...,n */
    int i;

    for( i = 1; i <= n; i++ )
    {
        if (p[p[i]] != i)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int i, n;
    int p[100001];  /* p[0] is not used */

    for(;;)
    {
        (void)scanf( "%d", &n);

        if( n==0 ) return 0;

        for( i = 1; i <= n; i++ )
        {
           (void)scanf( "%d", p+i );
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
