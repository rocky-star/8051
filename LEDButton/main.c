#include <reg52.h>

sbit LED = P1^0;
sbit SW = P3^0;

void main(void)
{
    while (1) {
        if (SW)
            LED = 1;
        else
            LED = 0;
    }
}