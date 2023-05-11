#include <iostm8l051f3.h>
#include "display.h"

int display_char[11] = {0xD7, 0x14, 0xCD, 0x5D, 0x1E, 0x5B, 0xDB, 0x15, 0xDF, 0x5F, 0x0F};

/* Output information on display using multiplexed display */
void display_output(int *p_display_buffer, struct display_interface *p_display)
{
    static int display_current_state = 0;
    int display_digit[4];
    int display_segments_buffer = 0;
    
    /* Splite the buffer into numbers */
    display_digit[0] = *p_display_buffer / 1000;
    display_digit[1] = (*p_display_buffer / 100) % 10;
    display_digit[2] = (*p_display_buffer / 10) % 10;
    display_digit[3] = *p_display_buffer  % 10;
    
    /* Replace the digit with a Celsius sign for the temperature display mode */
    if((p_display->mode) == 1) {
        display_digit[3] = 10;
    }
    
    /* Enable the division point in the temperature display mode.
       And the display of the point in the time mode for the indication of seconds */
    if((display_current_state == 1) && ((p_display->mode == 1) || (p_display->update_dot == 1))) {
        display_segments_buffer = display_char[display_digit[display_current_state]] | MASK_PB_ODR_ODR5;
    } else {
        display_segments_buffer = display_char[display_digit[display_current_state]];
    }
        
    /* Clean the display / turn off of digits */
    PA_ODR = 0;
    PC_ODR_bit.ODR4 = 0;
    
    /* Light up segments */
    PB_ODR = display_segments_buffer;
    
    /* Cyclic switch of indicators (turn on digits) */
    if((display_current_state == 0) && (p_display->enable_dig1 == 1)) {
        PA_ODR_bit.ODR3 = 1;
    } else if ((display_current_state == 1) && (p_display->enable_dig2 == 1)) {
        PA_ODR_bit.ODR2 = 1;
    } else if ((display_current_state == 2) && (p_display->enable_dig3 == 1)) {
        PA_ODR_bit.ODR1 = 1;
    } else if ((display_current_state == 3) && (p_display->enable_dig4 == 1)){
        PC_ODR_bit.ODR4 = 1;
    }
    
    /* Update state of display */
    if(display_current_state == 3) {
        display_current_state = 0;
    } else {
        display_current_state++;
    }
}