CC=gcc
CFLAGS=-Wall -I. -I.. -std=gnu99 -pedantic -march=native -O2


all: test-sub

test-sub: main.o sub.o
	$(CC) main.o sub.o -o test-sub $(CFLAGS)

sub.o: ../sub.c
	$(CC) -c ../sub.c $(CFLAGS)
	
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	-rm test-sub
	-rm *.o
