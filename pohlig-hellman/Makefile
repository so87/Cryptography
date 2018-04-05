Message = "Done building...\n"
factors = "\nBuildig factors..."
pohlig = "BUilding pohlig files..."

all: pohlig_driver
	@echo $(Message)

pohlig_driver: pohlig-driver.c shanks.c pohlig.c
	@echo $(pohlig)
	clang -lgmp pohlig-driver.c pohlig.c shanks.c factorize.c -o pohlig_driver
