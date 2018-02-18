Message = "Done building...\n"
gcd = "\nBuilding gcd driver..."
shanks = "Building shanks alg driver..."

all: gcd_driver shanks_driver
	@echo $(Message)

gcd_driver: gcd-driver.c shanks.c
	@echo $(gcd)
	@echo
	clang -lgmp gcd-driver.c shanks.c -o gcd_driver

shanks_driver: shanks-driver.c shanks.c
	@echo $(shanks)
	@echo	
	clang -lgmp shanks-driver.c shanks.c -o shanks_driver
