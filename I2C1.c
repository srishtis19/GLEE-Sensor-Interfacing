#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
//#include "I2C1.h"

void TWI_Master_init() {
	//CPU Clock = 8MHz, SCL Freq = 50kHz
	TWBR = 0x48; //Bit rate
	TWSR = (0<<TWPS0) | (0<<TWPS1); //Prescalar
	TWCR = (1<<TWEN); //TWI enable
}

void TWI_start() {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //send start condition
	while(!(TWCR & (1<<TWINT))); //wait for TWINT to set
}

//Slave Address and W/R
void TWI_SLA_W(unsigned char sla_w) {
	TWDR = sla_w;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

void TWI_Master_transmit(unsigned char data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
}

unsigned char TWI_Master_receive(unsigned char isLast) {
	unsigned char received_data;
	if(isLast == 0) {
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	}
	else {
		TWCR = (1<<TWINT)|(1<<TWEN);
	}
	
	while(!(TWCR & (1<<TWINT)));
	received_data = TWDR;
	//PORTA = received_data;
	return received_data;
}

void TWI_stop() {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}