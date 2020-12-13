
output: main_str.o cstrings.o libcstrings.a main.x
	gcc -Wall -O3 -ansi -pedantic cstrings.o main.o libcstrings.a main.x -output

cstrings.o: cstrings.h cstrings.c
	gcc -Wall -O3 -pedantic -c -o cstrings.o cstrings.c

main_str.o: main.c
	gcc -Wall -O3 -pedantic -c main.c -o main.o

libcstrings.a: cstrings.o cstrings.h cstrings.c
	ar rcs libcstrings.a cstrings.o

main.x: main.c main.o
	gcc -Wall -O3 -pedantic -o main.x main.o -L. -lcstrings

clean:
	rm *.o *.a *.x
