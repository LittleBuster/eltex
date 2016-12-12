CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -O2 -march=native


all: interpret

interpret: main.o
	$(CC) main.o -o interpret $(CFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	-rm interpret
	-rm *.o
