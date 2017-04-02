# Encryptions Library Test Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -g -I../../googletest/googletest/include -I..
LDFLAGS=-lEncryptions -L.. -L../../googletest/googlemock/gtest -lgtest -lpthread
TARGET=tests

include testcases/objects.mk

debug: CXXFLAGS += -g
debug: all

.PHONY: lib testcases clean clean-all

all: $(TARGET)

lib:
	$(MAKE) -C ..

testcases:
	$(MAKE) -C testcases

$(TARGET): tests.cpp lib testcases
	$(CXX) $(CXXFLAGS) tests.cpp $(addprefix testcases/, $(ENCRYPTIONS_TESTCASES_OBJECTS)) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

clean-all:  clean
	$(MAKE) clean -C testcases
	$(MAKE) clean-all -C ..