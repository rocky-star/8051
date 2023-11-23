// MM

#include <STC15F2K60S2.H>

unsigned char xdata *ssd_data = 0xE000;
unsigned char xdata *ssd_com  = 0xC000;

const unsigned char code column_codes_l6[] = { 0x2F, 0x1F, 0x0F };
const unsigned char code column_codes_h2[] = { 0x08, 0x02, 0x00 };
const unsigned char code scancodes_l4[] = { 0x07, 0x0B, 0x0D, 0x0E };

const unsigned char code ssd_digits[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90,
    0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

unsigned char key_value = 0xFF;

void delay(unsigned char time)
{
    unsigned char i;
    for (; time > 0; --time) {
        for (i = 125; i > 0; --i)
            ;
    }
}

unsigned char get_key(void)
{
    static unsigned char key_state = 0;
    unsigned char key_value = 0xFF;
    
    switch (key_state) {
    case 0:
        P3 = 0x0F;
        P42 = 0;
        P44 = 0;
        if (P3 != 0x0F) {
            key_state = 1;
        }
        break;
    case 1:
        P3 = 0x0F;
        P42 = 0;
        P44 = 0;
        if (P3 != 0x0F) {
            if (P30 == 0) {
                // Row 1
                P3 = 0xF0;
                P42 = 1;
                P44 = 1;
                
                if (P44 == 0) {
                    key_value = 0;
                    key_state = 2;
                } else if (P42 == 0) {
                    key_value = 1;
                    key_state = 2;
                } else if (P35 == 0) {
                    key_value = 2;
                    key_state = 2;
                } else if (P34 == 0) {
                    key_value = 3;
                    key_state = 2;
                }
            } else if (P31 == 0) {
                // Row 2
                P3 = 0xF0;
                P42 = 1;
                P44 = 1;
                
                if (P44 == 0) {
                    key_value = 4;
                    key_state = 2;
                } else if (P42 == 0) {
                    key_value = 5;
                    key_state = 2;
                } else if (P35 == 0) {
                    key_value = 6;
                    key_state = 2;
                } else if (P34 == 0) {
                    key_value = 7;
                    key_state = 2;
                }
            } else if (P32 == 0) {
                // Row 3
                P3 = 0xF0;
                P42 = 1;
                P44 = 1;
                
                if (P44 == 0) {
                    key_value = 8;
                    key_state = 2;
                } else if (P42 == 0) {
                    key_value = 9;
                    key_state = 2;
                } else if (P35 == 0) {
                    key_value = 10;
                    key_state = 2;
                } else if (P34 == 0) {
                    key_value = 11;
                    key_state = 2;
                }
            } else if (P33 == 0) {
                // Row 4
                P3 = 0xF0;
                P42 = 1;
                P44 = 1;
                
                if (P44 == 0) {
                    key_value = 12;
                    key_state = 2;
                } else if (P42 == 0) {
                    key_value = 13;
                    key_state = 2;
                } else if (P35 == 0) {
                    key_value = 14;
                    key_state = 2;
                } else if (P34 == 0) {
                    key_value = 15;
                    key_state = 2;
                }
            }
        }
        break;
    case 2:
        P3 = 0x0F;
        P42 = 0;
        P44 = 0;
        if (P3 == 0x0F)
            key_state = 0;
    }
    
    return key_value;
}

void read_keyboard(void)
{
    static unsigned char hang;
	static unsigned char key_state=0;	
	switch(key_state)
	{
		case 0:
		{
			P3 = 0x0f; P42 = 0; P44 = 0;
			if(P3 != 0x0f)
			key_state=1;	
		}break;
		case 1:
		{
			P3 = 0x0f; P42 = 0; P44 = 0;
			if(P3 != 0x0f)
			{
				if(P30 == 0)hang = 1;
				if(P31 == 0)hang = 2;
				if(P32 == 0)hang = 3;
				if(P33 == 0)hang = 4; 
				switch(hang){
					case 1:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) {key_value=0;key_state=2;}
						else if(P42 == 0) {key_value=1;key_state=2;}
						else if(P35 == 0) {key_value=2;key_state=2;}
						else if(P34 == 0) {key_value=3;key_state=2;}
					}break;
					case 2:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) {key_value=4;key_state=2;}
						else if(P42 == 0) {key_value=5;key_state=2;}
						else if(P35 == 0) {key_value=6;key_state=2;}
						else if(P34 == 0) {key_value=7;key_state=2;}
					}break;
					case 3:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) {key_value=8;key_state=2;}
						else if(P42 == 0) {key_value=9;key_state=2;}
						else if(P35 == 0) {key_value=10;key_state=2;}
						else if(P34 == 0) {key_value=11;key_state=2;}
					}break;
					case 4:{P3 = 0xf0; P42 = 1; P44 = 1;
						if(P44 == 0) {key_value=12;key_state=2;}
						else if(P42 == 0) {key_value=13;key_state=2;}
						else if(P35 == 0) {key_value=14;key_state=2;}
						else if(P34 == 0) {key_value=15;key_state=2;}
					}break;
				}	
			}
			else
			{
				key_state=0;	
			}  	   
		}break;
		case 2:     
		{
			P3 = 0x0f; P42 = 0; P44 = 0;
			if(P3 == 0x0f)
			key_state=0;	
		}break;
						
    } 
	
}

void main(void)
{   
    unsigned char ssd_no = 0;
    
    *ssd_com = 0;
    for (;;) {
        read_keyboard();
        
        *ssd_data = 0;
        *ssd_com = 1 << ssd_no;
        *ssd_data = key_value != 0xFF ? ssd_digits[key_value] : 0;
        if (++ssd_no == 8)
            ssd_no = 0;
    }
}