all: 
	make clean
	gcc -pedantic -Wall -g -o project0 project0_3.c
clean:
	-rm ./project0

