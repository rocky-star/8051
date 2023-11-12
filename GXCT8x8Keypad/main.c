#include <reg52.h>
#include <absacc.h>

const unsigned char data column_codes[] = { 0xEF, 0xDF, 0xBF, 0x7F };
const unsigned char data key_codes[] = {
    0xE7, 0xEB, 0xDB, 0xBB, 0xED,
    0xDF, 0xBF, 0xEE, 0xDE, 0xBE,
    0x7E, 0x7D, 0x7B, 0x77, 0xD7, 0xE7
};
const unsigned char data display_codes[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90,
    0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
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
    unsigned char i, j;
    XBYTE[0xA000] = 0x00;
    for (;;) {
        for (i = 0; i < 4; ++i) {
            P3 = column_codes[i];
            if ((P3 & 0x0F) != 0x0F) {
                for (j = 0; j < 16; ++j) {
                    if (key_codes[j] == P3) {
                        XBYTE[0xE000] = 0xFF;
                        XBYTE[0xC000] = 0xFF;
                        XBYTE[0xE000] = display_codes[j];
                        break;
                    }
                }
            }
        }
    }
}