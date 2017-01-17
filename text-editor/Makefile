CC=gcc
CFLAGS=-pedantic -Wall -std=gnu99 -march=native
LDFLAGS=-lncurses


all: editor

editor: main.o cui.o fileio.o
	$(CC) main.o cui.o fileio.o -o editor $(CFLAGS) $(LDFLAGS)

main.o:
	$(CC) main.c -c $(CFLAGS)

cui.o:
	$(CC) cui.c -c $(CFLAGS)

fileio.o:
	$(CC) fileio.c -c $(CFLAGS)


clean:
	-rm *.o
	-rm editor