#ifndef FOO_H_   /* Include guard */
#define FOO_H_

#include "gmp.h"
#include "factorize.h"

void pohlig(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h);

void chineese_remainder(mpz_t rop, mpz_t * y, struct factors * f,mpz_t prod, mpz_t prime, unsigned long len);


#endif // FOO_H_
