# common Makefile
CXX?=g++
LFLAGS=
CFLAGS=-std=c++11 -Wall -c

debug: CFLAGS += -g
debug: all

all: includes.o integer.o

includes.o: includes.h includes.cpp
	$(CXX) $(CFLAGS) includes.cpp

integer.o: integer.h integer.cpp
	$(CXX) $(CFLAGS) integer.cpp

clean:
	rm -f *.o
