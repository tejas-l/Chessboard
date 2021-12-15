/*
 * UART.h
 *
 * Created: 21-10-2021 17:41:55
 *  Author: lalit
 */ 


#ifndef UART_H_
#define UART_H_





void UART_init(int prescale);

void UART_send( unsigned char data);

void UART_putstring(char* StringPtr);



#endif /* UART_H_ */