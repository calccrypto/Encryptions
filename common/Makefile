# common Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c

include objects.mk

debug: CXXFLAGS += -g
debug: all

all: $(COMMON_OBJECTS)

.PHONY: clean

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(COMMON_OBJECTS)
