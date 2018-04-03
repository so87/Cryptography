#ifndef FOO_H_   /* Include guard */
#define FOO_H_


#include "shanks.h"
#include "pohlig.h"
#include "factorize.h"

void pohlig(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h);

void chineeseRemainder(mpz_t rop, const mpz_t * y, const struct factors * f, const mpz_t pri, int len);

void multiInverse(mpz_t rop, const mpz_t a, const mpz_t b);

#endif // FOO_H_
