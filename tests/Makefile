# Encryptions Library Test Makefile
CXX?=g++
LFLAGS=-lEncryptions -L..
CFLAGS=-std=c++11 -Wall
TARGET=tests

debug: CFLAGS += -g
debug: all

all: $(TARGET)

.PHONY: lib

lib:
	$(MAKE) -C ..

$(TARGET): tests.cpp lib
	$(CXX) $(CFLAGS) tests.cpp $(LFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	$(MAKE) -C .. clean