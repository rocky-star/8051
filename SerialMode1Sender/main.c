#include <reg52.h>

const char code seg_codes[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
};

void delay(unsigned int time)
{
    unsigned char j;
    for (; time > 0; --time) {
        for (j = 125; j > 0; --j) {
        }
    }
}

void main(void)
{
    unsigned char counter = 0;
    
    TMOD = 0x20;
    TH1 = TL1 = 0xF4; // Baud rate: 2400
    PCON = 0;
    
    RI = TI = 0;
    REN = 1;
    SM1 = 1;
    
    for (;;) {
        SBUF = counter;
        
        while (TI == 0)
            ;
        TI = 0;
        
        while (RI == 0)
            ;
        RI = 0;
        
        if (SBUF == counter) {
            P2 = seg_codes[counter];
            if (++counter > 15)
                counter = 0;
            delay(500);
        }
    }
}