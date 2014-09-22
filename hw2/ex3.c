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
    /*
       Add code to read from standard input a polynomial
       in the format described in the assignment document
       and construct its linked list representation
     */
}

/***************************************************/
void printPoly( Poly* p )
{
    /*
       Add code to print to standard output a polynomial
       in the format described in the assignment document
     */
}

/***************************************************/
Poly* addPoly( Poly* p1, Poly* p2 )
{
    /*
       Add code to compute the sum of two polynomials
       given as linked lists

     */
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
