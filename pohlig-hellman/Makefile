Message = "Done building...\n"
factors = "\nBuildig factors..."
pohlig = "BUilding pohlig files..."

all: pohlig_driver
	@echo $(Message)

youtube: SHELL:=/bin/bash
youtube:
	firefox https://www.youtube.com/watch?v=DfO-gf_a8Bc&list=PLSEW_LoxvVOaOltv3gwMblCkd1-ELiUd9

pohlig_driver: pohlig-driver.c
	@echo $(pohlig)
	clang -lgmp pohlig-driver.c pohlig.c shanks.c factorize.c -o pohlig_driver
