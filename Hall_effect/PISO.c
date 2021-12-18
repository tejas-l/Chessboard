/*
 * PISO.c
 *
 * Created: 30-11-2021 19:35:31
 *  Author: lalit
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "UART.h"

char abc[10]= {0};
char space = '\n';


uint8_t shiftIn(int mydataPin, int myclockPin) 
{
	uint8_t myDataIn = 0x00; 
	uint8_t temp = 0; 
	
	for (int i=0 ; i<8 ; i++)
		{
			 PORTD &= ~(1U<<myclockPin);
			_delay_us(4);
			 temp = (PIND & (1<<mydataPin));
// 			 sprintf(abc,"%d\t",temp);
// 			 UART_putstring(abc);
			 
			 if (temp)
			 {
				 myDataIn = myDataIn | (1<<i); 
				
			 } 
			 
		PORTD |= (1U<< myclockPin); 
			_delay_us(4); 
			 
		}
	/* UART_send(space);*/
	  return myDataIn; 
	  
}
	
void latch( int mylatchPin, int myclockPin)
{
	
	PORTD &= ~(1U<< myclockPin);
	_delay_us(20);
	PORTD &= ~(1U<<mylatchPin);  // Read Parallel
	_delay_us(20);
	PORTD |= (1U<<mylatchPin); // Serial Out
	_delay_us(20);
	

}
