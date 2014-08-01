# Encryptions Library Makefile
AR=ar
TARGET=libEncryptions.a

all: $(TARGET)

.PHONY: common Encryptions

common:
	$(MAKE) -C common

Encryptions:
	$(MAKE) -C Encryptions

$(TARGET): common Encryptions
	$(AR) -r $(TARGET) ./common/*.o ./Encryptions/*.o

clean:
	rm -f *.a
	$(MAKE) -C common clean
	$(MAKE) -C Encryptions clean