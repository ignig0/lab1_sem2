
all: matrix


matrix: complex.o integer.o main.o matrix.o
	gcc complex.o integer.o main.o matrix.o -o matrix


main.o: main.c
	gcc -c main.c

integer.o: integer.c
	gcc -c integer.c

complex.o:complex.c
	gcc -c complex.c

matrix.o: matrix.c
	gcc -c matrix.c

clean:
	rm -rf *.o matrix