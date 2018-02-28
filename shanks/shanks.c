#include "stdio.h"
#include "gmp.h"
#include "stdlib.h"
#include "shanks.h"
#include "math.h"

int shanks(mpz_t a, mpz_t b, mpz_t N, mpz_t x){
  // k = floor(sqrt(n)) + 1
  mpz_t k_mpz, one;
  mpz_init(one);
  mpz_set_str(one, "1", 10);
  mpz_init(k_mpz);
  mpz_sqrt(k_mpz, N);
  mpz_add(k_mpz, one, k_mpz);
  int k = mpz_get_ui(k_mpz);
  
  // Initilize array for a^1, ... a^k-1
  mpz_t * array_1;
  array_1 = malloc(sizeof(mpz_t)*k);  
 
  // Initilize varialbe for ba^-k, ... ba^-rk  
  mpz_t result;
  mpz_init(result);
  int n = mpz_get_ui(N);
  int r = k * ((n+1)/k); 
 
  // Evaluate a^1, a^2, ... a^k-1 and store (array 1)
  for(int i = 1; i < k-1; i++){
	mpz_init(array_1[i]);
	// calc a^i mod N 
	mpz_powm_ui(array_1[i], a, i, N);
  } 
  
  // Iterate through ba^-k, ba^-2k,...ba^-rk(array 2)
  // 			                  rk > N
  mpz_t powers, inverse_a, result_a, result_ab, result_mod;
  mpz_init(powers);
  mpz_init(inverse_a);
  mpz_init(result_a);
  mpz_init(result_ab);
  mpz_init(result_mod);
  int power_int;
  for(int i = 1; i < r; i++){
	// calc b*a^(-i*k) mod N
	
	// Find inverse
	power_int = i*k;
	mpz_invert(inverse_a, a, N);	
	mpz_powm_ui(result_a, inverse_a, power_int, N);
	
	// multiply a and b together
	mpz_mul(result_ab, result_a, b);
	
	// Mod the result
	mpz_mod(result_mod, result_ab, N);
	
	// Binary search through the first array
	int middle = binary_search(array_1, result_mod, 1, k-1);
	if(middle != -1){
	  // adding the index from first array to power(i*k)	
	  mpz_set_ui(x, middle+power_int);
	  return 1;		
	}
  }

  free(array_1);
  // Return 0 if solution
  // Return -1 if no solution
  return r;
};

int binary_search(mpz_t * array, mpz_t value, int low, int high){
  while(low <= high){
	int middle = low + (high-low)/2;
	
	// if value we are searching for is higher
	if(mpz_cmp(value, array[middle]) > 0){
	  low = middle + 1; 
	}
	
	// if number is lower
	else if(mpz_cmp(value, array[middle]) < 0){
	  high = middle - 1;
	}	
	
	// if number is the middle
  	else{
	  return middle;
	}	
	
  } 
 
  // number was not found
  return -1;
}
