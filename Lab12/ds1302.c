#include <STC15F2K60S2.h>
#include <intrins.h>

sbit CE   = P1^3;
sbit IO   = P2^3;
sbit SCLK = P1^7;

static void write_byte(unsigned char ch)
{
    unsigned char i;
    for (i = 8; i; --i) {
        SCLK = 0;
        IO = ch & 0x01;
        ch >>= 1;
        SCLK = 1;
    }
}

unsigned char ds1302_read(unsigned char addr)
{
    unsigned char i, ch = 0;
    
    CE = 0; _nop_();
    SCLK = 0; _nop_();
    CE = 1; _nop_();
    
    write_byte(addr);
    for (i = 8; i; --i) {
        SCLK = 0;
        ch >>= 1;
        if (IO)
            ch |= 0x80;
        SCLK = 1;
    }
    
    CE = 0; _nop_();
    CE = 0;
    SCLK = 0; _nop_();
    SCLK = 1; _nop_();
    IO = 0; _nop_();
    IO = 1; _nop_();
    
    return ch;
}

void ds1302_write(unsigned char addr, unsigned char ch)
{
    CE = 0; _nop_();
    SCLK = 0; _nop_();
    CE = 1; _nop_();
    
    write_byte(addr);
    write_byte(ch);
    
    CE = 0;
}