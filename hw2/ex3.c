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
}

/***************************************************/
void printPoly( Poly* p )
{
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
}
/***************************************************/
Poly* addPoly( Poly* p1, Poly* p2 )
{
    /*
       Add code to compute the sum of two polynomials
       given as linked lists

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
        }
        if(m2 == NULL){
            // append m1 to the end of sumPoly
        }
        if(m1->exp < m2->exp){
            // remove first of m1 and put it in addPoly
        }
        else if(m1->exp > m2->exp){
            // remove first of m2 and put it in addPoly
        }
        else{ // exponents are the same
            // remove both firsts and add the coefficients
        }
    }
}

/***************************************************/

int main()
{
    Poly* p1 = readPoly();
    Poly* p2 = readPoly();

    printPoly(p1);
    /*
    removeFirst(p1);
    printPoly(p1);
    removeFirst(p1);
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
