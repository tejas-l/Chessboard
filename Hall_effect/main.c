
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include "PISO.h"
#include "UART.h"
#include "Board.h"
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#define  clockPin  PORTD7
#define dataPin PORTD4
#define clockenable PORTD3 
#define latchPin PORTD5

// White Pieces  
#define WR1 51
#define WR2 52
#define WN1 31
#define WN2 32
#define WB1 41
#define WB2 42
#define WQ 91
#define WK 100

// Whirte Pawns 
#define WP1 10
#define WP2 11
#define WP3 13
#define WP4 14
#define WP5 15
#define WP6 16
#define WP7 17
#define WP8 18

// Black Pieces 
#define BR1 53
#define BR2 54
#define BN1 33
#define BN2 34
#define BB1 43
#define BB2 44
#define BQ 92
#define BK 200

// Black Pieces 
#define BP1 20
#define BP2 21
#define BP3 22
#define BP4 23
#define BP5 24
#define BP6 25
#define BP7 26
#define BP8 27

char String[25];
char String2[25];
char String3[25];
char String4[25];
volatile int boardstate [4][8] = {
						{0,0,WB1,WQ,WK,WB2,0,0}, 
						{0,0,WP3,WP4,WP5,WP6,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},	
					};  
void Initialization () 
{

	//PISO Init 

	
	DDRD |= (1U<<DDD5); // latch - Output
	DDRD |= (1U<<DDD7); // Clock - Output
	DDRD |= (1U<<DDD3); // ClockINH - Output
	DDRD &= ~(1U<<DDD4); // DataPin - Input


}
int Row4 = 11;
int Row3 = 12;
int Row2= 11;
int Row1 =10; 
uint8_t rows[4] = {0} ;  
int test = 0; 
int boardstateprev [4][8];
int rowsprev [4];
volatile int temp = 0; 
volatile int print = 0;
volatile int pick = 0; 
volatile int capture = 0;

void rowsupdate()
{
	int i;
	
	for (i=0;i<4;i++)
	{
		
		
		rowsprev[i] = rows[i];
		
	}
}
void boardupdate()
{
	int i,j;
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<8;j++)
		{
			boardstateprev[i][j] = boardstate[i][j];
		}
	}
}
void squareprev()
{
	int i,j;
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<8;j++)
		{
			if((rows[i] & (0x1<<j) ) != 0 ) // pick up piece - 0-->1 transition
			{ 
				_delay_ms(300); //debounce delay 
				
				if((rows[i] & (0x1<<j) ) != 0 )
				{
					
				
						int check = boardstate [i][j];
						
						if ( rows[i] != rowsprev[i])
						{
							if ( check != 0)
							{
								temp =boardstate[i][j];
								boardstate[i][j] = 0;
								print = 1;
								pick =1;
								rowsupdate();
								boardupdate();
						
							}
						}
				}
			}
		}
	}
}
void  squarenext()
{
	//char board[25];
	int i,j;
	
	for (i=0;i<4;i++)
	{
		for (j=0;j<8;j++)
		{
				if((rows[i] & (0x1<<j) )== 0 ) // 
				{
					_delay_ms(300); 
					
					if((rows[i] & (0x1<<j) )== 0 )
					{
						
					
							int  check = boardstateprev[i][j];
					
							if ( rows[i] != rowsprev[i]) 
							{
						
									if (check == 0)
									{
					
										boardstate[i][j] = temp ;
										print = 1; 
										pick = 0; 
								
										pieceprint(temp);
										printsquare(i,j); 
										rowsupdate();
										boardupdate();
						
						
										temp = 0;
						
									}
									
									if ( check !=0)
									{
									 
									 char cap [20];
									 
									 boardstate[i][j] = temp ;
									 print = 1;
									 pick = 0;
									 /*capture = 1;  */
									 
									 pieceprint(temp);
									 
									sprintf(cap,"x");
									UART_putstring(cap);
									 
									 printsquare(i,j);
									 rowsupdate();
									 boardupdate();
									 
									 
									 temp = 0;
									 
									
									
									}
					
							}
					}
			}  
		}
	}
}
void printboard()
{
	char p [25]; 
	for(int i=0; i<4; i++)
	{
		for(int j=0 ; j<8; j++)
		{
		//sprintf("\t%d",boardstate[i][j]);
		sprintf(p,"\t%d ",boardstate[i][j]);
		UART_putstring(p);
		}
		UART_putstring("\n\r");
		UART_putstring("\n\r");
	}
	
}
void printrows()
{
		char r [25];
	
	for (int i=0;i<4;i++)
	{
		sprintf(r,"\t %x \n\r ",rows[i]);
		UART_putstring(r);
	}
	
}
char s[20];
int main(void)
{
   Initialization(); 
    UART_init(BAUD_PRESCALER);
    while (1) 
    {
// 	
	latch(latchPin,clockPin);
	
	rows[3] = shiftIn(dataPin,clockPin);
	rows[2] = shiftIn(dataPin,clockPin);
	rows[1] = shiftIn(dataPin,clockPin);
	rows[0] = shiftIn(dataPin,clockPin);
	

// 	_delay_ms(500);
	//boardupdate(); 
//	rowsupdate();
	
	squareprev();
	_delay_ms(500);
	
// 	sprintf(s,"temp = %d \n\r",temp);
// 	UART_putstring(s);
		
		if (pick)
		{
			squarenext();
			_delay_ms(500);
		}
	
		if (print)
 			{		
				 sprintf(s,"temp = %d \n\r",temp);
					UART_putstring(s);
				printboard();
				_delay_ms(500);
				print= 0;
		}
	}
}