#include <reg52.h>

const unsigned char code digits[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

sbit sw = P3^0;
unsigned char digit_no = 0;

void delay(void)
{
    unsigned char i, j;
    for (i = 20; i > 0; --i) {
        for (j = 248; j > 0; --j) {
            ;
        }
    }
}

void main(void)
{
    for (;;) {
        if (!sw) {
            delay();
            if (!sw) {
                P2 = digits[digit_no];
                if (++digit_no > 9)
                    digit_no = 0;
                while (!sw)
                    ;
            }
        }
    }
}