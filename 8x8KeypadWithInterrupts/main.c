#include <reg52.h>

#define DISPLAY P0
#define KEYPAD P2

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

unsigned char digit = 0xFF;

void delay(unsigned char time)
{
    unsigned char i;
    for (; time > 0; --time) {
        for (i = 125; i > 0; --i) {
            ;
        }
    }
}

void inthandler(void) interrupt 0
{
    unsigned char i, j;
    DISPLAY = 0xFF;
        for (i = 0; i < 4; ++i) {
            KEYPAD = column_codes[i];
            if ((KEYPAD & 0x0F) != 0x0F) {
                for (j = 0; j < 16; ++j) {
                    if (key_codes[j] == KEYPAD) {
                        digit = display_codes[j];
                        break;
                    }
                }
            }
        }
        KEYPAD = 0x0F;
}

void main(void)
{
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    KEYPAD = 0x0F;
    for (;;)
        DISPLAY = digit;
}