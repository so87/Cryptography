// Simon Owens
// Dr. Morse Cryptography
// HW3 Pohlig Hellman Algorithm
#include "stdio.h"
#include "stdlib.h"
#include "gmp.h"
#include "pohlig.h"

int main(int argc, char **argv)
{
       // Make sure they are using the right things
       if ((argc !=2) && ( argc !=4)){
	printf("Usage: ./pohlig_driver <input file>\n");
	printf("your input file should tell how many tuples it contains\n");	
	printf("	OR\n");
	printf("Usage: ./pohlig_driver g h p \n");
	printf("	in the form    g^x = h mod p\n\n");
	return 1;
       }

	printf("This program tests the pohlig hellman algorithm\n");
	printf("--------------\n");	

	// Initialize	
	mpz_t g, h, p, exponent;
	mpz_init(g);
	mpz_init(h);
	mpz_init(p);
	mpz_init(exponent);
		
	// If the file format is being used
	FILE * file;	
	if(argc == 2){
		file = fopen(argv[1], "r");
		unsigned int touples = 0;
		fscanf(file, "%d", &touples);

        	for (unsigned int i = 0; i < touples; i++)
         	{
          	//Assign Values
          	mpz_inp_str(p, file, 10);
          	mpz_inp_str(g, file, 10);
          	mpz_inp_str(h, file, 10);

	  	// call the pohlig algorithm
          	pohlig(exponent, p, g, h);
		mpz_t check;
		mpz_init(check);
		mpz_powm(check,g,exponent,p);
		if(mpz_cmp(check,h) != 0){
			gmp_printf("wrong answer: %Zd h is: %Zd",check,h);
		}
          	gmp_printf("The exponent is : %Zd\n", exponent);
		if ((touples > 1) && (i != (touples-1)))
			printf("---------------\n");
         	}

	}
	
	// If the command line argument is being used
	if(argc == 4){
		mpz_set_si(p, atoi(argv[1]));
		mpz_set_si(g, atoi(argv[2]));
		mpz_set_si(h, atoi(argv[3]));

		//Call the pohlig algorithm
		printf("--------------\n");
		pohlig(exponent, p, h, g);
	
		//Print the results
		gmp_printf("The answer is: = %Zd\n",exponent);
	}


	// FIN
	printf("--------------\n");
	printf("End of program\n");
       
	if(argc == 2) 
	  free(file);

	return 0;
}

