#include <stdio.h>
#include <stdlib.h>

#define LEN 100000

typedef struct 
{
  int     len; 
  int   *data;
} vect_struct;



int sum( vect_struct* vector )
{
   /* Define and use local variables for convenience */
   int start, end, i, mysum; 
   int* data; 

   start=0;
   end = vector->len;
   data = vector->data;

   mysum = 0;
   for (i=start; i<end ; i++) 
    {
      mysum += data[i];
    }
   return mysum;
}


int main (int argc, char *argv[])
{
   int i;
   vect_struct* vector;

   /* Allocate storage and initialize values */
   vector = (vect_struct*)malloc( sizeof(vect_struct) );
   if(vector==NULL)
   {
      printf("Error allocating vector\n");
      exit(-1);
   }
   vector->len = LEN;
   vector->data = (int*) malloc (LEN*sizeof(int));
   if(vector->data==NULL)
   {
      printf("Error allocating memory\n");
      exit(-1);
   }
  
   for( i=0; i<vector->len; i++ ) 
     vector->data[i]=1;

  /* Print result  */ 
  printf ("Sum =  %d\n", sum(vector) );

  free(vector->data);
  free(vector);

}
