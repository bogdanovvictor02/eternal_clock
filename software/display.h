#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

struct display_interface {
    unsigned char mode: 1;
    unsigned char update_dot: 1;
    unsigned char enable_dig1: 1;
    unsigned char enable_dig2: 1;
    unsigned char enable_dig3: 1;
    unsigned char enable_dig4: 1;
};

void display_output(int *p_display_buffer, struct display_interface *p_display);

#endif