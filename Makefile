# Encryptions Library Makefile

all: common Encryptions

.PHONY: common Encryptions

common:
	$(MAKE) -C common

Encryptions:
	$(MAKE) -C Encryptions

clean:
	$(MAKE) -C common clean
	$(MAKE) -C Encryptions clean