#include <stdio.h>
#include <stdlib.h>

/***************************************************/
typedef struct Monomial {
    int coeff;     /* coefficient */
    int exp;       /* exponent    */
    struct Monomial *next;  /* next monomial */
} Mono;

typedef struct polynomial {
    int   deg;     /* degree */
    Mono* first;   /* first monomial */
    Mono* last;    /* last monomial  */
} Poly;

/***************************************************/
Mono* newMono( int c, int k, Mono* next)
{
    Mono* mono = (Mono*)malloc( sizeof(Mono) );
    if( mono == NULL ) return NULL;
    mono->coeff = c;
    mono->exp   = k;
    mono->next  = next;
    return mono;
}

/***************************************************/
Poly* newPoly()
{
    Poly* poly = (Poly*)malloc( sizeof(Poly) );
    poly->deg = 0;
    poly->first = poly->last = NULL;
    return poly;
}

/***************************************************/
void appendMono( Poly* p, Mono* m)
{
   if( p->first == NULL )  /* first monomial */
   {
      p->first = p->last = m;
   }
   else   /* add monomial after last */
   {
      p->last = p->last->next = m;
   }
}

/***************************************************/
Poly* readPoly()
{
  int coeff, exp;
  int doneReading = 0;
  Poly* p = newPoly();


  printf("Enter a polynomial: (separate each by an enter)");

  scanf("%d", &exp);
  printf(" ");
  
  p->deg = exp;
  while(!doneReading)
    {
      scanf("%d", &coeff);
      printf(" ");
      scanf("%d", &exp);
      printf(" ");

      Mono* mono = newMono(coeff, exp, NULL);
      appendMono(p, mono);

      if(exp == p->deg)
	doneReading = 1;
    }

  return p;
}

/***************************************************/
void printPoly( Poly* p )
{
  Mono* temp = p->first;
  printf("%d ", p->deg);

  while(temp)
    {
      printf("%d %d ", temp->coeff, temp->exp);
      temp = temp->next;
    }

  printf("\n");
}

/***************************************************/
Poly* addPoly( Poly* p1, Poly* p2 )
{
  Poly* pNew = newPoly();
  Mono *temp1 = p1->first, *temp2 = p2->first;

  /* Set degree of polynomial to the higher of the two */
  if(p1->deg > p2->deg)
      pNew->deg = p1->deg;
  else
      pNew->deg = p2->deg;

  /* Loop through both polynomials */
  while(temp1 || temp2)
    {
      /* If temp1 or temp2 is NULL pointer, just add the other */
      if(temp1 == NULL)
	{
	  Mono* temp = newMono(temp2->coeff, temp2->exp, NULL);
	  appendMono(pNew, temp);
	  
	  temp2 = temp2->next;
	}
      else if(temp2 == NULL)
	{
	  Mono* temp = newMono(temp1->coeff, temp1->exp, NULL);
	  appendMono(pNew, temp);

	  temp1 = temp1->next;
	}
      
      /* If not null and one is greater than the other, just use that one */
      else if(temp1->exp > temp2->exp)
	{
	  Mono* temp = newMono(temp2->coeff, temp2->exp, NULL);
	  appendMono(pNew, temp);

	  temp2 = temp2->next;
	}
      else if(temp2->exp > temp1->exp)
	{
	  Mono* temp = newMono(temp1->coeff, temp1->exp, NULL);
	  appendMono(pNew, temp);

	  temp1 = temp1->next;
	}

      /* If both are equal degrees, add the coefficients together */
      else if(temp1->exp == temp2->exp)
	{
	  Mono* temp = newMono(temp1->coeff+temp2->coeff, temp1->exp, NULL);
	  appendMono(pNew, temp);
	  
	  temp1 = temp1->next;
	  temp2 = temp2->next;
	}
    }

  return pNew;
}

/***************************************************/

int main()
{
    Poly* p1 = readPoly();
    Poly* p2 = readPoly();

    /*
    printPoly(p1);
    printPoly(p2);
    printf("\n\n\n");
    */

    if( (p1 == NULL) && (p2 == NULL) )
    {
        fprintf(stderr, "Could not allocate memory\n");
        return 1;
    }

    printPoly( addPoly( p1, p2 ) );

    return 0;
}
