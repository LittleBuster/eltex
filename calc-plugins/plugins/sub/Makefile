CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2


all: libsub

libsub: sub.o
	$(CC) sub.o -shared -o libsub.so $(CFLAGS)
	-cp libsub.so ../

sub.o: sub.c
	$(CC) -c -fPIC sub.c $(CFLAGS)

clean:
	-rm libsub.so
	-rm ../libsub.so
	-rm *.o