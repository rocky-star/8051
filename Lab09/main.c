// MM编程方式

#include <STC15F2K60S2.h>
#include <absacc.h>

const unsigned char code sentence[] = "The quick brown fox jumps over the lazy dog.\r\n";

void delay(unsigned char time)
{
    unsigned char i;
    for (; time > 0; --time) {
        for (i = 125; i > 0; --i) {
        }
    }
}

void send_string(unsigned char *s)
{
    for (; *s; ++s) {
        SBUF = *s;
        while (TI == 0)
            ;
        TI = 0;
    }
}

void main(void)
{
    unsigned char i = 0;
    
    XBYTE[0xA000] = 0;
    
    AUXR = 0;
    TMOD = 0x20;
    TH1 = TL1 = 0xFD;
    PCON = 0;
    SCON = 0x50;
    TR1 = 1;
    
    for (;;) {
        send_string(sentence);
        delay(200);
    }
}