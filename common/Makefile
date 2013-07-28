# common files Makefile

CC=g++
LFLAGS=
CFLAGS=-std=c++11 -Wall -c

all: includes.o integer.o

includes.o: includes.cpp includes.h
	$(CC) $(CFLAGS) includes.cpp

integer.o: integer.cpp integer.h
	$(CC) $(CFLAGS) integer.cpp

clean:
	rm -f *.o
