// MM编程方式

#include <STC15F2K60S2.h>
#include <absacc.h>
#include <ds1302.h>

#define TH0_INIT 0xFC
#define TL0_INIT 0x66

const unsigned char code display_digits[] = {
    // 0     1     2     3     4
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    // 5     6     7     8     9
    0x92, 0x82, 0xF8, 0x80, 0x90,
    // -
    0xBF, 0xFF
};
unsigned char display_buffer[8] = {11, 11, 11, 11, 11, 11, 11, 11};

unsigned char cycle_counter = 0;
bit should_read_ds1302 = 0;

void delay(unsigned char t)
{
    unsigned char i;
    for (; t; --t)
        for (i = 125; i; --i)
            ;
}

void refresh_displays(void) interrupt 1
{
    static unsigned char disp_no = 0;
    
    XBYTE[0xE000] = 0xFF;
    XBYTE[0xC000] = 1 << disp_no;
    XBYTE[0xE000] = display_digits[display_buffer[disp_no]];
    if (++disp_no == 8)
        disp_no = 0;
    
    if (++cycle_counter == 200) {
        cycle_counter = 0;
        should_read_ds1302 = 1;
    }
    
    TH0 = TH0_INIT;
    TL0 = TL0_INIT;
}

unsigned char init_time[] = {1, 9, 4, 2, 3, 1};

void reset_ds1302(void)
{
    ds1302_write(0x8E, 0x00);
    
    ds1302_write(DS1302_HOUR_W, (init_time[4] << 4) | init_time[5]);
    ds1302_write(DS1302_MINUTES_W, (init_time[2] << 4) | init_time[3]);
    ds1302_write(DS1302_SECONDS_W, (init_time[0] << 4) | init_time[1]);
    
    ds1302_write(0x8E, 0x80);
}

void main(void)
{
    unsigned char seconds, minutes, hour;
    
    // 禁用蜂鸣器等设备。
    XBYTE[0xA000] = 0;
    
    delay(200);
    AUXR = 0;
    
    // T0 用于刷新数码管。
    TMOD = 0x11;
    EA = 1;
    ET0 = 1;
    TH0 = TH0_INIT;
    TL0 = TL0_INIT;
    TR0 = 1;
    
    reset_ds1302();
    for (;;) {
        if (should_read_ds1302) {
            should_read_ds1302 = 0;
            
        seconds = ds1302_read(DS1302_SECONDS_R) & 0x7F;
        minutes = ds1302_read(DS1302_MINUTES_R) & 0x7F;
        hour    = ds1302_read(DS1302_HOUR_R)    & 0x1F;
            
            display_buffer[0] = hour >> 4;
            display_buffer[1] = hour & 0x0F;
            display_buffer[2] = 10;
            display_buffer[3] = minutes >> 4;
            display_buffer[4] = minutes & 0x0F;
            display_buffer[5] = 10;
            display_buffer[6] = seconds >> 4;
            display_buffer[7] = seconds & 0x0F;
        }
    }
}