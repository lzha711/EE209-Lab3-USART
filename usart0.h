/*
 * usart0.h
 *
 * Created: 8/13/2021 9:42:27 AM
 *  Author: lzha711
 */ 


#ifndef USART0_H_
#define USART0_H_

#include <stdint.h>

void USART0_init(unsigned int baud);
void USART0_transmit_char(unsigned char data);
void USART0_transmit_string(char* s);
unsigned char USART0_receive_char();
void USART0_receive_string(char* buf, uint8_t n);

#endif /* USART0_H_ */