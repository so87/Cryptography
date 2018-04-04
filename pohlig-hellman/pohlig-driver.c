// Simon Owens
// Dr. Morse Cryptography
// HW3 Pohlig Hellman Algorithm
#include "stdio.h"
#include "stdlib.h"
#include "gmp.h"
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
	printf("--------------\n");	

	// Initialize	
	mpz_t g, h, p, power, numTimes;
	mpz_init(g);
	mpz_init(h);
	mpz_init(p);
	mpz_init(power);
	mpz_init(numTimes);
		
	// If the file format is being used
	FILE * file;	
	if(argc == 2){
	file = fopen(argv[1], "r");
	mpz_inp_str(numTimes, file, 10);

        double numT =  mpz_get_d(numTimes);

        for (double i = 0; i < numT; i++)
         {
          //Assign Values
          mpz_inp_str(p, file, 10);
          mpz_inp_str(g, file, 10);
          mpz_inp_str(h, file, 10);

          pohlig(power, p, g, h);
          gmp_printf("The answer is : %Zd\n\n", power);
         }

	}
	
	// If the command line argument is being used
	if(argc == 4){
	mpz_set_si(p, atoi(argv[1]));
	mpz_set_si(g, atoi(argv[2]));
	mpz_set_si(h, atoi(argv[3]));
	//Call Pohlig
	printf("--------------\n");
	pohlig(power, p, h, g);
	//Print the results
	gmp_printf("The answer is: = %Zd\n",power);
	}


	// FIN
	printf("--------------\n");
	printf("End of program\n");
       
	if(argc == 2) 
	  free(file);

	return 0;
}

