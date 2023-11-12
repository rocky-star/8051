#include <reg52.h>
#include <absacc.h>

const unsigned char data digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
sbit button = P3^3;
sbit lcd_module = P1^7;

void delay(unsigned char time)
{
    unsigned char i;
    for (; time > 0; --time)
        for (i = 125; i > 0; --i)
            ;
}

void main(void)
{
    unsigned char position;
    
    lcd_module = 0;
    
    XBYTE[0xA000] = 0x00;
    
    for (position = 0; ; position = (position + 1) % 8) {
        XBYTE[0xE000] = 0xFF;
        XBYTE[0xC000] = 1 << position;
        XBYTE[0xE000] = ~digits[8 - position];
        delay(20);
    }
}