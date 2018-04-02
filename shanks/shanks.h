#ifndef FOO_H_   /* Include guard */
#define FOO_H_

#include "shanks.h"
#include "gmp.h"

void shanks(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h);
int binary_search(mpz_t * array, int size, mpz_t find);


#endif // FOO_H_
