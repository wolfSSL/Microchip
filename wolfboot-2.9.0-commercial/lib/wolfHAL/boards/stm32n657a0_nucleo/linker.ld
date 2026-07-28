/* linker.ld
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*
 * Linker script for STM32N657A0 (NUCLEO-N657X0-Q)
 *
 * The STM32N6 has no internal flash. Code runs from SRAM after boot ROM
 * loads it. For development, the firmware is loaded into AXISRAM via
 * debugger or boot ROM.
 *
 * ITCM:       64 KB at 0x00000000 (instruction TCM)
 * DTCM:       128 KB at 0x20000000 (data TCM)
 * FLEXRAM:    up to 400 KB at 0x34000000 — CPU-only in default boot
 *             config (allocated as M55 TCM unless RAMCFG repartitions).
 *             IVT lives here because the ROM jumps to 0x34000000.
 * AXISRAM1:   448 KB at 0x34064000 (non-cached alias, AXI-master visible).
 *             ETH DMA / other AXI masters can only reach memory from
 *             AXISRAM1 onward.
 * AXISRAM2:   1024 KB at 0x34100000
 *
 * Code/data live in RAM (FLEXRAM). Anything a peripheral DMA touches
 * (eth descriptor rings, eth frame buffers) goes in .axisram1 so it
 * lands in AXISRAM1 where the AXI master can reach it.
 */

ENTRY(Reset_Handler)


MEMORY
{
  RAM       (rwx) : ORIGIN = 0x34000000, LENGTH = 400K
  AXISRAM1  (rwx) : ORIGIN = 0x34064000, LENGTH = 448K
  AXISRAM2  (rwx) : ORIGIN = 0x34100000, LENGTH = 128K
}

_estack = ORIGIN(RAM) + LENGTH(RAM);
_Min_Stack_Size = 0x500;

SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >RAM

  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;
  } >RAM

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } >RAM

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >RAM
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >RAM

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >RAM
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >RAM
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >RAM

  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)

    . = ALIGN(4);
    _edata = .;
  } >RAM

  . = ALIGN(4);
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* AXI-master-visible RAM. Place anything a peripheral DMA reads or
   * writes (ETH descriptor rings, frame buffers, etc.) in this section
   * via __attribute__((section(".axisram1"))). */
  .axisram1 (NOLOAD) :
  {
    . = ALIGN(16);
    *(.axisram1)
    *(.axisram1*)
    . = ALIGN(16);
  } >AXISRAM1
}
