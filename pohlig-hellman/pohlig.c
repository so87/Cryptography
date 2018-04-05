// Simon Owens
// Homework assignment 3
// pohlig hellman implimentation

#include "pohlig.h"
#include "stdio.h"
#include "gmp.h"
#include "shanks.h"
#include "stdlib.h"

/* guidance:  https://en.wikipedia.org/wiki/Pohlig%E2%80%93Hellman_algorithm
 
 similar implimentation: https://github.com/Korzhenevski/Silver-Pohlig-Hellman-algorithm/blob/master/algorithm.cpp

*/
// Uses: multiplicitive inverse, shanks, and chinese remainder theorem
void pohlig(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t x)
{
  // Display what you are given for the user
  gmp_printf("%Zd^x = %Zd mod %Zd\n", g, x, p);
 
  // initilize 
  mpz_t n, n_copy ,h, g_copy, exp_copy, h_copy, q_copy , e_copy, one;
  mpz_t * array;
  mpz_init(n);
  mpz_init(n_copy);
  mpz_init(h);
  mpz_init(g_copy);
  mpz_init(exp_copy);
  mpz_init(h_copy);
  mpz_init(q_copy);
  mpz_init(e_copy);
  mpz_init_set_str(one, "1", 10);
  struct factors *factor_array = malloc(sizeof(struct factors)); 

  mpz_sub(n, p, one);
  mpz_set(n_copy, n);

  // use the factors library to factor...
  factor(n_copy,factor_array);

  array = malloc(sizeof(mpz_t)*factor_array->nfactors);

  for (unsigned long i = 0; i < factor_array->nfactors; i++){
      mpz_init(array[i]);
      mpz_set_ui(e_copy, factor_array->e[i]);
      mpz_powm(q_copy,factor_array->p[i], e_copy, p);
      mpz_cdiv_q(exp_copy, n, q_copy);
      mpz_powm(g_copy, g, exp_copy, p);
      mpz_powm(h_copy, x, exp_copy, p);
      
      //call Shank and find the value
      shanks(array[i], p, g_copy, h_copy, q_copy);
    }
    
    //  This will compute the value of the exponent... solves the descrete log prob
    //   for us
    chineese_remainder(rop, array, factor_array, n, p, factor_array->nfactors);
}

/* implimentation guidance: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/ */
void chineese_remainder(mpz_t rop, mpz_t * y, struct factors * array, mpz_t prod, mpz_t prime, unsigned long len)
{
  mpz_t p , sum, ropMul, temp_m1, temp_m2, rop_temp, q_temp, e_temp;
  unsigned long i;

  mpz_init(p);
  mpz_init(sum);
  mpz_init(ropMul);
  mpz_init(temp_m1);
  mpz_init(temp_m2);
  mpz_init(rop_temp);
  mpz_init(q_temp);
  mpz_init(e_temp);

  mpz_set_str(sum, "0", 10);

  for (i = 0; i < len; i++){
      mpz_set_ui(e_temp, ((struct factors *) array)->e[i]);
      mpz_powm(q_temp, ((struct factors *) array)->p[i], e_temp, prime);
      mpz_cdiv_q(p, prod, q_temp);
      mpz_invert(rop_temp, p, q_temp);
      mpz_mul(temp_m1, y[i], rop_temp);
      mpz_mul(temp_m2, temp_m1, p);
      mpz_add(sum, sum, temp_m2);
    }
  // finally mod out the result to be returned... again this is the right answer
  //  as long as there aren't any garbage values
  mpz_mod(rop,sum,prod);
}
