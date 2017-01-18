CC=gcc
CFLAGS=-pedantic -Wall -std=gnu99 -march=native
LDFLAGS=-lncurses


all: fmanager

fmanager: main.o filelist.o files.o
	$(CC) main.o filelist.o files.o -o fmanager $(CFLAGS) $(LDFLAGS)

main.o:
	$(CC) main.c -c $(CFLAGS)

filelist.o:
	$(CC) filelist.c -c $(CFLAGS)

files.o:
	$(CC) files.c -c $(CFLAGS)


clean:
	-rm *.o
	-rm fmanager
