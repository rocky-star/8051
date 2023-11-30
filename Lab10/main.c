// MM编程方式

#include <STC15F2K60S2.h>
#include <absacc.h>
#include <limits.h>
#include "i2c.h"

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

void delay(unsigned int t)
{
    unsigned char i = 150;
    for (; t; --t)
        for (; i; --i)
            ;
}

void main(void)
{
    unsigned char input;
    
    XBYTE[0xA000] = 0;
    
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    
    // Initialize PCF8591.
    i2c_start();
    i2c_write(0x90);
    i2c_wait_for_ack();
    i2c_write(0x03);
    i2c_wait_for_ack();
    i2c_stop();
    
    for (;;) {
        // Open PCF8591 for read.
        i2c_start();
        i2c_write(0x91);
        i2c_wait_for_ack();
        // Read data.
        input = i2c_read();
        i2c_ack(1);
        i2c_stop();
        
        ssd_buffer[5] = ssd_table[input / 100 % 10];
        ssd_buffer[6] = input > 9 ? ssd_table[input / 10 % 10] : 0xFF;
        ssd_buffer[7] = input > 99 ? ssd_table[input % 10] : 0xFF;
        
        delay(UINT_MAX);
    }
}