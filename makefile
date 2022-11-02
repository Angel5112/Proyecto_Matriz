all: matriz.o proy1.o
	gcc -g matriz.o proy1.o -o proy

matriz.o: matriz.c
	gcc -c matriz.c -o matriz.o

proy1.o: proy1.c
	gcc -c proy1.c -o proy1.o

test.o: test.c
	gcc -c test.c -o test.o

test: test.o
	./test