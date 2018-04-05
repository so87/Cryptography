#ifndef FOO_H_   /* Include guard */
#define FOO_H_

#include "gmp.h"
#include "factorize.h"

void pohlig(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h);

void chineese_remainder(mpz_t rop, mpz_t * y, struct factors * f, mpz_t prime, int len);

void multiplicitive_inverse(mpz_t rop, mpz_t x, mpz_t y);

#endif // FOO_H_
