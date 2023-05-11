#include <iostm8l051f3.h>
#include "init.h"
#include "display.h"

int display_output_buffer = 0;

volatile int display_update_counter = 0;
volatile int display_flag_update = 0;

int main(void)
{
    /* Startup initialization */
    GPIO_init();
    CLK_init();
    TIM2_init();
    RTC_init();
    //ADC_init();
    
    /* Enable intterupt */
    asm("rim");
    
    /* Startup initialization */
    struct display_interface display = {0, 0, 1, 1, 1, 1};
    
    while(1) {
        /* Display output */
        if(display_flag_update == 1) {
            display_flag_update = 0;
            
            display_output(&display_output_buffer, &display);
        }
    }
}

/* Interrupt occurs every 0.01ms */
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_OVR_UIF_handler(void)
{
    /* Reset interrupt flag */
    TIM2_SR1_bit.UIF = 0;
    
    /* Update display (500Hz)*/
    if(display_update_counter == 200) {
        display_update_counter = 0;
        display_flag_update = 1;
    } else {
        display_update_counter++;
    }
}