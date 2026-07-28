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

/* STM32U5A5 IRQ handlers (positions 0-124 per RM0456 NVIC mapping) */
void WWDG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PVD_PVM_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
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
void TIM8_BRK_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_UP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM8_CC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C1_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C2_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void USART3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UART5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPUART1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM15_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM16_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TIM17_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void COMP_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void OTG_FS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CRS_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FMC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void OCTOSPI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PWR_S3WU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SDMMC1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SDMMC2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel8_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel9_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel10_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel11_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel12_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel13_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel14_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void GPDMA1_Channel15_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C3_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAI1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SAI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void TSC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void RNG_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FPU_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void HASH_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void PKA_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void SPI3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C4_ER_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void I2C4_EV_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MDF1_FLT0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MDF1_FLT1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MDF1_FLT2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MDF1_FLT3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void UCPD1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ICACHE_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPTIM4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DCACHE1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADF1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void ADC4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPDMA1_Channel0_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPDMA1_Channel1_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPDMA1_Channel2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void LPDMA1_Channel3_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DMA2D_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void DCMI_PSSI_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void OCTOSPI2_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MDF1_FLT4_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void MDF1_FLT5_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void CORDIC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));
void FMAC_IRQHandler() __attribute__((weak, noreturn, alias("Default_Handler")));

#define RESERVED Default_Handler

