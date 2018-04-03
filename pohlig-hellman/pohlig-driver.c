// Simon Owens
// Dr. Morse Cryptography
// HW3 Pohlig Hellman Algorithm
#include "stdio.h"
#include "stdlib.h"
#include "gmp.h"
#include "stdbool.h"
#include "pohlig.h"

int main(int argc, char **argv)
{
       // Read in command line arguments
       if ((argc !=2) && ( argc !=4)){
     	printf("\nIncorrect format\n");
	printf("Usage: ./pohlig_driver <input file>\n");
	printf("	OR\n");
	printf("Usage: ./pohlig_driver A B N \n");
	printf("	in the form    A^x = B mod N\n\n");
	return 1;
       }
	printf("This program tests the pohlig hellman algorithm\n");

	// Initialize	
	mpz_t g, h, p, power;
	mpz_init(g);
	mpz_init(h);
	mpz_init(p);
	mpz_init(power);
	int touples = 1;
	
	// If the file format is being used
	FILE * file;
	if(argc == 2){
	file = fopen(argv[1], "r");
	fscanf(file, "%d", &touples);
	}
	
	// If the command line argument is being used
	if(argc == 4){
	mpz_set_si(p, atoi(argv[1]));
	mpz_set_si(g, atoi(argv[2]));
	mpz_set_si(h, atoi(argv[3]));
	}
	
	for(int i=0; i < touples; i++){
	// Assign values
        mpz_inp_str(p, file, 10);
        mpz_inp_str(g, file, 10);
        mpz_inp_str(h, file, 10);

	//Call Pohlig
	printf("--------------\n");
	pohlig(power, p, h, g);
	
	//Print the results
	gmp_printf("Power = %Zd\n",power);

	}

	printf("--------------\n");
	printf("End of program\n");
       
	if(argc == 2) 
	  free(file);

	return 0;
}

