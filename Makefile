# Encryptions Library Makefile
AR=ar
TARGET=libEncryptions.a

include common/objects.mk
include Encryptions/objects.mk
include modes/objects.mk

.PHONY: common Encryptions modes clean clean-all

all: $(TARGET)

common:
	$(MAKE) -C common

Encryptions:
	$(MAKE) -C Encryptions

modes:
	$(MAKE) -C modes

$(TARGET): common Encryptions modes
	$(AR) -r $(TARGET) $(addprefix common/, $(COMMON_OBJECTS)) $(addprefix Encryptions/, $(ENCRYPTIONS_OBJECTS)) $(addprefix modes/, $(MODES_OBJECTS))

clean:
	rm -f $(TARGET)

clean-all:  clean
	$(MAKE) clean -C common
	$(MAKE) clean -C Encryptions
	$(MAKE) clean -C modes