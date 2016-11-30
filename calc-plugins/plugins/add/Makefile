CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2


all: libadd

libadd: add.o
	$(CC) add.o -shared -o libadd.so $(CFLAGS)
	-cp libadd.so ../

add.o: add.c
	$(CC) -c -fPIC add.c $(CFLAGS)

clean:
	-rm libadd.so
	-rm ../libadd.so
	-rm *.o