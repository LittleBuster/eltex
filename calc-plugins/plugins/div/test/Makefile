CC=gcc
CFLAGS=-Wall -I. -I.. -std=gnu99 -pedantic -march=native -O2


all: test-div

test-div: main.o div.o
	$(CC) main.o div.o -o test-div $(CFLAGS)

div.o: ../div.c
	$(CC) -c ../div.c $(CFLAGS)
	
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	-rm test-div
	-rm *.o
