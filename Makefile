# Encryptions Library Makefile
AR=ar
TARGET=libEncryptions.a

include common/sources.make
COMMON_OBJECTS=$(addprefix common/, $(COMMON_SOURCES:.cpp=.o))

include Encryptions/sources.make
ENCRYPTIONS_OBJECTS=$(addprefix Encryptions/, $(ENCRYPTIONS_SOURCES:.cpp=.o))

include modes/sources.make
MODES_OBJECTS=$(addprefix modes/, $(MODES_SOURCES:.cpp=.o))

all: $(TARGET)

.PHONY: common Encryptions modes clean clean-all

common:
	$(MAKE) -C common

Encryptions:
	$(MAKE) -C Encryptions

modes:
	$(MAKE) -C modes

$(TARGET): common Encryptions modes
	$(AR) -r $(TARGET) $(COMMON_OBJECTS) $(ENCRYPTIONS_OBJECTS) $(MODES_OBJECTS)

clean:
	rm -f $(TARGET)

clean-all:  clean
	$(MAKE) clean -C common
	$(MAKE) clean -C Encryptions
	$(MAKE) clean -C modes