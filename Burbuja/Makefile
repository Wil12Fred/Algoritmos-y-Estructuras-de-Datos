CC = g++
CFLAGS= -std=c++11 -Wall -pedantic -O2

.SUFFIXES: .cc .o

.cc.o:
	$(CC) -c $(CFLAGS) $<

all: main

main: main.o
	$(CC) -o main $(CFLAGS) main.o

burbuja.o: main.cc

clean:
	rm -f *.o
	rm -f *.s
	rm -f main
