#include <reg52.h>

const unsigned char code digits[] = { 0x66, 0x5B };

sbit seg_a_sel = P3^0;
sbit seg_b_sel = P3^1;

void delay(unsigned char time)
{
    unsigned char j;
    for (; time > 0; --time) {
        for (j = 125; j > 0; --j) {
            ;
        }
    }
}

void main(void)
{
    char point = 0;
    for (;;) {
        P3 = 2 - point;
        P2 = digits[point];
        point = 1 - point;
        delay(30);
    }
}