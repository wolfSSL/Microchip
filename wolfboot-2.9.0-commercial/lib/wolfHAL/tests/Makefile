# Makefile
#
# Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#

WHAL_DIR = $(CURDIR)/..

.DEFAULT_GOAL := all

BOARD ?= stm32wb55xx_nucleo
BOARD_DIR = $(WHAL_DIR)/boards/$(BOARD)
BUILD_DIR = build/$(BOARD)
PERIPHERAL_DIR = $(WHAL_DIR)/boards/peripheral
INCLUDE = -I$(WHAL_DIR) -I. -I$(PERIPHERAL_DIR)

include $(BOARD_DIR)/board.mk

uc = $(shell echo $(1) | tr a-z A-Z)
CFLAGS += $(foreach t,$(TESTS),-DWHAL_TEST_ENABLE_$(call uc,$(t)))
CFLAGS += $(foreach t,$(TESTS),$(if $(shell find . -name 'test_$(PLATFORM)_$(t).c'),-DWHAL_TEST_ENABLE_$(call uc,$(t))_PLATFORM))

SOURCE = main.c
SOURCE += $(BOARD_SOURCE)
SOURCE += $(foreach t,$(TESTS),$(shell find . -name 'test_$(t).c'))
SOURCE += $(foreach t,$(TESTS),$(shell find . -name 'test_$(PLATFORM)_$(t).c'))

OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE))
DEPENDS = $(OBJECTS:.o=.d)

all: $(BUILD_DIR)/test_hw.bin

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(dir $@)
	$(GCC) $(CFLAGS) -c -o $@ $<

.SECONDARY:
$(BUILD_DIR)/%.elf: $(OBJECTS) $(LINKER_SCRIPT)
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -T $(LINKER_SCRIPT) -o $@ $(OBJECTS)

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) $^ -O binary $@

.PHONY: clean
clean:
	rm -rf build

-include $(DEPENDS)
