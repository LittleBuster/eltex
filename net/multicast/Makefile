CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2


all: multicast

multicast: listener.o sender.o
	$(CC) sender.o -o sender $(CFLAGS)
	$(CC) listener.o -o listener $(CFLAGS)

listener.o: listener.c
	$(CC) -c listener.c $(CFLAGS)

sender.o: sender.c
	$(CC) -c sender.c $(CFLAGS)


clean:
	-rm sender
	-rm listener
	-rm *.o