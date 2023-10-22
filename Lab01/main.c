#include <reg52.h>

sbit SW1 = P1^0;
sbit SW2 = P1^1;
sbit SW3 = P1^2;
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;

void main(void)
{
    for (;;) {
        LED1 = SW1;
        LED2 = SW2;
        LED3 = SW3;
    }
}