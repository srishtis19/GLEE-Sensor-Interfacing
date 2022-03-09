#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "I2C2.c"
#include "LSM9DS1.c"
#include "UART1.c"

void configure_ext_interrupt(){
	EIMSK|=(1<<INT0);						//Enable INT0
	EICRA|=(1<<ISC00)|(1<<ISC01);					//Configure INT0 as rising edge triggered
	
	sei();								//Global interrupt enable
}

uint8_t read_register(uint8_t sub){
	uint8_t temp;					//Variable to store register value
	TWI_Master_init();
	TWI_start();
	TWI_SLA_W(SADW);
	TWI_Master_transmit(sub);
	TWI_stop();
	TWI_start();
	//configure_acc(SADW,address);
	//I2C_Repeated_Start(SADR);
	
	temp=TWI_Master_receive(0);				//Obtain register value using I2C
	TWI_stop();
	return temp;
}

void LED_blink(){
	PORTB = 0x00;
	_delay_ms(1000);
	PORTB = 0xFF;
	_delay_ms(1000);
	PORTB = 0x00;
	_delay_ms(1000);
	PORTB = 0xFF;
	_delay_ms(1000);
	PORTB = 0x00;

	
}

//FINAL FUNCTION TO READ REGISTER VALUE
uint8_t read_register1(uint8_t sub){
	uint8_t temp;					//Variable to store register value
	I2C_init();	
	I2C_start();
	
	while(!I2C_SLA(SADW));
			
	while(!I2C_write(sub));
	
	while(!I2C_repeated_start());

	while(!I2C_SLAR(SADR));
	LED_blink();		
	temp = I2C_read_ack();

	I2C_stop();

	return temp;
}

void write_register(uint8_t address, uint8_t value){
	TWI_Master_init();
	TWI_start();
	TWI_SLA_W(SADW);
	TWI_Master_transmit(address);
	TWI_Master_transmit(value);
	TWI_stop();
	
}

void write_register1(uint8_t sub, uint8_t value){
	I2C_init();
	I2C_start();
	
	while(!I2C_SLA(SADW));

	while(!I2C_write(sub));
	
	while(!I2C_write(value));
	
	I2C_stop();
	LED_blink();
}

ISR(INT0_vect){
	
	for(int i=0;i<32;i++){
		read_acc(); 						//Acc data gets stored in Ax, Ay, Az
		_delay_ms(100);						//Rate of reading data from FIFO to be decided; should be > ODR for no overwrite
	}

}


int main(void)
{
	//uint8_t data_available= acc_data_available();
	
	DDRB = 0xFF;
	
	
	

	UART_init(9600);
	
	write_register1(CTRL_REG5_XL,0x38);			//Accelerometer X,Y,Z output enable
	write_register1(CTRL_REG6_XL,0x20);			//Output Data Rate=10 Hz, full scale deflection=2g
	//read_register1(CTRL_REG5_XL);
	//
	//acc_init();							//Initialize Accelerometer
	//PORTA = 0xFF;
	//
	//
	//
	uint8_t data;
	//Cont_init();
	
	//configure_ext_interrupt();
	//configure_interrupt();					//Enable interrupt generation when FIFO is full (32 unread samples)
	
	while(1){
		
		//write_register1(ACT_THS,0x38);			//Accelerometer X,Y,Z output enable
		//write_register1(CTRL_REG6_XL,0x20);			//Output Data Rate=10 Hz, full scale deflection=2g
		//read_register1(WHO_AM_I);
		
		
		data = read_register1(WHO_AM_I);
		UART_TxChar(data);
		//uint8_t status = read_register1(STATUS_REG1);
		//UART_TxChar(status);
		//if(status&(1<<0)){
			
		
		//if(data_available) {
			//read_acc(); 						//Acc data gets stored in Ax, Ay, Az
			//UART_transmit(Ax);
			//UART_transmit(Ax>>8);
			//UART_transmit(Ay);
			//UART_transmit(Ay>>8);
			//UART_transmit(Az);
			//UART_transmit(Az>>8);
		//}
	}
	
}
