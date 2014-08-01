# common files Makefile
CXX?=g++
LFLAGS=
CFLAGS=-std=c++11 -Wall -c

all: includes.o integer.o

includes.o: includes.cpp includes.h
	$(CXX) $(CFLAGS) includes.cpp

integer.o: integer.cpp integer.h
	$(CXX) $(CFLAGS) integer.cpp

clean:
	rm -f *.o
