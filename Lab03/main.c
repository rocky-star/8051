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
    unsigned char digit_no = 0;
    lcd_module = 0;
    
    XBYTE[0xA000] = 0x00;
    
    for (;;) {
        if (button == 0) {
            delay(20);
            if (button == 0)
                if (++digit_no > 99)
                    digit_no = 0;
            while (button == 0)
                ;
        }
        
        XBYTE[0xE000] = 0xFF;
        XBYTE[0xC000] = 0x80;
        XBYTE[0xE000] = ~digits[digit_no % 10];
        delay(20);
        
        XBYTE[0xE000] = 0xFF;
        XBYTE[0xC000] = 0x40;
        XBYTE[0xE000] = ~digits[digit_no / 10];

        delay(20);
    }
}