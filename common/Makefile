# common Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -c

include sources.make
OBJECTS=$(COMMON_SOURCES:.cpp=.o)

debug: CXXFLAGS += -g
debug: all

all: $(OBJECTS)

.PHONY: clean

%.o : %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
