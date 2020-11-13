/*
 * ESP8266.c
 *
 * Created: 2020-07-08 오전 11:14:09
 *  Author: ghhan
 */ 
#include "Board.h"

char AT_RST[50] = "AT+RST\r\n";            //Wifi 초기화
char AT_CWMODE[50] = "AT+CWMODE=2\r\n";       //Wifi 설정 명령 (1 = Station Mode, 2 = AP Mode, 3 = AP + Station Mode)
char AT_CWSAP[50] = "AT+CWSAP=\"SDA_6GNet\",\"123456789\",5,3\r\n";    //AP 모드 사용시 ssid, password, 채널, 보안방식을 설정
char AT_CWJAP[50] = "AT+CWJAP=\"SDA_RND\",\"sdarnd4500\"\r\n";      //AP 접속 명령 ("ssid", "password")
char AT_CIFSR[50] = "AT+CIFSR\r\n";			//모듈 IP 확인
char AT_CIPMUX[50] = "AT+CIPMUX=1\r\n";		//다중 접속 설정
char AT_CIPSTART[100] = "AT+CIPSTART=4,\"UDP\",\"192.168.0.00\",8002,8001,0\r\n";		//TCP 또는 UDP 포트 설정/연결
char AT_CIPSERVER[50] = "AT+CIPSERVER=1,10001\r\n";		//서버 설정
char AT_CIPSTATUS[50] = "AT+CIPSTATUS\r\n";			//정보 불러오기
char AT_CIPMODE[50] = "AT+CIPMODE=1\r\n";				//Transmission Mode 설정
char AT_CIPSEND[50] = "AT+CIPSEND=0,60\r\n";					//Receive 메세지 자동 Transmission
char AT_UARTDEF[50] = "AT+UART_DEF=115200,8,1,0,0\r\n";       //UART 재설정

void ESP8266_Init()	
{
	printString_usart1(AT_RST);
	_delay_ms(1000);
	printString_usart1(AT_CWMODE);
	_delay_ms(1000);
	printString_usart1(AT_CWSAP);
	_delay_ms(10000);
	printString_usart1(AT_CIFSR);
	_delay_ms(1000);
	printString_usart1(AT_CIPMUX);
	_delay_ms(1000);
	printString_usart1(AT_CIPSTART);
	_delay_ms(1000);
}

//void ESP8266_Init_Test()
//{
	//printString_usart1("AT+RST\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CWMODE=1\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CWJAP=\"SDA_RND\",\"sdarnd4500\"\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CIFSR\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CIPMUX=0\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CIPSTART=\"UDP\",\"192.168.0.46\",8002,8001,0\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CIPMODE=1\r\n");
	//while(Pass_flag){Pass_flag=0;}
	//printString_usart1("AT+CIPSEND\r\n");
	//while(Pass_flag){Pass_flag=0;}
//
	//UCSR0B=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
//}