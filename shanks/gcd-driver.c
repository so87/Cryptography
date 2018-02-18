// Simon Owens
// Dr. Morse Cryptography
// HW2 Shanks Algorithm
#include "stdio.h"
#include "gmp.h"
#include "shanks.h"

int main(int argc, char **argv)
{
       // Read in command line arguments
       if (argc != 2){
     	printf("Incorrect format\n");
	printf("Usage: ./shanks_alg <input file>\n");
	return 1;
       }
	printf("This program tests the GCD algorithm\n");

	// Initialize	
	mpz_t tempu, tempv, gcd, u, v;
	mpz_init(tempu);
	mpz_init(tempv);
	mpz_init(gcd);
	mpz_init(u);
	mpz_init(v);	
	FILE * file;
	file = fopen(argv[1], "r");
	
	// Assign values
	mpz_inp_str(u, file, 10);
	mpz_inp_str(v, file, 10);
	mpz_set(tempu, u);
	mpz_set(tempv, v);

	//Call GCD
	printf("--------------\n");
	binary_gcd(tempu, tempv, gcd);
	
	//Print the results
	gmp_printf("U equals: %Zd\n",u);
  	gmp_printf("V equals: %Zd\n",v);
	gmp_printf("GCD equals: %Zd\n", gcd);
	printf("--------------\n");
	printf("End of program\n");
	fclose(file);
        return 0;
}

