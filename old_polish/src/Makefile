F= -Wall -Wextra -Werror


libs:
	gcc $(F) -c operations.c -o ../build/op.o
	gcc $(F) -c yard.c -o ../build/ya.o
	gcc $(F) -c visual.c -o ../build/vi.o
	gcc $(F) -c input.c -o ../build/in.o

all: libs
	gcc $(F) ../build/*.o graph.c -o ../build/MAIN

run_dev:all
	../build/MAIN