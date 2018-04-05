// Simon Owens
// Homework assignment 3
// pohlig hellman implimentation... chinese remainder theorem stolen from
// stack overflow python code
#include "pohlig.h"
#include "stdio.h"
#include "gmp.h"
#include "shanks.h"
#include "stdlib.h"

void init_multiP_inv(mpz_t a, mpz_t b, mpz_t b0, mpz_t t, mpz_t q, mpz_t x0,
                        mpz_t x1, mpz_t zero, mpz_t one, mpz_t mulTemp,
                        mpz_t aIn, mpz_t bIn){
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
};

void init_pohlig(){


};

void init_chinese(){


};

/* guidance:  https://en.wikipedia.org/wiki/Pohlig%E2%80%93Hellman_algorithm
 
 similar implimentation: https://github.com/Korzhenevski/Silver-Pohlig-Hellman-algorithm/blob/master/algorithm.cpp

*/
void pohlig(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t x)
{
  // Display what you are given for the user
  gmp_printf("Prime: %Zd\n", p); 
  gmp_printf("Generator: %Zd\n", g);
  gmp_printf("H: %Zd \n", x);
  gmp_printf("Equation: g^x = h mod p\n");
  gmp_printf("         %Zd^x = %Zd mod %Zd\n", g, x, p);

  
  // initilize 
  mpz_t n, nTemp ,h, gTemp, expTemp, hTemp, qTemp , eTemp, one, result;
  mpz_t * gi;
  mpz_t * hi;
  mpz_t * yi;
  mpz_init(n);
  mpz_init(nTemp);
  mpz_init(h);
  mpz_init(gTemp);
  mpz_init(expTemp);
  mpz_init(hTemp);
  mpz_init(qTemp);
  mpz_init(eTemp);
  mpz_init(one);
  mpz_init(result);
  struct factors *factor_array = malloc(sizeof(struct factors)); 

  mpz_set_str(one,"1",10);
  mpz_sub(n,p,one);
  mpz_set(nTemp,n);

  // use the factors library to factor...
  factor(nTemp,factor_array);

  gi = malloc(sizeof(mpz_t)*factor_array->nfactors);
  hi = malloc(sizeof(mpz_t)*factor_array->nfactors);
  yi = malloc(sizeof(mpz_t)*factor_array->nfactors);

  for (int i = 0; i < factor_array->nfactors; i++){
      mpz_init(gi[i]);
      mpz_init(hi[i]);
      mpz_init(yi[i]);
    }


  for (int i = 0; i < factor_array->nfactors; i++){
      mpz_set_ui(eTemp, factor_array->e[i]);
      mpz_powm(qTemp,factor_array->p[i], eTemp, p);
      mpz_cdiv_q(expTemp,n,qTemp);
      mpz_powm(gTemp,g,expTemp,p);
      mpz_powm(hTemp,x,expTemp,p);
      
      //create the gi and hi
      mpz_set(gi[i],gTemp);
      mpz_set(hi[i],hTemp);
    }

  for (int i = 0; i < factor_array->nfactors; i++){
      mpz_set_ui(eTemp, factor_array->e[i]);
      mpz_powm(qTemp,factor_array->p[i], eTemp, p);
      mpz_set_ui(eTemp, factor_array->e[i]);
      
      //call Shank and make the yi
      shanks(yi[i],p,gi[i],hi[i],qTemp);
    }
    
    //  This will compute the value of the exponent... solves the descrete log prob
    //   for us
    chineese_remainder(rop, yi, factor_array, p, factor_array->nfactors);
}

/* implimentation guidance: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/ */
void chineese_remainder(mpz_t rop, mpz_t * y, struct factors * array, mpz_t prime, int len)
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

  for (i = 0; i < len; i++){
      // get the exponent
      mpz_set_ui(eTemp, ((struct factors *) array)->e[i]);
      // multiply the exponent by value in array 
      // mod it out
      mpz_powm(qTemp,((struct factors *) array)->p[i], eTemp, prime);
      // multiply that value by 
      mpz_mul(prod,prod,qTemp);
    }

  for (i = 0; i < len; i++){
      mpz_set_ui(eTemp, ((struct factors *) array)->e[i]);
      mpz_powm(qTemp,((struct factors *) array)->p[i], eTemp, prime);
      mpz_cdiv_q(p, prod, qTemp);
      multiplicitive_inverse(ropMul, p, qTemp);
      mpz_mul(tempMul1,y[i],ropMul);
      mpz_mul(tempMul2,tempMul1,p);
      mpz_add(sum,sum,tempMul2);
    }
  // finally mod out the result to be returned... again this is the right answer
  //  as long as there aren't any garbage values
  mpz_mod(rop,sum,prod);
}

/* guidance: https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ */
void multiplicitive_inverse(mpz_t rop, mpz_t aIn, mpz_t bIn)
{
  // initilize... moved to init function was very messy
  mpz_t a, b, b0, t, q, x0, x1, zero, one, mulTemp;
  init_multiP_inv(a, b, b0, t, q, x0, x1, zero, one, mulTemp, aIn, bIn);

  // if they are one then we don't do anything
  if (mpz_cmp(b,one) == 0){
   mpz_set(rop,one);
   return;
  }
  
  while(mpz_cmp(a,one) > 0){
   mpz_fdiv_q(q,a,b);
   mpz_set(t,b);
   mpz_mod(b,a,b);
   mpz_set(a,t);
   mpz_set(t,x0);

   mpz_mul(mulTemp,q,x0);
   mpz_sub(x0,x1,mulTemp);
   mpz_set(x1,t);
  }
  
  if (mpz_cmp(x1,zero) < 0){
    mpz_add(x1,x1,b0);
  }
  // prepare her to be sent back
  mpz_set(rop,x1);
}

