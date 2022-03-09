#ifndef _I2C1_
#define _I2C1_


//function definitions
void TWI_Master_init();
void TWI_start();
void TWI_SLA_W(unsigned char sla_w);
void TWI_Master_transmit(unsigned char data);
unsigned char TWI_Master_receive(unsigned char isLast);
void TWI_stop();
#endif