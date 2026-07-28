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

/* STM32WBA55 IRQ handlers (positions 0-71 from RM0493 Table 135) */
void WWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PVD_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TAMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RAMCFG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FLASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FLASH_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GTZC_TZIC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RCC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RCC_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
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
void IWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAES_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_BRK_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_UP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_CC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPUART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM16_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM17_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void COMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TSC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void AES_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RNG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FPU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PKA_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ICACHE_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADC4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RADIO_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void WKUP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HSEM_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HSEM_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void WKUP_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RCC_AUDIO_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));

#define RESERVED Default_Handler

/*
 * Cortex-M33 vector table for STM32WBA55.
 * Positions from RM0493 Table 135 (pages 591-594).
 */
void (* const interrupt_vector_table[])() __attribute__((section(".isr_vector"))) = {
    (void (*)())_estack,      /* Initial stack pointer */
    Reset_Handler,             /* Reset */
    NMI_Handler,               /* NMI */
    HardFault_Handler,         /* Hard fault */
    MemManage_Handler,         /* Memory management fault */
    BusFault_Handler,          /* Bus fault */
    UsageFault_Handler,        /* Usage fault */
    SecureFault_Handler,       /* Secure fault (Cortex-M33) */
    RESERVED,                  /* Reserved */
    RESERVED,                  /* Reserved */
    RESERVED,                  /* Reserved */
    SVC_Handler,               /* SVCall */
    DebugMon_Handler,          /* Debug monitor */
    RESERVED,                  /* Reserved */
    PendSV_Handler,            /* PendSV */
    SysTick_Handler,           /* SysTick */
    /* External interrupts (position 0-71) */
    WWDG_IRQHandler,           /*  0: Window watchdog */
    PVD_IRQHandler,            /*  1: PVD */
    RTC_IRQHandler,            /*  2: RTC non-secure */
    RTC_S_IRQHandler,          /*  3: RTC secure */
    TAMP_IRQHandler,           /*  4: Tamper */
    RAMCFG_IRQHandler,         /*  5: RAMCFG */
    FLASH_IRQHandler,          /*  6: Flash non-secure */
    FLASH_S_IRQHandler,        /*  7: Flash secure */
    GTZC_TZIC_IRQHandler,      /*  8: GTZC TZIC */
    RCC_IRQHandler,            /*  9: RCC non-secure */
    RCC_S_IRQHandler,          /* 10: RCC secure */
    EXTI0_IRQHandler,          /* 11: EXTI line 0 */
    EXTI1_IRQHandler,          /* 12: EXTI line 1 */
    EXTI2_IRQHandler,          /* 13: EXTI line 2 */
    EXTI3_IRQHandler,          /* 14: EXTI line 3 */
    EXTI4_IRQHandler,          /* 15: EXTI line 4 */
    EXTI5_IRQHandler,          /* 16: EXTI line 5 */
    EXTI6_IRQHandler,          /* 17: EXTI line 6 */
    EXTI7_IRQHandler,          /* 18: EXTI line 7 */
    EXTI8_IRQHandler,          /* 19: EXTI line 8 */
    EXTI9_IRQHandler,          /* 20: EXTI line 9 */
    EXTI10_IRQHandler,         /* 21: EXTI line 10 */
    EXTI11_IRQHandler,         /* 22: EXTI line 11 */
    EXTI12_IRQHandler,         /* 23: EXTI line 12 */
    EXTI13_IRQHandler,         /* 24: EXTI line 13 */
    EXTI14_IRQHandler,         /* 25: EXTI line 14 */
    EXTI15_IRQHandler,         /* 26: EXTI line 15 */
    IWDG_IRQHandler,           /* 27: IWDG */
    SAES_IRQHandler,           /* 28: Secure AES */
    GPDMA1_Channel0_IRQHandler, /* 29: GPDMA1 channel 0 */
    GPDMA1_Channel1_IRQHandler, /* 30: GPDMA1 channel 1 */
    GPDMA1_Channel2_IRQHandler, /* 31: GPDMA1 channel 2 */
    GPDMA1_Channel3_IRQHandler, /* 32: GPDMA1 channel 3 */
    GPDMA1_Channel4_IRQHandler, /* 33: GPDMA1 channel 4 */
    GPDMA1_Channel5_IRQHandler, /* 34: GPDMA1 channel 5 */
    GPDMA1_Channel6_IRQHandler, /* 35: GPDMA1 channel 6 */
    GPDMA1_Channel7_IRQHandler, /* 36: GPDMA1 channel 7 */
    TIM1_BRK_IRQHandler,       /* 37: TIM1 break */
    TIM1_UP_IRQHandler,        /* 38: TIM1 update */
    TIM1_TRG_COM_IRQHandler,   /* 39: TIM1 trigger/commutation */
    TIM1_CC_IRQHandler,        /* 40: TIM1 capture compare */
    TIM2_IRQHandler,           /* 41: TIM2 */
    TIM3_IRQHandler,           /* 42: TIM3 */
    I2C1_EV_IRQHandler,        /* 43: I2C1 event */
    I2C1_ER_IRQHandler,        /* 44: I2C1 error */
    SPI1_IRQHandler,           /* 45: SPI1 */
    USART1_IRQHandler,         /* 46: USART1 */
    USART2_IRQHandler,         /* 47: USART2 */
    LPUART1_IRQHandler,        /* 48: LPUART1 */
    LPTIM1_IRQHandler,         /* 49: LPTIM1 */
    LPTIM2_IRQHandler,         /* 50: LPTIM2 */
    TIM16_IRQHandler,          /* 51: TIM16 */
    TIM17_IRQHandler,          /* 52: TIM17 */
    COMP_IRQHandler,           /* 53: COMP */
    I2C3_EV_IRQHandler,        /* 54: I2C3 event */
    I2C3_ER_IRQHandler,        /* 55: I2C3 error */
    SAI1_IRQHandler,           /* 56: SAI1 */
    TSC_IRQHandler,            /* 57: TSC */
    AES_IRQHandler,            /* 58: AES */
    RNG_IRQHandler,            /* 59: RNG */
    FPU_IRQHandler,            /* 60: FPU */
    HASH_IRQHandler,           /* 61: HASH */
    PKA_IRQHandler,            /* 62: PKA */
    SPI3_IRQHandler,           /* 63: SPI3 */
    ICACHE_IRQHandler,         /* 64: ICACHE */
    ADC4_IRQHandler,           /* 65: ADC4 */
    RADIO_IRQHandler,          /* 66: 2.4 GHz RADIO */
    WKUP_IRQHandler,           /* 67: WKUP */
    HSEM_IRQHandler,           /* 68: HSEM non-secure */
    HSEM_S_IRQHandler,         /* 69: HSEM secure */
    WKUP_S_IRQHandler,         /* 70: WKUP secure */
    RCC_AUDIO_IRQHandler,      /* 71: RCC audio sync */
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
    __asm__("ldr r0, =_estack\n\t"
            "mov sp, r0");

    /* Copy data section from flash to RAM */
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
