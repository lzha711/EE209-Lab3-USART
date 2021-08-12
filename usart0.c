/* 
 * usart0.c
 * Initialization, char transmit and string transmit
 * Created: 8/13/2021 9:41:16 AM
 * Author: lzha711
 */ 

#include "usart0.h"
#include "common.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

// define macros
#define BIT_IS_SET(byte, bit) (byte & (1<<bit)) //if bit is set
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1<<bit))) // if bit is clear

void USART0_init(unsigned int baud){
	// calculate ubrr register value
	uint16_t ubrr = (F_CPU/16/baud - 1);
	UBRR0H = (unsigned char)(ubrr>>8); //high 8 bits
	UBRR0L = (unsigned char)ubrr;
	//enable receiver and transmitter
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	//enable receive interrupt
	UCSR0B |= (1<<RXCIE0);
	//set data frame 8N1
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

/* TRANSMIT A CHARACTER */
void USART0_transmit_char(unsigned char data){
	//wait for the transmit buffer to be empty
	while(BIT_IS_CLEAR(UCSR0A, UDRE0))
	; //when this bit is 1, the buffer is empty
	UDR0 = data;
}

/* TRANSMIT A STRING LINE */
void USART0_transmit_string(char* s){
	//transmit until NULL is received
	while(*s > 0) USART0_transmit_char(*s++);
}

/* RECEIVE A CHARACTER (Not needed in this lab)*/
unsigned char USART0_receive_char(){
	// wait for data to be ready
	while (BIT_IS_CLEAR(UCSR0A, RXC0))
	; //when receive buffer is empty, RXC0 is cleared
	return UDR0;
}

/* RECEIVE A STRING LINE (Not needed in this lab)*/
void USART0_receive_string(char* buf, uint8_t n){
	uint8_t bufIdx = 0;
	unsigned char c;
	//while received character is not carriage return
	//and end of buffer has not been reached
	do{
		c = USART0_receive_char();
		buf[bufIdx] = c;
		bufIdx++;
	}
	while( (bufIdx<n) && (c !='\r') );
	
	//ensure buffer is null terminated
	buf[bufIdx] = 0;
}
