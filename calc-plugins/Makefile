CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2
LDFLAGS=-ldl


all: calc

calc: main.o plist.o
	$(CC) main.o plist.o -o calc $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

plist.o: plist.c
	$(CC) -c plist.c $(CFLAGS)

clean:
	-rm calc
	-rm *.o