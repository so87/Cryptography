// Simon Owens
// shank redo

#include "math.h"
#include "stdio.h"
#include "gmp.h"
#include "stdlib.h"
#include "shanks.h"


void shanks(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h, const mpz_t N){
  // set all mpz variables
  mpz_t floor, mpz_one, a, a_contains, h_mod_answer;
  mpz_init(floor);
  mpz_init(mpz_one);
  mpz_set_str(mpz_one , "1", 10);
  // reading this N in to make it easier
  mpz_sqrt(floor,N);
  mpz_add(floor,floor,mpz_one);
  // setup all the arrays and structures for performing baby step giant step
  struct indexable_mpz * array_of_mpz;
  int baby_index = 0;
  struct indexable_mpz * baby_array = 0;
  struct indexable_mpz temp;
  // allocate the correct size
  array_of_mpz = malloc ((mpz_get_ui (floor)+1) * sizeof (struct indexable_mpz));
  mpz_init_set_ui (array_of_mpz[0].value, 1);
  // init this place with zero
  array_of_mpz[0].index = 0;
  mpz_init(temp.value);

  // loop through, cannot be over unsigned long int size or else god himself couldn't
  //  solve this problem
  for (unsigned long int i = 1; i <= mpz_get_ui (floor); i++)
    {
      array_of_mpz[i].index = i;
      mpz_init (array_of_mpz[i].value);
      mpz_powm_ui(array_of_mpz[i].value,g,i,p);
    }
  // we need to make sure it is in sorted order and keep track of it
  qsort(array_of_mpz, mpz_get_ui (floor)+1, sizeof (struct indexable_mpz), compare_my_indexed_mpz);

  // h* g^(-floor*q)
  mpz_init_set (a, g);
  // which will get us the result  h*a^floor
  //a = g^floor
  mpz_powm (a, a, floor, p);
  // a = g^inverse(floor)
  mpz_invert (a, a, p);
  mpz_init_set (a_contains,a);
  //h_mod_answer = h
  mpz_init_set (h_mod_answer, h);

  // search through our sorted array in O(lgn) time
  for (int i = 0; i <= mpz_get_ui (floor); i++)
    {

      mpz_set(temp.value, h_mod_answer);
      //find h*a^floor in array_of_mpz by doing binary search
      // we can use the built in bsearch because of our compare function and 
      // because everything is in sorted order
      baby_array = (struct indexable_mpz*) bsearch (&temp, array_of_mpz, mpz_get_ui (floor)+1, sizeof (struct indexable_mpz),  compare_my_indexed_mpz);

      // needs to be greater than 0 if we are going to find the returned result
      if (baby_array > 0)
        {
          baby_index = baby_array->index;
          mpz_mul_ui (floor,floor,i); 
          mpz_add_ui (floor,floor,baby_index);
          // need to return the rop
          mpz_set (rop, floor);
          return;
        }
      //h = h*a^i
      // not expecting any bad input
      mpz_mul (h_mod_answer, h_mod_answer, a);
      mpz_mod(h_mod_answer, h_mod_answer, p);

    }

}

// this function helps me compare two indexable mpz structures
// they know their size and value
int compare_my_indexed_mpz(const void* x, const void* y){
        struct indexable_mpz *lhs = (struct indexable_mpz*)x;
        struct indexable_mpz* rhs = (struct indexable_mpz*)y;
        return(mpz_cmp(lhs->value,rhs->value));

}

