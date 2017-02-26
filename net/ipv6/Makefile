CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2


all: ipvsix

ipvsix: client.o server.o
	$(CC) server.o -o server $(CFLAGS)
	$(CC) client.o -o client $(CFLAGS)

client.o: client.c
	$(CC) -c client.c $(CFLAGS)

server.o: server.c
	$(CC) -c server.c $(CFLAGS)


clean:
	-rm server
	-rm client
	-rm *.o