/* startup_riscv.c
 *
 * Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfBoot.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

#include <stdint.h>
#include "hal/riscv.h"

extern void trap_entry(void);
extern void trap_exit(void);

extern uint32_t  _start_vector;
extern uint32_t  _stored_data;
extern uint32_t  _start_data;
extern uint32_t  _end_data;
extern uint32_t  _start_bss;
extern uint32_t  _end_bss;
extern uint32_t  _end_stack;
extern uint32_t  _start_heap;
extern uint32_t  _global_pointer;
extern void (* const IV[])(void);

extern void main(void);
void __attribute__((naked,section(".init"))) _reset(void) {
    register uint32_t *src, *dst;
    asm volatile("la gp, _global_pointer");
    asm volatile("la sp, _end_stack");

    /* Set up vectored interrupt table. The +1 sets MODE=1 (vectored). */
#ifdef WOLFBOOT_RISCV_MMODE
    asm volatile("csrw mtvec, %0":: "r"((uint8_t *)(&_start_vector) + 1));
#else
    asm volatile("csrw stvec, %0":: "r"((uint8_t *)(&_start_vector) + 1));
#endif

    src = (uint32_t *) &_stored_data;
    dst = (uint32_t *) &_start_data;
    /* Copy the .data section from flash to RAM. */
    while (dst < (uint32_t *)&_end_data) {
        *dst = *src;
        dst++;
        src++;
    }

    /* Initialize the BSS section to 0 */
    dst = &_start_bss;
    while (dst < (uint32_t *)&_end_bss) {
        *dst = 0U;
        dst++;
    }

    /* Run wolfboot */
    main();
    while(1)
        ;
}

void do_boot(const uint32_t *app_offset)
{

}

static uint32_t synctrap_cause = 0;
void __attribute__((naked)) isr_synctrap(void)
{
#ifdef WOLFBOOT_RISCV_MMODE
    asm volatile("csrr %0, mcause" : "=r"(synctrap_cause));
    asm volatile("mret");
#else
    asm volatile("csrr %0, scause" : "=r"(synctrap_cause));
    asm volatile("sret");
#endif
}

void isr_empty(void)
{

}
