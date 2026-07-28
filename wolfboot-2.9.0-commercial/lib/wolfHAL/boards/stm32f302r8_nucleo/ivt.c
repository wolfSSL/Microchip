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

/* STM32F302x6/x8 peripheral interrupts (RM0365 Table 41) */
void WWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PVD_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TAMPER_STAMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_WKUP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FLASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RCC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI2_TS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADC1_2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CAN_TX_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CAN_RX0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CAN_RX1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CAN_SCE_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI9_5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_CC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void EXTI15_10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_Alarm_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USBWakeUp_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM6_DAC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void COMP2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void COMP4_6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USB_HP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USB_LP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USBWakeUp_RMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FPU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));

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
    /* STM32F302x6/x8 peripheral interrupts (position 0-81) */
    WWDG_IRQHandler,                   /* 0 */
    PVD_IRQHandler,                    /* 1 */
    TAMPER_STAMP_IRQHandler,           /* 2 */
    RTC_WKUP_IRQHandler,               /* 3 */
    FLASH_IRQHandler,                  /* 4 */
    RCC_IRQHandler,                    /* 5 */
    EXTI0_IRQHandler,                  /* 6 */
    EXTI1_IRQHandler,                  /* 7 */
    EXTI2_TS_IRQHandler,               /* 8 */
    EXTI3_IRQHandler,                  /* 9 */
    EXTI4_IRQHandler,                  /* 10 */
    DMA1_Channel1_IRQHandler,          /* 11 */
    DMA1_Channel2_IRQHandler,          /* 12 */
    DMA1_Channel3_IRQHandler,          /* 13 */
    DMA1_Channel4_IRQHandler,          /* 14 */
    DMA1_Channel5_IRQHandler,          /* 15 */
    DMA1_Channel6_IRQHandler,          /* 16 */
    DMA1_Channel7_IRQHandler,          /* 17 */
    ADC1_2_IRQHandler,                 /* 18 */
    CAN_TX_IRQHandler,                 /* 19 */
    CAN_RX0_IRQHandler,                /* 20 */
    CAN_RX1_IRQHandler,                /* 21 */
    CAN_SCE_IRQHandler,                /* 22 */
    EXTI9_5_IRQHandler,                /* 23 */
    TIM1_BRK_TIM15_IRQHandler,        /* 24 */
    TIM1_UP_TIM16_IRQHandler,          /* 25 */
    TIM1_TRG_COM_TIM17_IRQHandler,     /* 26 */
    TIM1_CC_IRQHandler,                /* 27 */
    TIM2_IRQHandler,                   /* 28 */
    RESERVED,                          /* 29 */
    RESERVED,                          /* 30 */
    I2C1_EV_IRQHandler,                /* 31 */
    I2C1_ER_IRQHandler,                /* 32 */
    I2C2_EV_IRQHandler,                /* 33 */
    I2C2_ER_IRQHandler,                /* 34 */
    RESERVED,                          /* 35 */
    SPI2_IRQHandler,                   /* 36 */
    USART1_IRQHandler,                 /* 37 */
    USART2_IRQHandler,                 /* 38 */
    USART3_IRQHandler,                 /* 39 */
    EXTI15_10_IRQHandler,              /* 40 */
    RTC_Alarm_IRQHandler,              /* 41 */
    USBWakeUp_IRQHandler,              /* 42 */
    RESERVED,                          /* 43 */
    RESERVED,                          /* 44 */
    RESERVED,                          /* 45 */
    RESERVED,                          /* 46 */
    RESERVED,                          /* 47 */
    RESERVED,                          /* 48 */
    RESERVED,                          /* 49 */
    RESERVED,                          /* 50 */
    SPI3_IRQHandler,                   /* 51 */
    RESERVED,                          /* 52 */
    RESERVED,                          /* 53 */
    TIM6_DAC_IRQHandler,               /* 54 */
    RESERVED,                          /* 55 */
    RESERVED,                          /* 56 */
    RESERVED,                          /* 57 */
    RESERVED,                          /* 58 */
    RESERVED,                          /* 59 */
    RESERVED,                          /* 60 */
    RESERVED,                          /* 61 */
    RESERVED,                          /* 62 */
    RESERVED,                          /* 63 */
    COMP2_IRQHandler,                  /* 64 */
    COMP4_6_IRQHandler,                /* 65 */
    RESERVED,                          /* 66 */
    RESERVED,                          /* 67 */
    RESERVED,                          /* 68 */
    RESERVED,                          /* 69 */
    RESERVED,                          /* 70 */
    RESERVED,                          /* 71 */
    I2C3_EV_IRQHandler,                /* 72 */
    I2C3_ER_IRQHandler,                /* 73 */
    USB_HP_IRQHandler,                 /* 74 */
    USB_LP_IRQHandler,                 /* 75 */
    USBWakeUp_RMP_IRQHandler,          /* 76 */
    RESERVED,                          /* 77 */
    RESERVED,                          /* 78 */
    RESERVED,                          /* 79 */
    RESERVED,                          /* 80 */
    FPU_IRQHandler,                    /* 81 */
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
