#ifdef AT89C52
#include <reg52.h>
#else
#include <STC15F2K60S2.H>
#endif
#include <absacc.h>

sbit S7 = P3^0;
sbit S6 = P3^1;

unsigned char xdata *ssd_digit = 0xE000;
unsigned char xdata *ssd_com = 0xC000;
const char code ssd_table[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90
};

unsigned char ssd_buffer[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char ssd_digit_no = 0;

void handle_t0(void) interrupt 1
{
    *ssd_digit = 0xFF;
    *ssd_com = 1 << ssd_digit_no;
    *ssd_digit = ssd_buffer[ssd_digit_no];
    if (++ssd_digit_no == 8)
        ssd_digit_no = 0;
    
    TH0 = 0xFC;
    TL0 = 0x18;
}

unsigned char counter = 0;

//void handle_interrupt_1(void) interrupt 1
//{
//    if (!S7)
//        if (++counter >= 100)
//            counter = 99;
//    if (!S6)
//        if (counter > 0)
//            --counter;
//    TH0 = 0xFC;
//    TL0 = 0x18;
//}

void handle_t1(void) interrupt 3
{
    if (S7)
        if (++counter == 100)
            counter = 0;
    if (S6)
        if (counter)
            --counter;
}

void main(void)
{
    TMOD = 0x11;
    TH0 = 0xFC;
    TL0 = 0x18;
    TH1 = 0xFC;
    TL1 = 0x18;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    ET1 = 1;
    TR1 = 1;
    
    XBYTE[0xA000] = 0;
    
    for (;;) {
        ssd_buffer[7] = ssd_table[counter % 10];
        ssd_buffer[6] = counter > 9 ? ssd_table[counter / 10] : 0xFF;
    }
}