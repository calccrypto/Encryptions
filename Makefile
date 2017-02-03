# Encryptions Library Makefile
AR=ar
TARGET=libEncryptions.a

all: $(TARGET)

.PHONY: common Encryptions clean clean-all

common:
	$(MAKE) -C common

Encryptions:
	$(MAKE) -C Encryptions

$(TARGET): common Encryptions
	$(AR) -r $(TARGET) ./common/*.o ./Encryptions/*.o

clean:
	rm -f *.a

clean-all:  clean
	$(MAKE) clean -C common
	$(MAKE) clean -C Encryptions