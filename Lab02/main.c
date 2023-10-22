#include <reg52.h>

const unsigned char led_states[8] = {
    0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F
};

void delay(unsigned char time)
{
    unsigned char i;
    for (; time > 0; --time) {
        for (i = 125; i > 0; --i) {
            ;
        }
    }
}

void main(void)
{
    unsigned char i;
    for (;;) {
        for (i = 0; i < 8; ++i) {
            P0 = led_states[i];
            delay(200);
        }
        for (i = 8; i > 0; --i) {
            P0 = led_states[i - 1];
            delay(200);
        }
    }
}