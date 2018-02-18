// Simon Owens
// Dr. Morse Cryptography
// HW2 Shanks Algorithm
#include "stdio.h"
#include "gmp.h"
#include "shanks.h"
#include "stdbool.h"

int main(int argc, char **argv)
{
       // Read in command line arguments
       if (argc != 2){
     	printf("Incorrect format\n");
	printf("Usage: ./shanks_alg <input file>\n");
	return 1;
       }
	printf("This program tests the Shanks algorithm\n");

	// Initialize	
	mpz_t a, b, N, power;
	mpz_init(a);
	mpz_init(b);
	mpz_init(N);
	mpz_init(power);
	FILE * file;
	file = fopen(argv[1], "r");
	
	// Assign values
	mpz_inp_str(a, file, 10);
	mpz_inp_str(b, file, 10);
	mpz_inp_str(N, file, 10);
	
	//Call Shanks
	printf("--------------\n");
	bool solution = shanks(a,b, N, power);
	
	//Print the results
	gmp_printf("%Zd^x = %Zd mod %Zd\n",a,b,N);
	
	if(solution){	
	gmp_printf("X equals: %Zd\n", power);	
	}	
	else{
	printf("The value of X could not be found after 100 iterations\n");
	}	

	printf("--------------\n");
	printf("End of program\n");
	fclose(file);
        return 0;
}

