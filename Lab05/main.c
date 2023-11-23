// MM

#include <reg52.h>

const unsigned char led_states[8] = {
    0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F
};

extern void delay(unsigned char);

void main(void)
{
    unsigned char i;
    unsigned char xdata *led = 0x8000;
    for (;;) {
        for (i = 0; i < 8; ++i) {
            *led = led_states[i];
            delay(200);
        }
        for (i = 8; i > 0; --i) {
            *led = led_states[i - 1];
            delay(200);
        }
    }
}