Message = "Done building...\n"
gcd = "\nBuilding gcd driver..."
shanks = "Building shanks alg driver..."

all: shanks_driver
	@echo $(Message)

shanks_driver: shanks-driver.c shanks.c
	@echo $(shanks)
	@echo	
	clang -lgmp shanks-driver.c shanks.c -o shanks_driver
