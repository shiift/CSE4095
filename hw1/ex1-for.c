#include <stdio.h>

/* Forward declaration */
int sumNum(int n);

int main() 
{
    int n;
    int sum;
    
    /* Get the number to sum  */
    printf( "Enter the value of n: " );
    scanf( "%d", &n );
    
    /* Get the sum of the number  */
    sum = sumNum(n);
    printf( "Sum is %d\n", sum );
}

int sumNum(int n)
{
  int sum = 0;
  int i, strt, end;

  /* Set the correct start and end points */
  if(n >= 0)
    {
      strt = n;
      end = 2 * n;
    }
  else
    {
      strt = 2 * n;
      end = n;
    }

  /* Loop from start to end and generate the sum */
  for(i = strt; i <= end; i++)
    sum += i;

  return sum;
}
