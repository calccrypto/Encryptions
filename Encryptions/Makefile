# Encryptions Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c

include objects.mk

debug: CXXFLAGS += -g
debug: all

all: $(ENCRYPTIONS_OBJECTS)

.PHONY: clean

%.o : %.cpp %.h ../common/cryptomath.h ../common/includes.h SymAlg.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(ENCRYPTIONS_OBJECTS)
