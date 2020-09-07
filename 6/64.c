#include <stdio.h>
#include <stdlib.h>

typedef struct fraction_st Fraction;

struct fraction_st{
    unsigned int numerator, denominator;
};

/* Algorithm for determining greatest common divisor, needed in (d) */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

/* Exercise a: Set fraction
 * Parameters: numerator and denominator
 * Returns: pointer to allocated fraction
 */
Fraction* setFraction(unsigned int numerator, unsigned int denominator){
    Fraction *f = malloc(sizeof(struct fraction_st));
    f->numerator = numerator;
    f->denominator = denominator;
    return f;
}

unsigned int getNum(const Fraction *f){
    return f->numerator;
}

unsigned int getDenom(const Fraction *f){
    return f->denominator;
}

void freeFraction(Fraction *f){
    free(f);
}



/* Exercise b: Compare values
 * Parameters: two fractions to be compared
 * Returns:
 * -1 if a is smaller than b
 * 0 if the fractions are equal
 * 1 if a is larger than b
 */
int compFraction(const Fraction *a, const Fraction *b){
    double x = (a->numerator/(double)a->denominator);
    double y = (b->numerator/(double)b->denominator); 
    return (x>=y) ? ((x==y) ? 0 : 1) : -1;
}

/* Exercise c: Add values
 * Parameters: two fractions to be added
 * Returns: sum of the fractions
 */
Fraction* addFraction(const Fraction *a, const Fraction *b){
    Fraction *f = malloc(sizeof(struct fraction_st));
    (a->denominator==b->denominator) ? (
        (f->numerator = a->numerator + b->numerator),(f->denominator = a->denominator)
    ):(
        (f->numerator = a->numerator*b->denominator + b->numerator*a->denominator),(f->denominator = a->denominator * b->denominator)
    );
    return f;
}

/* Reduce fraction
 * Parameters: Fraction to be reduced. Reduction happens on the object itself */
void reduceFraction(Fraction* val){
    int a = gcd(val->numerator, val->denominator);
    val->numerator /= a;
    val->denominator /= a;
}

/* Not needed, but it will be useful to implement this */
void printFraction(const Fraction *val){
    printf("%d/%d", val->numerator, val->denominator);
}
