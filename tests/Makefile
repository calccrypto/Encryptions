# Encryptions Library Test Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall
LDFLAGS=-lEncryptions -L..
TARGET=tests

debug: CXXFLAGS += -g
debug: all

all: $(TARGET)

.PHONY: lib clean clean-all

lib:
	$(MAKE) -C ..

$(TARGET): tests.cpp lib
	$(CXX) $(CXXFLAGS) tests.cpp $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

clean-all:  clean
	$(MAKE) clean-all -C ..