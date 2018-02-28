#ifndef FOO_H_   /* Include guard */
#define FOO_H_

#include "shanks.h"
#include "gmp.h"

int shanks(mpz_t a, mpz_t b, mpz_t N, mpz_t x);
int binary_search(mpz_t * array, mpz_t value, int low, int high);
#endif // FOO_H_
