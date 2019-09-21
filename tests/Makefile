# Encryptions Library Test Makefile
CXX?=g++
CXXFLAGS=-std=c++11 -Wall -g -D_POSIX_C_SOURCE=200809L -I../../googletest/googletest/include -I..
LDFLAGS=-lEncryptions -L.. -L../../googletest/build/lib -lgtest -lgtest_main -lpthread
TARGET=tests

include objects.mk

debug: CXXFLAGS += -g
debug: all

.PHONY: clean clean-all

all: $(TARGET)

../libEncryptions.a:
	$(MAKE) -C ..

$(ENCRYPTIONS_TESTCASES_OBJECTS): %.o : %.cpp testvectors/plainkeycipher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): ../libEncryptions.a $(ENCRYPTIONS_TESTCASES_OBJECTS)
	$(CXX) $(CXXFLAGS) $(ENCRYPTIONS_TESTCASES_OBJECTS) $(LDFLAGS) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(ENCRYPTIONS_TESTCASES_OBJECTS) $(TARGET)

clean-all:  clean
	$(MAKE) clean-all -C ..
