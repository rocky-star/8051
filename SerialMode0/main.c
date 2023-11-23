#include <reg52.h>

void delay(unsigned char time);

void main(void)
{
    unsigned char i, led;
    for (;;) {
        led = 0x7F;
        for (i = 0; i < 8; ++i) {
            SBUF = led;
            do
                ;
            while (TI == 0);
            led = (led >> 1) | 0x80;
            delay(255);
        }
    }
}