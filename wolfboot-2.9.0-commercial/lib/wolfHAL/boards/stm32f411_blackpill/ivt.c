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
void SVC_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DebugMon_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PendSV_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SysTick_Handler() __attribute__((weak, noreturn, alias("Default_Handler")));

/* STM32F411 peripheral interrupts */
void WWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PVD_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_WKUP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FLASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RCC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI9_5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_CC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI15_10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_Alarm_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SDIO_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void OTG_FS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FPU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));

#define RESERVED Default_Handler

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

void (* const interrupt_vector_table[])() __attribute__((section(".isr_vector"))) = {
    (void (*)())_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    RESERVED,                          /* Reserved */
    RESERVED,                          /* Reserved */
    RESERVED,                          /* Reserved */
    RESERVED,                          /* Reserved */
    SVC_Handler,
    DebugMon_Handler,
    RESERVED,                          /* Reserved */
    PendSV_Handler,
    SysTick_Handler,
    /* STM32F411 peripheral interrupts */
    WWDG_IRQHandler,                   /* 0 */
    PVD_IRQHandler,                    /* 1 */
    TAMP_STAMP_IRQHandler,             /* 2 */
    RTC_WKUP_IRQHandler,               /* 3 */
    FLASH_IRQHandler,                  /* 4 */
    RCC_IRQHandler,                    /* 5 */
    EXTI0_IRQHandler,                  /* 6 */
    EXTI1_IRQHandler,                  /* 7 */
    EXTI2_IRQHandler,                  /* 8 */
    EXTI3_IRQHandler,                  /* 9 */
    EXTI4_IRQHandler,                  /* 10 */
    DMA1_Stream0_IRQHandler,           /* 11 */
    DMA1_Stream1_IRQHandler,           /* 12 */
    DMA1_Stream2_IRQHandler,           /* 13 */
    DMA1_Stream3_IRQHandler,           /* 14 */
    DMA1_Stream4_IRQHandler,           /* 15 */
    DMA1_Stream5_IRQHandler,           /* 16 */
    DMA1_Stream6_IRQHandler,           /* 17 */
    ADC_IRQHandler,                    /* 18 */
    RESERVED,                          /* 19 */
    RESERVED,                          /* 20 */
    RESERVED,                          /* 21 */
    RESERVED,                          /* 22 */
    EXTI9_5_IRQHandler,                /* 23 */
    TIM1_BRK_TIM9_IRQHandler,         /* 24 */
    TIM1_UP_TIM10_IRQHandler,          /* 25 */
    TIM1_TRG_COM_TIM11_IRQHandler,     /* 26 */
    TIM1_CC_IRQHandler,                /* 27 */
    TIM2_IRQHandler,                   /* 28 */
    TIM3_IRQHandler,                   /* 29 */
    TIM4_IRQHandler,                   /* 30 */
    I2C1_EV_IRQHandler,                /* 31 */
    I2C1_ER_IRQHandler,                /* 32 */
    I2C2_EV_IRQHandler,                /* 33 */
    I2C2_ER_IRQHandler,                /* 34 */
    SPI1_IRQHandler,                   /* 35 */
    SPI2_IRQHandler,                   /* 36 */
    USART1_IRQHandler,                 /* 37 */
    USART2_IRQHandler,                 /* 38 */
    RESERVED,                          /* 39 */
    EXTI15_10_IRQHandler,              /* 40 */
    RTC_Alarm_IRQHandler,              /* 41 */
    OTG_FS_WKUP_IRQHandler,            /* 42 */
    RESERVED,                          /* 43 */
    RESERVED,                          /* 44 */
    RESERVED,                          /* 45 */
    RESERVED,                          /* 46 */
    DMA1_Stream7_IRQHandler,           /* 47 */
    RESERVED,                          /* 48 */
    SDIO_IRQHandler,                   /* 49 */
    TIM5_IRQHandler,                   /* 50 */
    SPI3_IRQHandler,                   /* 51 */
    RESERVED,                          /* 52 */
    RESERVED,                          /* 53 */
    RESERVED,                          /* 54 */
    RESERVED,                          /* 55 */
    DMA2_Stream0_IRQHandler,           /* 56 */
    DMA2_Stream1_IRQHandler,           /* 57 */
    DMA2_Stream2_IRQHandler,           /* 58 */
    DMA2_Stream3_IRQHandler,           /* 59 */
    DMA2_Stream4_IRQHandler,           /* 60 */
    RESERVED,                          /* 61 */
    RESERVED,                          /* 62 */
    RESERVED,                          /* 63 */
    RESERVED,                          /* 64 */
    RESERVED,                          /* 65 */
    RESERVED,                          /* 66 */
    OTG_FS_IRQHandler,                 /* 67 */
    DMA2_Stream5_IRQHandler,           /* 68 */
    DMA2_Stream6_IRQHandler,           /* 69 */
    DMA2_Stream7_IRQHandler,           /* 70 */
    USART6_IRQHandler,                 /* 71 */
    I2C3_EV_IRQHandler,                /* 72 */
    I2C3_ER_IRQHandler,                /* 73 */
    RESERVED,                          /* 74 */
    RESERVED,                          /* 75 */
    RESERVED,                          /* 76 */
    RESERVED,                          /* 77 */
    RESERVED,                          /* 78 */
    RESERVED,                          /* 79 */
    RESERVED,                          /* 80 */
    FPU_IRQHandler,                    /* 81 */
    RESERVED,                          /* 82 */
    RESERVED,                          /* 83 */
    SPI4_IRQHandler,                   /* 84 */
    SPI5_IRQHandler,                   /* 85 */
};

void __attribute__((naked)) Reset_Handler()
{
    __asm__("ldr r0, =_estack\n\t"
            "mov sp, r0");

    /* Copy data section from flash to RAM */
    uint32_t data_section_size = _edata - _sdata;
    memcpy(_sdata, _sidata, data_section_size * 4);

    /* Zero out bss */
    uint32_t bss_section_size = _ebss - _sbss;
    memset(_sbss, 0, bss_section_size * 4);

    /* Set Interrupt Vector Table Offset */
    uint32_t *vtor = (uint32_t *)0xE000ED08;
    *vtor = (uint32_t)interrupt_vector_table;

    main();
}
