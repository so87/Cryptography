// Simon Owens
// Dr. Morse Cryptography
// HW2 Shanks Algorithm
#include "stdio.h"
#include "stdlib.h"
#include "gmp.h"
#include "shanks.h"
#include "stdbool.h"

int main(int argc, char **argv)
{
       // Read in command line arguments
       if ((argc !=2) && ( argc !=4)){
     	printf("\nIncorrect format\n");
	printf("Usage: ./shanks_alg <input file>\n");
	printf("	OR\n");
	printf("Usage: ./shanks_alg A B N \n");
	printf("	in the form    A^x = B mod N\n\n");
	return 1;
       }
	printf("This program tests the Shanks algorithm\n");

	// Initialize	
	mpz_t a, b, N, power;
	mpz_init(a);
	mpz_init(b);
	mpz_init(N);
	mpz_init(power);
	
	// If the file format is being used
	if(argc == 2){
	FILE * file;
	file = fopen(argv[1], "r");
	
	// Assign values
	mpz_inp_str(a, file, 10);
	mpz_inp_str(b, file, 10);
	mpz_inp_str(N, file, 10);
	fclose(file);
	}

	// If the command line argument is being used
	if(argc == 4){
	mpz_set_si(a, atoi(argv[1]));
	mpz_set_si(b, atoi(argv[2]));
	mpz_set_si(N, atoi(argv[3]));
	}
	

	//Call Shanks
	printf("--------------\n");
	int solution = shanks(a,b, N, power);
	
	//Print the results
	gmp_printf("%Zd^x = %Zd mod %Zd\n",a,b,N);
	
	if(solution == 1){	
	gmp_printf("X equals: %Zd\n", power);	
	}	
	else{
	printf("The value of X could not be found after %d iterations\n", solution);
	}	

	printf("--------------\n");
	printf("End of program\n");
        return 0;
}

