#ifndef DS1302_H
#define DS1302_H

#define DS1302_SECONDS_R 0x81
#define DS1302_SECONDS_W 0x80

#define DS1302_MINUTES_R 0x83
#define DS1302_MINUTES_W 0x82

#define DS1302_HOUR_R    0x85
#define DS1302_HOUR_W    0x84

unsigned char ds1302_read(unsigned char addr);
void ds1302_write(unsigned char addr, unsigned char ch);

#endif