#include <reg51.h>
#include <absacc.h>

const unsigned char led_states[8] = {
    0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F
};

sbit LED_M = P1^7;

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
    
    LED_M = 0;
    for (;;) {
        for (i = 0; i < 8; ++i) {
            XBYTE[0x8000] = led_states[i];
            delay(200);
        }
        for (i = 8; i > 0; --i) {
            XBYTE[0x8000] = led_states[i - 1];
            delay(200);
        }
    }
}