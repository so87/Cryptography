#ifndef FOO_H_   /* Include guard */
#define FOO_H_

#include "hw1.h"

void eea(mpz_t u, mpz_t v, mpz_t d, const mpz_t a, const mpz_t b);
void primitive_root(mpz_t rop, mpz_t p, const int n, const mpz_t* factors);
void init_eea(mpz_t u, mpz_t v, mpz_t d,  mpz_t a, mpz_t b, FILE* stream);
void init_prim_root(mpz_t p, mpz_t p_minus_1, mpz_t one);

#endif // FOO_H_
