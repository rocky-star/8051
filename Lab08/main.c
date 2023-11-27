#ifdef AT89C52
#include <reg52.h>
#else
#include <STC15F2K60S2.H>
#endif

sbit S7 = P3^0;
sbit S6 = P3^1;

unsigned char xdata *ssd_data = 0xE000;
unsigned char xdata *ssd_com  = 0xC000;

const unsigned char code ssd_digits[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90
};

unsigned char counter = 0;

void handle_interrupt_1(void) interrupt 1
{
    if (!S7)
        if (++counter >= 100)
            counter = 99;
    if (!S6)
        if (counter > 0)
            --counter;
    TH0 = 0xFC;
    TL0 = 0x18;
}

void main(void)
{
    unsigned char i;
    
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    EA = 1;
    ET0 = 1;
    TR0 = 0;
    
    for (;;) {
        for (i = 0; i < 6; ++i) {
            *ssd_data = 0xFF;
            *ssd_com = 1 << i;
            *ssd_data = 0xFF;
        }
        
        *ssd_data = 0xFF;
        *ssd_com = 1 << 6;
        *ssd_data = ssd_digits[counter / 10];
        
        *ssd_data = 0xFF;
        *ssd_com = 1 << 7;
        *ssd_data = ssd_digits[counter % 10];
    }
}