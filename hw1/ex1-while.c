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
        add code to compute using only "while" loops the sum of integers
        from n to 2n if n is nonnegative, or from 2n to n if 
        n is negative  
    */
    int i;
    if(n >= 0){
        i = n;
        while(i <= 2 * n){
            sum += i++;
        }
    }else{
        i = 2 * n;
        while(i <= n){
            sum += i++;
        }
    }

=======
    
    /* Get the sum of the number  */
    sum = sumNum(n);
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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
  i = strt;
  while(i <= end)
    sum += (i++);

  return sum;
}
