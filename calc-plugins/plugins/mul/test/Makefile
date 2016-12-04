CC=gcc
CFLAGS=-Wall -I. -I.. -std=gnu99 -pedantic -march=native -O2


all: test-mul

test-mul: main.o mul.o
	$(CC) main.o mul.o -o test-mul $(CFLAGS)

mul.o: ../mul.c
	$(CC) -c ../mul.c $(CFLAGS)
	
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	-rm test-mul
	-rm *.o
