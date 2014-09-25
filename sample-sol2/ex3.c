#include <stdio.h>
#include <stdlib.h>

/***************************************************/
typedef struct Monomial {
    int coeff;     /* coefficient */
    int exp;       /* exponent    */
    struct Monomial *next;  /* next monomial */
} Mono;

/***************************************************/
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
    if( poly == NULL ) return NULL;
    poly->deg = 0;
    poly->first = poly->last = NULL;
    return poly;
}

/***************************************************/
void freePoly(Poly* p)
{
    Mono *m1, *m2;

    if( p == NULL ) return;
    m1 = p->first;

    while( m1 != NULL )
    {
       m2 = m1->next;
       free(m1);
       m1 = m2;
    }
    free(p);
    return;
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
    int n, c, k;

    Poly* poly = newPoly();
    if( poly == NULL ) return NULL;

    scanf( "%d", &n);
    poly->deg = n;
    poly->first = poly->last = NULL;

    do
    {
        scanf( "%d %d", &c, &k );
        appendMono( poly, newMono(c, k, NULL) );
    }
    while( k < n);

    return poly;
}

/***************************************************/
void printPoly( Poly* p )
{
    Mono* m;

    if( p == NULL || p->first == NULL )
    {
       return;
    }
    else
    {
       /* print degree */
       printf( "%d ", p->deg );

       m = p->first;
       while( m != NULL )
       {
           printf( "%d %d ", m->coeff, m->exp );
           m = m->next;
       }
       /* end with newline character */
       printf( "\n" );
    }
}

/***************************************************/
Poly* addPoly( Poly* p1, Poly* p2 )
{
    Mono *m1, *m2;
    Poly* result = newPoly();

    m1 = (p1==NULL ? NULL : p1->first);
    m2 = (p2==NULL ? NULL : p2->first);

    while( m1!=NULL && m2!=NULL )
    {
       if( m1->exp == m2->exp )
       {
          if( m1->coeff + m2->coeff != 0 )
          {
             appendMono( result, newMono(m1->coeff + m2->coeff, m1->exp, NULL) );
          }
          m1 = m1->next;
          m2 = m2->next;
       }
       else if( m1->exp < m2->exp )
       {
          appendMono( result, newMono(m1->coeff, m1->exp, NULL) );
          m1 = m1->next;
       }
       else /*m1->exp > m2->exp */
       {
          appendMono( result, newMono(m2->coeff, m2->exp, NULL) );
          m2 = m2->next;
       }
    }

    /* append leftover monomials, if any */
    while( m1!=NULL )
    {
       appendMono( result, newMono(m1->coeff, m1->exp, NULL) );
       m1 = m1->next;
    }

    while( m2!=NULL )
    {
       appendMono( result, newMono(m2->coeff, m2->exp, NULL) );
       m2 = m2->next;
    }

   if( result->last != NULL )
   {
       result->deg = result->last->exp;
   }
   else
   {
       result->deg = 0;  /* zero polynomial */
   }

   return result;
}

/***************************************************/ 

int main()
{
    Poly* p1 = readPoly();
    Poly* p2 = readPoly();
    Poly* sum;

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

    printPoly( sum = addPoly( p1, p2 ) );

    freePoly(p1);
    freePoly(p2);
    freePoly(sum);

    return 0;
}
