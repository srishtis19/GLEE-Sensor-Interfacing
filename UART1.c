#include <avr/io.h>
#include <util/delay.h>
#include "UART1.h"

void UART_init(long USART_BAUDRATE)
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);	/* Turn on transmission and reception */
	UCSR0C |= (1 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);/* Use 8-bit char size */
	UBRR0L = BAUD_PRESCALE;			/* Load lower 8-bits of the baud rate */
	UBRR0H = (BAUD_PRESCALE >> 8);		/* Load upper 8-bits*/
}
unsigned char UART_RxChar()
{
	while ((UCSR0A & (1 << RXC0)) == 0);	/* Wait till data is received */
	return(UDR0);				/* Return the byte */
}
void UART_TxChar(char ch)
{
	while (! (UCSR0A & (1<<UDRE0)));  /* Wait for empty transmit buffer */
	UDR0 = ch ;
}