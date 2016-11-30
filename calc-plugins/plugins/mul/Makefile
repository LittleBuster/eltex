CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2


all: libmul

libmul: mul.o
	$(CC) mul.o -shared -o libmul.so $(CFLAGS)
	-cp libmul.so ../

mul.o: mul.c
	$(CC) -c -fPIC mul.c $(CFLAGS)

clean:
	-rm libmul.so
	-rm ../libmul.so
	-rm *.o