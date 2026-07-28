# board.mk
#
# Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
#
# This file is part of wolfBoot.
#
# Contact licensing@wolfssl.com with any questions or comments.
#
# https://www.wolfssl.com
#

_BOARD_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

PLATFORM = stm32wb
TESTS ?= clock gpio flash timer rng aes_ecb aes_cbc aes_ctr aes_gcm aes_gmac aes_ccm pka block uart i2c

GCC = $(GCC_PATH)arm-none-eabi-gcc
LD = $(GCC_PATH)arm-none-eabi-ld
OBJCOPY = $(GCC_PATH)arm-none-eabi-objcopy

CFLAGS += -Wall -Werror $(INCLUDE) -g3 -Os -ffunction-sections -fdata-sections \
 -ffreestanding -nostdlib -mcpu=cortex-m4 \
 -DPLATFORM_STM32WB -MMD -MP \
 $(if $(DMA),-DBOARD_DMA) \
 $(if $(filter iwdg,$(WATCHDOG)),-DBOARD_WATCHDOG_IWDG -DWHAL_CFG_STM32WB_IWDG_DIRECT_API_MAPPING) \
 $(if $(filter wwdg,$(WATCHDOG)),-DBOARD_WATCHDOG_WWDG -DWHAL_CFG_STM32WB_WWDG_DIRECT_API_MAPPING) \
 $(if $(DMA),-DWHAL_CFG_STM32WB_UART_DMA_DIRECT_API_MAPPING,-DWHAL_CFG_STM32WB_UART_DIRECT_API_MAPPING) \
 -DWHAL_CFG_STM32WB_GPIO_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_SPI_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_I2C_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_RCC_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_RNG_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_DMA_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_INIT_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_ECB_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_CBC_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_CTR_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_GCM_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_GMAC_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_AES_CCM_DIRECT_API_MAPPING \
 -DWHAL_CFG_STM32WB_PKA_DIRECT_API_MAPPING \
 -DWHAL_CFG_SYSTICK_TIMER_DIRECT_API_MAPPING \
 -DWHAL_CFG_NVIC_IRQ_DIRECT_API_MAPPING
LDFLAGS = --omagic -static --gc-sections

LINKER_SCRIPT ?= $(_BOARD_DIR)/linker.ld

INCLUDE += -I$(_BOARD_DIR) -I$(WHAL_DIR)/boards/peripheral

BOARD_SOURCE = $(_BOARD_DIR)/ivt.c
BOARD_SOURCE += $(_BOARD_DIR)/board.c
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/*.c)
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/*/flash.c)
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/*/sensor.c)
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/*/block.c)
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/irq/cortex_m4_nvic.c)
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/*/stm32wb_*.c)
BOARD_SOURCE += $(wildcard $(WHAL_DIR)/src/*/systick.c)

# Peripheral devices
include $(WHAL_DIR)/boards/peripheral/board.mk

# Flash via openocd: make flash BOARD=<board> IMAGE=<path/to/image>
OPENOCD ?= /opt/openocd/bin/openocd
OPENOCD_INTERFACE ?= interface/stlink.cfg
OPENOCD_TARGET ?= target/stm32wbx.cfg

.PHONY: flash
flash:
	@test -n "$(IMAGE)" || { echo "IMAGE=<path/to/image> required" >&2; exit 1; }
	$(OPENOCD) -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) \
	 -c "program $(IMAGE) verify reset exit"
