Message = "Done building...\n"
factors = "\nBuildig factors..."
shanks = "Building shanks alg driver..."
pohlig = "BUilding poholig files..."

all: pohlig_driver
	@echo $(Message)

pohlig_driver: pohlig-driver.c shanks.c
	@echo $(shanks)
	@echo	
	clang -lgmp pohlig-driver.c shanks.c factorize.c -o shanks_driver

