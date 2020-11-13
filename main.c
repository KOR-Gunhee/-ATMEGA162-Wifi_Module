/*
 * Atmega162.c
 *
 * Created: 2020-06-25 오후 2:39:39
 * Author : ghhan
 */ 

#include "main.h"

char *ptr;
char AT_LENGH[70]="";
char F_IP[30]="AT+CIPSTART=\"UDP\",\"";
char B_IP[30]="\",8002,8001,0\r\n";

void IPsave_wifi(char *msg)
{
	LCD_wBCommand(0x01);

	ptr = strtok(msg, "\"");
	ptr = strtok(NULL, "\"");
	LCD_wBCommand(0x80 | 0x00);  // DDRAM Address = 0x00 설정
	LCD_wString("IP:"); // WESNET 문자열 출력
	LCD_wString(ptr); // WESNET 문자열 출력
	LCD_wBCommand(0x80 | 0x40);  // DDRAM Address = 0x40 설정
	LCD_wString("LI:8001,TI:8002"); // WESNET 문자열 출력
}

void IP_Change(char *msg)
{
	char *qtr=0;

	LCD_wBCommand(0x01);		//Clear Dislay
	LCD_wBCommand(0x80 | 0x00);  // DDRAM Address = 0 설정
	LCD_wString("WIFI MODULE");     // 텍스트 LCD 문자열 출력
	LCD_wBCommand(0x80 | 0x40);  // DDRAM Address = 0x40 설정
	LCD_wString("RESETTING..."); // WESNET 문자열 출력

	qtr = strtok(msg, ":");
	qtr = strtok(NULL, ":");
	qtr = strtok(NULL, "\n");

	printString_usart1("AT+RST\r\n");
	_delay_ms(1000);
	printString_usart1("AT+CWMODE=2\r\n");
	_delay_ms(1000);
	printString_usart1("AT+CWSAP=\"SDA_6GNet\",\"123456789\",5,3\r\n");
	_delay_ms(10000);
	printString_usart1("AT+CIFSR\r\n");
	_delay_ms(1000);
	printString_usart1("AT+CIPMUX=0\r\n");
	_delay_ms(1000);
//	printString_usart1("AT+CIPSTART=\"UDP\",\"192.168.0.43\",8002,8001,0\r\n");
	printString_usart1("AT+CIPSTART=\"UDP\",\"");
	_delay_ms(10);
	printString_usart1(qtr);
	_delay_ms(10);
	printString_usart1("\",8002,8001,0\r\n");
	_delay_ms(1000);
	printString_usart1("AT+CIPMODE=1\r\n");
	_delay_ms(1000);
	printString_usart1("AT+CIPSEND\r\n");
	_delay_ms(1000);

	PORTD=0x4;			//Switch IC PD2 Enable
	UDP_mode=1;

	LCD_wBCommand(0x01);		//Clear Dislay
	LCD_wBCommand(0x80 | 0x00);  // DDRAM Address = 0x00 설정
	LCD_wString("TP:"); // WESNET 문자열 출력
	LCD_wString(qtr); // WESNET 문자열 출력
	LCD_wBCommand(0x80 | 0x40);  // DDRAM Address = 0x40 설정
	LCD_wString("LI:8001,TI:8002"); // WESNET 문자열 출력
}

void Init_Wifi(char *msg)
{
	LCD_wBCommand(0x01);		//Clear Dislay

	LCD_wBCommand(0x80 | 0x00);  // DDRAM Address = 0 설정
	LCD_wString("WIFI MODULE");     // 텍스트 LCD 문자열 출력
	LCD_wBCommand(0x80 | 0x40);  // DDRAM Address = 0x40 설정
	LCD_wString("RESETTING..."); // WESNET 문자열 출력

	printString_usart1("+++");
	_delay_ms(5000);
	printString_usart1("AT+CIPMODE=0\r\n");
	_delay_ms(1000);
	printString_usart1("AT+CIPCLOSE\r\n");
	_delay_ms(1000);

	ESP8266_Init();
}

void CMD_Transmit(char *msg)
{
	ptr = strtok(msg, ":");
	ptr = strtok(NULL, "\n");

	strcat(ptr, "\n\r");

	printString_usart0(ptr);
}

void Sel_mode(uint8_t num)
{
	switch(num){
		case IPSAVE_mode:
		IPsave_wifi(&str_ip);
		break;
		case IPCHANGE_mode:
		IP_Change(&str_chip);
		break;
		case INIT_mode:
		Init_Wifi(&str_us1);
		break;
		case CMD_mode:
		CMD_Transmit(&str_us1);
		default:
		break;
	}

	mode_flag=0;
}
void Board_Init()
{
	mode_flag=0;
	UDP_mode=0;

	DDRD=0x0C;			//Switch IC PD2/PD3 Output Enable
	PORTD=0x08;			//Switch IC PD3 Enable

	usart_Init();
	sei();
	LCD_Init();         // 텍스트 LCD 초기화 - 함수 호출
	ESP8266_Init();

//	printString_usart1("AT+UART_DEF=115200,8,1,0,0\r\n");
}

int main(void)
{
    /* Replace with your application code */
	Board_Init();	

    while (1) 
    {
		Sel_mode(mode_flag);	
	}
}

