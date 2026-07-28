/* ivt.c
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
#include <stddef.h>

extern uint32_t _estack[];
extern uint32_t _sidata[];
extern uint32_t _sdata[];
extern uint32_t _edata[];
extern uint32_t _sbss[];
extern uint32_t _ebss[];

extern void main();

void __attribute__((naked,noreturn)) Default_Handler()
{
    while(1);
}

void Reset_Handler() __attribute__((weak));
void NMI_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HardFault_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MemManage_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void BusFault_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UsageFault_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SecureFault_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SVC_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DebugMon_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PendSV_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SysTick_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));

/* STM32N657 IRQ handlers (key positions from RM0486) */
void PVD_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DTS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RCC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LOCKUP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CACHE_ECC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TCM_ECC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void BKPSRAM_ECC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel8_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel9_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel11_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel12_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel13_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel14_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel15_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void IWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void WWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI8_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI9_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI11_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI12_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI13_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI14_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI15_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RNG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PKA_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CRYP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAES_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPUART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ETH1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FDCAN1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FPU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));

#define RESERVED Default_Handler

/*
 * Cortex-M55 vector table for STM32N657.
 * Key IRQ positions from RM0486. Gaps filled with RESERVED.
 * This is a minimal table covering the most important peripherals.
 */
void (* const interrupt_vector_table[])() __attribute__((section(".isr_vector"))) = {
    (void (*)())_estack,       /* Initial stack pointer */
    Reset_Handler,              /* Reset */
    NMI_Handler,                /* NMI */
    HardFault_Handler,          /* Hard fault */
    MemManage_Handler,          /* Memory management fault */
    BusFault_Handler,           /* Bus fault */
    UsageFault_Handler,         /* Usage fault */
    SecureFault_Handler,        /* Secure fault */
    RESERVED,                   /* Reserved */
    RESERVED,                   /* Reserved */
    RESERVED,                   /* Reserved */
    SVC_Handler,                /* SVCall */
    DebugMon_Handler,           /* Debug monitor */
    RESERVED,                   /* Reserved */
    PendSV_Handler,             /* PendSV */
    SysTick_Handler,            /* SysTick */
    /* External interrupts (position 0+) */
    PVD_IRQHandler,             /*  0: PVD */
    DTS_IRQHandler,             /*  1: DTS */
    RCC_IRQHandler,             /*  2: RCC */
    LOCKUP_IRQHandler,          /*  3: Lockup */
    CACHE_ECC_IRQHandler,       /*  4: Cache ECC */
    TCM_ECC_IRQHandler,         /*  5: TCM ECC */
    BKPSRAM_ECC_IRQHandler,     /*  6: BKPSRAM ECC */
    RESERVED,                   /*  7 */
    RESERVED,                   /*  8 */
    RESERVED,                   /*  9 */
    RESERVED,                   /* 10 */
    GPDMA1_Channel0_IRQHandler, /* 11: GPDMA1 channel 0 */
    GPDMA1_Channel1_IRQHandler, /* 12: GPDMA1 channel 1 */
    GPDMA1_Channel2_IRQHandler, /* 13: GPDMA1 channel 2 */
    GPDMA1_Channel3_IRQHandler, /* 14: GPDMA1 channel 3 */
    GPDMA1_Channel4_IRQHandler, /* 15: GPDMA1 channel 4 */
    GPDMA1_Channel5_IRQHandler, /* 16: GPDMA1 channel 5 */
    GPDMA1_Channel6_IRQHandler, /* 17: GPDMA1 channel 6 */
    GPDMA1_Channel7_IRQHandler, /* 18: GPDMA1 channel 7 */
    GPDMA1_Channel8_IRQHandler, /* 19: GPDMA1 channel 8 */
    GPDMA1_Channel9_IRQHandler, /* 20: GPDMA1 channel 9 */
    GPDMA1_Channel10_IRQHandler, /* 21: GPDMA1 channel 10 */
    GPDMA1_Channel11_IRQHandler, /* 22: GPDMA1 channel 11 */
    GPDMA1_Channel12_IRQHandler, /* 23: GPDMA1 channel 12 */
    GPDMA1_Channel13_IRQHandler, /* 24: GPDMA1 channel 13 */
    GPDMA1_Channel14_IRQHandler, /* 25: GPDMA1 channel 14 */
    GPDMA1_Channel15_IRQHandler, /* 26: GPDMA1 channel 15 */
    IWDG_IRQHandler,            /* 27: IWDG */
    WWDG_IRQHandler,            /* 28: WWDG */
    RESERVED,                   /* 29 */
    RESERVED,                   /* 30 */
    RESERVED,                   /* 31 */
    RESERVED,                   /* 32 */
    RESERVED,                   /* 33 */
    EXTI0_IRQHandler,           /* 34: EXTI line 0 */
    EXTI1_IRQHandler,           /* 35: EXTI line 1 */
    EXTI2_IRQHandler,           /* 36: EXTI line 2 */
    EXTI3_IRQHandler,           /* 37: EXTI line 3 */
    EXTI4_IRQHandler,           /* 38: EXTI line 4 */
    EXTI5_IRQHandler,           /* 39: EXTI line 5 */
    EXTI6_IRQHandler,           /* 40: EXTI line 6 */
    EXTI7_IRQHandler,           /* 41: EXTI line 7 */
    EXTI8_IRQHandler,           /* 42: EXTI line 8 */
    EXTI9_IRQHandler,           /* 43: EXTI line 9 */
    EXTI10_IRQHandler,          /* 44: EXTI line 10 */
    EXTI11_IRQHandler,          /* 45: EXTI line 11 */
    EXTI12_IRQHandler,          /* 46: EXTI line 12 */
    EXTI13_IRQHandler,          /* 47: EXTI line 13 */
    EXTI14_IRQHandler,          /* 48: EXTI line 14 */
    EXTI15_IRQHandler,          /* 49: EXTI line 15 */
    RNG_IRQHandler,             /* 50: RNG */
    PKA_IRQHandler,             /* 51: PKA */
    HASH_IRQHandler,            /* 52: HASH */
    CRYP_IRQHandler,            /* 53: CRYP */
    SAES_IRQHandler,            /* 54: SAES */
    RESERVED,                   /* 55 */
    RESERVED,                   /* 56 */
    RESERVED,                   /* 57 */
    RESERVED,                   /* 58 */
    RESERVED,                   /* 59 */
    RESERVED,                   /* 60 */
    RESERVED,                   /* 61 */
    TIM1_IRQHandler,            /* 62: TIM1 */
    RESERVED,                   /* 63 */
    RESERVED,                   /* 64 */
    RESERVED,                   /* 65 */
    TIM2_IRQHandler,            /* 66: TIM2 */
    TIM3_IRQHandler,            /* 67: TIM3 */
    TIM4_IRQHandler,            /* 68: TIM4 */
    TIM5_IRQHandler,            /* 69: TIM5 */
    TIM6_IRQHandler,            /* 70: TIM6 */
    TIM7_IRQHandler,            /* 71: TIM7 */
    RESERVED,                   /* 72 */
    RESERVED,                   /* 73 */
    RESERVED,                   /* 74 */
    RESERVED,                   /* 75 */
    I2C1_IRQHandler,            /* 76: I2C1 */
    I2C2_IRQHandler,            /* 77: I2C2 */
    I2C3_IRQHandler,            /* 78: I2C3 */
    I2C4_IRQHandler,            /* 79: I2C4 */
    RESERVED,                   /* 80 */
    RESERVED,                   /* 81 */
    SPI1_IRQHandler,            /* 82: SPI1 */
    SPI2_IRQHandler,            /* 83: SPI2 */
    SPI3_IRQHandler,            /* 84: SPI3 */
    SPI4_IRQHandler,            /* 85: SPI4 */
    SPI5_IRQHandler,            /* 86: SPI5 */
    SPI6_IRQHandler,            /* 87: SPI6 */
    USART1_IRQHandler,          /* 88: USART1 */
    USART2_IRQHandler,          /* 89: USART2 */
    USART3_IRQHandler,          /* 90: USART3 */
    RESERVED,                   /* 91 */
    RESERVED,                   /* 92 */
    RESERVED,                   /* 93 */
    RESERVED,                   /* 94 */
    RESERVED,                   /* 95 */
    RESERVED,                   /* 96 */
    RESERVED,                   /* 97 */
    LPUART1_IRQHandler,         /* 98: LPUART1 */
    RESERVED,                   /* 99 */
    RESERVED,                   /* 100 */
    RESERVED,                   /* 101 */
    RESERVED,                   /* 102 */
    RESERVED,                   /* 103 */
    RESERVED,                   /* 104 */
    RESERVED,                   /* 105 */
    RESERVED,                   /* 106 */
    RESERVED,                   /* 107 */
    RESERVED,                   /* 108 */
    RESERVED,                   /* 109 */
    RESERVED,                   /* 110 */
    RESERVED,                   /* 111 */
    RESERVED,                   /* 112 */
    RESERVED,                   /* 113 */
    RESERVED,                   /* 114 */
    RESERVED,                   /* 115 */
    RESERVED,                   /* 116 */
    RESERVED,                   /* 117 */
    RESERVED,                   /* 118 */
    RESERVED,                   /* 119 */
    RESERVED,                   /* 120 */
    RESERVED,                   /* 121 */
    RESERVED,                   /* 122 */
    RESERVED,                   /* 123 */
    RESERVED,                   /* 124 */
    RESERVED,                   /* 125 */
    RESERVED,                   /* 126 */
    RESERVED,                   /* 127 */
    RESERVED,                   /* 128 */
    RESERVED,                   /* 129 */
    ETH1_IRQHandler,            /* 130: ETH1 */
    RESERVED,                   /* 131 */
    FDCAN1_IRQHandler,          /* 132: FDCAN1 */
    RESERVED,                   /* 133 */
    RESERVED,                   /* 134 */
    RESERVED,                   /* 135 */
    RESERVED,                   /* 136 */
    RESERVED,                   /* 137 */
    RESERVED,                   /* 138 */
    RESERVED,                   /* 139 */
    FPU_IRQHandler,             /* 140: FPU */
};

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];

    return dest;
}

void *memset(void *s, int c, size_t n)
{
    unsigned char *p = s;
    unsigned char v = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
        p[i] = v;

    return s;
}

void __attribute__((naked)) Reset_Handler()
{
    /* Copy data section from load address to RAM */
    uint32_t data_section_size = _edata - _sdata;
    memcpy(_sdata, _sidata, data_section_size*4);

    /* Zero out bss */
    uint32_t bss_section_size = _ebss - _sbss;
    memset(_sbss, 0, bss_section_size*4);

    /* Set Interrupt Vector Table Offset */
    uint32_t *vtor = (uint32_t *)0xE000ED08;
    *vtor = (uint32_t)interrupt_vector_table;

    main();
}
