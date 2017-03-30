# Encryptions testcases Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c -I../../../googletest/googletest/include -I../..

include objects.mk

debug: CXXFLAGS += -g
debug: all

all: $(ENCRYPTIONS_TESTCASES_OBJECTS)

%.o : %.cpp testvectors/plainkeycipher.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(ENCRYPTIONS_TESTCASES_OBJECTS)
