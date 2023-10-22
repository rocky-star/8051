#include <reg52.h>

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
    for (;;) {
        while (P0 == 0xFF)
            ;
        delay(20);
        if (P0 != 0xFF) {
            /*
            switch (~P0) {
                case 0x01: P1 = 0xFE; break;
                case 0x02: P1 = 0xFD; break;
                case 0x04: P1 = 0xFB; break;
                case 0x08: P1 = 0xF7; break;
                case 0x10: P1 = 0xEF; break;
                case 0x20: P1 = 0xDF; break;
                case 0x40: P1 = 0xBF; break;
                case 0x80: P1 = 0x7F; break;
            }
            */
            P1 = P0;
        }
    }
}