#include "stdio.h"
#include "gmp.h"

//BINARY GCD ALGORITHM
//Allows us to only use shifts and subtraction!
void binary_gcd(mpz_t u, mpz_t v, mpz_t r){
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
}

int main(int argc, char** argv){
    mpz_t u, v, r;
    mpz_init_set_str(u, argv[1], 10);
    mpz_init_set_str(v, argv[2], 10);
    mpz_init_set_str(r, "1", 10);
    binary_gcd(u, v, r);
    gmp_printf("%Zd\n", r);
    return 0;
}

