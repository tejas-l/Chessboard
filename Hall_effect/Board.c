#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>
#include "PISO.h"
#include "UART.h"
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)


void pieceprint(int piece)
{
	char p [20]; 
	
	 switch (piece) 
	 {
		 case 51: 
		 case 52:
		 case 53:
		 case 54: 
		 
	sprintf(p,"Rook--");
	UART_putstring(p);
		 break;
		 
		 case 31:
		 case 32: 
		 case 33:
		 case 34:
		 
		sprintf(p,"Knight--");
		UART_putstring(p);
		 break; 
		 
		 case 41:
		 case 42:
		 case 43:
		 case 44: 
		 
		sprintf(p,"Bishop--");
		UART_putstring(p);
		break; 
		
		case 91:
		case 92:
		
		sprintf(p,"Queen--");
		UART_putstring(p);
		break;
		
		case 100:
		case 200: 
		
		sprintf(p,"King--");
		UART_putstring(p);
		break;
		
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		sprintf(p,"\n\r");
		UART_putstring(p);
		
		 default:
		 sprintf(p,"\n\r");
		 UART_putstring(p);
		 break;
		 
	 }
}


void rankprint(int j )

{
		char t[20];
		
		switch (j)
		{
			case 0:
			
			sprintf(t,"1 \n\r");
			UART_putstring(t);
			break;
			
			case 1:
			sprintf(t,"2 \n\r");
			UART_putstring(t);
			break; 
			
			case 2:
			sprintf(t,"3 \n\r");
			UART_putstring(t);
			break; 
			
			case 3: 
			sprintf(t,"4 \n\r");
			UART_putstring(t);
			break; 
			
			case 4: 
			sprintf(t,"5 \n\r");
			UART_putstring(t);
			break;
			
			case 5:
			sprintf(t,"6 \n\r");
			UART_putstring(t);
			break;
			
			case 6: 
			sprintf(t,"7 \n\r");
			UART_putstring(t);
			break;
			
			case 7:
			sprintf(t,"8 \n\r");
			UART_putstring(t);
			break; 
			
			default:
			sprintf(t,"\n\r");
			UART_putstring(t);
			break;
			
		}
		
			 
}

void printsquare(int i, int j)
{
	char s[20]; 
	
		switch(j)
		{
			case 0: 
			sprintf(s,"a");
			UART_putstring(s);
			rankprint(i);
			break; 
			
			case 1: 
			sprintf(s,"b");
			UART_putstring(s);
			rankprint(i);
			break;
			
			case 2: 
			sprintf(s,"c");
			UART_putstring(s);
			rankprint(i);
			break;
			
			case 3: 
			sprintf(s,"d");
			UART_putstring(s);
			rankprint(i);
			break;
			
			case 4: 
			sprintf(s,"e");
			UART_putstring(s);
			rankprint(i);
			break;
			
			case 5: 
			sprintf(s,"f");
			UART_putstring(s);
			rankprint(i);
			break;
			
			case 6: 
			sprintf(s,"g");
			UART_putstring(s);
			rankprint(i);
			break;
			
			case 7: 
			sprintf(s,"h");
			UART_putstring(s);
			rankprint(i);
			break;
			
		}
}