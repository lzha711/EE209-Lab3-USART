/*
 * USART_209.c
 * Better structure. All functions related to usart are now in usart0.c
 * Include file is usart0.h
 * common.h defines the clock frequency
 * Created: 8/13/2021 9:40:06 AM
 * Author : lzha711
 */ 

#include "usart0.h"
#include "common.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define BIT_IS_SET(byte, bit) (byte & (1<<bit)) //if bit is set
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1<<bit))) // if bit is clear

static uint8_t digits[3] = {0,0,0};	//Initializing array holding the 3 digits to be sent to printing	
#define PRIME_RANGE 300 // checking number range
#define RXBufSize 100 //for echoing, not needed in this lab
char RXBuf[RXBufSize];

//Function returns 1 if chk_no is a prime
uint8_t check_prime(uint16_t chk_no){
	for(uint16_t i=2; i<chk_no; i++){
		if( (chk_no % i) == 0){	 //a number that can be divided by number less than itself is not a prime
			return 0;	 //Return FALSE
		}
	}
	return 1;			 //If chk_no cannot be divided by a number less than itself, it is a prime
}


void print_3digit_number(uint16_t number, uint8_t* digits){
	digits[0] = number%10;			//First digit
	digits[1] = (number/10)%10;		//Second digit
	digits[2] = (number/100)%10;		//Third digit
	
	for(uint8_t i = 3; i>0; i--){
		USART0_transmit_char(digits[i-1]+48);		//Transmitting each digit one at a time
	}
	USART0_transmit_char(10);				//Line feed
	USART0_transmit_char(13);			        //carriage return
}


// main program
int main(void)
{
	USART0_init(9600); //set baud rate to 9600
	
	uint16_t prime_array[62];
	prime_array[0] = 2;
	uint8_t prime_index = 1;
	
	for(uint16_t i=3; i<PRIME_RANGE; i++){		//Check if prime number and print
		if(check_prime(i)){
			prime_array[prime_index] = i;
			prime_index++;
			print_3digit_number(i, digits);
		}
	}
	
	USART0_transmit_string("Total number of primes are: ");
	print_3digit_number(prime_index, digits); //print the total number of primes
	
	while (1) {
		// do nothing
	}
	return(0); // should never get here
}
