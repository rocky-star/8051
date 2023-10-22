#include <reg52.h>

sbit led = P1^0;

void delay(void)
{
    unsigned char i, j;
    for (i = 0; i < 100; ++i)
        for (j = 0; j < 100; ++j)
            ;
}

void main(void)
{
    for (;;) {
        led = 0;
        delay();
        led = 1;
        delay();
    }
}