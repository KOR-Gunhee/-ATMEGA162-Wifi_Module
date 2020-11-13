/*
 * Uart.h
 *
 * Created: 2020-07-07 오전 10:52:35
 *  Author: ghhan
 */ 


#ifndef UART_H_
#define UART_H_

void usart_Init();
void transmitByte_usart0(unsigned char ch);
void transmitByte_usart1(unsigned char ch);
uint8_t receiveByte_usart0();
uint8_t receiveByte_usart1();
int printString_usart0(char *str);
int printString_usart1(char *str);
void readString_usart0(char str[], uint8_t maxLength);
void readString_usart1(char str[], uint8_t maxLength);


#endif /* UART_H_ */