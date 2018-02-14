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
        printf("This program tests the Primitive Root Function\n");
        printf("Usage: ./hw2_driver file \n");

        mpz_t a,b,gcd,u,v;
        FILE * file;
        file = fopen(argv[1], "r");

        //Call initalize
        printf("--------------\n");
	mpz_t rop, p;
	int n;
	mpz_t* factors;
	mpz_init(rop);
	mpz_init(p);

	//Read in data
	mpz_inp_str(p, file, 10);
	fscanf(file, "%d", &n);
	factors = malloc(sizeof(mpz_t)* n);

	//Read in how many factors the size is
	for(int i =0; i < n; i++){	
	mpz_inp_str(factors[i], file, 10);
	}

	// Call Primitive root
 	primitive_root(rop, p, n, factors);		
		
        //Print the results
	gmp_printf("prime:          %Zd\n", p);
	printf("numb factors:   %d\n", n);
  	gmp_printf("primitive root: %Zd\n", rop);
        printf("--------------\n");
        printf("End of program\n");
	free(factors);
        fclose(file);
        return 0;
}

