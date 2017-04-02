# Modes of Operation Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c

include objects.mk

debug: CXXFLAGS += -g
debug: all

.PHONY: clean

all: $(MODES_OBJECTS)

%.o : %.cpp %.h ../common/cryptomath.h ../common/includes.h SymAlg.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(MODES_OBJECTS)
