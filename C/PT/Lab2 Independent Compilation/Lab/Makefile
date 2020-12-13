
output: main_str.o libstrings.o libstrings.a main_str.x
	gcc -Wall -O3 -ansi -pedantic libstrings.o main_str.o libstrings.a main_str.x -output

libstrings.o: libstrings.h libstrings.c
	gcc -Wall -O3 -pedantic -c -o libstrings.o libstrings.c

main_str.o: main_str.c
	gcc -Wall -O3 -pedantic -c main_str.c -o main_str.o

libstrings.a: libstrings.o
	ar rcs libstrings.a libstrings.o

main_str.x: main_str.c main_str.o
	gcc -Wall -O3 -pedantic -o main_str.x main_str.o -L. -lstrings

clean:
	rm *.o *.a *.x
