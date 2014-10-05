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
Mono* removeFirst( Poly* p){
    if( p->first == NULL) return NULL;
    Mono* oldFirst = p->first;
    p->first = oldFirst->next;
    oldFirst->next = NULL;
    return oldFirst;
}

/***************************************************/
Poly* readPoly()
{
<<<<<<< HEAD
    /*
       Add code to read from standard input a polynomial
       in the format described in the assignment document
       and construct its linked list representation
     */
    int deg, c, k;
    Poly* poly = newPoly();
    scanf("%d", &deg); 
    if (deg < 0) return poly;
    poly->deg = deg;
    do {
        scanf("%d",&c);
        scanf("%d",&k);
        appendMono(poly, newMono(c,k,NULL));
    } while(k != deg);
    return poly;
=======
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
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
}

/***************************************************/
void printPoly( Poly* p )
{
<<<<<<< HEAD
    /*
       Add code to print to standard output a polynomial
       in the format described in the assignment document
     */
    Mono* mono = p->first;
    int deg = p->deg;
    printf("%d", deg);
    while(mono != NULL){
        printf(" %d %d",mono->coeff,mono->exp);
        mono = mono->next;
    }
    printf("\n");
=======
  Mono* temp = p->first;
  printf("%d ", p->deg);

  while(temp)
    {
      printf("%d %d ", temp->coeff, temp->exp);
      temp = temp->next;
    }

  printf("\n");
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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

<<<<<<< HEAD
     */
    // Go through the linked lists which are sorted least
    // to greatest and find the smaller of the two
    // - take the smaller and put it in the new poly
    // - if they're the same add them

    Poly* sumPoly = newPoly();
    Mono* m1 = p1->first;
    Mono* m2 = p2->first;
    while(m1 != NULL || m2 != NULL){
        if(m1 == NULL){
            // append m2 to the end of sumPoly
            sumPoly->last->next = p2->first;
            sumPoly->last = p2->last;
            sumPoly->deg = p2->deg;
            break;
        }
        if(m2 == NULL){
            // append m1 to the end of sumPoly
            sumPoly->last->next = p1->first;
            sumPoly->last = p1->last;
            sumPoly->deg = p1->deg;
            break;
        }
        if(m1->exp < m2->exp){
            // remove first of m1 and put it in addPoly
            Mono* tempMono = removeFirst(p1);
            appendMono(sumPoly, tempMono);
            sumPoly->deg = tempMono->exp;
        }
        else if(m1->exp > m2->exp){
            // remove first of m2 and put it in addPoly
            Mono* tempMono = removeFirst(p2);
            appendMono(sumPoly, tempMono);
            sumPoly->deg = tempMono->exp;
        }
        else{ // exponents are the same
            // remove both firsts and add the coefficients
            Mono* sumMono = removeFirst(p1);
            Mono* tempMono = removeFirst(p2);
            sumMono->coeff += tempMono->coeff;
            if(sumMono->coeff != 0){
                appendMono(sumPoly, sumMono);
                sumPoly->deg = sumPoly->last->exp;
            }
        }
        m1 = p1->first;
        m2 = p2->first;
    }
    free(p1);
    free(p2);
    return sumPoly;
=======
  return pNew;
>>>>>>> 445d210ae5251ac3c641e54e7aeae5a2be4c6d4f
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
