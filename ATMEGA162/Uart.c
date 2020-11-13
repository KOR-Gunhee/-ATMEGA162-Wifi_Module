/*
 * Uart.c
 *
 * Created: 2020-07-07 오전 10:52:44
 *  Author: ghhan
 */ 

#include "Board.h"

#define MY_CPU 16000000UL

#define USART_BAUDRATE 115200
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void usart_Init()
{
	//3. UBRR0은 16비트 레지스터이기 때문에 8비트씩 나누어서 넣어야 한다.
// 	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
// 	UBRR0L = (uint8_t) UBRR_VALUE;
// 	UBRR1H = (uint8_t)(UBRR_VALUE>>8);
// 	UBRR1L = (uint8_t) UBRR_VALUE;

	UBRR0H = 0;
	UBRR0L = 8;
	UBRR1H = 0;
	UBRR1L = 8;

	//5. 송수신을 가능하게 한다.
	UCSR0B=(1<<RXEN0)|(1<<TXEN0)|(0<<RXCIE0);
	UCSR1B=(1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
}

void transmitByte_usart0(unsigned char ch)
{
	//이전 전송이 끝나기를 기다림
	while(!(UCSR0A&(1<<UDRE0))){};
	
	UDR0 = ch;                                            /* send data */
}

void transmitByte_usart1(unsigned char ch)
{
	//이전 전송이 끝나기를 기다림
	while(!(UCSR1A&(1<<UDRE1))){};
	
	UDR1 = ch;                                            /* send data */
}

uint8_t receiveByte_usart0() {
	// 수신 되기를 기다림
	while(!(UCSR0A&(1<<RXC0))){};
	return UDR0;                                /* return register value */
}

uint8_t receiveByte_usart1() {
	// 수신 되기를 기다림
	while(!(UCSR1A&(1<<RXC1))){};
	return UDR1;                                /* return register value */
}

int printString_usart0(char *str)
{
	while (*str!= 0x00) {
		transmitByte_usart0(*str);
		str++;
	}
	return 0;
}

int printString_usart1(char *str)
{
	while (*str!= 0x00) {
		transmitByte_usart1(*str);
		str++;
	}
	return 0;
}

void readString_usart0(char str[], uint8_t maxLength) {
	char response;
	uint8_t i;
	i = 0;
	while (i < (maxLength - 1)) {                   /* prevent over-runs */
		response = receiveByte_usart0();
		transmitByte_usart0(response);                                    /* echo */
		if (response == '\r') {                     /* enter marks the end */
			break;
		}
		else {
			str[i] = response;                       /* add in a letter */
			i++;
		}
	}
	str[i] = 0;                          /* terminal NULL character */
}

void readString_usart1(char str[], uint8_t maxLength) {
	char response;
	uint8_t i;
	i = 0;
	while (i < (maxLength - 1)) {                   /* prevent over-runs */
		response = receiveByte_usart1();
		transmitByte_usart1(response);                                    /* echo */
		if (response == '\r') {                     /* enter marks the end */
			break;
		}
		else {
			str[i] = response;                       /* add in a letter */
			i++;
		}
	}

	str[i] = 0;                          /* terminal NULL character */
}