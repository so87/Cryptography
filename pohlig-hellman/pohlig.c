#include "stdio.h"
#include "gmp.h"
#include "shanks.h"
#include "pohlig.h"
#include "factorize.h"
#include "stdbool.h"

void pohlig(mpz_t rop, const mpz_t p,
         const mpz_t g,
         const mpz_t h)
{
	printf("Testing Pohlig\n");



}

void chineeseRemainder(mpz_t rop, const mpz_t * y,
                       const struct factors * f,
                       const mpz_t pri,
                       int len)
{



}

void multiInverse(mpz_t rop, const mpz_t aIn,
                  const mpz_t bIn)
{
//gmp_printf("a = %Zd, b = %Zd\n", aIn,bIn);

  bool found = false;
  mpz_t a, b,b0, t, q, x0, x1, zero, one, mulTemp;

  mpz_init(a);
  mpz_init(b);
  mpz_init(b0);
  mpz_init(t);
  mpz_init(q);
  mpz_init(x0);
  mpz_init(x1);
  mpz_init(zero);
  mpz_init(one);
  mpz_init(mulTemp);

  mpz_set(a,aIn);
  mpz_set(b,bIn);

  mpz_set(b0,b);
  mpz_set_str(x0, "0", 10);
  mpz_set_str(x1, "1", 10);

  mpz_set_str(zero, "0", 10);
  mpz_set_str(one, "1", 10);

  if (mpz_cmp(b,one) == 0)
    {
      mpz_set(rop,one);
      found = true;
    }

  if (!found)
    {

      while(mpz_cmp(a,one) > 0)
        {
          mpz_fdiv_q(q,a,b);
          mpz_set(t,b);
          mpz_mod(b,a,b);
          mpz_set(a,t);
          mpz_set(t,x0);

          mpz_mul(mulTemp,q,x0);
          mpz_sub(x0,x1,mulTemp);
          mpz_set(x1,t);
        }

      if (mpz_cmp(x1,zero) < 0)
        {
          mpz_add(x1,x1,b0);
        }

      mpz_set(rop,x1);

    }
  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(b0);
  mpz_clear(t);
  mpz_clear(q);
  mpz_clear(x0);
  mpz_clear(x1);
  mpz_clear(zero);
  mpz_clear(one);
  mpz_clear(mulTemp);


}

