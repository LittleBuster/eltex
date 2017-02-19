CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2
LDFLAGS=-lpcap


all: app

app: main.o
	$(CC) main.o -o app $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)


clean:
	-rm app
	-rm *.o