CC=gcc
CFLAGS=-Wall

all: main

main: main.o pgcd.o
	$(CC) $(CFLAGS) -o main main.o pgcd.o

main.o: main.c pgcd.h
	$(CC) $(CFLAGS) -c main.c

pgcd.o: pgcd.c pgcd.h
	$(CC) $(CFLAGS) -c pgcd.c

clean:
	rm -f *.o main

test: main
	./main
