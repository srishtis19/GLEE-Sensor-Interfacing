#define F_CPU 8000000UL						/* Define CPU clock Frequency e.g. here its 8MHz */

#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>						/* Include inbuilt defined Delay header file */
#include <string.h>						/* Include string header file */
#include <math.h>						/* Include math function */
#include <stdio.h>
#include "I2C.c"
#include "LSM9DS1.h"

int main(void)
{
   char sensor_data;
   
   I2C_Init();						//Initialize I2C 
   char reg_addr = 0x6B;			        //8 bit sub-address
   configure_acc(SADW,reg_addr);			
   
   while(1)
   {
	   I2C_Repeated_Start(SADR);
	   sensor_data=I2C_Read_Ack();
   }
   
   I2C_Stop();
   
   
}



