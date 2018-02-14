#include "stdio.h"
#include "gmp.h"

int main(int argc, char **argv)
{
	// Allocating space for these structures
	mpz_t a, b;	
	mpz_init(a);
	mpz_init(b);

	// Base 10	
	mpz_set_str(a,"12394871230000000000000000000000000048912398471247891239478123047891230789", 10);
	// Base 2
	mpz_set_str(b, "010101010010101010101001010101010010101001010101010100101010101", 2);

	// Z is to print out the mpz type
	gmp_printf("This is a: %Zd\n", a);	
	gmp_printf("This is b: %Zi\n", b);

	return 0;
}
