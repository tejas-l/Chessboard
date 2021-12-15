/*
 * Hall_effect.c
 *
 * Created: 22-11-2021 10:22:15
 * Author : lalit
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include "PISO.h"
#include "UART.h"
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#define  clockPin  PORTD7
#define dataPin PORTB1
#define clockenable PORTB2 
#define latchPin PORTB0

char String[25];
char String2[25];
char String3[25];
char String4[25];

void Initialization () 
{
	
	//PISO Init 
	
	DDRB |= (1U<<DDB0); // latch - Output
	DDRD |= (1U<<DDD7); // Clock - Output
	DDRB |= (1U<<DDB2); // ClockINH - Output
	DDRB &= ~(1U<<DDB1); // DataPin - Input
	 
	
}


int Row4 = 11;
int Row3 = 12;
int Row2= 11;
int Row1 =10; 
uint8_t rows[4] = {0} ;  
int test = 0; 

void  squareprev()
{
	char board[25];
	int i,j;
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<8;j++)
		{
				if((rows[i] & (0x1<<j) ) != 0 )
				{
					sprintf(board," %d,%d \n\r ",i,j);
					UART_putstring(board);
				}
		}
	}
}

int main(void)
{
   Initialization(); 
    UART_init(BAUD_PRESCALER);
    while (1) 
    {
// 	
	latch(latchPin,clockPin);
	
	rows[4] = shiftIn(dataPin,clockPin);
	rows[3] = shiftIn(dataPin,clockPin);
	rows[2] = shiftIn(dataPin,clockPin);
	rows[1] = shiftIn(dataPin,clockPin);
	
	/*Row4 = shiftIn(dataPin,clockPin);
	Row3 = shiftIn(dataPin,clockPin);
	Row2 = shiftIn(dataPin,clockPin);
	Row1 = shiftIn(dataPin,clockPin);
	
	sprintf(String," %x  ",Row4);
	UART_putstring(String);
	sprintf(String2," %x  ",Row3);
	UART_putstring(String2);
	sprintf(String3," %x  ",Row2);
	UART_putstring(String3);
	sprintf(String4," %x\n\r  ",Row1);
	UART_putstring(String4);
	
	_delay_ms(200);
	*/ 
	squareprev();
	_delay_ms(200);

	}
}
