#include <reg52.h>

sbit button0 = P0^0;
sbit button1 = P0^1;
sbit button2 = P0^2;
sbit button3 = P0^3;

sbit led0 = P2^0;
sbit led1 = P2^1;
sbit led2 = P2^2;
sbit led3 = P2^3;

void inthandler(void) interrupt 0
{
    /*
    if (button0 == 0)
        led0 = !led0;
    if (button1 == 0)
        led1 = !led1;
    if (button2 == 0)
        led2 = !led2;
    if (button3 == 0)
        led3 = !led3;
    */
    unsigned char button = ~(P0 & 0x0F);
    if (button) {
        P2 ^= button;
    }
}

void main(void)
{
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    for (;;)
        ;
}