// Simon Owens aka "the kid"
// shank redo
// i calculated size wrong in my last shank attempt thats why it didn't
//  work for large numbers........... can i have my points back? :]

#include "stdio.h"
#include "gmp.h"
#include "stdlib.h"
#include "shanks.h"
#include "math.h"


void shanks(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h){
	// init
        mpz_t floor,N;
        mpz_init(N);
        mpz_init(floor);
	
	// find the floor of the (p-1)^1/2 + 1
        mpz_sub_ui(N,p,1);
        mpz_sqrt(floor,N);
        mpz_add_ui(floor,floor,1);
        struct indexable_mpz * powers;
	// this isn't ever going to be over 65,535 bits. God himself
	// couldn't even bruteforce that
        unsigned int size = mpz_get_ui(floor);

	// create the array
        powers = malloc(sizeof(struct indexable_mpz) * size);
        mpz_init(powers[0].g);
        mpz_set_str(powers[0].g,"1",10);
       
	// we won't use that zero index so just fill it up. Don't want to 
	// accidently access a memory address or randmo value 
	powers[0].index = 0;
        for(int i=1;i <= size;i++){
                mpz_init(powers[i].g);
                mpz_mul(powers[i].g,powers[i-1].g,g);
                mpz_mod(powers[i].g,powers[i].g,p);
                powers[i].index = i;
        }

	// need to sort so we can search in O(lgn) time... qsort is easy
        qsort ( powers, size, sizeof(struct indexable_mpz), compare_my_indexed_mpz);
        
	// find x = g^-n
        mpz_t x;
        mpz_init(x);
        mpz_invert(x,g,p);
	// make sure the answer is moded
        mpz_powm (x, x, floor, p);
        mpz_t H;
        mpz_init_set(H,h);

	// keep trying up to your size... we are not expecting any bad input
	for(int i=0;i<= size;i++){
		// O(lgn) because it is sorted :]
                int j = binary_search(powers,size,H);
                
		// if found h*x^i return i*n + j                
                if(j >= 0){
                        mpz_mul_ui(rop , floor, i);
                        mpz_add_ui(rop, rop, powers[j].index);
                        return;
                }
		// otherwise continue to multiply and then mod out
                mpz_mul (H, H, x);
                mpz_mod (H, H, p);
        }

}

// this function helps me compare two indexable mpz structures
// they know their size and value
int compare_my_indexed_mpz(const void* x, const void* y){
        struct indexable_mpz *lhs = (struct indexable_mpz*)x;
        struct indexable_mpz* rhs = (struct indexable_mpz*)y;
        return(mpz_cmp(lhs->g,rhs->g));

}

// can do a binary search because indexable_mpz know their place
// and we bc we sorted them with qsort
int binary_search(struct indexable_mpz * arr, int size, mpz_t find){
        int l,r;
        l = 0; r = size;
        while(l <= r){
                int m = l+(r-l)/2;
                if(mpz_cmp(arr[m].g,find) == 0)return m;
                if(mpz_cmp(arr[m].g,find) < 0) l = m+1;
                else r = m-1;

        }
        return -1;

}
