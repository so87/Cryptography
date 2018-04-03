#include "pohlig.h"
#include "stdio.h"
#include "gmp.h"
#include "shanks.h"
#include "stdbool.h"

void pohlig(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h)
{
	printf("Testing Pohlig\n");



}

void chineeseRemainder(mpz_t rop, const mpz_t * y, const struct factors * f, const mpz_t pri, int len)
{
  mpz_t p , prod, sum, pTemp, ropMul, tempMul1, tempMul2, ropTemp, qTemp, eTemp;
  int i;

  mpz_init(p);
  mpz_init(prod);
  mpz_init(sum);
  mpz_init(pTemp);
  mpz_init(ropMul);
  mpz_init(tempMul1);
  mpz_init(tempMul2);
  mpz_init(ropTemp);
  mpz_init(qTemp);
  mpz_init(eTemp);

  mpz_set_str(prod, "1", 10);
  mpz_set_str(sum, "0", 10);

  for (i = 0; i < len; i++)
    {
      mpz_set_ui(eTemp, ((struct factors *)f)->e[i]);
      mpz_powm(qTemp,((struct factors *)f)->p[i], eTemp, pri);
      mpz_mul(prod,prod,qTemp);
    }

  for (i = 0; i < len; i++)
    {
      mpz_set_ui(eTemp, ((struct factors *)f)->e[i]);
      mpz_powm(qTemp,((struct factors *)f)->p[i], eTemp, pri);
      mpz_cdiv_q(p, prod, qTemp);
      multiInverse(ropMul, p, qTemp);
      mpz_mul(tempMul1,y[i],ropMul);
      mpz_mul(tempMul2,tempMul1,p);
      mpz_add(sum,sum,tempMul2);
    }
  mpz_mod(rop,sum,prod);

  mpz_clear(p);
  mpz_clear(prod);
  mpz_clear(sum);
  mpz_clear(pTemp);
  mpz_clear(ropMul);
  mpz_clear(tempMul1);
  mpz_clear(tempMul2);
  mpz_clear(ropTemp);
  mpz_clear(qTemp);
  mpz_clear(eTemp);
}

void multiInverse(mpz_t rop, const mpz_t aIn, const mpz_t bIn)
{
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

