#include "stdio.h"
#include "gmp.h"
#include "hw1.h"
#include "stdbool.h"
void primitive_root(mpz_t rop, mpz_t p, const int n, const mpz_t* factors){
  // P is the prime
  // n is the number of factors
  // factors is all of the factors 
  bool accept = false;
  mpz_t p_minus_1, one; 
  init_prim_root(p, p_minus_1, one); 
  for(unsigned int i=2; mpz_cmp_ui(p,i+1)> 0;i++){
      mpz_t placeholder;
      mpz_init(placeholder);
      mpz_set_si(placeholder,i);
      for(int j = 0; j < n;j++){
          mpz_t q,r;
          mpz_init(q);
          mpz_init(r);
	  // Set the value of the temporary variables
	  mpz_powm(r,placeholder,q,p);
          mpz_fdiv_q(q,p_minus_1,factors[j]);
          if(mpz_cmp_si(r,1) == 0){
            accept = true;
          }
      }
      // if it is accepted we need to break
      if(accept){
      	mpz_set(rop,placeholder);
      	return;
      }
      accept = false;
  } 
};

void init_prim_root(mpz_t p, mpz_t p_minus_1, mpz_t one){
  mpz_init(p_minus_1);
  mpz_init(one);
  mpz_set_str(one,"1",10);
  mpz_sub(p_minus_1,p,one);
};
void init_eea(mpz_t u, mpz_t v, mpz_t gcd, mpz_t a, mpz_t b, FILE* stream){
  // Initializing the numbers 
  mpz_init(a);
  mpz_init(b);
  mpz_init(gcd);
  mpz_init(u);
  mpz_init(v);
  mpz_inp_str(a, stream, 10);
  mpz_inp_str(b, stream, 10);
  mpz_inp_str(gcd, stream, 10);
  gmp_printf("a:        %Zd\n", a);
  gmp_printf("b:        %Zd\n", b);
  gmp_printf("gcd:      %Zd\n", gcd);
  printf("--------------\n");
};
void eea(mpz_t u, mpz_t v, mpz_t d, const mpz_t a, const mpz_t b){
   	mpz_t ai, bi;
        mpz_t g, y;
        mpz_init(ai);
        mpz_init(bi);
        mpz_init(g);
        mpz_init(y);

        // set all of the values.  These must be initialized
        mpz_set(ai,a);
        mpz_set(bi,b);
        mpz_set_str(u,"0",10);
        mpz_set_str(v,"1",10);
        mpz_set_str(g,"1",10);
        mpz_set_str(y,"0",10);
        // continue to loop until we find it
        while(mpz_cmp_si(bi,0) != 0){
                // these are throw away variables we need everytime to reverse the gcd process
                mpz_t q,r;
                mpz_t currentU, currentV, mult;
                mpz_init(q);
                mpz_init(r);
                mpz_init(mult);
                mpz_init(currentU);
                mpz_init(currentV);
                mpz_fdiv_r(r , ai, bi);
                mpz_fdiv_q(q , ai , bi);
                // multiply them together
                mpz_mul(mult, g, q);
                // now do the sub to find your value
                mpz_sub(currentU, u, mult);

                mpz_mul(mult , y , q);
                mpz_sub(currentV , v , mult);

                // set all of the values now
                mpz_set(ai , bi);
                mpz_set(bi , r);
                mpz_set(u , g);
                mpz_set(v , y);
                mpz_set(g , currentU);
                mpz_set(y , currentV);
         }
};

