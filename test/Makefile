# Encryptions Library Test Makefile
CXX?=g++
LFLAGS=-lEncryptions -L..
CFLAGS=-std=c++11 -Wall
TARGET=test

debug: CFLAGS += -g
debug: all

all: $(TARGET)

.PHONY: lib

lib:
	$(MAKE) -C ..

$(TARGET): test.cpp lib
	$(CXX) $(CFLAGS) test.cpp $(LFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	$(MAKE) -C .. clean