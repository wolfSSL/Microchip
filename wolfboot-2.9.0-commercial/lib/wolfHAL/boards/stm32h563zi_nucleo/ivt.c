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

/* STM32H563 peripheral interrupts */
void WWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PVD_AVD_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RTC_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TAMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RAMCFG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FLASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FLASH_S_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GTZC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
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
void GPDMA1_Channel0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void IWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADC1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DAC1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FDCAN1_IT0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FDCAN1_IT1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_BRK_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_UP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM1_CC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPUART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_BRK_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_UP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_CC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADC2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM15_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM16_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM17_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USB_DRD_FS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CRS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UCPD1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FMC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void OCTOSPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SDMMC1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART11_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA2_Channel7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART7_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART8_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART9_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART12_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FDCAN2_IT0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FDCAN2_IT1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DTS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ETH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ETH_WKUP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RNG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FPU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ICACHE_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DCACHE1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C4_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C4_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM6_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));

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
    SecureFault_Handler,
    RESERVED,
    RESERVED,
    RESERVED,
    SVC_Handler,
    DebugMon_Handler,
    RESERVED,
    PendSV_Handler,
    SysTick_Handler,
    /* STM32H563 peripheral interrupts */
    WWDG_IRQHandler,            /* 0 */
    PVD_AVD_IRQHandler,         /* 1 */
    RTC_IRQHandler,             /* 2 */
    RTC_S_IRQHandler,           /* 3 */
    TAMP_IRQHandler,            /* 4 */
    RAMCFG_IRQHandler,          /* 5 */
    FLASH_IRQHandler,           /* 6 */
    FLASH_S_IRQHandler,         /* 7 */
    GTZC_IRQHandler,            /* 8 */
    RCC_IRQHandler,             /* 9 */
    RCC_S_IRQHandler,           /* 10 */
    EXTI0_IRQHandler,           /* 11 */
    EXTI1_IRQHandler,           /* 12 */
    EXTI2_IRQHandler,           /* 13 */
    EXTI3_IRQHandler,           /* 14 */
    EXTI4_IRQHandler,           /* 15 */
    EXTI5_IRQHandler,           /* 16 */
    EXTI6_IRQHandler,           /* 17 */
    EXTI7_IRQHandler,           /* 18 */
    EXTI8_IRQHandler,           /* 19 */
    EXTI9_IRQHandler,           /* 20 */
    EXTI10_IRQHandler,          /* 21 */
    EXTI11_IRQHandler,          /* 22 */
    EXTI12_IRQHandler,          /* 23 */
    EXTI13_IRQHandler,          /* 24 */
    EXTI14_IRQHandler,          /* 25 */
    EXTI15_IRQHandler,          /* 26 */
    GPDMA1_Channel0_IRQHandler, /* 27 */
    GPDMA1_Channel1_IRQHandler, /* 28 */
    GPDMA1_Channel2_IRQHandler, /* 29 */
    GPDMA1_Channel3_IRQHandler, /* 30 */
    GPDMA1_Channel4_IRQHandler, /* 31 */
    GPDMA1_Channel5_IRQHandler, /* 32 */
    GPDMA1_Channel6_IRQHandler, /* 33 */
    GPDMA1_Channel7_IRQHandler, /* 34 */
    IWDG_IRQHandler,            /* 35 */
    RESERVED,                   /* 36 */
    ADC1_IRQHandler,            /* 37 */
    DAC1_IRQHandler,            /* 38 */
    FDCAN1_IT0_IRQHandler,      /* 39 */
    FDCAN1_IT1_IRQHandler,      /* 40 */
    TIM1_BRK_IRQHandler,        /* 41 */
    TIM1_UP_IRQHandler,         /* 42 */
    TIM1_TRG_COM_IRQHandler,    /* 43 */
    TIM1_CC_IRQHandler,         /* 44 */
    TIM2_IRQHandler,            /* 45 */
    TIM3_IRQHandler,            /* 46 */
    TIM4_IRQHandler,            /* 47 */
    TIM5_IRQHandler,            /* 48 */
    TIM6_IRQHandler,            /* 49 */
    TIM7_IRQHandler,            /* 50 */
    I2C1_EV_IRQHandler,         /* 51 */
    I2C1_ER_IRQHandler,         /* 52 */
    I2C2_EV_IRQHandler,         /* 53 */
    I2C2_ER_IRQHandler,         /* 54 */
    SPI1_IRQHandler,            /* 55 */
    SPI2_IRQHandler,            /* 56 */
    SPI3_IRQHandler,            /* 57 */
    USART1_IRQHandler,          /* 58 */
    USART2_IRQHandler,          /* 59 */
    USART3_IRQHandler,          /* 60 */
    UART4_IRQHandler,           /* 61 */
    UART5_IRQHandler,           /* 62 */
    LPUART1_IRQHandler,         /* 63 */
    LPTIM1_IRQHandler,          /* 64 */
    TIM8_BRK_IRQHandler,        /* 65 */
    TIM8_UP_IRQHandler,         /* 66 */
    TIM8_TRG_COM_IRQHandler,    /* 67 */
    TIM8_CC_IRQHandler,         /* 68 */
    ADC2_IRQHandler,            /* 69 */
    LPTIM2_IRQHandler,          /* 70 */
    TIM15_IRQHandler,           /* 71 */
    TIM16_IRQHandler,           /* 72 */
    TIM17_IRQHandler,           /* 73 */
    USB_DRD_FS_IRQHandler,      /* 74 */
    CRS_IRQHandler,             /* 75 */
    UCPD1_IRQHandler,           /* 76 */
    FMC_IRQHandler,             /* 77 */
    OCTOSPI1_IRQHandler,        /* 78 */
    SDMMC1_IRQHandler,          /* 79 */
    I2C3_EV_IRQHandler,         /* 80 */
    I2C3_ER_IRQHandler,         /* 81 */
    SPI4_IRQHandler,            /* 82 */
    SPI5_IRQHandler,            /* 83 */
    SPI6_IRQHandler,            /* 84 */
    USART6_IRQHandler,          /* 85 */
    USART10_IRQHandler,         /* 86 */
    USART11_IRQHandler,         /* 87 */
    SAI1_IRQHandler,            /* 88 */
    SAI2_IRQHandler,            /* 89 */
    GPDMA2_Channel0_IRQHandler, /* 90 */
    GPDMA2_Channel1_IRQHandler, /* 91 */
    GPDMA2_Channel2_IRQHandler, /* 92 */
    GPDMA2_Channel3_IRQHandler, /* 93 */
    GPDMA2_Channel4_IRQHandler, /* 94 */
    GPDMA2_Channel5_IRQHandler, /* 95 */
    GPDMA2_Channel6_IRQHandler, /* 96 */
    GPDMA2_Channel7_IRQHandler, /* 97 */
    UART7_IRQHandler,           /* 98 */
    UART8_IRQHandler,           /* 99 */
    UART9_IRQHandler,           /* 100 */
    UART12_IRQHandler,          /* 101 */
    RESERVED,                   /* 102 */
    FDCAN2_IT0_IRQHandler,      /* 103 */
    FDCAN2_IT1_IRQHandler,      /* 104 */
    RESERVED,                   /* 105 */
    RESERVED,                   /* 106 */
    DTS_IRQHandler,             /* 107 */
    RESERVED,                   /* 108 */
    RESERVED,                   /* 109 */
    RESERVED,                   /* 110 */
    ETH_IRQHandler,             /* 111 */
    ETH_WKUP_IRQHandler,        /* 112 */
    RESERVED,                   /* 113 */
    RESERVED,                   /* 114 */
    RNG_IRQHandler,             /* 115 */
    HASH_IRQHandler,            /* 116 */
    RESERVED,                   /* 117 */
    FPU_IRQHandler,             /* 118 */
    ICACHE_IRQHandler,          /* 119 */
    DCACHE1_IRQHandler,         /* 120 */
    RESERVED,                   /* 121 */
    RESERVED,                   /* 122 */
    I2C4_EV_IRQHandler,         /* 123 */
    I2C4_ER_IRQHandler,         /* 124 */
    LPTIM3_IRQHandler,          /* 125 */
    LPTIM4_IRQHandler,          /* 126 */
    LPTIM5_IRQHandler,          /* 127 */
    LPTIM6_IRQHandler,          /* 128 */
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
