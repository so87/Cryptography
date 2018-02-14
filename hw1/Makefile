Message = "Done Building both main programs"
d1 = "Building driver1.c ..."
d2 = "Building driver2.c ..."

all: hw1_driver1 hw1_driver2
	@echo $(Message)

hw1_driver1: driver1.c eea_prim_root.c
	@echo $(d1)
	clang -lgmp driver1.c eea_prim_root.c -o hw1_driver1

hw1_driver2: driver2.c eea_prim_root.c
	@echo $(d2)
	clang -lgmp driver2.c eea_prim_root.c -o hw1_driver2

