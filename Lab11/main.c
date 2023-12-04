// MM编程方式

#include <STC15F2K60S2.h>
#include <absacc.h>
#include <intrins.h>
#define TH1_INIT 0xF8
#define TL1_INIT 0xCC

sbit US_IN  = P1^0;
sbit US_OUT = P1^1;

const unsigned char code display_digits[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90
};
unsigned char display_buffer[8] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

void delay_14us(void)
{
    unsigned char i;
    _nop_();
    _nop_();
    for (i = 33; i; --i)
        ;
}

void send_waves(void)
{
    unsigned char i;
    for (i = 8; i; --i) {
        US_IN = 1;
        delay_14us();
        US_IN = 0;
        delay_14us();
    }
}

void refresh_displays(void) interrupt 3
{
    static unsigned char disp_no = 0;
    
    XBYTE[0xE000] = 0xFF;
    XBYTE[0xC000] = 1 << disp_no;
    XBYTE[0xE000] = display_buffer[disp_no];
    
    if (++disp_no == 8)
        disp_no = 0;
    
    TH1 = TH1_INIT;
    TL1 = TL1_INIT;
}

void main(void)
{
    // 禁用蜂鸣器等设备。
    XBYTE[0xA000] = 0;
    
    // T0 用于超声波检测，T1 用于刷新数码管。
    TMOD = 0x11;
    ET1 = 1;
    TH1 = TH1_INIT;
    TL1 = TL1_INIT;
    TR1 = 1;
    
    for (;;) {
        EA = 0;
        send_waves();
        EA = 1;
        
        TH0 = TL0 = 0;
        TR0 = 1;
        // 等待波到达或 T0 溢出。
        while (US_OUT && !TF0)
            ;
        TR0 = 0;
        
        if (TF0)
            TF0 = 0;
        else {
            unsigned time = (TH0 * 256) + TL0;
            unsigned dist = (unsigned) ((time * 0.017 * 12) / 11.0592);
            display_buffer[5] = display_digits[dist / 100];
            display_buffer[6] = display_digits[dist / 10 % 10];
            display_buffer[7] = display_digits[dist % 10];
        }
    }
}