/*
 * Cortex-M33 vector table for STM32U5A5xx.
 * Positions per RM0456 NVIC interrupt mapping (124 external interrupts).
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
    /* External interrupts (position 0+) */
    WWDG_IRQHandler,           /*  0: Window watchdog */
    PVD_PVM_IRQHandler,        /*  1: PVD/PVM */
    RTC_IRQHandler,            /*  2: RTC non-secure */
    RTC_S_IRQHandler,          /*  3: RTC secure */
    TAMP_IRQHandler,           /*  4: Tamper non-secure */
    RAMCFG_IRQHandler,         /*  5: RAMCFG */
    FLASH_IRQHandler,          /*  6: Flash non-secure */
    FLASH_S_IRQHandler,        /*  7: Flash secure */
    GTZC_IRQHandler,           /*  8: GTZC TZIC */
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
    ADC1_IRQHandler,           /* 37: ADC1 */
    DAC1_IRQHandler,           /* 38: DAC1 */
    FDCAN1_IT0_IRQHandler,     /* 39: FDCAN1 IT0 */
    FDCAN1_IT1_IRQHandler,     /* 40: FDCAN1 IT1 */
    TIM1_BRK_IRQHandler,       /* 41: TIM1 break */
    TIM1_UP_IRQHandler,        /* 42: TIM1 update */
    TIM1_TRG_COM_IRQHandler,   /* 43: TIM1 trigger/commutation */
    TIM1_CC_IRQHandler,        /* 44: TIM1 capture compare */
    TIM2_IRQHandler,           /* 45: TIM2 */
    TIM3_IRQHandler,           /* 46: TIM3 */
    TIM4_IRQHandler,           /* 47: TIM4 */
    TIM5_IRQHandler,           /* 48: TIM5 */
    TIM6_IRQHandler,           /* 49: TIM6 */
    TIM7_IRQHandler,           /* 50: TIM7 */
    TIM8_BRK_IRQHandler,       /* 51: TIM8 break */
    TIM8_UP_IRQHandler,        /* 52: TIM8 update */
    TIM8_TRG_COM_IRQHandler,   /* 53: TIM8 trigger/commutation */
    TIM8_CC_IRQHandler,        /* 54: TIM8 capture compare */
    I2C1_EV_IRQHandler,        /* 55: I2C1 event */
    I2C1_ER_IRQHandler,        /* 56: I2C1 error */
    I2C2_EV_IRQHandler,        /* 57: I2C2 event */
    I2C2_ER_IRQHandler,        /* 58: I2C2 error */
    SPI1_IRQHandler,           /* 59: SPI1 */
    SPI2_IRQHandler,           /* 60: SPI2 */
    USART1_IRQHandler,         /* 61: USART1 */
    USART2_IRQHandler,         /* 62: USART2 */
    USART3_IRQHandler,         /* 63: USART3 */
    UART4_IRQHandler,          /* 64: UART4 */
    UART5_IRQHandler,          /* 65: UART5 */
    LPUART1_IRQHandler,        /* 66: LPUART1 */
    LPTIM1_IRQHandler,         /* 67: LPTIM1 */
    LPTIM2_IRQHandler,         /* 68: LPTIM2 */
    TIM15_IRQHandler,          /* 69: TIM15 */
    TIM16_IRQHandler,          /* 70: TIM16 */
    TIM17_IRQHandler,          /* 71: TIM17 */
    COMP_IRQHandler,           /* 72: COMP */
    OTG_FS_IRQHandler,         /* 73: OTG_FS */
    CRS_IRQHandler,            /* 74: CRS */
    FMC_IRQHandler,            /* 75: FMC */
    OCTOSPI1_IRQHandler,       /* 76: OCTOSPI1 */
    PWR_S3WU_IRQHandler,       /* 77: PWR S3WU */
    SDMMC1_IRQHandler,         /* 78: SDMMC1 */
    SDMMC2_IRQHandler,         /* 79: SDMMC2 */
    GPDMA1_Channel8_IRQHandler, /* 80: GPDMA1 channel 8 */
    GPDMA1_Channel9_IRQHandler, /* 81: GPDMA1 channel 9 */
    GPDMA1_Channel10_IRQHandler, /* 82: GPDMA1 channel 10 */
    GPDMA1_Channel11_IRQHandler, /* 83: GPDMA1 channel 11 */
    GPDMA1_Channel12_IRQHandler, /* 84: GPDMA1 channel 12 */
    GPDMA1_Channel13_IRQHandler, /* 85: GPDMA1 channel 13 */
    GPDMA1_Channel14_IRQHandler, /* 86: GPDMA1 channel 14 */
    GPDMA1_Channel15_IRQHandler, /* 87: GPDMA1 channel 15 */
    I2C3_EV_IRQHandler,        /* 88: I2C3 event */
    I2C3_ER_IRQHandler,        /* 89: I2C3 error */
    SAI1_IRQHandler,           /* 90: SAI1 */
    SAI2_IRQHandler,           /* 91: SAI2 */
    TSC_IRQHandler,            /* 92: TSC */
    RESERVED,                  /* 93: reserved (AES not present on nonsecure side) */
    RNG_IRQHandler,            /* 94: RNG */
    FPU_IRQHandler,            /* 95: FPU */
    HASH_IRQHandler,           /* 96: HASH */
    PKA_IRQHandler,            /* 97: PKA */
    LPTIM3_IRQHandler,         /* 98: LPTIM3 */
    SPI3_IRQHandler,           /* 99: SPI3 */
    I2C4_ER_IRQHandler,        /* 100: I2C4 error */
    I2C4_EV_IRQHandler,        /* 101: I2C4 event */
    MDF1_FLT0_IRQHandler,      /* 102: MDF1 filter 0 */
    MDF1_FLT1_IRQHandler,      /* 103: MDF1 filter 1 */
    MDF1_FLT2_IRQHandler,      /* 104: MDF1 filter 2 */
    MDF1_FLT3_IRQHandler,      /* 105: MDF1 filter 3 */
    UCPD1_IRQHandler,          /* 106: UCPD1 */
    ICACHE_IRQHandler,         /* 107: ICACHE */
    LPTIM4_IRQHandler,         /* 108: LPTIM4 */
    DCACHE1_IRQHandler,        /* 109: DCACHE1 */
    ADF1_IRQHandler,           /* 110: ADF1 */
    ADC4_IRQHandler,           /* 111: ADC4 */
    LPDMA1_Channel0_IRQHandler, /* 112: LPDMA1 channel 0 */
    LPDMA1_Channel1_IRQHandler, /* 113: LPDMA1 channel 1 */
    LPDMA1_Channel2_IRQHandler, /* 114: LPDMA1 channel 2 */
    LPDMA1_Channel3_IRQHandler, /* 115: LPDMA1 channel 3 */
    DMA2D_IRQHandler,          /* 116: DMA2D */
    DCMI_PSSI_IRQHandler,      /* 117: DCMI/PSSI */
    OCTOSPI2_IRQHandler,       /* 118: OCTOSPI2 */
    MDF1_FLT4_IRQHandler,      /* 119: MDF1 filter 4 */
    MDF1_FLT5_IRQHandler,      /* 120: MDF1 filter 5 */
    CORDIC_IRQHandler,         /* 121: CORDIC */
    FMAC_IRQHandler,           /* 122: FMAC */
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
