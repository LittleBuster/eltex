CC=gcc
CFLAGS=-Wall -I. -I.. -std=gnu99 -pedantic -march=native -O2


all: test-add

test-add: main.o add.o
	$(CC) main.o add.o -o test-add $(CFLAGS)

add.o: ../add.c
	$(CC) -c ../add.c $(CFLAGS)
	
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

clean:
	-rm test-add
	-rm *.o
