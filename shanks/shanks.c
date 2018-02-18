#include "stdio.h"
#include "gmp.h"
#include "stdlib.h"
#include "shanks.h"
#include "stdbool.h"
#include "math.h"

int shanks(mpz_t a, mpz_t b, mpz_t N, mpz_t x){
  bool solution = false;
  // Chose some random K
  int k=100;
  
  // Initilize array for a^1, ... a^k-1
  mpz_t * array_1;
  array_1 = malloc(sizeof(mpz_t)*k);  
 
  // Initilize array for ba^-k, ... ba^-rk  
  mpz_t * array_2;
  int n = mpz_get_ui(N);
  int r = k * ((n+1)/k); 
  array_2 = malloc(sizeof(mpz_t)*r);
 
  // Evaluate a^1, a^2, ... a^k-1 and store (array 1)
  for(int i = 1; i < k-1; i++){
	mpz_init(array_1[i]);
	// calc a^i mod N 
	
  } 

  // Iterate through ba^-k, ba^-2k,...ba^-rk(array 2)
  // 			                  rk > N
  for(int i = 1; i < r; i++){
	mpz_init(array_2[i]);
	// calc b*a^(-i*k) mod N

  	// If they match, solve by
  	
		// adding rk(array 2) to k(array 1)
  }

  free(array_1);
  free(array_2); 
  // Return 0 if solution
  // Return -1 if no solution
  return solution;
};

//BINARY GCD ALGORITHM
//Allows us to only use shifts and subtraction!
void binary_gcd(mpz_t u,mpz_t v, mpz_t r){
    if(mpz_cmp(u, v) == 0 || mpz_cmp_d(v, 0) == 0){
        mpz_set(r, u);
    }
    else if(mpz_cmp_d(u, 0) == 0){
        mpz_set(r, v);
    }
    else if(mpz_even_p(u) != 0){
        if(mpz_odd_p(v) != 0){
            mpz_fdiv_q_2exp(u, u, 1);
            binary_gcd(u, v, r);
        }
        else{
            mpz_fdiv_q_2exp(u, u, 1);
            mpz_fdiv_q_2exp(v, v, 1);
            binary_gcd(u, v, r);
            mpz_mul_2exp(r, r, 1);
        }
    }

    else if(mpz_even_p(v) != 0){
        mpz_fdiv_q_2exp(v, v, 1);
        binary_gcd(u, v, r);
    }

    else if(mpz_cmp(u, v) > 0){
        mpz_sub(u, u, v);
        mpz_fdiv_q_2exp(u, u, 1);
        binary_gcd(u, v, r);
    }
    else{
        mpz_sub(v, v, u);
        mpz_fdiv_q_2exp(v, v, 1);
        binary_gcd(v, u, r);
    }
};
