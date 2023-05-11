#include <iostm8l051f3.h>

void GPIO_init(void)
{
    /* Configured RESET pin as a GPIO pin (disable external RESET) */
    RST_CR = 0xD0;
    
    /* DIG1(PA3), DIG2(PA2), DIG3(PA1) - Output, Push-Pull, Slow mode */
    PA_DDR = MASK_PA_DDR_DDR3 | MASK_PA_DDR_DDR2 | MASK_PA_DDR_DDR1;
    PA_CR1 = MASK_PA_CR1_C13 | MASK_PA_CR1_C12 | MASK_PA_CR1_C11;
    
    /* SEG_A(PB0), SEG_B(PB2), SEG_C(PB4), SEG_D(PB6), 
       SEG_E(PB7), SEG_F(PB1), SEG_G(PB3), SEG_DP(PB5) - 
       Output, Push-Pull, Slow mode */
    PB_DDR = MASK_PB_DDR_DDR7 | MASK_PB_DDR_DDR6 | MASK_PB_DDR_DDR5 | MASK_PB_DDR_DDR4 | 
             MASK_PB_DDR_DDR3 | MASK_PB_DDR_DDR2 | MASK_PB_DDR_DDR1 | MASK_PB_DDR_DDR0;
    PB_CR1 = MASK_PB_CR1_C17 | MASK_PB_CR1_C16 | MASK_PB_CR1_C15 | MASK_PB_CR1_C14 | 
             MASK_PB_CR1_C13 | MASK_PB_CR1_C12 | MASK_PB_CR1_C11 | MASK_PB_CR1_C10;
    
    /* DIG_4(PC4) - Output, Push-Pull, Slow mode,
       BTN_SET(PC1), BTN_UP(PC0) - Input, Pull-Up, Without interrupt */
    PC_DDR = MASK_PC_DDR_DDR4;
    PC_CR1 = MASK_PC_CR1_C14 | MASK_PC_CR1_C11 | MASK_PC_CR1_C10;
}

void CLK_init(void)
{
    /* HSI devided by 1 (16 MHz) */
    CLK_CKDIVR_bit.CKM = 0;
    
    /* LSE enable */
    CLK_ECKR_bit.LSEON = 1;
    /* Wait LSE stabilization */
    while(CLK_ECKR_bit.LSERDY != 1);
    
    /* Clock enable: TIM2 */
    CLK_PCKENR1_bit.PCKEN10 = 1;
    /* Clock enable: ADC1, RTC */
    CLK_PCKENR2 = MASK_CLK_PCKENR2_PCKEN20 | MASK_CLK_PCKENR2_PCKEN22;
    
    /* LSE clock used as RTC clock source */
    CLK_CRTCR_bit.RTCSEL3 = 1;
    /* Wait RTC clock change procedure is complete */
    while(CLK_CRTCR_bit.RTCSWBSY == 1);
}

/* Input clock no devided (16MHz), up-counter, interrupt occurs every 100kHZ */
void TIM2_init(void)
{
    /* Set the Autoreload value (CPU_CLK 16MHZ -> TIM2_CLK 100kHz) */
    TIM2_ARRH = 0x00;
    TIM2_ARRL = 0xA0;   // 16MHz divided by 160 (0xA0)
    
    /* Re-initializes the counter and generates an update of the registers */
    TIM2_EGR_bit.UG = 1;
    
    /* Enable update interrupt */
    TIM2_IER_bit.UIE = 1;
    
    /* Enable the TIM2 counter */
    TIM2_CR1_bit.CEN = 1;
}

void RTC_init(void)
{
    
}

void ADC_init(void)
{
    /* ADC enable */
    //ADC1_CR1_bit.ADON = 1;
    
    /* DMA disable */
    //ADC1_SQR1_bit.DMAOFF = 1;
    
    /* Channel 22 (PD0) connect to ADC */
    //ADC1_SQR2_bit.CHSEL_S22 = 1;
}