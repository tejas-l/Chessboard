
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
volatile int boardstate [8][8] = {
						{WR1,WN1,WB1,WQ,WK,WB2,WN2,WR2}, 
						{WP1,WP2,WP3,WP4,WP5,WP6,WP7,WP8},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},	
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{BP1,BP2,BP3,BP4,BP5,BP6,BP7,BP8},
						{BR1,BN1,BB1,BQ,BK,BB2,BN2,BR2}	
								
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
uint8_t rows[8] = {0} ;  
int test = 0; 
int boardstateprev [4][8];
int rowsprev [8];
volatile int temp = 0; 
volatile int print = 0;
volatile int pick = 0; 


void rowsupdate() // Update the elements in rowsprev to current rows value 
{
	int i;
	
	for (i=0;i<8;i++)
	{
		
		
		rowsprev[i] = rows[i];
		
	}
}
void boardupdate() // Update the boardstateprev array to reflect the current positions of pieces on the board 
{
	int i,j;
	
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
			boardstateprev[i][j] = boardstate[i][j];
		}
	}
}
void squareprev() //  Identify Square from which a piece is picked up 
{
	int i,j;
	
	for (i=0;i<8;i++)
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
void  squarenext() // identify the square where the picked piece is placed 
{
	//char board[25];
	int i,j;
	
	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
				if((rows[i] & (0x1<<j) )== 0 ) // piece placed - 1-->0 transition 
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
									
									if ( check !=0) // Captures - If a piece already exists on the square where new piece is placed. 
									{
									 
									 char cap [20];
									 
									 boardstate[i][j] = temp ;
									 print = 1;
									 pick = 0;
									 
									 
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
	for(int i=0; i<8; i++)
	{
		for(int j=0 ; j<8; j++)
		{
		//sprintf("\t%d",boardstate[i][j]); //for debugging
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
	
	for (int i=0;i<8;i++)
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
	
	// Shift In data from 8 PISO shift registers and store it in an Array 
	
	rows[7] = shiftIn(dataPin,clockPin);
	rows[6] = shiftIn(dataPin,clockPin);
	rows[5] = shiftIn(dataPin,clockPin);
	rows[4] = shiftIn(dataPin,clockPin);
	rows[3] = shiftIn(dataPin,clockPin);
	rows[2] = shiftIn(dataPin,clockPin);
	rows[1] = shiftIn(dataPin,clockPin);
	rows[0] = shiftIn(dataPin,clockPin);
	

// 	_delay_ms(500);
	//boardupdate();  //for debugging 
//	rowsupdate(); //for debugging
	
	squareprev();
	_delay_ms(500);
	
// 	sprintf(s,"temp = %d \n\r",temp);
// 	UART_putstring(s); //for debugging
		
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