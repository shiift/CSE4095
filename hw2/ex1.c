#include <stdio.h>
#include <string.h>

int inOrder(int n, int* p)
{
  int contains[n + 1]; /* Extra space because it begins at 1 */
  int isInOrder = 1;
  int currentNum = p[1] - 1;
  int i;

  memset(contains, 0, sizeof(int) * n);

  for(i = 1; i < n; i++) /* Starts at 1: 0 is unused */
    {
      /* Check if increments or starts loop over */
      if((p[i] == currentNum + 1 || p[i] == currentNum - 1
	  || p[i] == 1 || p[i] == n) && !contains[p[i]])
	{
	  currentNum = p[i];
	  contains[p[i]] = 1;
	}
      else
	{
	  isInOrder = 0;
	  break;
	}
    }
  
  return isInOrder;
}

int correctPositions(int n, int* p)
{
  int isInCorrectPositions = 1;
  int i;

  for(i = 1; i < n; i++)
    {
      if(p[p[i]] != i) /* Positions must all match */
	{
	  isInCorrectPositions = 0; 
	  break;
	}
    }

  return isInCorrectPositions;
}

int super( int n, int* p )
{
  return inOrder(n, p) && correctPositions(n, p);
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
