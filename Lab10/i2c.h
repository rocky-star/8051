#ifndef I2C_H
#define I2C_H

void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char ch);
unsigned char i2c_read(void);
void i2c_wait_for_ack(void);
void i2c_ack(bit ack);

#endif