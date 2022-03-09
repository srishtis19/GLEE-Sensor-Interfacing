#ifndef _I2C2_
#define _I2C2_


#define SCL_CLK 100000L
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

//function definitions
char I2C_check_status(char status_code);
void I2C_init();
char I2C_start();
char I2C_repeated_start();
char I2C_stop();
char I2C_write(char byte);
char I2C_SLA(char byte);
char I2C_SLAR(char byte);
char I2C_read_ack();
char I2C_read_nack();

#endif