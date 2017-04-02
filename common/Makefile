# common Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c

include objects.mk

debug: CXXFLAGS += -g
debug: all

.PHONY: clean

all: $(COMMON_OBJECTS)

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(COMMON_OBJECTS)
