/*
 * LCD1602.c
 *
 * Created: 2020-07-07 오후 12:01:53
 *  Author: ghhan
 */ 

#include "Board.h"

#define sbi(x, y) (x |= (1 << y))  // x의 y 비트를 설정(1)
#define cbi(x, y) (x &= ~(1 << y)) // x의 y 비트를 클리어(0)

// CON 포트는 포트 C와 연결됨을 정의
#define LCD_CON      PORTA
// DATA 포트는 포트 A와 연결됨을 정의
#define LCD_DATA     PORTC
// DATA 포트의 출력 방향 설정 매크로를 정의
#define LCD_DATA_DIR DDRC
// DATA 포트의 입력 방향 설정 매크로를 정의
#define LCD_DATA_IN  PINC
// RS 신호의 비트 번호 정의
#define LCD_RS   0
// RW 신호의 비트 번호 정의
#define LCD_RW   1
// E 신호의 비트 번호 정의
#define LCD_E    2

// 텍스트 LCD로 부터 상태(명령)를 읽는 함수
unsigned char LCD_rCommand(void){
	unsigned char temp=1;
	 
	LCD_DATA_DIR = 0X00;
	 
	cbi(LCD_CON, LCD_RS); // 0번 비트 클리어, RS = 0, 명령
	sbi(LCD_CON, LCD_RW); // 1번 비트 설정, RW = 1, 읽기
	sbi(LCD_CON, LCD_E);  // 2번 비트 설정, E = 1
	_delay_us(1);
	 
	temp = LCD_DATA_IN;      // 명령 읽기
	_delay_us(1);
	 
	cbi(LCD_CON, LCD_E);  // 명령 읽기 동작 끝
	 
	LCD_DATA_DIR = 0XFF;
	_delay_us(1);
	 
	return temp;
}

// 텍스트 LCD의 비지 플래그 상태를 확인하는 함수
char LCD_BusyCheck(unsigned char temp){
	if(temp & 0x80)          return 1;
	else            return 0;
}

// 텍스트 LCD에 명령을 출력하는 함수 - 단, 비지플래그 체크하지 않음
void LCD_wCommand(char cmd){
	cbi(LCD_CON, LCD_RS); // 0번 비트 클리어, RS = 0, 명령
	cbi(LCD_CON, LCD_RW); // 1번 비트 클리어, RW = 0, 쓰기
	sbi(LCD_CON, LCD_E);  // 2번 비트 설정, E = 1
	 
	LCD_DATA = cmd;          // 명령 출력
	_delay_us(1);
	cbi(LCD_CON, LCD_E);  // 명령 쓰기 동작 끝
	 
	_delay_us(1);
}

// 텍스트 LCD에 명령을 출력하는 함수 - 단, 비지플래그 체크함
void LCD_wBCommand(char cmd){
	while(LCD_BusyCheck(LCD_rCommand()))
	_delay_us(1);
	cbi(LCD_CON, LCD_RS); // 0번 비트 클리어, RS = 0, 명령
	cbi(LCD_CON, LCD_RW); // 1번 비트 클리어, RW = 0, 쓰기
	sbi(LCD_CON, LCD_E);  // 2번 비트 설정, E = 1
	 
	LCD_DATA = cmd;          // 명령 출력
	_delay_us(1);
	cbi(LCD_CON, LCD_E);  // 명령 쓰기 동작 끝
	 
	_delay_us(1);
}

// 텍스트 LCD를 초기화하는 함수
void LCD_Init(void){

	// 포트 A의 방향 설정, 0 : 입력, 1 : 출력
	DDRA = 0xFF;
	
	// 포트 C의 방향 설정, 0 : 입력, 1 : 출력
	DDRC = 0xFF;

	_delay_ms(100);
	// 비지 플래그를 체크하지 않는 Function Set
	LCD_wCommand(0x38);
	_delay_ms(10);
	// 비지 플래그를 체크하지 않는 Function Set
	LCD_wCommand(0x38);
	_delay_us(200);
	// 비지 플래그를 체크하지 않는 Function Set
	LCD_wCommand(0x38);
	_delay_us(200);
	 
	// 비지 플래그를 체크하는 Function Set
	LCD_wBCommand(0x38);
	// 비지 플래그를 체크하는 Display On/Off Control
	LCD_wBCommand(0x0c);
	// 비지 플래그를 체크하는 Clear Display
	LCD_wBCommand(0x01);

	LCD_wBCommand(0x80 | 0x00);  // DDRAM Address = 0 설정
	LCD_wString("WIFI MODULE");     // 텍스트 LCD 문자열 출력
	LCD_wBCommand(0x80 | 0x40);  // DDRAM Address = 0x40 설정
	LCD_wString("LOADING..."); // WESNET 문자열 출력
}

// 텍스트 LCD에 1바이트 데이터를 출력하는 함수
void LCD_wData(unsigned char dat){
	while(LCD_BusyCheck(LCD_rCommand()))
	_delay_us(1);
	 
	sbi(LCD_CON, LCD_RS); // 0번 비트 설정, RS = 1, 데이터
	cbi(LCD_CON, LCD_RW); // 1번 비트 클리어, RW = 0, 쓰기
	sbi(LCD_CON, LCD_E); // 2번 비트 설정, E = 1
	 
	LCD_DATA = dat;       // 데이터 출력
	_delay_us(1);
	cbi(LCD_CON, LCD_E);  // 데이터 쓰기 동작 끝
	 
	_delay_us(1);
}

// 텍스트 LCD에 문자열을 출력하는 함수
int LCD_wString(char *str)
{
	while (*str!= 0x00) {
		LCD_wData(*str);
		str++;
	}
	return 0;
}
