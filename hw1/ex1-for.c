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
<<<<<<< HEAD

    /* 
        add code to compute using only "for" loops the sum of integers 
        from n to 2n if n is nonnegative, or from 2n to n if 
        n is negative
    */
    int i;
    if(n >= 0){
        for(i = n; i <= 2 * n; i++){
            sum += i;
        }
    }else{
        for(i = 2 * n; i <= n; i++){
            sum += i;
        }
    }
=======
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
    
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
