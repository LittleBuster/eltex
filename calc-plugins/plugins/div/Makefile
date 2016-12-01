CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2


all: libdiv

libdiv: div.o
	$(CC) div.o -shared -o libdiv.so $(CFLAGS)
	-cp libdiv.so ../

div.o: div.c
	$(CC) -c -fPIC div.c $(CFLAGS)

clean:
	-rm libdiv.so
	-rm ../libdiv.so
	-rm *.o