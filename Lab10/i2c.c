#include <STC15F2K60S2.h>

sbit SCL = P2^0;
sbit SDA = P2^1;

static void delay(void)
{
    unsigned char t = 20;
    while (--t)
        ;
}

void i2c_start(void)
{
    SCL = 1; delay();
    SDA = 1; delay();
    SDA = 0; delay();
    SCL = 0; delay();
}

void i2c_stop(void)
{
    unsigned char t = 20;
    
    SDA = 0; delay();
    SCL = 1; delay();
    SDA = 1; delay();
    
    while (--t)
        ;
}

void i2c_write(unsigned char ch)
{
    unsigned char i;
    for (i = 0; i < 8; ++i) {
        SDA = (bit) (ch & 0x80); delay();
        SCL = 1; delay();
        SCL = 0; delay();
        ch <<= 1;
    }
}

unsigned char i2c_read(void)
{
    unsigned char i, ch = 0;
    
    delay(); delay();
    SDA = 1; delay();
    for (i = 0; i < 8; ++i) {
        SCL = 0; delay();
        SCL = 1; delay();
        ch <<= 1;
        if (SDA)
            ch |= 0x01;
    }
    SCL = 0; delay();
    return ch;
}

void i2c_wait_for_ack(void)
{
    unsigned char i = 0;
    
    delay();
    SDA = 1; delay();
    SCL = 1; delay();
    while (SDA && i < 250)
        ++i;
    SCL = 0; delay();
}

void i2c_ack(bit ack)
{
    SDA = ack; delay();
    SCL = 1; delay();
    SCL = 0; delay();
}