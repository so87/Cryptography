#ifndef FOO_H_   /* Include guard */
#define FOO_H_

#include "gmp.h"

// makes keeping track of the index alot easier
struct indexable_mpz {
        mpz_t value;
        int index; // can be an integer, won't ever store that many

};

void shanks(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h, const mpz_t n);

int compare_my_indexed_mpz(const void* a, const void* b);

#endif // FOO_H_
