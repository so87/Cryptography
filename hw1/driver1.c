// Simon Owens
// Dr. Morse Cryptography
// HW1
#include "stdio.h"
#include "gmp.h"
#include "hw1.h"

int main(int argc, char **argv)
{
       // Read in command line arguments
       if (argc != 2){
     	printf("Incorrect format\n");
	return 1;
       }
	printf("This program tests the Extended Euclidian Algorithm\n");
	printf("Usage: ./hw1_driver file \n");

	// Initialize	
	mpz_t a, b, gcd, u, v;
	FILE * file;
	file = fopen(argv[1], "r");

	//Call EEA
	printf("--------------\n");
	init_eea(a,b,gcd,u,v,file);
	eea(u,v,gcd,a,b);	
	
	//Print the results
	gmp_printf("U equals: %Zd\n",u);
  	gmp_printf("V equals: %Zd\n",v);
	printf("--------------\n");
	printf("End of program\n");
	fclose(file);
        return 0;
}

