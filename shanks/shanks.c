#include "stdio.h"
#include "gmp.h"
#include "stdlib.h"
#include "shanks.h"
#include "math.h"
// need a structure to keep track of index
typedef struct {
        mpz_t g;
        int index;

}mpz;

int compare(const void* a, const void* b){
        mpz *lhs = (mpz*)a;
        mpz* rhs = (mpz*)b;
        return(mpz_cmp(lhs->g,rhs->g));

}

int binary_search(mpz * array, int size, mpz_t find);
void shanks(mpz_t rop, const mpz_t p, const mpz_t g, const mpz_t h){
	//Set up for n = floor of sqrt p-1 + 1  
        mpz_t n,N;
        mpz_init(N);
        mpz_init(n);
        mpz_sub_ui(N,p,1);
        mpz_sqrt(n,N);
        mpz_add_ui(n,n,1);
        mpz * powers;
        int size = mpz_get_ui(n);

        powers = malloc(sizeof(mpz) * size);
        mpz_init(powers[0].g);
        mpz_set_str(powers[0].g,"1",10);
        powers[0].index = 0;
        for(int i=1;i <= size;i++){
                mpz_init(powers[i].g);
                mpz_mul(powers[i].g,powers[i-1].g,g);
                mpz_mod(powers[i].g,powers[i].g,p);
                powers[i].index = i;
        }

        qsort ( powers, size, sizeof(mpz), compare );
        // set u = g^-n
        mpz_t u;
        mpz_init(u);
        mpz_invert(u,g,p);
        mpz_powm (u, u, n, p);
        mpz_t H;
        mpz_init_set(H,h);

	for(int i=0;i<= size;i++){

                int j = binary_search(powers,size,H);
                // if found h*u^i return i*n + j                
                if(j >= 0){
                        mpz_mul_ui(rop,n,i);
                        mpz_add_ui(rop,rop,powers[j].index);
                        return;
                }
                mpz_mul (H, H, u);
                mpz_mod (H, H, p);
        }

};


int binary_search(mpz * arr, int size, mpz_t find){
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
